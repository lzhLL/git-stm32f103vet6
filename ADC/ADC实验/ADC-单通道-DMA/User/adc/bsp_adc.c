#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue;

static void ADCx_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// ��ADC_GPIOB��ʱ��
	ADC_GPIO_APBxClock_FUN(ADC_GPIO_CLK, ENABLE);
	
	// ��ADC��GPIO����Ϊģ������ģʽ
	GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//����Ϊģ������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	//��ʼ��ADC_GPIO
	GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);	

}


static void ADCx_Mode_Config(void) {
	ADC_InitTypeDef  	ADC_InitStruct;
	DMA_InitTypeDef		DMA_InitStruct;

		//typedef struct
//{
//  uint32_t DMA_PeripheralBaseAddr;   // �����ַ
//  uint32_t DMA_MemoryBaseAddr;       // �洢����ַ
//  uint32_t DMA_DIR;                  // ���䷽��
//  uint32_t DMA_BufferSize;           // ������Ŀ
//  uint32_t DMA_PeripheralInc;        // �����ַ����ģʽ
//  uint32_t DMA_MemoryInc;            // �洢����ַ����ģʽ
//  uint32_t DMA_PeripheralDataSize;   // �������ݿ��
//  uint32_t DMA_MemoryDataSize;       // �洢�����ݿ��
//  uint32_t DMA_Mode;                 // ģʽѡ��
//  uint32_t DMA_Priority;             // ͨ�����ȼ�
//  uint32_t DMA_M2M;                  // �洢�����洢��ģʽ
//}DMA_InitTypeDef;
	
	
	
	// ��ADC�����ʱ��
	ADC_APBxClock_FUN(ADC_CLK, ENABLE);
	
	//��DMA��ʱ�ӣ���ԭ��ͼ������DMA������AHB����
	RCC_AHBPeriphClockCmd(ADC_DMA_CLK, ENABLE);

	// ����DMA1�Ĺ�������(ADC���ݼĴ�����SDRAM������)
	DMA_DeInit(ADC_DMA_CHANNEL);
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)( & (ADC_x->DR));//�����ַ��ADC1_DR�Ĵ�����ַ
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)( & (ADC_ConvertedValue) );//�洢������ַ�Ǳ����ĵ�ַ
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;	//������ADC,��������Դ
	DMA_InitStruct.DMA_BufferSize = 1;	//ֻ��һ��ͨ��������Ҳֻ��һ��
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ��������
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;//�洢����ַ��������
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//����ADC1��������2���ֽڵĿ��
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�洢�����ݿ��Ϊ16λ
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;//ֻҪDR�Ĵ��������ݣ��Ͳ��ϴ��͸�����
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;//DMA���ȼ�
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;//M TO Mģʽ��ʹ��
	
	//���DMA�ĳ�ʼ������
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStruct);
	
	//ʹ��DMA����DMA���ã�
	DMA_Cmd(ADC_DMA_CHANNEL, ENABLE);
/* ---------------------------------------------------------------------------- */
	
	// ����ADC�Ĺ�������
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//����ת��
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right ;//�����Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_InitStruct.ADC_NbrOfChannel = 1;//ͨ����Ŀ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//��ͨ��


	// ���ADC�ĳ�ʼ������
	ADC_Init(ADC_x, &ADC_InitStruct);
	
	//����ADCʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	//����ͨ����ת��˳��
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	
	// ʹ��ADC
	ADC_Cmd(ADC_x, ENABLE);
	
	//ʹ��ADC_DMA
	ADC_DMACmd(ADC_x, ENABLE);
	
	//ADC��ʼУ׼
	ADC_StartCalibration(ADC_x);
	
	//�ȴ�У׼���
	while( ADC_GetCalibrationStatus(ADC_x) );
	
	//�������ADC
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




