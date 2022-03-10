#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

void SystemInit(void);

int main(void) {
	
#if 0
	/* RCC_APB2ENR GPIOB��ʱ�ӣ� ƫ����Ϊ0x18 ������ַΪAHB, rcc��ʼ��ַΪ0x40021000 */
	*((unsigned int*) 0x40021018) |= (1 << 3);//��GPIOBʱ��
	
	//����GPIOB_CRL�Ĵ���Ϊͨ���������ģʽ������ٶ�Ϊ10MHZ
	*((unsigned int*) 0x40010c00) &= ~(16 << 0);	//ǰ��λ��0
	*((unsigned int*) 0x40010c00) |= (1 << 0);		//bit0��1
	
	//��GPIOB_ODR�Ĵ������bit0���0(����LED_G��)
	*((unsigned int*) 0x40010c0c) &= ~(1 << 0);
	
#elif 0
	/* RCC_APB2ENR GPIOB��ʱ�ӣ� ƫ����Ϊ0x18 ������ַΪAHB, rcc��ʼ��ַΪ0x40021000 */
	RCC->APB2ENR |= (1 << 3);//��GPIOBʱ��

	//����GPIOB_CRL�Ĵ���Ϊ���ģʽ
	GPIOB->CRL &= ~((256 << 0) | (20 << 0) | (21 << 0) | (22 << 0) | (23 << 0));	//ǰ8λ��0,bit20~23��0
	GPIOB->CRL |= ((1 << 0) | (1 << 4) | (1 << 20));		//bit0��1
	
	//��GPIOB_BSRR�Ĵ�����bit0��1, Ŀ������GPIOB_ODRbit0Ϊ1(Ϩ��LED_G��)
	//GPIO_SetBits(GPIOB, GPIO_Pin_0);
	
	//��GPIOB_BRR�Ĵ�����bit0��1, Ŀ������GPIOB_ODRbit0Ϊ0(����LED_G��)
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	
#elif 1
	/* RCC_APB2ENR GPIOB��ʱ�ӣ� ƫ����Ϊ0x18 ������ַΪAHB, rcc��ʼ��ַΪ0x40021000 */
	RCC->APB2ENR |= (1 << 3);//��GPIOBʱ��

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//��GPIOB_BSRR�Ĵ�����bit0��1, Ŀ������GPIOB_ODRbit0Ϊ1(Ϩ��LED_G��)
	//GPIO_SetBits(GPIOB, GPIO_Pin_0);
	
	//��GPIOB_BRR�Ĵ�����bit0��1, Ŀ������GPIOB_ODRbit0Ϊ0(����LED_G��)
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
	
	
#endif
	return 0;

}

void SystemInit(void) { 

	
	//������Ϊ�գ�Ŀ����Ϊ��ƭ�������������� 
	return ;
}




