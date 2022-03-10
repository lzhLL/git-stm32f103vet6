#if 0
#include <reg52.h>

sbit LED = P0^0

void main(void) {
	P0 = 0xfe;		//���߲���

	LED = 0;			//λ����
	
	return ;
}


#endif




/* дһ����ʱ������ʵ����˸PB0 PB1 PB5  */
#include "stm32f10x.h"

void LedInit(void);
void SystemInit(void);
void delay(unsigned int n);

int main(void) {
	LedInit();
	while(1) {
		//��GPIOB_ODR�Ĵ������bit0��bit1��bit5���0(����LED_GGB��)
		*((unsigned int*) 0x40010c0c) &= ~((1 << 0) | (1 << 1) | (1 << 5));
		delay(100000);
		//��GPIOB_ODR�Ĵ������bit0��bit1��bit5���1(Ϩ��LED_GGB��)
		*((unsigned int*) 0x40010c0c) |= ((1 << 0) | (1 << 1) | (1 << 5));
		delay(100000);	
	}
	
	return 0;
}


void LedInit(void) {
	/* RCC_APB2ENR�� ��GPIOB��ʱ�ӣ� ƫ����Ϊ0x18 ������ַΪAHB, rcc��ʼ��ַΪ0x40021000 */
	*((unsigned int*) 0x40021018) |= (1 << 3);//��GPIOBʱ��
	
	//����GPIOB_CRL�Ĵ���Ϊ���ģʽ
	*((unsigned int*) 0x40010c00) &= ~((256 << 0) | (20 << 0) | (21 << 0) | (22 << 0) | (23 << 0));	//ǰ8λ��0,bit20~23��0
	*((unsigned int*) 0x40010c00) |= ((1 << 0) | (1 << 4) | (1 << 20));		//bit0��1
	return ;
}

void SystemInit(void) { 

	
	//������Ϊ�գ�Ŀ����Ϊ��ƭ�������������� 
	return ;
}


void delay(unsigned int n) {
    unsigned int i,j;
    for(j = 0; j<5; j++)
    {
        for(i = 0;i<n;i++);
    }
		return ;
}

