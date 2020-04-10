#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "uart.h"
 
/************************************************
 ALIENTEK��ӢSTM32������ʵ��4
 ���� ʵ��   
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/



void data_get_main(void);
//int data_get_slave1(int dd1);
//int data_get_slave2(int angle1);
void data_judge(int temp2);
void data_manage(void);
void carControl(void);
int send_data_to(char num);//���ڷ���ָ�����


uint8_t Usart1_tx,Usart1_rx,tx2;
uint8_t Usart1_Buffer[10];
static int Usart_sta=0;
int temp0,temp1=0;
signed int dd_H,dd_L,dd_sum,dd_aver,an_sum,an_aver;
int an_1,an_2;
int angle,dd,angle1,dd1;
int dd_group[500],dd_error[500],an_group[500],an_error[500];


 int main(void)
 {		
// 	u16 t;  
//	u16 len;	
//	u16 times=0;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
 	while(1)
	{
                             
                          data_get_main();
														
														if(Usart_sta==1)
														{
															data_judge(Usart1_tx);
															data_manage();
//															printf("distance= %d",dd);
//															printf("\n");
//															printf("angle= %d",angle);
//															printf("\n");
														//	delay_ms (10); 
															carControl();
															
															
//															if (dd < 10)
//															{
//											                  send_data_to(0xff);
//																				send_data_to(0xfe);
//																				send_data_to(0x01);
//																				send_data_to(0x00);
//																				send_data_to(0x00);
//																				send_data_to(0x00);
//																				send_data_to(0x00);
//																				send_data_to(0x00);
//																				send_data_to(0x00);
//																				send_data_to(0x00);
//															}
//															else 
//															{
//															
//															if (angle>65000 || angle<100)
//																		{
//////																			if (dd > 10)
//////																			{
//																				send_data_to(0xff);
//																				send_data_to(0xfe);
//																				send_data_to(0x01);
//																				send_data_to(0x00);
//																				send_data_to(0x00);
//																				send_data_to(0x00);
//																				send_data_to(0x05);
//																				send_data_to(0x00);
//																				send_data_to(0x00);
//																				send_data_to(0x00);
//////																			} else
//////																			{
////																				send_data_to(0xff);
////																				send_data_to(0xfe);
////																				send_data_to(0x01);
////																				send_data_to(0x00);
////																				send_data_to(0x00);
////																				send_data_to(0x00);
////																				send_data_to(0x00);
////																				send_data_to(0x00);
////																				send_data_to(0x00);
////																				send_data_to(0x00);
//////																			}
//																		}
//																			else if (angle > 100 || angle < 30000)
//																				{
//////																					if (dd > 10)
//////																					{
//																						send_data_to(0xff);
//																						send_data_to(0xfe);
//																						send_data_to(0x01);
//																						send_data_to(0x00);
//																						send_data_to(0x05);
//																						send_data_to(0x00);
//																						send_data_to(0x00);
//																						send_data_to(0x00);
//																						send_data_to(0x00);
//																						send_data_to(0x00);
//////																					} else
//////																					{
////																						send_data_to(0xff);
////																						send_data_to(0xfe);
////																						send_data_to(0x01);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
//////																					}
//																				}
//																				
//																				else  
//																				{
//////																					if (dd > 10)
//////																					{
//																						send_data_to(0xff);
//																						send_data_to(0xfe);
//																						send_data_to(0x01);
//																						send_data_to(0x00);
//																						send_data_to(0x05);
//																						send_data_to(0x00);
//																						send_data_to(0x00);
//																						send_data_to(0x00);
//																						send_data_to(0x00);
//																						send_data_to(0x04);
//////																					} else
//////																					{
////																						send_data_to(0xff);
////																						send_data_to(0xfe);
////																						send_data_to(0x01);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
////																						send_data_to(0x00);
//////																					}
//																				}
//																			}															
//                                  

			//printf("���");					//���Գɹ� ���Խ���


	                               }	 
    }
 
	}
 
 
 
 void data_get_main()
{
	int time1=0,time2=0,time3=0,time4=0,time5=0,time6=0,time7=0,time8=0;//����ѭ������
	
	for(time1=0;time1<1;time1++)//���ݻ�ȡѭ����time1�Ƚϵ�ֵΪ��ȡ����
	{
		Usart1_rx=0;
		delay_ms(10);
		for(temp0=0,temp1=0;temp0<10;temp0++)
		{
			if(Usart1_Buffer[temp0]==0xD6 && Usart1_Buffer[temp0+1]==0x6D)
			{
				Usart_sta=1;
				Usart1_tx=temp0;
				data_judge(Usart1_tx);
				dd=(int)(Usart1_Buffer[dd_H]*16*16+Usart1_Buffer[dd_L]);
				angle=(int)(Usart1_Buffer[an_1]-Usart1_Buffer[an_2]);
				dd_group[temp1]=dd;
				an_group[temp1]=angle;
				temp1++;
			}
		}
	}

	for(time2=0;time2<temp1;time2++)//ƽ��ֵԤ��
	{
		dd_sum+=dd_group[time2];
		an_sum+=an_group[time2];
	}
	dd_aver=dd_sum/temp1;
	an_aver=an_sum/temp1;
	
	for(time4=0;time4<temp1;time4++)//�������ɸѡ
	{
		if((dd_group[time4]>=(dd_aver*1.2))||(dd_group[time4]<=(dd_aver*0.8)))
		{
			dd_error[time3]=dd_group[time4];
			time3++;
		}
	}
	
	for(time5=0;time5<temp1;time5++)//�Ƕ����ɸѡ
	{
		if((an_group[time5]>=(an_aver*1.2))||(an_group[time5]<=(an_aver*0.8)))
		{
			an_error[time6]=an_group[time5];
			time6++;
		}
	}
	for(time7=0;time7<time3;time7++)//��������޳�
	{
		dd_sum=dd_sum-dd_error[time7];
	}
	dd_aver=dd_sum/(temp1-time3);
	dd_sum=0;
	
//	printf("distance_avr= %d\n",dd_aver);
				
	for(time8=0;time8<time6;time8++)//�Ƕ�����޳�
	{
		an_sum=an_sum-an_error[time8];
	}
	an_aver=an_sum/(temp1-time6);
	an_sum=0;
//	printf("angle_avr= %d",an_aver);
	
}
	




void data_judge(int temp2)//����λ�����б��� 
						
{
	dd_H=temp2+3;
	dd_L=temp2+2;
	an_2=temp2+5;
	an_1=temp2+4;
	
	if(dd_H>=10)
	{
		dd_H=dd_H-10;
	}
	if(dd_L>=10)
	{
		dd_L=dd_L-10;
	}
	if(an_1>=10)
	{
		an_1=an_1-10;
	}
	if(an_2>=10)
	{
		an_2=an_2-10;
	}
}
void data_manage()
{
	dd=(int)(Usart1_Buffer[dd_H]*16*16+Usart1_Buffer[dd_L]);
	angle=(int)(Usart1_Buffer[an_1]-Usart1_Buffer[an_2]);
	
//				printf("distance= %d\n",dd);
//				printf("angle= %d\n",angle);
			 
}	













void carControl(void)
{
	
		 
	if (angle>-35 && angle<35)
	{
		if (dd > 100 && dd < 2000)
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		} else
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		}
	}
	
	else if (angle > 35 && angle < 75)
	{
		if (dd > 100 && dd < 2000)
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		} else
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		}
	}
	else if (angle > 75 && angle < 110)
	{
		if (dd > 100 && dd < 2000)
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		} else
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		}
	}
	
	else if (angle > 110 && angle < 135)
	{
		if (dd > 100 && dd < 2000)
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x02);
		} else
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		}
	}
	
	else if (angle < -35 && angle >-75 )
	{
		if (dd > 100 && dd < 2000)
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x04);
		} else
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		}
	}
	
	else if (angle > -110 && angle < -75)
	{
		if (dd > 100 && dd < 2000)
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x04);
		} else
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		}
	}
	
	
	else if (angle > -135 && angle < -110)
	{
		if (dd > 100 && dd < 2000)
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x06);
		} else
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		}
	}
	
	
	else if (angle < -120 || angle >120 )
	{
		if (dd > 100 && dd < 2000)
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x01);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x0c);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x02);
		} else
		{
			send_data_to(0xff);
			send_data_to(0xfe);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
			send_data_to(0x00);
		}
	}
	}




int send_data_to(char num)//���ڷ���ָ�����
{
	USART_SendData(USART1, num);//�򴮿�1��������
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	return 0;
}
	
