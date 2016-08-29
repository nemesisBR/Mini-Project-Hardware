
#include<p18f4520.h>
#pragma config OSC=HS
#pragma config WDT=OFF
#pragma config LVP=OFF
#define ldata PORTD
#define rs PORTEbits.RE0
#define rw PORTEbits.RE1
#define en PORTEbits.RE2
#define s1 PORTAbits.RA0
#define s2 PORTAbits.RA1
#define s3 PORTBbits.RB0
#define s4 PORTBbits.RB1
void delay(unsigned char val)
	{
		int i,j;
		for(i=0;i<val;i++)
			for(j=0;j<165;j++);
	}
void motor_rotate_l()
{       CCP1CON=0x0C;  
        T2CON=0x07;
        PORTCbits.RC0=0;
        PORTCbits.RC1=1;
         CCPR1L=0xFD	;
		CCP1CONbits.DC1B0=0;
		CCP1CONbits.DC1B1=1;
        
        
        
        delay(1000);
		
		
        PORTCbits.RC0=0;
        PORTCbits.RC1=0;
}
void motor_rotate_r()
{       CCP1CON=0x0C;  
        T2CON=0x07;
        PORTCbits.RC0=1;
        PORTCbits.RC1=0;
         CCPR1L=0xFD	;
		CCP1CONbits.DC1B0=0;
		CCP1CONbits.DC1B1=1;
               
        
        delay(1000);
		
		
        PORTCbits.RC0=0;
        PORTCbits.RC1=0;
        
        delay(5000);
}
void lcdcmd(unsigned char val)
	{
		ldata=val;
		rs=0;
		rw=0;
		en=1;
		delay(10);
		en=0;
	}
void lcddata(unsigned char val)
	{
		ldata=val;
		rs=1;
		rw=0;
		en=1;
		delay(10);
		en=0;
	}




char dataread()
{
    
   while(!PIR1bits.RCIF);
   

return RCREG; 
}
	
   


void TRANS(char data)
	{
		while(TXSTAbits.TRMT==0);
		TXREG=data;
	} 


void main(void)
{   
     
	unsigned char i,c[10],p;
   unsigned char k[]={"1234"};
   unsigned char nv[]={"NO VACANT SLOTS"};
    unsigned char b[]={" SLOT:"};
    unsigned char P_Slot[4];
	unsigned char a[]={"Ya"};
    
    unsigned char A[10] = {'\0'};
    TRISCbits.TRISC2=0;
	TRISCbits.TRISC0=0;
	TRISCbits.TRISC1=0;
	
    TRISAbits.TRISA0=1;
    TRISAbits.TRISA1=1;
    TRISBbits.TRISB0=1;      
	TRISBbits.TRISB1=1;
            
    PR2=0xBB;

	
    ADCON1=0x0F;
	TRISD=0x00;
    TRISE=0x00;
	TRISB=0x00;
     while(1)
    {
    lcdcmd(0x38);
	lcdcmd(0x0E);
	lcdcmd(0x06);
	lcdcmd(0x01);
	lcdcmd(0x80);

     
	SPBRGH=0x01;
	SPBRG=0x38;
	TXSTA=0b00100100;
	RCSTAbits.SPEN=1;
	BAUDCONbits.BRG16=1;
	
	TRISCbits.TRISC6=0;
	TRISCbits.TRISC7=1;
   
  	for(i=0;a[i]!='\0';i++)
    {
    TRANS(a[i]);
    }
   TXSTAbits.TXEN=0;
   
   
   
    RCSTAbits.CREN=1;
    
      for(i=0;i<10;i++)
    {
          
    c[i]=dataread();   
      
    }
    
    c[10]='\0';
   RCSTAbits.CREN=0;
   if(s1==1)
       P_Slot[0]=1;
   else if(s1==0) 
       P_Slot[0]=0;
       
    if(s2==1)
       P_Slot[1]=1;
   else if(s2==0) 
       P_Slot[1]=0;
    
    if(s3==1)
       P_Slot[2]=1;
   else if(s3==0) 
       P_Slot[2]=0;
    
    if(s4==1)
       P_Slot[3]=1;
   else if(s4==0) 
       P_Slot[3]=0;
   
   
    for(i=0;i<10;i++)
    {   
    lcddata(c[i]);
    delay(100);
    }
   lcdcmd(0xC0);
   
   for(i=0;i<4;i++)
    {
       if(P_Slot[i]==0)
       {  p=i;
          break;
       }
       else
           p=5;
     
      
    }
   if(p!=5)
   {
   for(i=0;i<6;i++)
    {   
    lcddata(b[i]);

    delay(100);
    }
   lcddata(k[p]);
   
   delay(500);
   }
   else
   {
       for(i=0;i<16;i++)
    {   
    lcddata(nv[i]);

    delay(100);
    }
   }
       
  
  motor_rotate_l();
  delay(50000);
  motor_rotate_r();  
  
}
    
}


