#include "sys.h"
#include "fontupd.h"
#include "w25qxx.h" 
#include "text.h"
u8 **fonts;
void Get_HzMat(unsigned char *code,unsigned char *mat,u8 size)
{		    
	unsigned char qh,ql;
	unsigned char i;					  
	unsigned long foffset; 
	u8 csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数	 
	qh=*code;
	ql=*(++code);
	if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)//非 常用汉字
	{   		    
	    for(i=0;i<csize;i++)*mat++=0x00;//填充满格
	    return; //结束访问
	}          
	if(ql<0x7f)ql-=0x40;//注意!
	else ql-=0x41;
	qh-=0x81;   
	foffset=((unsigned long)190*qh+ql)*csize;	//得到字库中的字节偏移量  		  
	switch(size)
	{
		case 12:
			W25QXX_Read(mat,foffset+ftinfo.f12addr,csize);
			break;
		case 16:
			W25QXX_Read(mat,foffset+ftinfo.f16addr,csize);
			break;
		case 24:
			W25QXX_Read(mat,foffset+ftinfo.f24addr,csize);
			break;
		case 32:
			W25QXX_Read(mat,foffset+ftinfo.f32addr,csize);
			break;	
	}     												    
}

//显示一个指定大小的汉字
//x,y :汉字的坐标
//font:汉字GBK码
//size:字体大小
//mode:0,正常显示,1,叠加显示	   
void Show_Font(u16 x,u16 y,u8 *font,u8 size,u8 mode)
{
	u8 dzk[128];   
	Get_HzMat(font,dzk,size);	//得到相应大小的点阵数据 
}

void Get_Char(u8 *str,u8 size){
	
}

void Get_Font(u8 *font,u8 size){
	u8 dzk[128]; 
	Get_HzMat(font,dzk,size);	//得到相应大小的点阵数据 
}

void Show_Str(u8 *str,u8 size,u8 char_count)
{											  	  
		u8 bHz=0;     //字符或者中文  	    				    				  	  
    while(*str!=0)//数据未结束
    { 
        if(!bHz)
        {
	        if(*str>0x80)bHz=1;//中文 
	        else              //字符
	        {      
							Get_Char(str,size);//有效部分写入 
							str++; 
	        }
        }else//中文 
        {     
						bHz=0;//有汉字库    						     
						Get_Font(str,size); //显示这个汉字,空心显示						
						str+=2;     
        }						 
    }   
}  
