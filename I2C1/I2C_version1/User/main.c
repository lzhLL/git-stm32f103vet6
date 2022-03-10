#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"

extern uint8_t ucTemp;
uint8_t read_ee_data[10] = {0};
uint8_t write_ee_data[8] = {2,3,4,5,6,7};
uint8_t pBuffer[22] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
void Delay(unsigned int n) {
    unsigned int i,j;
    for(j = 0; j<5000; j++)
    {
        for(i = 0;i<n;i++);
    }
		return ;
}


//1.初始化IIC相关的GPIO
//2.配置IIC外设的工作模式
//3.编写IIC写入EEPROM的Byte write函数
//4.编写IIC读取EEPROM的RANDOM Read函数
//5.使用read函数及write函数进行读写校验
//6.编写page write 及seq read函数并校验

int main(void) {
	uint8_t i = 0;
	// 来到这里的时候，系统的时钟已经被配置成72M。
	LED_GPIO_Config();//LED的GPIO初始化配置
	USART_Config();		//初始化串口配置
	I2C_EE_Config();	//EEPROM初始化
	
	Usart_SendStr(DEBUG_USARTx, "这是一个I2C通讯实验！\n");
	printf("这是一个I2C通讯实验\n");
	
	//写入一个字节
	EEPROM_Byte_Write(11, 0x55); 
	
	//等待写入EEPROM完成
	EEPROM_WaitForWriteEnd();
	
	//读出数据
	EEPROM_Read(11, read_ee_data, 1);
	
	printf("接收到的数据为:0x%x\r\n", read_ee_data[0]);
	
	//写入8个字节
	EEPROM_Page_Write(17, write_ee_data, 6);
	//等待写入EEPROM完成
	EEPROM_WaitForWriteEnd();	
	//读出数据
	EEPROM_Read(17, read_ee_data, 6);
	for(i = 0; i < 6; i++) {
		printf("%d\r\n", read_ee_data[i]);
	}
	
	I2C_EE_BufferWrite(pBuffer, 17, 22);
	EEPROM_Read(17, read_ee_data, 22);
	for(i = 0; i < 22; i++) {
		printf("%d ", read_ee_data[i]);
		if( (i % 8) == 7) {
			printf("\r\n");
		}
	}
	
	while(1) {
		switch(ucTemp) {
			case 0x01:	
				LED_RED;
				break;
			
			case 0x02:	
				LED_GREEN;

				break;

			case 0x03:	
				LED_BLUE;

				break;
			
			default:
				LED_RGBOFF;
				break;
		}
		
	}
	
}
