#ifndef __STM32F10X_H__
#define __STM32F10X_H__

typedef unsigned int		uint32_t;	//无符号32位变量
typedef unsigned short	uint16_t;	//无符号16位变量
	
/* 外设基地址 */
#define PERIPH_BASE 		((unsigned int) 0x40000000)

/* 总线基地址 */
#define APB1PERIPH_BASE		(PERIPH_BASE + 0)
#define APB2PERIPH_BASE		(PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0x20000)

//RCC基地址
#define RCC_BASE					(AHBPERIPH_BASE + 0x1000)

/* GPIO 外设基地址 */
#define GPIOA_BASE 			(APB2PERIPH_BASE + 0x800)
#define GPIOB_BASE 			(APB2PERIPH_BASE + 0xC00)
#define GPIOC_BASE 			(APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE 			(APB2PERIPH_BASE + 0x1C00)
#define GPIOE_BASE 			(APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE 			(APB2PERIPH_BASE + 0x2000)
#define GPIOG_BASE 			(APB2PERIPH_BASE + 0x2400)


//#define GPIOB_CRL					(*((unsigned int *)(GPIOB_BASE + 0)))
//#define GPIOB_ODR					(*((unsigned int *)(GPIOB_BASE + 0x0c)))
	

/* 寄存器基地址，以GPIOB为例 */
//#define GPIOB_CRL			(*((unsigned int *)(GPIOB_BASE + 0x00)))
//#define GPIOB_CRH			(*((unsigned int *)(GPIOB_BASE + 0x04)))
//#define GPIOB_IDR			(*((unsigned int *)(GPIOB_BASE + 0x08)))
//#define GPIOB_ODR			(*((unsigned int *)(GPIOB_BASE + 0x0c)))
//#define GPIOB_BSRR		(*((unsigned int *)(GPIOB_BASE + 0x10)))
//#define GPIOB_BRR			(*((unsigned int *)(GPIOB_BASE + 0x14)))
//#define GPIOB_LCKR		(*((unsigned int *)(GPIOB_BASE + 0x18)))


/* GPIO寄存器列表 */
typedef struct {
	uint32_t	CRL;	//GPIO 端口配置低寄存器		地址偏移:0x00
	uint32_t	CRH;	//GPIO 端口配置高寄存器		地址偏移:0x04
	uint32_t	IDR;	//GPIO 数据输入寄存器		地址偏移:0x08
	uint32_t	ODR;	//GPIO 数据输出寄存器		地址偏移:0x0c
	uint32_t	BSRR;	//GPIO 位设置/清除寄存器	地址偏移:0x10
	uint32_t	BRR;	//GPIO 端口位清除寄存器		地址偏移:0x14
	uint32_t	LCKR;	//GPIO 端口配置锁定寄存器	地址偏移:0x18
}GPIO_TypeDef;


#define GPIOA	((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB	((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC	((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD	((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE	((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOF	((GPIO_TypeDef *)GPIOF_BASE)
#define GPIOG	((GPIO_TypeDef *)GPIOG_BASE)
#define GPIOH	((GPIO_TypeDef *)GPIOH_BASE)


/*APB2 外设时钟使能寄存器(RCC_APB2ENR) 偏移地址：0x18*/
#define RCC_APB2ENR				(*((unsigned int*)(RCC_BASE + 0x18)))

typedef struct {
	uint32_t	CR;				//时钟控制寄存器(RCC_CR)偏移地址: 0x00
	uint32_t	CFGR;			//时钟配置寄存器(RCC_CFGR)偏移地址: 0x04
	uint32_t	CIR;			//时钟中断寄存器 (RCC_CIR)偏移地址: 0x08
	uint32_t	APB2RSTR;	//APB2 外设复位寄存器 (RCC_APB2RSTR)偏移地址: 0x0C
	uint32_t	APB1RSTR;	//APB1 外设复位寄存器 (RCC_APB1RSTR)偏移地址：0x10
	uint32_t	AHBENR;		//AHB外设时钟使能寄存器 (RCC_AHBENR)偏移地址：0x14
	uint32_t	APB2ENR;	//APB2 外设时钟使能寄存器(RCC_APB2ENR)偏移地址：0x18
	uint32_t	APB1ENR;	//APB1 外设时钟使能寄存器(RCC_APB1ENR)偏移地址：0x1C
	uint32_t	BDCR;			//备份域控制寄存器 (RCC_BDCR)偏移地址：0x20
	uint32_t	CSR;			//控制/状态寄存器 (RCC_CSR)偏移地址：0x24
}RCC_TypeDef;

#define RCC ((RCC_TypeDef *)RCC_BASE)

#endif
