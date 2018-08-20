#include "sys.h" 
#include "fontupd.h"
#include "w25qxx.h"
#include "text.h"	
#define FONTINFOADDR 	1024*1024*12 					//WarShip STM32F103 V3�Ǵ�12M��ַ�Ժ�ʼ����ֿ�
//���������ֿ������Ϣ����ַ����С��
_font_info ftinfo;

u8 font_init(void)
{		
	u8 t=0;
	W25QXX_Init();  
	while(t<10)//������ȡ10��,���Ǵ���,˵��ȷʵ��������,�ø����ֿ���
	{
		t++;
		W25QXX_Read((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo));//����ftinfo�ṹ������
		if(ftinfo.fontok==0XAA)break;
		//delay_ms(20);
	}
	if(ftinfo.fontok!=0XAA)return 1;
	return 0;		    
}

