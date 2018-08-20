#include "sys.h" 
#include "fontupd.h"
#include "w25qxx.h"
#include "text.h"	
#define FONTINFOADDR 	1024*1024*12 					//WarShip STM32F103 V3是从12M地址以后开始存放字库
//用来保存字库基本信息，地址，大小等
_font_info ftinfo;

u8 font_init(void)
{		
	u8 t=0;
	W25QXX_Init();  
	while(t<10)//连续读取10次,都是错误,说明确实是有问题,得更新字库了
	{
		t++;
		W25QXX_Read((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo));//读出ftinfo结构体数据
		if(ftinfo.fontok==0XAA)break;
		//delay_ms(20);
	}
	if(ftinfo.fontok!=0XAA)return 1;
	return 0;		    
}

