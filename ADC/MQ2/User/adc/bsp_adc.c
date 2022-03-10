#include "bsp_adc.h"

static void ADCx_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 打开ADC_GPIOB的时钟
	ADC_GPIO_APBxClock_FUN(ADC_GPIO_CLK, ENABLE);
	
	// 将ADC的GPIO配置为模拟输入模式
	GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//必须为模拟输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	//初始化ADC_GPIO
	GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);	

}


static void ADCx_Mode_Config(void) {
	ADC_InitTypeDef  ADC_InitStruct;
	
		// 打开ADC外设的时钟
	ADC_APBxClock_FUN(ADC_CLK, ENABLE);
	
	// 配置ADC的工作参数
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//连续转换
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right ;//右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//通道数目
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//单通道
	
	
	// 完成ADC的初始化配置
	ADC_Init(ADC_x, &ADC_InitStruct);

	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	
	ADC_ITConfig(ADC_x, ADC_IT_EOC, ENABLE);
	
	// 使能ADC
	ADC_Cmd(ADC_x, ENABLE);
	
	//ADC开始校准
	ADC_StartCalibration(ADC_x);
	
	//等待校准完成
	while( ADC_GetCalibrationStatus(ADC_x) );
	
	//软件触发ADC
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}


static void ADC_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置ADC为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

void ADCx_Init(void) {
	ADC_NVIC_Config();
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
	
}

uint16_t ADC_Trans(void) {
	uint32_t sum = 0;
	uint16_t adc_val = 0;
	uint8_t i = 0;
	for(i = 0; i < 50; i++) {
		sum += ADC_ConvertedValue;
	}
	adc_val = sum / 50;
	
	return adc_val;
}



