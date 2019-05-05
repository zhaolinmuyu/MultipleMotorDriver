#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "MicroStepDriver.h" 

//ALIENTEK ̽����STM32F407������ ʵ��18
//ADCģ��ת��ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾
//���ߣ�����ԭ�� @ALIENTEK



int main(void) {
	u16 data1;
	double data_0,data_6,data_5; //ͨ��0��ͨ��5��ͨ��6�ľ׽���
	u16 force;
	u16 cycleNum;
	u8 pattern;
	u8 speed=100;
	u16 biteNumber=1;//��ǰҧ�ϴ���
	delay_init(168);   	//��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED
	Adc_Init();         //��ʼ��ADC
  move(1);
  move(2);                            //������ĳ�����ת 
  move(3);
  move(4);                            //������ĳ�����ת 
	
	/*
	while(1) {
		if(USART_RX_STA&0x8000) {
			USART_RX_STA=0;
			LED0=!LED0; //led�Ʒ�ת����ʾ����λ�����յ�����

			if(USART_RX_BUF[0]==1) { //���յ�1��ʾ��λ��������ʼָ��

				force=USART_RX_BUF[1]*256+USART_RX_BUF[2]; //�趨�ľ׽���
				cycleNum=USART_RX_BUF[3]*256+USART_RX_BUF[4]; //�趨��ѭ������
				pattern=USART_RX_BUF[5]; //�趨�ľ׽�ģʽ
				//speed=USART_RX_BUF[6];  //�趨���ٶ�
				if(pattern==1) { //ҧ��ģʽ
						 s(1,speed);
						 s(2,speed);
	           move(1);
				     move(2);                            //������ĳ�����ת 
			     
					while(!(USART_RX_STA&0x8000)) { //û���յ��µ�ָ���һֱ����
						USART1->SR; //��մ���1��־λ

						data1=Get_Adc_Average(ADC_Channel_4,10);//��ȡͨ��0��ת��ֵ��10��ȡƽ��
						data_0=Get_ForceNum(data1); //ͨ��0�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_7,10);//��ȡͨ��6��ת��ֵ��
						data_6=Get_ForceNum(data1); //ͨ��6�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_5,10);//��ȡͨ��5��ת��
						data_5=Get_ForceNum(data1); //ͨ��5�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						if((data_0>=force||data_6>=force||data_5>=force)&&biteNumber<=cycleNum) { //�����һ����������ѹ��ֵ�����趨ֵ�������ת
							
	             Locate_Abs(1,0, 3200,3200,100);
				       Locate_Abs(2,0, 3200,3200,100);    //�����ת��ԭ�����
							                                          
							biteNumber++;
						} else if((data_0>=force||data_6>=force||data_5>=force)&&biteNumber==cycleNum) { //�ﵽҧ�ϴ�����ֻ�ѵ������
             
							 Locate_Abs(1,0, 3200,3200,100);
				       Locate_Abs(2,0, 3200,3200,100);    //�����ת��ԭ�����
							break; //�������ݲɼ�����ѭ��
						}
						if(MSD1_status.running == FALSE &&MSD2_status.running ==FALSE){
							     move(1);
				           move(2);                      //������ĳ�����ת 
							    }			
						delay_ms(5);
				}
					
					if(USART_RX_BUF[0]==2) { //��ʼ�����н��յ�ֹͣ�ź�
						 stop(1);
				     stop(2);                             //���ֹͣ����      
						USART_RX_STA=0;
					} else if(USART_RX_BUF[0]==3) { //��ʼ�����н��յ���λ�ź�
						USART_RX_STA=0;
					}
				} else if(pattern==2) { //����׽�
					while(!(USART_RX_STA&0x8000)) { //û���յ��µ�ָ���һֱ����
						USART1->SR; //��մ���1��־λ
            
						data1=Get_Adc_Average(ADC_Channel_0,10);//��ȡͨ��0��ת��ֵ��10��ȡƽ��
						data_0=Get_ForceNum(data1); //ͨ��0�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_6,10);//��ȡͨ��6��ת��ֵ��
						data_6=Get_ForceNum(data1); //ͨ��6�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_5,10);//��ȡͨ��5��ת��
						data_5=Get_ForceNum(data1); //ͨ��5�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						delay_ms(5);
					}
				} else if(pattern==3) { //����׽�
					while(!(USART_RX_STA&0x8000)) { //û���յ��µ�ָ���һֱ����
						USART1->SR; //��մ���1��־λ

						data1=Get_Adc_Average(ADC_Channel_0,10);//��ȡͨ��0��ת��ֵ��10��ȡƽ��
						data_0=Get_ForceNum(data1); //ͨ��0�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_6,10);//��ȡͨ��6��ת��ֵ��
						data_6=Get_ForceNum(data1); //ͨ��6�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_5,10);//��ȡͨ��5��ת��
						data_5=Get_ForceNum(data1); //ͨ��5�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						delay_ms(5);
					}
				} else if(pattern==4) { //���Ͼ׽�
					while(!(USART_RX_STA&0x8000)) { //û���յ��µ�ָ���һֱ����
						USART1->SR; //��մ���1��־λ

						data1=Get_Adc_Average(ADC_Channel_0,10);//��ȡͨ��0��ת��ֵ��10��ȡƽ��
						data_0=Get_ForceNum(data1); //ͨ��0�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_6,10);//��ȡͨ��6��ת��ֵ��
						data_6=Get_ForceNum(data1); //ͨ��6�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						data1=Get_Adc_Average(ADC_Channel_5,10);//��ȡͨ��5��ת��
						data_5=Get_ForceNum(data1); //ͨ��5�ľ׽���

						USART_SendData(USART1,(data1>>8)&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
						USART_SendData(USART1,data1&0xFF);
						while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);

						delay_ms(5);
					}
				}
			} else if(USART_RX_BUF[0]==2)	{ //���յ�ָֹͣ��

			}

			else if(USART_RX_BUF[0]==3) {  //���յ���λָ��

			}
		}
	}
	
	*/
}



