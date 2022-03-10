#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f10x.h"

//R -- 红灯
#define LED_R_GPIO_PORT			GPIOB				 								/* GPIO端口 */
#define LED_R_GPIO_CLOCK		RCC_APB2Periph_GPIOB				/* GPIO端口时钟 */
#define LED_R_GPIO_PIN			GPIO_Pin_5									/* 第5个引脚 */

//G -- 绿灯
#define LED_G_GPIO_PORT			GPIOB				 								/* GPIO端口 */
#define LED_G_GPIO_CLOCK		RCC_APB2Periph_GPIOB				/* GPIO端口时钟 */
#define LED_G_GPIO_PIN			GPIO_Pin_0									/* 第0个引脚 */

//B -- 蓝灯
#define LED_B_GPIO_PORT			GPIOB				 								/* GPIO端口 */
#define LED_B_GPIO_CLOCK		RCC_APB2Periph_GPIOB				/* GPIO端口时钟 */
#define LED_B_GPIO_PIN			GPIO_Pin_1									/* 第1个引脚 */


#define LED_ALL_GPIO_PIN	(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_5)

#define ON	1
#define OFF	(!ON)

/* 使用标准的固件库控制IO */
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


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平
#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态

/* 定义控制IO的宏 */
#define LED_RED_TOGGLE		 digitalToggle(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LED_RED_OFF		   	 digitalHi(LED_R_GPIO_PORT,LED_R_GPIO_PIN)
#define LED_RED_ON			   digitalLo(LED_R_GPIO_PORT,LED_R_GPIO_PIN)

#define LED_GREEN_TOGGLE	 digitalToggle(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_GREEN_OFF		   digitalHi(LED_G_GPIO_PORT,LED_G_GPIO_PIN)
#define LED_GREEN_ON			 digitalLo(LED_G_GPIO_PORT,LED_G_GPIO_PIN)

#define LED_BLUE_TOGGLE		 digitalToggle(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_BLUE_OFF		   digitalHi(LED_B_GPIO_PORT,LED_B_GPIO_PIN)
#define LED_BLUE_ON			   digitalLo(LED_B_GPIO_PORT,LED_B_GPIO_PIN)


/* 基本混色，后面高级用法使用PWM可混出全彩颜色,且效果更好 */

//红
#define LED_RED  \
					LED_RED_ON;\
					LED_GREEN_OFF\
					LED_BLUE_OFF

//绿
#define LED_GREEN		\
					LED_RED_OFF;\
					LED_GREEN_ON\
					LED_BLUE_OFF

//蓝
#define LED_BLUE	\
					LED_RED_OFF;\
					LED_GREEN_OFF\
					LED_BLUE_ON

					
//黄(红+绿)					
#define LED_YELLOW	\
					LED_RED_ON;\
					LED_GREEN_ON\
					LED_BLUE_OFF
					
//紫(红+蓝)
#define LED_PURPLE	\
					LED_RED_ON;\
					LED_GREEN_OFF\
					LED_BLUE_ON

//青(绿+蓝)
#define LED_CYAN \
					LED_RED_OFF;\
					LED_GREEN_ON\
					LED_BLUE_ON
					
//白(红+绿+蓝)
#define LED_WHITE	\
					LED_RED_ON;\
					LED_GREEN_ON\
					LED_BLUE_ON
					
//黑(全部关闭)
#define LED_RGBOFF	\
					LED_RED_OFF;\
					LED_GREEN_OFF\
					LED_BLUE_OFF



//#define LED_RGB(a)	if(a) GPIO_ResetBits(LED_GPIO_PORT, LED_ALL_GPIO_PIN); else GPIO_SetBits(LED_GPIO_PORT, LED_ALL_GPIO_PIN);

void LED_GPIO_Config(void);

#endif
