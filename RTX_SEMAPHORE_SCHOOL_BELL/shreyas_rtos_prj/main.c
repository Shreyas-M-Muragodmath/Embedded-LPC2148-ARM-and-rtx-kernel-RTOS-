#include <RTL.h>                      
#include <LPC21xx.h>                  
#include <stdio.h>
#define DESIRED_COUNT	1000			// for 1sec
#define PRESCALER	11999

char arr1[10],arr2[10],arr3[20];
void InitTimer0(void);
void rtc(void)
{
PREINT=0X5A;
PREFRAC=0X46C0;
CCR=0X00;
SEC=1;
MIN=1;
HOUR=8;
CCR=0X01;
}

unsigned int x,y,z;

__task void task1 (void);
__task void task2(void);
void init_serial (void);
void delay(void);       

OS_TID tsk1, tsk2;
OS_SEM semaphore1;


unsigned int i=0,j=0;
unsigned char k;
unsigned int count=0;

unsigned int Disp[16]={0x003F0000, 0x00060000, 0x005B0000, 0x004F0000, 0x00660000,0x006D0000,
  0x007D0000, 0x00070000, 0x007F0000, 0x006F0000, 0x00770000,0x007C0000,
  0x00390000, 0x005E0000, 0x00790000, 0x00710000 };

unsigned char msg1[]="PRAYER\r\n";
unsigned char msg2[]="CLASS 1\r\n";
unsigned char msg3[]="CLASS 2\r\n";
unsigned char msg4[]="HOLIDAY\r\n";

__task void task1 (void) {
 
OS_RESULT ret;
os_tsk_prio_self(2);
tsk2 = os_tsk_create (task2, 0);
while (1){
	 
     ret = os_sem_wait (semaphore1, 0x0f);
	   delay();	  delay();  delay();
	   init_serial();
	   U0THR = '\t';
	   U0THR = '\t';
	   if(count==0){
	   	   if (ret == OS_R_SEM)
			{
				while (msg1[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = msg1[i];
			    	i++;
			    }
			    i=0;
				j=0;
				x=SEC; 	y=MIN; z=HOUR;
				U0THR='\n';
				sprintf(arr1,"\n\tsec:%d\n\t",x);
				U0THR='\n';
  					while (arr1[j] != '\0')
					{	 
	  					while (!(U0LSR & 0x20));
	  					U0THR = arr1[j];
						j++;
					}
					U0THR='\n';


			IO0DIR=0x00000020;
			IO0SET=0X00000020;
			delay(); delay();delay();delay();
			IO0CLR=0x00000020;
     
			    os_sem_send (semaphore1);
			}
	   }

	   else if(count==1){
	   	   if (ret == OS_R_SEM)
			{
				while (msg2[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = msg2[i];
			    	i++;
					
				 }
			    i=0;
				j=0;
	   			x=SEC; 	y=MIN; z=HOUR;
				U0THR='\n';
  	   			sprintf(arr1,"\n\tsec:%d\n\t",x);
				U0THR='\n';
  				while (arr1[j] != '\0')
				{	 
	  				while (!(U0LSR & 0x20));
	  				U0THR = arr1[j];
					j++;
				}
				U0THR='\n';

			    
				
			IO0DIR=0x00000020;
			IO0SET=0X00000020;
			delay(); delay();delay();delay();
			IO0CLR=0x00000020;
			     
			    os_sem_send (semaphore1);
			}	   	

	   }

	   else if(count==2){
	   	   if (ret == OS_R_SEM)
			{
			
				while (msg3[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = msg3[i];
			    	i++;
			    }
			    i=0; 
				j=0;
				x=SEC; 	y=MIN; z=HOUR;
				U0THR='\n';
				sprintf(arr1,"\n\tsec:%d\n\t",x);
				U0THR='\n';
  				while (arr1[j] != '\0')
					{	 
	  					while (!(U0LSR & 0x20));
	  					U0THR = arr1[j];
						j++;
					}
					U0THR='\n';

			IO0DIR=0x00000020;
			IO0SET=0X00000020;
			delay(); delay();delay();delay();
			IO0CLR=0x00000020;
    
			    os_sem_send (semaphore1);
			}	   		
			
	   }

	   else{
	   	   if (ret == OS_R_SEM)
			{
				while (msg4[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = msg4[i];
			    	i++;
			    }
			    i=0;
				j=0;
				x=SEC; 	y=MIN; z=HOUR;
				U0THR='\n';
				sprintf(arr1,"\n\tsec:%d\n\t",x);
				U0THR='\n';
  				while (arr1[j] != '\0')
				{	 
	  				while (!(U0LSR & 0x20));
	  				U0THR = arr1[j];
					j++;
				}
				U0THR='\n';

				
			IO0DIR=0x00000020;
			IO0SET=0X00000020;
			delay(); delay();delay();delay();
			IO0CLR=0x00000020;

			break;	     
			   // os_sem_send (semaphore1);
			}	   		
		
	   }

	 	
}
}

__task void task2 (void) {
 
  while (1)
  {

if(count==0){
	os_sem_send (semaphore1);	
} 


	PINSEL0 = 0X00000000 ;			// Configure P0.16-p0.23 as GPIO
	IODIR0=0X00FF0000;
	InitTimer0();  					// initialise timer0 - 
	T0TCR = 0x01;					// start timer

for(k=0;k<7;k++)
{
IOCLR0=0x00ff0000;
IODIR0=0x10ff0000; 
IOSET0=0x10000000;
while(!( T0IR==0x01));			   // wait for overflow
T0IR=0x01;						  // clear flag
IOSET0=Disp[k];   
delay();
delay();
IOCLR0=0x00ff0000;
}
count++;
os_sem_send (semaphore1);
   
}
   
}
 
void InitTimer0(void)
{
		 	
	T0PR=PRESCALER;
	T0MR0=DESIRED_COUNT;	//interrupt every 1 sec for interval = 1000
	T0MCR=3;		//interrupt and reset when counter=match
	T0TCR=2;		 //	reset timer
   
}

void init_serial (void) {
  PINSEL0 = 0X0000005;                              
  U0LCR = 0x83;                            
  U0DLL = 0x61;                            
  U0LCR = 0x03;                                                
}


int main (void)
 {
  
  rtc(); 
  
  os_sem_init (semaphore1, 1);
 
  os_sys_init (task1);
}


void delay(void)
{ unsigned long int j;
for(j=0;j<650000;j++);
}


