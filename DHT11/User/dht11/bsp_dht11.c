#include "bsp_dht11.h"
#include "bsp_usart.h"

/* static�������� */
static void DHT11_GPIO_Config(void);
static void DHT11_Mode_Out_PP(void);
static void DHT11_Mode_IPU(void);
static uint8_t DHT11_ReadByte(void);

void DHT11_Init(void) {
	DHT11_GPIO_Config();	//���ģʽ

	DHT11_Dout_1;	// һ��ʼ����PE6

	return ;
}

/* ����DHT11��I/O�� Ϊͨ���������ģʽ */
static void DHT11_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	// �򿪴���GPIO��ʱ��
	DHT11_Dout_SCK_APBxClkCmd(DHT11_Dout_GPIO_CLK, ENABLE);

	/*ѡ��Ҫ���Ƶ�DHT11_Dout_GPIO_PORT����*/	
	GPIO_InitStructure.GPIO_Pin = DHT11_Dout_GPIO_PIN;
	
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* ��ʼ��GPIOE */
	GPIO_Init(DHT11_Dout_GPIO_PORT, &GPIO_InitStructure);
  
	return ;
}

static void DHT11_Mode_Out_PP(void) {
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*ѡ��Ҫ���Ƶ�DHT11_Dout_GPIO_PORT����*/															   
  	GPIO_InitStructure.GPIO_Pin = DHT11_Dout_GPIO_PIN;	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*���ÿ⺯������ʼ��DHT11_Dout_GPIO_PORT*/
  	GPIO_Init(DHT11_Dout_GPIO_PORT, &GPIO_InitStructure);	 	 
	
}

/* ����DHT11��I/O�� Ϊ��������ģʽ */
static void DHT11_Mode_IPU(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	// �򿪴���GPIO��ʱ��
	DHT11_Dout_SCK_APBxClkCmd(DHT11_Dout_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = DHT11_Dout_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;					// ��DHT11��GPIO����Ϊ��������ģʽ
	
	/* ��ʼ��GPIOE */
	GPIO_Init(DHT11_Dout_GPIO_PORT, &GPIO_InitStructure);
  
	return ;
}




/* ��DHT11��ȡһ���ֽڣ���λ���� */
static uint8_t DHT11_ReadByte(void) {
	uint8_t i, dht11_onebyte_data = 0;

	/* ѭ��8�ζ�ȡһ���ֽڵ����� */
	for(i = 0; i < 8; i++) {
		//ÿ1bit����Ҫ��ʱ50us���ܿ�ʼ��
		while( 0 == DHT11_Dout_IN() );

		//26~28usΪ0��70usΪ1��ȡ50us��ʱ���ȡ��ƽ
		DHT11_DELAY_US(50);
		
		if( 1 == DHT11_Dout_IN() ) {		//���Ϊ�ߵ�ƽ
			dht11_onebyte_data |= (uint8_t)(1 << 0);		//��1 
			while( 1 == DHT11_Dout_IN() );		
		} else {
			dht11_onebyte_data &= (uint8_t)~(1 << 0);	//��0   
			
		}
		
		if(i == 7) {
			break;
		}
		//ÿ����һ��bit��dht11_onebyte_data����һλ
		dht11_onebyte_data = dht11_onebyte_data << 1;
		
	}

	return dht11_onebyte_data;
}





/* ��ȡ��ʪ��40bits������ */
uint8_t DHT11_Read_TempAndHumidity(DHT11_Data_TypeDef* DHT11_Data) {
	//���߿���״̬Ϊ�ߵ�ƽ
	DHT11_Mode_Out_PP();
	//DHT11_Dout_1;
	
	//������ʼ������ʼ�źţ����ͣ�
	DHT11_Dout_0;
	
	//����������ʱ18ms
	DHT11_DELAY_MS(18);
	
	//��������20~40us
	DHT11_Dout_1;
	DHT11_DELAY_US(30);

	/*������Ϊ����ģʽ �ȴ�DHT11������Ӧ�ź�*/ 
	DHT11_Mode_IPU();
	
	//���DHT11������Ӧ�ź�(�͵�ƽ�ź�)
	if( 0 == DHT11_Dout_IN() ) {
		//�ȴ�DHT11����Ӧ�ź�(80us)�����������󣬽��ᷢ���ߵ�ƽ
		while(DHT11_Dout_IN() == 0);
		
		//�ȴ�DHT11����80us����
		while(DHT11_Dout_IN() == 1);
		
		//��ʼ������ 
		DHT11_Data->humi_int = DHT11_ReadByte();
		DHT11_Data->humi_deci = DHT11_ReadByte();
		DHT11_Data->temp_int = DHT11_ReadByte();
		DHT11_Data->temp_deci = DHT11_ReadByte();
		DHT11_Data->check_sum = DHT11_ReadByte();
	} 
	
	//���ݴ��ͽ���ʱ���ӻ�����50us
	DHT11_DELAY_US(50);

	//GPIO�������ģʽ�������ߵ�ƽ���ͷ�����
	DHT11_GPIO_Config();
	DHT11_Dout_1;
	
	/*����ȡ�������Ƿ���ȷ*/
	if(DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int+ DHT11_Data->temp_deci) {
		return SUCCESS;	//�ɹ���ȡ��ʪ�������򷵻�0
	} else {
		printf("��ȡ��ʪ�����ݲ���ȷ������\n");
		return ERROR;	//��ȡʧ��
	}
	
	
} 

/*************************************END OF FILE******************************/
