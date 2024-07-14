#include "stm32f10x.h"                  // Device header
#include "math.h"
#define Dimension 36

uint8_t Distance_Fun(uint8_t X,uint8_t Y)
{
	if(X>Y){return X-Y;}
	else{return Y-X;}
}

uint8_t Fmin_Fun(uint8_t a,uint8_t b,uint8_t c)
{
	uint8_t min;
	min = fmin(a,b);
	if(min<=c){return min;}
	else{return c;}
}


float DTM_Distance(uint8_t Mpu6050_Data_Get[Dimension],uint8_t Mpu6050_Data_Model[Dimension])
{
	uint8_t MPU6050_Distance[Dimension][Dimension] = {{0}};
	MPU6050_Distance[0][0] = Distance_Fun(Mpu6050_Data_Get[0],Mpu6050_Data_Model[0]);
	
	for(uint8_t c=1;c<Dimension;c++){
	MPU6050_Distance[c][0] = MPU6050_Distance[c-1][0]+Distance_Fun(Mpu6050_Data_Get[c],Mpu6050_Data_Model[0]);	
}
	for(uint8_t d=1;d<Dimension;d++){
	MPU6050_Distance[0][d] = MPU6050_Distance[0][d-1]+Distance_Fun(Mpu6050_Data_Get[0],Mpu6050_Data_Model[d]);	
}
	for(uint8_t a=1;a<Dimension;a++)
	{
		for(uint8_t b=1;b<Dimension;b++)
		{
			MPU6050_Distance[a][b] = Distance_Fun(Mpu6050_Data_Get[a],Mpu6050_Data_Model[b])+Fmin_Fun(MPU6050_Distance[a-1][b],MPU6050_Distance[a][b-1],MPU6050_Distance[a-1][b-1]);
		}			
	}
	
	uint8_t i = Dimension-1;
	uint8_t j = Dimension-1;
	uint8_t m;
	float SumNum=0;
	float AveNum=0;
	uint8_t count = 0;
	uint8_t distance[Dimension*2] = {0};
	while(1)
	{
		if(i>0&&j>0)
		{
			m = Fmin_Fun(MPU6050_Distance[i-1][j],MPU6050_Distance[i][j-1],MPU6050_Distance[i-1][j-1]);
			if(m==MPU6050_Distance[i-1][j-1])
			{
				distance[count] = MPU6050_Distance[i][j]-MPU6050_Distance[i-1][j-1];
				i--;
				j--;
				count++;
			}
			else if(m==MPU6050_Distance[i][j-1])
			{
				distance[count] = MPU6050_Distance[i][j]-MPU6050_Distance[i][j-1];
				j--;
				count++;
			}
			else if(m==MPU6050_Distance[i-1][j])
			{
				distance[count] = MPU6050_Distance[i][j]-MPU6050_Distance[i-1][j];
				i--;
				count++;
			}
	
		}
		else if(i==0&&j==0)
		{
			distance[count] = MPU6050_Distance[i][j];
			count++;
			break;
		}
		else if(i==0)
		{
			distance[count] = MPU6050_Distance[i][j]-MPU6050_Distance[i][j-1];
			j--;
			count++;
		}
		else if(j==0)
		{
			distance[count] = MPU6050_Distance[i][j]-MPU6050_Distance[i-1][j];
			i--;
			count++;
		}
		
	}
		for(int e=0;e<count;e++)
		{
			SumNum = SumNum+distance[e];
		}
		AveNum = SumNum/count;
		return AveNum;	
}
