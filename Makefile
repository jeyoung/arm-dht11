CC=		arm-none-eabi-gcc
OBJCOPY=	arm-none-eabi-objcopy

PROJECT=	temp
OUTPUT=		$(PROJECT).elf
BINARY=		$(PROJECT).bin

DEPS=		startup.c dht11.c

FLAGS=		-g -Os -Wall -pedantic
FLAGS_ARCH=     -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian -mfpu=vfp

CFLAGS=		$(FLAGS) --std=c11 -ffunction-sections -fdata-sections
CFLAGS_ARCH=	$(CFLAGS) $(FLAGS_ARCH)

LDFLAGS=	$(FLAGS)
LDFLAGS_ARCH=	$(LDFLAGS) $(FLAGS_ARCH) -specs=nosys.specs -nostartfiles \
		-T st_nucleo_f4.ld


.PHONY: clean all
all: clean $(OUTPUT) $(PROJECT).o

clean:
	find -name '*.o' -exec rm {} +
	find -name '$(OUTPUT)' -exec rm {} +
	find -name '$(BINARY)' -exec rm {} +

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS_ARCH) -c $< $(DEPS)

$(OUTPUT): $(PROJECT).o $(DEPS:.c=.o)
	$(CC) $(LDFLAGS_ARCH) -o $@ $^

.PHONY: upload debug
upload: $(OUTPUT)
	$(OBJCOPY) -O binary $(OUTPUT) $(BINARY)
	openocd \
	    -f interface/stlink-v2-1.cfg \
	    -f board/st_nucleo_f4.cfg \
	    -c "program $(BINARY) erase verify reset exit 0x8000000"

debug: upload $(OUTPUT)
	openocd -f board/st_nucleo_f4.cfg -f interface/stlink-v2-1.cfg \
	    -c "gdb_port 3333" -c "telnet_port 4444"
