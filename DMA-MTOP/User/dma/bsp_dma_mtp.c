#include "bsp_dma_mtp.h"

uint8_t SendBuff[SENDBUFF_SIZE];

/**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USARTx, &USART_InitStructure);	
	
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


//memory -> P(USART->DR)
void USARTx_DMA_Config(void) {
	//�ȶ���DMA�ṹ��
	DMA_InitTypeDef 	DMA_InitStruct;
	//typedef struct
//{
//  uint32_t DMA_PeripheralBaseAddr;   // �����ַ
//  uint32_t DMA_MemoryBaseAddr;       // �洢����ַ
//  uint32_t DMA_DIR;                  // ���䷽��
//  uint32_t DMA_BufferSize;           // ������Ŀ
//  uint32_t DMA_PeripheralInc;        // �����ַ����ģʽ
//  uint32_t DMA_MemoryInc;            // �洢����ַ����ģʽ
//  uint32_t DMA_PeripheralDataSize;   // �������ݿ��
//  uint32_t DMA_MemoryDataSize;       // �洢�����ݿ��
//  uint32_t DMA_Mode;                 // ģʽѡ��
//  uint32_t DMA_Priority;             // ͨ�����ȼ�
//  uint32_t DMA_M2M;                  // �洢�����洢��ģʽ
//}DMA_InitTypeDef;
	
	
	//��DMA��ʱ�ӣ���ԭ��ͼ������DMA������AHB����
	RCC_AHBPeriphClockCmd(USART_TX_DMA_CLK, ENABLE);
	
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)USART_DR_ADDRESS;
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)SendBuff;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;	//������Ŀ�ĵ�ַ
	DMA_InitStruct.DMA_BufferSize = SENDBUFF_SIZE;	//5000������
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ����
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢����ַ����
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�ĸ��ֽڵĿ��
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݿ��Ϊ32λ
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;//����һ��
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;//
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	
	//��ʼ��DMA
	DMA_Init(USART_TX_DMA_CHANNEL, &DMA_InitStruct);
	
	//���DMA1_FLAG_TC6��־λ
	DMA_ClearFlag(USART_TX_DMA_FLAG_TC);
	
	//ʹ��DMA����DMA���ã�
	DMA_Cmd(USART_TX_DMA_CHANNEL, ENABLE);
	
}			
