#include "inc/lm4f120h5qr.h"

#include <stdint.h>
#include <stdlib.h>
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#define LCD_H_

#define LCDPORT                  GPIO_PORTB_BASE
#define LCDPORTENABLE    SYSCTL_PERIPH_GPIOB
#define RS                               GPIO_PIN_0
#define E                                GPIO_PIN_1
#define D4                               GPIO_PIN_4
#define D5                               GPIO_PIN_5
#define D6                               GPIO_PIN_6
#define D7                               GPIO_PIN_7


void Lcd_Komut(unsigned char);  //Lcd ye komut göndermeye yarar    internetten alınmıstır
void Lcd_Temizle(void);                 //Lcd ekranını temizler    internetten alınmıstır
void Lcd_Puts(char*);                   //String ifade yazdırır    internetten alınmıstır
void Lcd_Goto(char,char);               //Kursorü istenilen yere gönderir internetten alınmıstır
void Lcd_init(void);                    //Lcd başlangıç ayarları   internetten alınmıstır
void Lcd_Putch(unsigned char);  //Tek karekter yazdırır            internetten alınmıstır



void Lcd_init() {

        SysCtlPeripheralEnable(LCDPORTENABLE);
        GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

        SysCtlDelay(30000);

        GPIOPinWrite(LCDPORT, RS,  0x00 );

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(30000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(30000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(30000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x20 );
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(30000);

        Lcd_Komut(0x28);
        Lcd_Komut(0xC0);
        Lcd_Komut(0x06);
        Lcd_Komut(0x80);
        Lcd_Komut(0x28);
        Lcd_Komut(0x0f);
        Lcd_Temizle();

}
void Lcd_Komut(unsigned char c) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(50000);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x00);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(50000);

}

void Lcd_Putch(unsigned char d) {

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0xf0) );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(30000);

        GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (d & 0x0f) << 4 );
        GPIOPinWrite(LCDPORT, RS, 0x01);
        GPIOPinWrite(LCDPORT, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(LCDPORT, E, 0x00);

        SysCtlDelay(30000);

}
void Lcd_Goto(char x, char y){

        if(x==1)
                Lcd_Komut(0x80+((y-1)%16));
        else
                Lcd_Komut(0xC0+((y-1)%16));
}

void Lcd_Temizle(void){
        Lcd_Komut(0x01);
        SysCtlDelay(10);
}

void Lcd_Puts( char* s){

        while(*s)
                Lcd_Putch(*s++);
}

void PortE_init() {
   volatile unsigned long tmp;
   SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
   tmp = SYSCTL_RCGCGPIO_R;
   GPIO_PORTE_LOCK_R = 0x4C4F434B;
   GPIO_PORTE_CR_R = 0x3F;
   GPIO_PORTE_AMSEL_R = 0x00;
   GPIO_PORTE_PCTL_R = 0x00000000;
   GPIO_PORTE_DIR_R = 0x00;
   GPIO_PORTE_AFSEL_R = 0x00;
   GPIO_PORTE_PUR_R = 0x3F;
   GPIO_PORTE_DEN_R = 0x3F;
   }

void PortA_init(){
	volatile unsigned long tmp;
	SYSCTL_RCGC2_R |=SYSCTL_RCGC2_GPIOA;
	tmp=SYSCTL_RCGC2_R;
	GPIO_PORTA_DIR_R|=0xFF;
	GPIO_PORTA_AFSEL_R |=~0xFF;
	GPIO_PORTA_DEN_R |=0xFF;
}


int main(void) {
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

	volatile unsigned long delay;

	PortE_init();
	PortA_init();
	int but1,but2,but3,but4,but5,but6,i;
	int count=0;
	int count2=0;
	int count3=0;
	int count4=0;
	int countres=0;

	int bolum1 = 0, kalan1;
	int kalan2;
	int kalan3;
	int kalan4;


	Lcd_init();
	Lcd_Goto(1,12);
	Lcd_Puts("00 00");


	while (1){

		but1=GPIO_PORTE_DATA_R & 0x10;
		but2=GPIO_PORTE_DATA_R & 0x20;
		but3=GPIO_PORTE_DATA_R & 0x08;
		but4=GPIO_PORTE_DATA_R & 0x04;
		but5=GPIO_PORTE_DATA_R & 0x02;
		but6=GPIO_PORTE_DATA_R & 0x01;

	    for(i=0;i<1000000;i++);



	 		if (but1!=0x10){
	 			count++;

	 			GPIO_PORTA_DATA_R |= 0x04;
	 			SysCtlDelay(4000000);
	 			GPIO_PORTA_DATA_R = 0x00;

	 			if(count==1){
			//Lcd_Temizle();

	 			Lcd_Goto(1,12);
	 			Lcd_Puts("1");

			}
	 			else if(count==2){

	 				Lcd_Goto(1,12);
	 				Lcd_Puts("2");
	 			}
	 			else if(count==3){

	 				Lcd_Goto(1,12);
	 				Lcd_Puts("3");
	 			}
	 			else if(count==4){

	 				Lcd_Goto(1,12);
	 				Lcd_Puts("4");
	 			}
	 			else if(count==5){

	 				Lcd_Goto(1,12);
	 				Lcd_Puts("5");
	 			}
	 			else if(count==6){
	 				Lcd_Goto(1,12);
	 				Lcd_Puts("6");
	 			}
	 			else if(count==7){
	 				Lcd_Goto(1,12);
	 				Lcd_Puts("7");
	 			}
	 			else if(count==8){
	 				Lcd_Goto(1,12);
	 				Lcd_Puts("8");
	 			}
	 			else if(count==9){
	 				Lcd_Goto(1,12);
	 				Lcd_Puts("9");
	 			}
	 			else if(count>9){
	 				Lcd_Goto(1,12);
	 				Lcd_Puts("0");
	 				count=0;
	 			}


	 		}

		else if (but2!=0x20){
			count2++;
		GPIO_PORTA_DATA_R |= 0x08;
		SysCtlDelay(4000000);
		GPIO_PORTA_DATA_R = 0x00;

		if(count2==1){

			Lcd_Goto(1,13);
			Lcd_Puts("1");

		}
		else if(count2==2){

			Lcd_Goto(1,13);
			Lcd_Puts("2");
			}
		else if(count2==3){

			Lcd_Goto(1,13);
			Lcd_Puts("3");
		}
		else if(count2==4){
			Lcd_Goto(1,13);
			Lcd_Puts("4");

		}
		else if(count2==5){
			Lcd_Goto(1,13);
			Lcd_Puts("5");
		}
		else if(count2==6){
			Lcd_Goto(1,13);
			Lcd_Puts("6");
		}
		else if(count2==7){
			Lcd_Goto(1,13);
			Lcd_Puts("7");
		}
		else if(count2==8){
			Lcd_Goto(1,13);
			Lcd_Puts("8");
		}

		else if(count2==9){
			Lcd_Goto(1,13);
			Lcd_Puts("9");
		}
		else if (count2>9){
			Lcd_Goto(1,13);
			Lcd_Puts("0");
			count2=0;
		}





	}
		else if(but3!=0x08){
			countres++;
			GPIO_PORTA_DATA_R |= 0x10;
			SysCtlDelay(4000000);
			GPIO_PORTA_DATA_R = 0x00;
			if(countres==1){
				Lcd_Goto(1,14);
				Lcd_Puts(".");
				}
			else {
				for(i=0;i<7000000;i++);
				Lcd_Temizle();
				count=0;
				countres=0;
				count2=0;
				count3=0;
				count4=0;
				Lcd_Goto(1,12);
				Lcd_Puts("00 00");
			}




}
		else if(but4!=0x04){
			count3++;
			GPIO_PORTA_DATA_R |= 0x20;
			SysCtlDelay(4000000);
			GPIO_PORTA_DATA_R = 0x00;

			if(count3==1){
				Lcd_Goto(1,15);
				Lcd_Puts("1");

			}
			else if(count3==2){
				Lcd_Goto(1,15);
				Lcd_Puts("2");
			}
			else if(count3==3){
				Lcd_Goto(1,15);
				Lcd_Puts("3");
			}
			else if(count3==4){
				Lcd_Goto(1,15);
				Lcd_Puts("4");
			}
			else if(count3==5){
				Lcd_Goto(1,15);
				Lcd_Puts("5");
			}
			else if(count3==6){
				Lcd_Goto(1,15);
				Lcd_Puts("6");
			}
			else if(count3==7){
				Lcd_Goto(1,15);
				Lcd_Puts("7");
			}
			else if (count3==8){
				Lcd_Goto(1,15);
				Lcd_Puts("8");
			}
			else if(count3==9){
				Lcd_Goto(1,15);
				Lcd_Puts("9");
			}
			else if (count3>9){
				Lcd_Goto(1,15);
				Lcd_Puts("0");
				count3=0;
			}


		}
		else if(but5!=0x02){
			count4++;
			GPIO_PORTA_DATA_R |= 0x40;
			SysCtlDelay(4000000);
			GPIO_PORTA_DATA_R = 0x00;


			if(count4==1){
				Lcd_Goto(1,16);
				Lcd_Puts("1");
			}
			else if(count4==2){
				Lcd_Goto(1,16);
				Lcd_Puts("2");
			}
			else if(count4==3){
				Lcd_Goto(1,16);
				Lcd_Puts("3");
			}
			else if (count4==4){
				Lcd_Goto(1,16);
				Lcd_Puts("4");
			}
			else if(count4==5){
				Lcd_Goto(1,16);
				Lcd_Puts("5");
			}
			else if (count4==6){
				Lcd_Goto(1,16);
				Lcd_Puts("6");
			}
			else if (count4==7){
				Lcd_Goto(1,16);
				Lcd_Puts("7");
			}
			else if (count4==8){
				Lcd_Goto(1,16);
				Lcd_Puts("8");
			}
			else if(count4==9){
				Lcd_Goto(1,16);
				Lcd_Puts("9");
			}

			else if (count4>9){
				Lcd_Goto(1,16);
				Lcd_Puts("0");
				count4=0;
			}


		}

		else if(but6!= 0x01){

					GPIO_PORTA_DATA_R |= 0x80;
					SysCtlDelay(4000000);
					GPIO_PORTA_DATA_R = 0x00;

					if(count>=2){

								bolum1 = count/2;
								kalan1 = count%2;
								if(bolum1 ==4){
									Lcd_Goto(2,1);
									Lcd_Puts("4 yirmilik  ");
									if(kalan1 ==1){
									SysCtlDelay(40000000);
									Lcd_Goto(1,12);
									Lcd_Puts("1");
									SysCtlDelay(40000000);
									Lcd_Goto(2,1);
									Lcd_Puts("1 onluk     ");
									SysCtlDelay(40000000);
									Lcd_Goto(1,12);
									Lcd_Puts("0");
									SysCtlDelay(40000000);

									}
									else if(kalan1 ==0){

									SysCtlDelay(40000000);
									Lcd_Goto(1,12);
									Lcd_Puts("0");
									SysCtlDelay(40000000);

		   						   	}

								}
								else if(bolum1 == 3){
									Lcd_Goto(2,1);
									Lcd_Puts("3 yirmilik  ");
									if(kalan1 ==1){
									SysCtlDelay(40000000);
									Lcd_Goto(1,12);
									Lcd_Puts("1");
									SysCtlDelay(40000000);
									Lcd_Goto(2,1);
									Lcd_Puts("1 onluk    ");
									SysCtlDelay(40000000);
									Lcd_Goto(1,12);
									Lcd_Puts("0");
									SysCtlDelay(40000000);

		                                                 	}
									else if(kalan1 ==0){

										SysCtlDelay(40000000);
										Lcd_Goto(1,12);
										Lcd_Puts("0");
										SysCtlDelay(40000000);

										}
								}
								else if (bolum1 == 2){
									Lcd_Goto(2,1);
									Lcd_Puts("2 yirmilik  ");
									if(kalan1 ==1){
										SysCtlDelay(40000000);
										Lcd_Goto(1,12);
										Lcd_Puts("1");
										SysCtlDelay(40000000);
										Lcd_Goto(2,1);
										Lcd_Puts("1 onluk     ");
										SysCtlDelay(40000000);
										Lcd_Goto(1,12);
										Lcd_Puts("0");
										SysCtlDelay(40000000);


									}
									else if(kalan1 ==0){

									SysCtlDelay(40000000);
									Lcd_Goto(1,12);
									Lcd_Puts("0");
									SysCtlDelay(40000000);

									}
								}
								else if (bolum1 == 1){
									Lcd_Goto(2,1);
									Lcd_Puts("1 yirmilik   ");
									if(kalan1 ==1){
										SysCtlDelay(40000000);
										Lcd_Goto(1,12);
										Lcd_Puts("1");
										SysCtlDelay(40000000);
										Lcd_Goto(2,1);
										Lcd_Puts("1 onluk     ");
										SysCtlDelay(40000000);
										Lcd_Goto(1,12);
										Lcd_Puts("0");
										SysCtlDelay(40000000);

									}
										else if(kalan1 ==0){

										SysCtlDelay(40000000);
										Lcd_Goto(1,12);
										Lcd_Puts("0");
										SysCtlDelay(40000000);

										}
								}


							}

							else if (count==1){
								Lcd_Goto(2,1);
								Lcd_Puts("1 onluk      ");
								SysCtlDelay(40000000);
								Lcd_Goto(1,12);
								Lcd_Puts("0");

							}
							else if(count == 0){
								Lcd_Goto(2,1);
								Lcd_Puts("          ");
								SysCtlDelay(40000000);
							}

							kalan2 = count2%5;
							if(count2>=5){
								Lcd_Goto(2,1);
								Lcd_Puts("1 beslik     ");
							}
							if(kalan2==4){
								SysCtlDelay(40000000);
								Lcd_Goto(1,13);
								Lcd_Puts("4");
								SysCtlDelay(40000000);
								Lcd_Goto(2,1);
								Lcd_Puts("4 birlik     ");
								Lcd_Goto(1,13);
								Lcd_Puts("0");

							}
							else if(kalan2==3){
								SysCtlDelay(40000000);
								Lcd_Goto(1,13);
								Lcd_Puts("3");
								SysCtlDelay(40000000);
								Lcd_Goto(2,1);
								Lcd_Puts("3 birlik     ");
								Lcd_Goto(1,13);
								Lcd_Puts("0");

							}
							else if(kalan2==2){
								SysCtlDelay(40000000);
								Lcd_Goto(1,13);
								Lcd_Puts("2");
								SysCtlDelay(40000000);
								Lcd_Goto(2,1);
								Lcd_Puts("2 birlik     ");
								Lcd_Goto(1,13);
								Lcd_Puts("0");
							}
							else if(kalan2==1){
								SysCtlDelay(40000000);
								Lcd_Goto(1,13);
								Lcd_Puts("1");
								SysCtlDelay(40000000);
								Lcd_Goto(2,1);
								Lcd_Puts("1 birlik     ");
								Lcd_Goto(1,13);
								Lcd_Puts("0");

							}
							else if(count2==0){
								SysCtlDelay(40000000);
								Lcd_Goto(1,13);
								Lcd_Puts("0");
								SysCtlDelay(40000000);
								Lcd_Goto(2,1);
								Lcd_Puts("           ");

							}
					kalan3 = count3%5;
					if(count3>=5){
						SysCtlDelay(40000000);
						Lcd_Goto(2,1);
						Lcd_Puts("1 yarimlik   ");
					}

					if(kalan3==4){
						SysCtlDelay(40000000);
						Lcd_Goto(1,15);
						Lcd_Puts("4");
						SysCtlDelay(40000000);
						Lcd_Goto(2,1);
						Lcd_Puts("1 ceyreklik");
						SysCtlDelay(40000000);
						if(count4==9){
							Lcd_Goto(1,15);
							Lcd_Puts("24");
							Lcd_Goto(2,1);
							Lcd_Puts("2 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("4 kurusluk ");
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}

						else if(count4==8){
							Lcd_Goto(1,15);
							Lcd_Puts("23");
							Lcd_Goto(2,1);
							Lcd_Puts("2 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("3 kurusluk ");
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}

						else if(count4==7){
							Lcd_Goto(1,15);
							Lcd_Puts("22");
							Lcd_Goto(2,1);
							Lcd_Puts("2 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("2 kurusluk ");
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}
						else if(count4==6){
							Lcd_Goto(1,15);
							Lcd_Puts("21");
							Lcd_Goto(2,1);
							Lcd_Puts("2 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("1 kurusluk ");
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}
						else if(count4==5){
							Lcd_Goto(1,15);
							Lcd_Puts("20");
							Lcd_Goto(2,1);
							Lcd_Puts("2 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}
						else if(count4==4){
							Lcd_Goto(1,15);
							Lcd_Puts("19");
							Lcd_Goto(2,1);
							Lcd_Puts("1 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("9 kurusluk  ");
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}
						else if(count4==3){
							Lcd_Goto(1,15);
							Lcd_Puts("18");
							Lcd_Goto(2,1);
							Lcd_Puts("1 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("8 kurusluk  ");
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}
						else if(count4==2){
							Lcd_Goto(1,15);
							Lcd_Puts("17");
							Lcd_Goto(2,1);
							Lcd_Puts("1 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("7 kurusluk  ");
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}
						else if(count4==1){
							Lcd_Goto(1,15);
							Lcd_Puts("16");
							Lcd_Goto(2,1);
							Lcd_Puts("1 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("6 kurusluk  ");
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}
						else if(count4==0){
							Lcd_Goto(1,15);
							Lcd_Puts("15");
							Lcd_Goto(2,1);
							Lcd_Puts("1 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("5 kurusluk  ");
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}

					}
						else if(kalan3==3){
								SysCtlDelay(40000000);
								Lcd_Goto(1,15);
								Lcd_Puts("3");
								SysCtlDelay(40000000);
								Lcd_Goto(2,1);
								Lcd_Puts("1 ceyreklik ");
								SysCtlDelay(40000000);
								if(count4==9){
									Lcd_Goto(1,15);
									Lcd_Puts("14");
									Lcd_Goto(2,1);
									Lcd_Puts("1 metalik");
									SysCtlDelay(40000000);
									Lcd_Goto(1,15);
									Lcd_Puts("0");
									Lcd_Goto(2,1);
									Lcd_Puts("4 kurusluk ");
									Lcd_Goto(1,16);
									Lcd_Puts("0");
								}

								else if(count4==8){
									Lcd_Goto(1,15);
									Lcd_Puts("13");
									Lcd_Goto(2,1);
									Lcd_Puts("1 metalik");
									SysCtlDelay(40000000);
									Lcd_Goto(1,15);
									Lcd_Puts("0");
									Lcd_Goto(2,1);
									Lcd_Puts("3 kurusluk ");
									Lcd_Goto(1,16);
									Lcd_Puts("0");
								}

								else if(count4==7){
									Lcd_Goto(1,15);
									Lcd_Puts("12");
									Lcd_Goto(2,1);
									Lcd_Puts("1 metalik");
									SysCtlDelay(40000000);
									Lcd_Goto(1,15);
									Lcd_Puts("0");
									Lcd_Goto(2,1);
									Lcd_Puts("2 kurusluk ");
									Lcd_Goto(1,16);
									Lcd_Puts("0");
								}
								else if(count4==6){
									Lcd_Goto(1,15);
									Lcd_Puts("11");
									Lcd_Goto(2,1);
									Lcd_Puts("1 metalik");
									SysCtlDelay(40000000);
									Lcd_Goto(1,15);
									Lcd_Puts("0");
									Lcd_Goto(2,1);
									Lcd_Puts("1 kurusluk ");
									Lcd_Goto(1,16);
									Lcd_Puts("0");
								}
								else if(count4==5){
									Lcd_Goto(1,15);
									Lcd_Puts("10");
									Lcd_Goto(2,1);
									Lcd_Puts("1 metalik");
									SysCtlDelay(40000000);
									Lcd_Goto(1,15);
									Lcd_Puts("00");
								}
								else if(count4==4){
									SysCtlDelay(40000000);
									Lcd_Goto(1,15);
									Lcd_Puts("09");
									SysCtlDelay(40000000);
									Lcd_Goto(2,1);
									Lcd_Puts("9 kurusluk  ");
									Lcd_Goto(1,15);
									Lcd_Puts("00");
								}
								else if(count4==3){
									SysCtlDelay(40000000);
									Lcd_Goto(1,15);
									Lcd_Puts("08");
									SysCtlDelay(40000000);
									Lcd_Goto(2,1);
									Lcd_Puts("8 kurusluk  ");
									Lcd_Goto(1,15);
									Lcd_Puts("00");
								}
								else if(count4==2){
									SysCtlDelay(40000000);
									Lcd_Goto(1,15);
									Lcd_Puts("07");
									SysCtlDelay(40000000);
									Lcd_Goto(2,1);
									Lcd_Puts("7 kurusluk  ");
									Lcd_Goto(1,15);
									Lcd_Puts("00");
								}
								else if(count4==1){

									SysCtlDelay(40000000);
									Lcd_Goto(1,15);
									Lcd_Puts("06");
									SysCtlDelay(40000000);
									Lcd_Goto(2,1);
									Lcd_Puts("6 kurusluk  ");
									Lcd_Goto(1,15);
									Lcd_Puts("00");
								}
								else if(count4==0){
									SysCtlDelay(40000000);
									Lcd_Goto(1,15);
									Lcd_Puts("05");
									Lcd_Goto(2,1);
									SysCtlDelay(40000000);
									Lcd_Puts("5 kurusluk  ");
									Lcd_Goto(1,15);
									Lcd_Puts("00");
								}


					}
					else if(kalan3==2){
						SysCtlDelay(40000000);
						Lcd_Goto(1,15);
						Lcd_Puts("2");

						if(count4==9){
							Lcd_Goto(2,1);
							Lcd_Puts("1 ceyreklik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("4 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}

						else if(count4==8){
							Lcd_Goto(2,1);
							Lcd_Puts("1 ceyreklik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("3 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}

						else if(count4==7){
							Lcd_Goto(2,1);
							Lcd_Puts("1 ceyreklik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("2 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}
						else if(count4==6){
							Lcd_Goto(2,1);
							Lcd_Puts("1 ceyreklik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("1 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}
						else if(count4==5){
							Lcd_Goto(1,15);
							Lcd_Puts("25");
							Lcd_Goto(2,1);
							Lcd_Puts("1 ceyreklik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}
						else if(count4==4){
							Lcd_Goto(1,15);
							Lcd_Puts("24");
							Lcd_Goto(2,1);
							Lcd_Puts("2 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("4 kurusluk  ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}
						else if(count4==3){
							Lcd_Goto(1,15);
							Lcd_Puts("23");
							Lcd_Goto(2,1);
							Lcd_Puts("2 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("3 kurusluk  ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}
						else if(count4==2){
							Lcd_Goto(1,15);
							Lcd_Puts("22");
							Lcd_Goto(2,1);
							Lcd_Puts("2 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("2 kurusluk  ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}
						else if(count4==1){
							Lcd_Goto(1,15);
							Lcd_Puts("21");
							Lcd_Goto(2,1);
							Lcd_Puts("2 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("0");
							Lcd_Goto(2,1);
							Lcd_Puts("1 kurusluk  ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}
						else if(count4==0){
							Lcd_Goto(1,15);
							Lcd_Puts("20");
							Lcd_Goto(2,1);
							Lcd_Puts("2 metalik");
							SysCtlDelay(40000000);
							Lcd_Goto(1,15);
							Lcd_Puts("00");
						}

					}

					else if(kalan3==1){
						SysCtlDelay(40000000);
						Lcd_Goto(1,15);
						Lcd_Puts("1");
						SysCtlDelay(40000000);
						Lcd_Goto(2,1);
						Lcd_Puts("1 metelik  ");
						SysCtlDelay(40000000);
						Lcd_Goto(1,15);
						Lcd_Puts("0");
						if(count4==9){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("9 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}
						else if(count4==8){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("8 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}

						else if(count4==7){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("7 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}
						else if(count4==6){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("6 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}
						else if(count4==5){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("5 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}
						else if(count4==4){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("4 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}

						else if(count4==3){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("3 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");
						}
						else if(count4==2){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("2 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}
						else if(count4==1){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("1 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}
						else if(count4 ==0){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("           ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}

					}
					else if(count3==0 || count3 ==5){
						SysCtlDelay(40000000);
						Lcd_Goto(1,15);
						Lcd_Puts("0");
						if(count4==9){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("9 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}
						else if(count4==8){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("8 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}

						else if(count4==7){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("7 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}
						else if(count4==6){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("6 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}
						else if(count4==5){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("5 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}
						else if(count4==4){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("4 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}

						else if(count4==3){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("3 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}
						else if(count4==2){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("2 kurusluk  ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}
						else if(count4==1){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("1 kurusluk ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}
						else if(count4 ==0){
							SysCtlDelay(40000000);
							Lcd_Goto(2,1);
							Lcd_Puts("           ");
							SysCtlDelay(40000000);
							Lcd_Goto(1,16);
							Lcd_Puts("0");

						}

					}





}
}
}
