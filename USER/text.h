#ifndef __TEXT_H__
#define __TEXT_H__	 
#include <stm32f10x.h>
#include "fontupd.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//������ʾ ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
 					     
void Get_HzMat(unsigned char *code,unsigned char *mat,u8 size);			//�õ����ֵĵ�����
void Show_Str(u8 *str,u8 size,u8 char_count);	//��ָ��λ����ʾһ���ַ��� 
void Show_Str_Mid(u16 x,u16 y,u8*str,u8 size,u8 len);
void Get_Font(u8 *font,u8 size);
void Get_Char(u8 *font,u8 size);
extern u8 **fonts;
#endif
