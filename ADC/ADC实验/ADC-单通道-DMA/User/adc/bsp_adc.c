#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue;

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
	ADC_InitTypeDef  	ADC_InitStruct;
	DMA_InitTypeDef		DMA_InitStruct;

		//typedef struct
//{
//  uint32_t DMA_PeripheralBaseAddr;   // 外设地址
//  uint32_t DMA_MemoryBaseAddr;       // 存储器地址
//  uint32_t DMA_DIR;                  // 传输方向
//  uint32_t DMA_BufferSize;           // 传输数目
//  uint32_t DMA_PeripheralInc;        // 外设地址增量模式
//  uint32_t DMA_MemoryInc;            // 存储器地址增量模式
//  uint32_t DMA_PeripheralDataSize;   // 外设数据宽度
//  uint32_t DMA_MemoryDataSize;       // 存储器数据宽度
//  uint32_t DMA_Mode;                 // 模式选择
//  uint32_t DMA_Priority;             // 通道优先级
//  uint32_t DMA_M2M;                  // 存储器到存储器模式
//}DMA_InitTypeDef;
	
	
	
	// 打开ADC外设的时钟
	ADC_APBxClock_FUN(ADC_CLK, ENABLE);
	
	//开DMA的时钟，看原理图，发现DMA挂载在AHB总线
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);

	// 配置DMA1的工作参数(ADC数据寄存器往SDRAM传数据)
	DMA_DeInit(ADC_DMA_CHANNEL);
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)( & (ADC_x->DR));//外设地址是ADC1_DR寄存器地址
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)( & (ADC_ConvertedValue) );//存储器基地址是变量的地址
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;	//外设是ADC,属于数据源
	DMA_InitStruct.DMA_BufferSize = 1;	//只有一个通道，变量也只有一个
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址不用增长
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;//存储器地址不用增长
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设ADC1的数据是2个字节的宽度
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//存储器数据宽度为16位
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;//只要DR寄存器有数据，就不断传送给变量
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;//DMA优先级
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;//M TO M模式不使用
	
	//完成DMA的初始化配置
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStruct);
	
	//使能DMA（让DMA能用）
	DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);
/* ---------------------------------------------------------------------------- */
	
	// 配置ADC的工作参数
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//连续转换
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right ;//数据右对齐
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitStruct.ADC_NbrOfChannel = 1;//通道数目
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//单通道


	// 完成ADC的初始化配置
	ADC_Init(ADC_x, &ADC_InitStruct);
	
	//配置ADC时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//配置通道的转换顺序
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	
	// 使能ADC
	ADC_Cmd(ADC_x, ENABLE);
	
	//使能ADC_DMA
	ADC_DMACmd(ADC_x, ENABLE);
	
	//ADC开始校准
	ADC_StartCalibration(ADC_x);
	
	//等待校准完成
	while( ADC_GetCalibrationStatus(ADC_x) );
	
	//软件触发ADC
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}




void ADCx_Init(void) {
	
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




