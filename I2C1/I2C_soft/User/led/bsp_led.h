#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f10x.h"

//R -- ���
#define LED_R_GPIO_PORT			GPIOB				 								/* GPIO�˿� */
#define LED_R_GPIO_CLOCK		RCC_APB2Periph_GPIOB				/* GPIO�˿�ʱ�� */
#define LED_R_GPIO_PIN			GPIO_Pin_5									/* ��5������ */

//G -- �̵�
#define LED_G_GPIO_PORT			GPIOB				 								/* GPIO�˿� */
#define LED_G_GPIO_CLOCK		RCC_APB2Periph_GPIOB				/* GPIO�˿�ʱ�� */
#define LED_G_GPIO_PIN			GPIO_Pin_0									/* ��0������ */

//B -- ����
#define LED_B_GPIO_PORT			GPIOB				 								/* GPIO�˿� */
#define LED_B_GPIO_CLOCK		RCC_APB2Periph_GPIOB				/* GPIO�˿�ʱ�� */
#define LED_B_GPIO_PIN			GPIO_Pin_1									/* ��1������ */


#define LED_ALL_GPIO_PIN	(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5)

#define ON	1
#define OFF	(!ON)

/* ʹ�ñ�׼�Ĺ̼������IO */
#define LED1(a)	if(a) \
											GPIO_ResetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN); \
										else \
											GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);

										
#define LED2(a)	if(a) \
											GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN); \
										else \
											GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);										

										
#define LED3(a)	if(a) \
											GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN); \
										else \
											GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);										


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬

/* �������IO�ĺ� */
#define LED_RED_TOGGLE		 digitalToggle(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LED_RED_OFF		   	 digitalHi(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LED_RED_ON			   digitalLo(LED_R_GPIO_PORT,LED_R_GPIO_PIN)

#define LED_GREEN_TOGGLE	 digitalToggle(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_GREEN_OFF		   digitalHi(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_GREEN_ON			 digitalLo(LED_G_GPIO_PORT,LED_G_GPIO_PIN)

#define LED_BLUE_TOGGLE		 digitalToggle(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_BLUE_OFF		   digitalHi(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_BLUE_ON			   digitalLo(LED_B_GPIO_PORT,LED_B_GPIO_PIN)


/* ������ɫ������߼��÷�ʹ��PWM�ɻ��ȫ����ɫ,��Ч������ */

//��
#define LED_RED  \
					LED_RED_ON;\
					LED_GREEN_OFF\
					LED_BLUE_OFF

//��
#define LED_GREEN		\
					LED_RED_OFF;\
					LED_GREEN_ON\
					LED_BLUE_OFF

//��
#define LED_BLUE	\
					LED_RED_OFF;\
					LED_GREEN_OFF\
					LED_BLUE_ON

					
//��(��+��)					
#define LED_YELLOW	\
					LED_RED_ON;\
					LED_GREEN_ON\
					LED_BLUE_OFF
					
//��(��+��)
#define LED_PURPLE	\
					LED_RED_ON;\
					LED_GREEN_OFF\
					LED_BLUE_ON

//��(��+��)
#define LED_CYAN \
					LED_RED_OFF;\
					LED_GREEN_ON\
					LED_BLUE_ON
					
//��(��+��+��)
#define LED_WHITE	\
					LED_RED_ON;\
					LED_GREEN_ON\
					LED_BLUE_ON
					
//��(ȫ���ر�)
#define LED_RGBOFF	\
					LED_RED_OFF;\
					LED_GREEN_OFF\
					LED_BLUE_OFF



//#define LED_RGB(a)	if(a) GPIO_ResetBits(LED_GPIO_PORT, LED_ALL_GPIO_PIN); else GPIO_SetBits(LED_GPIO_PORT, LED_ALL_GPIO_PIN);

void LED_GPIO_Config(void);

#endif
