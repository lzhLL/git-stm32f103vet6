#include "bsp_adc.h"

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
	ADC_InitTypeDef  ADC_InitStruct;
	
		// ��ADC�����ʱ��
	ADC_APBxClock_FUN(ADC_CLK, ENABLE);
	
	// ����ADC�Ĺ�������
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;//����ת��
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right ;//�Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_InitStruct.ADC_NbrOfChannel = 1;//ͨ����Ŀ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;//��ͨ��
	
	
	// ���ADC�ĳ�ʼ������
	ADC_Init(ADC_x, &ADC_InitStruct);

	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	
	ADC_ITConfig(ADC_x, ADC_IT_EOC, ENABLE);
	
	// ʹ��ADC
	ADC_Cmd(ADC_x, ENABLE);
	
	//ADC��ʼУ׼
	ADC_StartCalibration(ADC_x);
	
	//�ȴ�У׼���
	while( ADC_GetCalibrationStatus(ADC_x) );
	
	//�������ADC
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}


static void ADC_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* ����ADCΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
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



