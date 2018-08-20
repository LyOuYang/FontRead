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
	u8 csize=(size/8+((size%8)?1:0))*(size);//�õ�����һ���ַ���Ӧ������ռ���ֽ���	 
	qh=*code;
	ql=*(++code);
	if(qh<0x81||ql<0x40||ql==0xff||qh==0xff)//�� ���ú���
	{   		    
	    for(i=0;i<csize;i++)*mat++=0x00;//�������
	    return; //��������
	}          
	if(ql<0x7f)ql-=0x40;//ע��!
	else ql-=0x41;
	qh-=0x81;   
	foffset=((unsigned long)190*qh+ql)*csize;	//�õ��ֿ��е��ֽ�ƫ����  		  
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

//��ʾһ��ָ����С�ĺ���
//x,y :���ֵ�����
//font:����GBK��
//size:�����С
//mode:0,������ʾ,1,������ʾ	   
void Show_Font(u16 x,u16 y,u8 *font,u8 size,u8 mode)
{
	u8 dzk[128];   
	Get_HzMat(font,dzk,size);	//�õ���Ӧ��С�ĵ������� 
}

void Get_Char(u8 *str,u8 size){
	
}

void Get_Font(u8 *font,u8 size){
	u8 dzk[128]; 
	Get_HzMat(font,dzk,size);	//�õ���Ӧ��С�ĵ������� 
}

void Show_Str(u8 *str,u8 size,u8 char_count)
{											  	  
		u8 bHz=0;     //�ַ���������  	    				    				  	  
    while(*str!=0)//����δ����
    { 
        if(!bHz)
        {
	        if(*str>0x80)bHz=1;//���� 
	        else              //�ַ�
	        {      
							Get_Char(str,size);//��Ч����д�� 
							str++; 
	        }
        }else//���� 
        {     
						bHz=0;//�к��ֿ�    						     
						Get_Font(str,size); //��ʾ�������,������ʾ						
						str+=2;     
        }						 
    }   
}  
