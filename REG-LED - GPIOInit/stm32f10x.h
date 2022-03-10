#ifndef __STM32F10X_H__
#define __STM32F10X_H__

typedef unsigned int		uint32_t;	//�޷���32λ����
typedef unsigned short	uint16_t;	//�޷���16λ����
	
/* �������ַ */
#define PERIPH_BASE 		((unsigned int) 0x40000000)

/* ���߻���ַ */
#define APB1PERIPH_BASE		(PERIPH_BASE + 0)
#define APB2PERIPH_BASE		(PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE		(PERIPH_BASE + 0x20000)

//RCC����ַ
#define RCC_BASE					(AHBPERIPH_BASE + 0x1000)

/* GPIO �������ַ */
#define GPIOA_BASE 			(APB2PERIPH_BASE + 0x800)
#define GPIOB_BASE 			(APB2PERIPH_BASE + 0xC00)
#define GPIOC_BASE 			(APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE 			(APB2PERIPH_BASE + 0x1C00)
#define GPIOE_BASE 			(APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE 			(APB2PERIPH_BASE + 0x2000)
#define GPIOG_BASE 			(APB2PERIPH_BASE + 0x2400)


//#define GPIOB_CRL					(*((unsigned int *)(GPIOB_BASE + 0)))
//#define GPIOB_ODR					(*((unsigned int *)(GPIOB_BASE + 0x0c)))
	

/* �Ĵ�������ַ����GPIOBΪ�� */
//#define GPIOB_CRL			(*((unsigned int *)(GPIOB_BASE + 0x00)))
//#define GPIOB_CRH			(*((unsigned int *)(GPIOB_BASE + 0x04)))
//#define GPIOB_IDR			(*((unsigned int *)(GPIOB_BASE + 0x08)))
//#define GPIOB_ODR			(*((unsigned int *)(GPIOB_BASE + 0x0c)))
//#define GPIOB_BSRR		(*((unsigned int *)(GPIOB_BASE + 0x10)))
//#define GPIOB_BRR			(*((unsigned int *)(GPIOB_BASE + 0x14)))
//#define GPIOB_LCKR		(*((unsigned int *)(GPIOB_BASE + 0x18)))


/* GPIO�Ĵ����б� */
typedef struct {
	uint32_t	CRL;	//GPIO �˿����õͼĴ���		��ַƫ��:0x00
	uint32_t	CRH;	//GPIO �˿����ø߼Ĵ���		��ַƫ��:0x04
	uint32_t	IDR;	//GPIO ��������Ĵ���		��ַƫ��:0x08
	uint32_t	ODR;	//GPIO ��������Ĵ���		��ַƫ��:0x0c
	uint32_t	BSRR;	//GPIO λ����/����Ĵ���	��ַƫ��:0x10
	uint32_t	BRR;	//GPIO �˿�λ����Ĵ���		��ַƫ��:0x14
	uint32_t	LCKR;	//GPIO �˿����������Ĵ���	��ַƫ��:0x18
}GPIO_TypeDef;


#define GPIOA	((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB	((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC	((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD	((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE	((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOF	((GPIO_TypeDef *)GPIOF_BASE)
#define GPIOG	((GPIO_TypeDef *)GPIOG_BASE)
#define GPIOH	((GPIO_TypeDef *)GPIOH_BASE)


/*APB2 ����ʱ��ʹ�ܼĴ���(RCC_APB2ENR) ƫ�Ƶ�ַ��0x18*/
#define RCC_APB2ENR				(*((unsigned int*)(RCC_BASE + 0x18)))

typedef struct {
	uint32_t	CR;				//ʱ�ӿ��ƼĴ���(RCC_CR)ƫ�Ƶ�ַ: 0x00
	uint32_t	CFGR;			//ʱ�����üĴ���(RCC_CFGR)ƫ�Ƶ�ַ: 0x04
	uint32_t	CIR;			//ʱ���жϼĴ��� (RCC_CIR)ƫ�Ƶ�ַ: 0x08
	uint32_t	APB2RSTR;	//APB2 ���踴λ�Ĵ��� (RCC_APB2RSTR)ƫ�Ƶ�ַ: 0x0C
	uint32_t	APB1RSTR;	//APB1 ���踴λ�Ĵ��� (RCC_APB1RSTR)ƫ�Ƶ�ַ��0x10
	uint32_t	AHBENR;		//AHB����ʱ��ʹ�ܼĴ��� (RCC_AHBENR)ƫ�Ƶ�ַ��0x14
	uint32_t	APB2ENR;	//APB2 ����ʱ��ʹ�ܼĴ���(RCC_APB2ENR)ƫ�Ƶ�ַ��0x18
	uint32_t	APB1ENR;	//APB1 ����ʱ��ʹ�ܼĴ���(RCC_APB1ENR)ƫ�Ƶ�ַ��0x1C
	uint32_t	BDCR;			//��������ƼĴ��� (RCC_BDCR)ƫ�Ƶ�ַ��0x20
	uint32_t	CSR;			//����/״̬�Ĵ��� (RCC_CSR)ƫ�Ƶ�ַ��0x24
}RCC_TypeDef;

#define RCC ((RCC_TypeDef *)RCC_BASE)

#endif
