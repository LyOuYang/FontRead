#include "delay.h"
#include "fontupd.h"
#include "text.h"
int main(void){
	//delay_init();	    	 //延时函数初始化	
	font_init();
	Show_Str("中",16,1);
	Show_Str("中",32,1);
}
