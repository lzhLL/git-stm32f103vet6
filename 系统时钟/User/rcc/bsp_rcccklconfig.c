#include "bsp_rccclkconfig.h"


void HSE_SetSysClk(uint32_t RCC_PLLMul_x) {
	ErrorStatus HSEStatus;
	
	// ��RCC �Ĵ�����λ�ɸ�λֵ
	RCC_DeInit();		
	
	//1��ʹ��HSE
	RCC_HSEConfig(RCC_HSE_ON);
	
	//2���ȴ�HSE����
	HSEStatus = RCC_WaitForHSEStartUp();
	if(SUCCESS == HSEStatus) {
		/* ʹ��Ԥȡָ */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);
		
		/* HCLK = SYSCLK = 72M */
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		/* PCLK1 = HCLK/2 = 36M*/
		RCC_PCLK1Config(RCC_SYSCLK_Div2);
		/* PCLK2 = HCLK = 72M */
		RCC_PCLK2Config(RCC_SYSCLK_Div1);
		
		/*  ���໷����: PLLCLK = HSE * 9 = 72 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		
		// ʹ��PLL
		RCC_PLLCmd(ENABLE);
		
		/* �ȴ�PLL�ȶ� */
		while(RESET == RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
		
		/* ѡ��PLLCLK��Ϊϵͳʱ��*/
		RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK);
		
		/* �ȴ�PLLCLK�л�Ϊϵͳʱ�� */
		while( RCC_GetSYSCLKSource() != 0x08 );
	} else {
	
	}



}

void MCO_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
}

///**
//  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
//  *         and PCLK1 prescalers. 
//  * @note   This function should be used only after reset.
//  * @param  None
//  * @retval None
//  */
//static void SetSysClockTo72(void)
//{
//  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
//  
//  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
//  /* ʹ��HSE */    
//  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
// 
//  /* �ȴ�HSE����������ʱ����  */
//  do
//  {
//    HSEStatus = RCC->CR & RCC_CR_HSERDY;
//    StartUpCounter++;  
//  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

//  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
//  {
//    HSEStatus = (uint32_t)0x01;
//  }
//  else
//  {
//    HSEStatus = (uint32_t)0x00;
//  }  

////���HSE�����ɹ�������������ִ��
//  if (HSEStatus == (uint32_t)0x01)
//  {
//    /* ʹ��Ԥȡָ */
//    FLASH->ACR |= FLASH_ACR_PRFTBE;

//    /* Flash 2 wait state */
//    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
//    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

// 
//    /* HCLK = SYSCLK = 72M */
//    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
//      
//    /* PCLK2 = HCLK = 72M */
//    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
//    
//    /* PCLK1 = HCLK = 36M */
//    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
//    
//   
//    /* ���໷����: PLLCLK = PREDIV1 * 9 = 72 MHz */ 
//    RCC->CFGR &= (uint32_t)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
//    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 | 
//                            RCC_CFGR_PLLMULL9); 
//#else    
//    /*  ���໷����: PLLCLK = HSE * 9 = 72 MHz */
//    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
//                                        RCC_CFGR_PLLMULL));
//    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
//#endif /* STM32F10X_CL */

//    /* ʹ�� PLL */
//    RCC->CR |= RCC_CR_PLLON;

//    /* �ȴ�PLL�ȶ� */
//    while((RCC->CR & RCC_CR_PLLRDY) == 0)
//    {
//    }
//    
//    /* ѡ��PLLCLK��Ϊϵͳʱ�� */
//    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
//    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

//    /* �ȴ�PLLCLK�л�Ϊϵͳʱ�� */
//    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
//    {
//    }
//  }
//  else
//  { /* If HSE fails to start-up, the application will have wrong clock 
//         configuration. User can add here some code to deal with this error */
//  }
//}
//#endif

