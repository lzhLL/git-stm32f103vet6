#include "bsp_dht11.h"
#include "bsp_usart.h"

/* static函数声明 */
static void DHT11_GPIO_Config(void);
static void DHT11_Mode_Out_PP(void);
static void DHT11_Mode_IPU(void);
static uint8_t DHT11_ReadByte(void);

void DHT11_Init(void) {
	DHT11_GPIO_Config();	//输出模式

	DHT11_Dout_1;	// 一开始拉高PE6

	return ;
}

/* 配置DHT11的I/O口 为通用推挽输出模式 */
static void DHT11_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	// 打开串口GPIO的时钟
	DHT11_Dout_SCK_APBxClkCmd(DHT11_Dout_GPIO_CLK, ENABLE);

	/*选择要控制的DHT11_Dout_GPIO_PORT引脚*/	
	GPIO_InitStructure.GPIO_Pin = DHT11_Dout_GPIO_PIN;
	
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	
	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* 初始化GPIOE */
	GPIO_Init(DHT11_Dout_GPIO_PORT, &GPIO_InitStructure);
  
	return ;
}

static void DHT11_Mode_Out_PP(void) {
 	GPIO_InitTypeDef GPIO_InitStructure;

	 	/*选择要控制的DHT11_Dout_GPIO_PORT引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = DHT11_Dout_GPIO_PIN;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	/*调用库函数，初始化DHT11_Dout_GPIO_PORT*/
  	GPIO_Init(DHT11_Dout_GPIO_PORT, &GPIO_InitStructure);	 	 
	
}

/* 配置DHT11的I/O口 为浮空输入模式 */
static void DHT11_Mode_IPU(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	// 打开串口GPIO的时钟
	DHT11_Dout_SCK_APBxClkCmd(DHT11_Dout_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = DHT11_Dout_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;					// 将DHT11的GPIO配置为浮空输入模式
	
	/* 初始化GPIOE */
	GPIO_Init(DHT11_Dout_GPIO_PORT, &GPIO_InitStructure);
  
	return ;
}




/* 从DHT11读取一个字节：高位先行 */
static uint8_t DHT11_ReadByte(void) {
	uint8_t i, dht11_onebyte_data = 0;

	/* 循环8次读取一个字节的数据 */
	for(i = 0; i < 8; i++) {
		//每1bit都需要延时50us才能开始读
		while( 0 == DHT11_Dout_IN() );

		//26~28us为0，70us为1。取50us的时候读取电平
		DHT11_DELAY_US(50);
		
		if( 1 == DHT11_Dout_IN() ) {		//如果为高电平
			dht11_onebyte_data |= (uint8_t)(1 << 0);		//置1 
			while( 1 == DHT11_Dout_IN() );		
		} else {
			dht11_onebyte_data &= (uint8_t)~(1 << 0);	//置0   
			
		}
		
		if(i == 7) {
			break;
		}
		//每读完一个bit，dht11_onebyte_data左移一位
		dht11_onebyte_data = dht11_onebyte_data << 1;
		
	}

	return dht11_onebyte_data;
}





/* 读取温湿度40bits的数据 */
uint8_t DHT11_Read_TempAndHumidity(DHT11_Data_TypeDef* DHT11_Data) {
	//总线空闲状态为高电平
	DHT11_Mode_Out_PP();
	//DHT11_Dout_1;
	
	//主机开始发送起始信号（拉低）
	DHT11_Dout_0;
	
	//主机至少延时18ms
	DHT11_DELAY_MS(18);
	
	//主机拉高20~40us
	DHT11_Dout_1;
	DHT11_DELAY_US(30);

	/*主机设为输入模式 等待DHT11发出响应信号*/ 
	DHT11_Mode_IPU();
	
	//如果DHT11发出响应信号(低电平信号)
	if( 0 == DHT11_Dout_IN() ) {
		//等待DHT11的响应信号(80us)结束，结束后，将会发出高电平
		while(DHT11_Dout_IN() == 0);
		
		//等待DHT11拉高80us结束
		while(DHT11_Dout_IN() == 1);
		
		//开始读数据 
		DHT11_Data->humi_int = DHT11_ReadByte();
		DHT11_Data->humi_deci = DHT11_ReadByte();
		DHT11_Data->temp_int = DHT11_ReadByte();
		DHT11_Data->temp_deci = DHT11_ReadByte();
		DHT11_Data->check_sum = DHT11_ReadByte();
	} 
	
	//数据传送结束时，从机拉低50us
	DHT11_DELAY_US(50);

	//GPIO设置输出模式，并拉高电平，释放总线
	DHT11_GPIO_Config();
	DHT11_Dout_1;
	
	/*检查读取的数据是否正确*/
	if(DHT11_Data->check_sum == DHT11_Data->humi_int + DHT11_Data->humi_deci + DHT11_Data->temp_int+ DHT11_Data->temp_deci) {
		return SUCCESS;	//成功读取温湿度数据则返回0
	} else {
		printf("读取温湿度数据不正确！！！\n");
		return ERROR;	//读取失败
	}
	
	
} 

/*************************************END OF FILE******************************/
