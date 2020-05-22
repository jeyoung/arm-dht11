extern unsigned long _estack;
extern unsigned long _sidata;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;

extern int main(void);

__attribute__((naked)) void Reset_Handler()
{
    unsigned long *source = &_sidata;
    unsigned long *destination = &_sdata;

    while (destination < &_edata)
    {
        *destination++ = *source++;
    }

    destination = &_sbss;
    while (destination < &_ebss)
    {
        *destination++ = 0;
    }

    main();
}

void default_handler(void)
{
    while (1);
}

void NMI_Handler(void) __attribute__((weak, alias("default_handler")));
void HardFault_Handler(void) __attribute__((weak, alias("default_handler")));
void MemManage_Handler(void) __attribute__((weak, alias("default_handler")));
void BusFault_Handler(void) __attribute__((weak, alias("default_handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("default_handler")));
void SVCall_Handler(void) __attribute__((weak, alias("default_handler")));
void DebugMonitor_Handler(void) __attribute__((weak, alias("default_handler")));
void PendSV_Handler(void) __attribute__((weak, alias("default_handler")));
void Systick_Handler(void) __attribute__((weak, alias("default_handler")));
void WWDG_Handler(void) __attribute__((weak, alias("default_handler")));
void PVD_Handler(void) __attribute__((weak, alias("default_handler")));
void TAMP_STAMP_Handler(void) __attribute__((weak, alias("default_handler")));
void RTC_WKUP_Handler(void) __attribute__((weak, alias("default_handler")));
void FLASH_Handler(void) __attribute__((weak, alias("default_handler")));
void RCC_Handler(void) __attribute__((weak, alias("default_handler")));
void EXTI0_Handler(void) __attribute__((weak, alias("default_handler")));
void EXTI1_Handler(void) __attribute__((weak, alias("default_handler")));
void EXTI2_Handler(void) __attribute__((weak, alias("default_handler")));
void EXTI3_Handler(void) __attribute__((weak, alias("default_handler")));
void EXTI4_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream0_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream1_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream2_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream3_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream4_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream5_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream6_Handler(void) __attribute__((weak, alias("default_handler")));
void ADC_Handler(void) __attribute__((weak, alias("default_handler")));
void CAN1_TX_Handler(void) __attribute__((weak, alias("default_handler")));
void CAN1_RX0_Handler(void) __attribute__((weak, alias("default_handler")));
void CAN1_RX1_Handler(void) __attribute__((weak, alias("default_handler")));
void CAN1_SCE_Handler(void) __attribute__((weak, alias("default_handler")));
void EXTI9_5_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM1_BRK_TIM9_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM1_UP_TIM10_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM1_TRIG_COM_TIM11_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM1_CC_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM2_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM3_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM4_Handler(void) __attribute__((weak, alias("default_handler")));
void I2C1_EV_Handler(void) __attribute__((weak, alias("default_handler")));
void I2C1_ER_Handler(void) __attribute__((weak, alias("default_handler")));
void I2C2_EV_Handler(void) __attribute__((weak, alias("default_handler")));
void I2C2_ER_Handler(void) __attribute__((weak, alias("default_handler")));
void SPI1_Handler(void) __attribute__((weak, alias("default_handler")));
void SPI2_Handler(void) __attribute__((weak, alias("default_handler")));
void USART1_Handler(void) __attribute__((weak, alias("default_handler")));
void USART2_Handler(void) __attribute__((weak, alias("default_handler")));
void USART3_Handler(void) __attribute__((weak, alias("default_handler")));
void EXTI15_10_Handler(void) __attribute__((weak, alias("default_handler")));
void RTC_Alarm_Handler(void) __attribute__((weak, alias("default_handler")));
void OTG_FS_WKUP_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM8_BRK_TIM12_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM8_UP_TIM13_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM8_TRIG_COM_TIM14_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM8_CC_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA1_Stream7_Handler(void) __attribute__((weak, alias("default_handler")));
void FMC_Handler(void) __attribute__((weak, alias("default_handler")));
void SDIO_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM5_Handler(void) __attribute__((weak, alias("default_handler")));
void SPI3_Handler(void) __attribute__((weak, alias("default_handler")));
void UART4_Handler(void) __attribute__((weak, alias("default_handler")));
void UART5_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM6_DAC_Handler(void) __attribute__((weak, alias("default_handler")));
void TIM7_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream0_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream1_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream2_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream3_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream4_Handler(void) __attribute__((weak, alias("default_handler")));
void CAN2_TX_Handler(void) __attribute__((weak, alias("default_handler")));
void CAN2_RX0_Handler(void) __attribute__((weak, alias("default_handler")));
void CAN2_RX1_Handler(void) __attribute__((weak, alias("default_handler")));
void CAN2_SCE_Handler(void) __attribute__((weak, alias("default_handler")));
void OTG_FS_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream5_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream6_Handler(void) __attribute__((weak, alias("default_handler")));
void DMA2_Stream7_Handler(void) __attribute__((weak, alias("default_handler")));
void USART6_Handler(void) __attribute__((weak, alias("default_handler")));
void I2C3_EV_Handler(void) __attribute__((weak, alias("default_handler")));
void I2C3_ER_Handler(void) __attribute__((weak, alias("default_handler")));
void OTG_HS_EP1_OUT_Handler(void) __attribute__((weak, alias("default_handler")));
void OTG_HS_EP1_IN_Handler(void) __attribute__((weak, alias("default_handler")));
void OTG_HS_WKUP_Handler(void) __attribute__((weak, alias("default_handler")));
void OTG_HS_Handler(void) __attribute__((weak, alias("default_handler")));
void DCMI_Handler(void) __attribute__((weak, alias("default_handler")));
void FPU_Handler(void) __attribute__((weak, alias("default_handler")));
void SPI4_Handler(void) __attribute__((weak, alias("default_handler")));
void SAI1_Handler(void) __attribute__((weak, alias("default_handler")));
void SAI2_Handler(void) __attribute__((weak, alias("default_handler")));
void QuadSPI_Handler(void) __attribute__((weak, alias("default_handler")));
void HDMI_CEC_Handler(void) __attribute__((weak, alias("default_handler")));
void SPDIF_RX_Handler(void) __attribute__((weak, alias("default_handler")));
void FMPI2C1_Handler(void) __attribute__((weak, alias("default_handler")));
void FMPI2C1_Error_Handler(void) __attribute__((weak, alias("default_handler")));

__attribute__((section(".vector")))
const unsigned long vector_table[] =
{
    (unsigned long)&_estack,
    (unsigned long)&Reset_Handler,
    (unsigned long)&NMI_Handler,
    (unsigned long)&HardFault_Handler,
    (unsigned long)&MemManage_Handler,
    (unsigned long)&BusFault_Handler,
    (unsigned long)&UsageFault_Handler,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)&SVCall_Handler,
    (unsigned long)&DebugMonitor_Handler,
    (unsigned long)0,
    (unsigned long)&PendSV_Handler,
    (unsigned long)&Systick_Handler,
    (unsigned long)&WWDG_Handler,
    (unsigned long)&PVD_Handler,
    (unsigned long)&TAMP_STAMP_Handler,
    (unsigned long)&RTC_WKUP_Handler,
    (unsigned long)&FLASH_Handler,
    (unsigned long)&RCC_Handler,
    (unsigned long)&EXTI0_Handler,
    (unsigned long)&EXTI1_Handler,
    (unsigned long)&EXTI2_Handler,
    (unsigned long)&EXTI3_Handler,
    (unsigned long)&EXTI4_Handler,
    (unsigned long)&DMA1_Stream0_Handler,
    (unsigned long)&DMA1_Stream1_Handler,
    (unsigned long)&DMA1_Stream2_Handler,
    (unsigned long)&DMA1_Stream3_Handler,
    (unsigned long)&DMA1_Stream4_Handler,
    (unsigned long)&DMA1_Stream5_Handler,
    (unsigned long)&DMA1_Stream6_Handler,
    (unsigned long)&ADC_Handler,
    (unsigned long)&CAN1_TX_Handler,
    (unsigned long)&CAN1_RX0_Handler,
    (unsigned long)&CAN1_RX1_Handler,
    (unsigned long)&CAN1_SCE_Handler,
    (unsigned long)&EXTI9_5_Handler,
    (unsigned long)&TIM1_BRK_TIM9_Handler,
    (unsigned long)&TIM1_UP_TIM10_Handler,
    (unsigned long)&TIM1_TRIG_COM_TIM11_Handler,
    (unsigned long)&TIM1_CC_Handler,
    (unsigned long)&TIM2_Handler,
    (unsigned long)&TIM3_Handler,
    (unsigned long)&TIM4_Handler,
    (unsigned long)&I2C1_EV_Handler,
    (unsigned long)&I2C1_ER_Handler,
    (unsigned long)&I2C2_EV_Handler,
    (unsigned long)&I2C2_ER_Handler,
    (unsigned long)&SPI1_Handler,
    (unsigned long)&SPI2_Handler,
    (unsigned long)&USART1_Handler,
    (unsigned long)&USART2_Handler,
    (unsigned long)&USART3_Handler,
    (unsigned long)&EXTI15_10_Handler,
    (unsigned long)&RTC_Alarm_Handler,
    (unsigned long)&OTG_FS_WKUP_Handler,
    (unsigned long)&TIM8_BRK_TIM12_Handler,
    (unsigned long)&TIM8_UP_TIM13_Handler,
    (unsigned long)&TIM8_TRIG_COM_TIM14_Handler,
    (unsigned long)&TIM8_CC_Handler,
    (unsigned long)&DMA1_Stream7_Handler,
    (unsigned long)&FMC_Handler,
    (unsigned long)&SDIO_Handler,
    (unsigned long)&TIM5_Handler,
    (unsigned long)&SPI3_Handler,
    (unsigned long)&UART4_Handler,
    (unsigned long)&UART5_Handler,
    (unsigned long)&TIM6_DAC_Handler,
    (unsigned long)&TIM7_Handler,
    (unsigned long)&DMA2_Stream0_Handler,
    (unsigned long)&DMA2_Stream1_Handler,
    (unsigned long)&DMA2_Stream2_Handler,
    (unsigned long)&DMA2_Stream3_Handler,
    (unsigned long)&DMA2_Stream4_Handler,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)&CAN2_TX_Handler,
    (unsigned long)&CAN2_RX0_Handler,
    (unsigned long)&CAN2_RX1_Handler,
    (unsigned long)&CAN2_SCE_Handler,
    (unsigned long)&OTG_FS_Handler,
    (unsigned long)&DMA2_Stream5_Handler,
    (unsigned long)&DMA2_Stream6_Handler,
    (unsigned long)&DMA2_Stream7_Handler,
    (unsigned long)&USART6_Handler,
    (unsigned long)&I2C3_EV_Handler,
    (unsigned long)&I2C3_ER_Handler,
    (unsigned long)&OTG_HS_EP1_OUT_Handler,
    (unsigned long)&OTG_HS_EP1_IN_Handler,
    (unsigned long)&OTG_HS_WKUP_Handler,
    (unsigned long)&OTG_HS_Handler,
    (unsigned long)&DCMI_Handler,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)&FPU_Handler,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)&SPI4_Handler,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)&SAI1_Handler,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)0,
    (unsigned long)&SAI2_Handler,
    (unsigned long)&QuadSPI_Handler,
    (unsigned long)&HDMI_CEC_Handler,
    (unsigned long)&SPDIF_RX_Handler,
    (unsigned long)&FMPI2C1_Handler,
    (unsigned long)&FMPI2C1_Error_Handler
};
