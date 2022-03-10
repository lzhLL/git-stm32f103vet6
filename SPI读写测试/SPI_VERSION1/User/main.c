#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"
#include "bsp_spi_flash.h"

uint8_t I2C_Test(void);

extern uint8_t ucTemp;
uint8_t read_ee_buf[256] = {0};
uint8_t write_ee_buf[256] = {0};
uint8_t write_spi_buff[256] = {0};
uint8_t read_spi_buff[4096] = {0};


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
	// 来到这里的时候，系统的时钟已经被配置成72M。
	uint32_t spi_flash_id = 0;
	uint16_t i = 0;
	
	
	LED_GPIO_Config();//LED的GPIO初始化配置
	USART_Config();		//初始化串口配置
	I2C_EE_Config();	//EEPROM初始化
	SPI_FLASH_Config();//初始化SPI
	
	Usart_SendStr(DEBUG_USARTx, "这是一个SPI通讯实验！\n");
	printf("这是一个SPI通讯实验\n");
	
	spi_flash_id = SPI_Read_ID();
	printf("spi_flash_id = %x\n\r", spi_flash_id);
	
	SPI_Erase_Ssector(0);	
	
	printf("写入数据：\n\r");
	for(i = 0; i < 256; i++) {
		write_spi_buff[i] = i;
		printf("%3d ", write_spi_buff[i]);
		if( (i%16) == 15 ) {
			printf("\n\r");
		}
	}
	SPI_Write_Data(0, write_spi_buff, 256);
	
	printf("\n\r读出数据：\n\r");
	SPI_Read_Data(0, read_spi_buff, 256);
	for(i = 0; i < 256; i++) {
		printf("%3d ",read_spi_buff[i]);
		if( (i%16) == 15 ) {
			printf("\n\r");
		}
	}
	while(1) {
//		switch(ucTemp) {
//			case 0x01:	
//				LED_RED;
//				break;
//			
//			case 0x02:	
//				LED_GREEN;

//				break;

//			case 0x03:	
//				LED_BLUE;

//				break;
//			
//			default:
//				LED_RGBOFF;
//				break;
//		}
		
	}
	
}

uint8_t I2C_Test(void) {
	uint16_t i = 0;
	printf("写入的数据\n\r");
	
	for(i = 0; i < 256; i++) {
		write_ee_buf[i] = i;
		
		printf("%3d ", write_ee_buf[i]);
		if( (i % 16) == 15) {
			printf("\r\n");
		}
	}
	
	I2C_EE_BufferWrite(write_ee_buf, 0, 256);
	printf("\n\r写入成功!\n\r");
	printf("\n\r读出的数据\n\r");
	
	EEPROM_Read(0, read_ee_buf, 256);
	for(i = 0; i < 256; i++) {	
		printf("%3d ", read_ee_buf[i]);
		if( (i % 16) == 15) {
			printf("\r\n");
		}
	}	
	
	return 1;
}
