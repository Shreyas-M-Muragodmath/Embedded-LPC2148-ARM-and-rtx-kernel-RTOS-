//CODE BY SHREYAS

#include <RTL.h>                      
#include <LPC21xx.h>                  
#include <stdio.h>
#define DESIRED_COUNT	1000			// for 1sec
#define PRESCALER	11999

void InitTimer0(void);


__task void task1 (void);
__task void task2(void);
void init_serial (void);
void delay(void);       

OS_TID tsk1, tsk2;
OS_SEM semaphore1;


unsigned int i=0;
unsigned char k,mg;
unsigned int count=0;

unsigned char m[]="press 1 for monday time table\r\n";
unsigned char t[]="press 2 for tuesday time table\r\n";
unsigned char w[]="press 3 for wednesday time table\r\n";

unsigned char mon[]="monday\r\n";
unsigned char mons1[]="M subject 1\r\n";
unsigned char mont1[]="M teacher 1\r\n";
unsigned char mons1time[]="8:00 to 10:00\r\n";

unsigned char tue[]="tuesday\r\n";
unsigned char tues1[]="T subject 2\r\n";
unsigned char tuet1[]="T teacher 2\r\n";
unsigned char tues1time[]="01:30 to 03:30\r\n";

unsigned char wed[]="wednesday\r\n";
unsigned char weds1[]="W subject 3\r\n";
unsigned char wedt1[]="W teacher 3\r\n";
unsigned char weds1time[]="10:15 to 12:15\r\n";

unsigned char msg[]="not valid\r\n";

__task void task1 (void) {
 
OS_RESULT ret;
os_tsk_prio_self(2);
tsk2 = os_tsk_create (task2, 0);
while (1){

     ret = os_sem_wait (semaphore1, 0x0f);
	   delay();	  delay();  delay();
	   init_serial();
	   if(mg=='1'){
	   	   if (ret == OS_R_SEM)
			{
				while (mon[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = mon[i];
			    	i++;
			    }
			    i=0;
					
					while (mons1[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = mons1[i];
			    	i++;
			    }
			    i=0;
					
					while (mont1[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = mont1[i];
			    	i++;
			    }
			    i=0;
					
					while (mons1time[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = mons1time[i];
			    	i++;
			    }
			    i=0;
					
					
     
			    os_sem_send (semaphore1);
			}
	   }

	   else if(mg=='2'){
	   	   if (ret == OS_R_SEM)
			{
				while (tue[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = tue[i];
			    	i++;
			    }
			    i=0;
					
					while (tues1[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = tues1[i];
			    	i++;
			    }
			    i=0;
					
					while (tuet1[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = tuet1[i];
			    	i++;
					}
			    i=0;

					while (tues1time[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = tues1time[i];
			    	i++;
			    }
			    i=0;
			     
			    os_sem_send (semaphore1);
			}	   	
		}
	   

	   else if(mg=='3'){
	   	  	   	   if (ret == OS_R_SEM)
			{
				while (wed[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = wed[i];
			    	i++;
			    }
			    i=0;
					
					while (weds1[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = weds1[i];
			    	i++;
			    }
			    i=0;
					
					while (wedt1[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = wedt1[i];
			    	i++;
					}
			    i=0;

					while (weds1time[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = weds1time[i];
			    	i++;
			    }
			    i=0;
			     
			    os_sem_send (semaphore1);
			}	   	
		}
			
	   

	   else{
	   	   if (ret == OS_R_SEM)
			{
				while (msg[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = msg[i];
			    	i++;
			    }
			    i=0;
					     
			    os_sem_send (semaphore1);
			}	   		
		
	   }

	 	
}
}

__task void task2 (void) {
 
  while (1)
{

while (m[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = m[i];
			    	i++;
			    }
			    i=0;

while (t[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = t[i];
			    	i++;
			    }
			    i=0;

while (w[i] != '\0')
			    {
			     	while (!(U0LSR & 0x20));
			     	U0THR = w[i];
			    	i++;
			    }
			    i=0;					
	
	
	
while(!(U0LSR & 0x01));
mg=U0RBR;

os_sem_send (semaphore1);
   
}
   
}
 


void init_serial (void) {
  PINSEL0 = 0X0000005;                              
  U0LCR = 0x83;                            
  U0DLL = 0x61;                            
  U0LCR = 0x03;                                                
}


int main (void)
{
  
   
  
  os_sem_init (semaphore1, 1);
 
  os_sys_init (task1);
}


void delay(void)
{ unsigned long int j;
for(j=0;j<650000;j++);
}


