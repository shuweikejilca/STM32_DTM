#include "stm32f10x.h"
#include "OLED,h"
#include "DTM.h"

int main(void){
	OLED_Init();
    OLED_ShowString(1, 1,"DTM_Distance");	
	float result;
	uint8_t Data_Get[36] = {19,29,3,4,5,6,7,8};
	uint8_t Data_Model[36] = {31,13,7,8,1,1,1,1};
	result = DTM_Distance(Data_Get,Data_Model);
	
	OLED_ShowNum(3, 1, result*10000, 5);// 目前只能显示整型，所以乘以10000做处理
	
	while(1)
	{
		
		
	}

}
