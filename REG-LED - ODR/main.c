
#include "stm32f10x.h"

int main(void) {
	
#if 0
	/* RCC_APB2ENR GPIOB��ʱ�ӣ� ƫ����Ϊ0x18 ������ַΪAHB, rcc��ʼ��ַΪ0x40021000 */
	*((unsigned int*) 0x40021018) |= (1 << 3);//��GPIOBʱ��
	
	//����GPIOB_CRL�Ĵ���Ϊ���ģʽ
	*((unsigned int*) 0x40010c00) &= ~(16 << 0);	//ǰ��λ��0
	*((unsigned int*) 0x40010c00) |= (1 << 0);		//bit0��1
	
	//��GPIOB_ODR�Ĵ������bit0���0(����LED_G��)
	*((unsigned int*) 0x40010c0c) &= ~(1 << 0);
	
#elif 0
	
	/* RCC_APB2ENR GPIOB��ʱ�ӣ� ƫ����Ϊ0x18 ������ַΪAHB, rcc��ʼ��ַΪ0x40021000 */
	RCC_APB2ENR |= (1 << 3);//��GPIOBʱ��
	
	//����GPIOB_CRL�Ĵ���Ϊ���ģʽ
	GPIOB_CRL &= ~(16 << 0);	//ǰ��λ��0
	GPIOB_CRL |= (1 << 0);		//bit0��1
	
	//��GPIOB_ODR�Ĵ������bit0���0(����LED_G��)
	GPIOB_ODR &= ~(1 << 0);
	
#elif 0
		/* RCC_APB2ENR GPIOB��ʱ�ӣ� ƫ����Ϊ0x18 ������ַΪAHB, rcc��ʼ��ַΪ0x40021000 */
	RCC->APB2ENR |= (1 << 3);//��GPIOBʱ��
	
	//����GPIOB_CRL�Ĵ���Ϊ���ģʽ
	GPIOB->CRL &= ~(16 << 0);	//ǰ��λ��0
	GPIOB->CRL |= (1 << 0);		//bit0��1
	
	//��GPIOB_ODR�Ĵ������bit0���0(����LED_G��)
	GPIOB->ODR &= ~(1 << 0);
	//GPIOB->ODR |= (1 << 0);
	
#elif 1
		/* RCC_APB2ENR GPIOB��ʱ�ӣ� ƫ����Ϊ0x18 ������ַΪAHB, rcc��ʼ��ַΪ0x40021000 */
	RCC->APB2ENR |= (1 << 3);//��GPIOBʱ��
	
	//����GPIOB_CRL�Ĵ���Ϊ���ģʽ
	GPIOB->CRL &= ~(16 << 0);	//ǰ��λ��0
	GPIOB->CRL |= (1 << 0);		//bit0��1
	
	//��GPIOB_ODR�Ĵ������bit0���0(����LED_G��)
	GPIOB->ODR &= ~(1 << 0);
	
#endif	
	return 0;

}

void SystemInit(void) { 

	
	//������Ϊ�գ�Ŀ����Ϊ��ƭ�������������� 
	return ;
}

