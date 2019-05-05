#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "MicroStepDriver.h" 

//ALIENTEK 探索者STM32F407开发板 实验18
//ADC模数转换实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司
//作者：正点原子 @ALIENTEK



int main(void) {
	u16 data1;
	double data_0,data_6,data_5; //通道0、通道5和通道6的咀嚼力
	u16 force;
	u16 cycleNum;
	u8 pattern;
	u8 speed=100;
	u16 biteNumber=1;//当前咬合次数
	delay_init(168);   	//初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED
	Adc_Init();         //初始化ADC
  move(1);
  move(2);                            //电机动的程序，正转 
  move(3);
  move(4);                            //电机动的程序，正转 
	
	/*
	while(1) {
		if(USART_RX_STA&0x8000) {
			USART_RX_STA=0;
			LED0=!LED0; //led灯翻转，显示从上位机接收到数据

			if(USART_RX_BUF[0]==1) { //接收到1表示上位机发出开始指令

				force=USART_RX_BUF[1]*256+USART_RX_BUF[2]; //设定的咀嚼力
				cycleNum=USART_RX_BUF[3]*256+USART_RX_BUF[4]; //设定的循环次数
				pattern=USART_RX_BUF[5]; //设定的咀嚼模式
				//speed=USART_RX_BUF[6];  //设定的速度
				if(pattern==1) { //咬合模式
						 s(1,speed);
						 s(2,speed);
	           move(1);
				     move(2);                            //电机动的程序，正转 
			     
					while(!(USART_RX_STA&0x8000)) { //没接收到新的指令就一直运行
						USART1->SR; //清空串口1标志位

						data1=Get_Adc_Average(ADC_Channel_4,10);//获取通道0的转换值，10次取平均
						data_0=Get_ForceNum(data1); //通道0的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_7,10);//获取通道6的转换值
						data_6=Get_ForceNum(data1); //通道6的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_5,10);//获取通道5的转换
						data_5=Get_ForceNum(data1); //通道5的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						if((data_0>=force||data_6>=force||data_5>=force)&&biteNumber<=cycleNum) { //如果有一个传感器的压力值超过设定值，电机反转
							
	             Locate_Abs(1,0, 3200,3200,100);
				       Locate_Abs(2,0, 3200,3200,100);    //电机反转回原点程序
							                                          
							biteNumber++;
						} else if((data_0>=force||data_6>=force||data_5>=force)&&biteNumber==cycleNum) { //达到咬合次数，只把电机回升
             
							 Locate_Abs(1,0, 3200,3200,100);
				       Locate_Abs(2,0, 3200,3200,100);    //电机反转回原点程序
							break; //跳出数据采集发送循环
						}
						if(MSD1_status.running == FALSE &&MSD2_status.running ==FALSE){
							     move(1);
				           move(2);                      //电机动的程序，正转 
							    }			
						delay_ms(5);
				}
					
					if(USART_RX_BUF[0]==2) { //开始过程中接收到停止信号
						 stop(1);
				     stop(2);                             //电机停止程序      
						USART_RX_STA=0;
					} else if(USART_RX_BUF[0]==3) { //开始过程中接收到复位信号
						USART_RX_STA=0;
					}
				} else if(pattern==2) { //纵向咀嚼
					while(!(USART_RX_STA&0x8000)) { //没接收到新的指令就一直运行
						USART1->SR; //清空串口1标志位
            
						data1=Get_Adc_Average(ADC_Channel_0,10);//获取通道0的转换值，10次取平均
						data_0=Get_ForceNum(data1); //通道0的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_6,10);//获取通道6的转换值
						data_6=Get_ForceNum(data1); //通道6的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_5,10);//获取通道5的转换
						data_5=Get_ForceNum(data1); //通道5的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						delay_ms(5);
					}
				} else if(pattern==3) { //横向咀嚼
					while(!(USART_RX_STA&0x8000)) { //没接收到新的指令就一直运行
						USART1->SR; //清空串口1标志位

						data1=Get_Adc_Average(ADC_Channel_0,10);//获取通道0的转换值，10次取平均
						data_0=Get_ForceNum(data1); //通道0的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_6,10);//获取通道6的转换值
						data_6=Get_ForceNum(data1); //通道6的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_5,10);//获取通道5的转换
						data_5=Get_ForceNum(data1); //通道5的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						delay_ms(5);
					}
				} else if(pattern==4) { //复合咀嚼
					while(!(USART_RX_STA&0x8000)) { //没接收到新的指令就一直运行
						USART1->SR; //清空串口1标志位

						data1=Get_Adc_Average(ADC_Channel_0,10);//获取通道0的转换值，10次取平均
						data_0=Get_ForceNum(data1); //通道0的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_6,10);//获取通道6的转换值
						data_6=Get_ForceNum(data1); //通道6的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_5,10);//获取通道5的转换
						data_5=Get_ForceNum(data1); //通道5的咀嚼力

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						delay_ms(5);
					}
				}
			} else if(USART_RX_BUF[0]==2)	{ //接收到停止指令

			}

			else if(USART_RX_BUF[0]==3) {  //接收到复位指令

			}
		}
	}
	
	*/
}



