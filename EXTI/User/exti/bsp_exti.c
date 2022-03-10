#include "bsp_exti.h"

//static关键字声明的作用是只能被EXIT_Key_Config(void)函数所用，其他函数是用不了的
static void EXTI_NVIC_Config(void) {	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//配置中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStruct);
	

	//配置中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStruct);
}


//使能中断请求:key1外部中断初始化函数
void EXIT_Key_Config(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	//配置中断优先级
	EXTI_NVIC_Config();
	
/* 初始化GPIOA */
		//打开APB2时钟
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLOCK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入，GPIO电平由外部决定
	
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStruct);
	
	
/* 初始化GPIOC */
		//打开APB2时钟
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLOCK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入，GPIO电平由外部决定
	
	GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStruct);	
	
	
	
	//初始化EXTI(选输入线)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);					//打开AFIO寄存器的时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);		//选择作为EXTI Line的GPIO脚。
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;		//对应PA0的引脚
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	//中断
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	//触发选择：上升沿
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);
	
	
	//初始化EXTI(选输入线)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);					//打开AFIO寄存器的时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);		//选择作为EXTI Line的GPIO脚。
	
	EXTI_InitStruct.EXTI_Line = EXTI_Line13;		//对应PA0的引脚
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	//中断
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	//触发选择：上升沿
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	EXTI_Init(&EXTI_InitStruct);

}
