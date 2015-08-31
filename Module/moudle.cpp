#include "moudle.h"


#define BUZZER_PIN 5
#define PIR_IRQ_PIN 0


#define KEY1_PIN 13
#define KEY2_PIN 14
#define KEY3_PIN 15
#define KEY4_PIN 16
#define KEY5_PIN 17
#define KEY6_PIN 18
#define KEY7_PIN 19
#define KEY8_PIN 20
#define KEY9_PIN 21

#define PIR_CLEAR_TIME 10

MoudleStateStruct MoudleState;
uint32_t IRQ_Time = 0;
/*------------------------------------------------------------------
Clock
*/

void MoudleClass::SetClock(uint16_t year,uint8_t month,uint8_t date,uint8_t hour,uint8_t min,uint8_t sec,uint8_t week)
{
  _DateTime.begin();
  _DateTime.fillByYMD(year,month,date);
  _DateTime.fillByHMS(hour,min,sec);
  _DateTime.fillDayOfWeek(week);
  _DateTime.setTime();
}

void MoudleClass::GetClock(void)
{
  _DateTime.getTime();
  MoudleState.year = _DateTime.year+2000;
  MoudleState.month = _DateTime.month;
  MoudleState.date = _DateTime.dayOfMonth;
  MoudleState.hour = _DateTime.hour;
  MoudleState.min = _DateTime.minute;
  MoudleState.sec = _DateTime.second;
  MoudleState.week = _DateTime.dayOfWeek;
}


/*------------------------------------------------------------------
Buzzer
*/

void MoudleClass::BuzzerInit(void)
{
  pinMode(BUZZER_PIN, OUTPUT);
}

void MoudleClass::SetBuzzerOn(void)
{
  digitalWrite(BUZZER_PIN, HIGH); 
  delay(50); 
  digitalWrite(BUZZER_PIN, LOW); 
  delay(50); 
}


/*------------------------------------------------------------------
PIR
*/
void PIR_IRQHandler(void)
{
   MoudleState.PIR_State = 1;
   IRQ_Time = MoudleState.hour*3600 + MoudleState.min*60 + MoudleState.sec;
}

void MoudleClass::PIR_ClearState(void)
{
	uint16_t timetmp;
	timetmp =MoudleState.hour*3600 + MoudleState.min*60+MoudleState.sec;
	InUsetime = (timetmp - IRQ_Time)/60;
	InUsetime = InUsetime >= 99 ? 99 : InUsetime;
	if(timetmp - IRQ_Time >= PIR_CLEAR_TIME)
	{
	  MoudleState.PIR_State = 0;
	  InUsetime = 0;
	}
}


void MoudleClass::PIRInit(void)
{
  attachInterrupt(PIR_IRQ_PIN, PIR_IRQHandler, RISING);
}




/*------------------------------------------------------------------
key
*/
void MoudleClass::KeyInit(void)
{
	
	pinMode(KEY1_PIN, INPUT_PULLUP);
	pinMode(KEY2_PIN, INPUT_PULLUP);
	pinMode(KEY3_PIN, INPUT_PULLUP);
	pinMode(KEY4_PIN, INPUT_PULLUP);
	pinMode(KEY5_PIN, INPUT_PULLUP);
	pinMode(KEY6_PIN, INPUT_PULLUP);
	pinMode(KEY7_PIN, INPUT_PULLUP);
	pinMode(KEY8_PIN, INPUT_PULLUP);
	pinMode(KEY9_PIN, INPUT_PULLUP);

}

void MoudleClass::KeyProc(void)
{
	uint8_t Light_DualBitState;
	
	uint8_t key1=0;static uint8_t lastkey1=1;
	uint8_t key2=0;static uint8_t lastkey2=1;
	uint8_t key3=0;static uint8_t lastkey3=1;
	uint8_t key4=0;static uint8_t lastkey4=1;
	uint8_t key5=0;static uint8_t lastkey5=1;
	uint8_t key6=0;static uint8_t lastkey6=1;
	uint8_t key7=0;static uint8_t lastkey7=1;
	uint8_t key8=0;static uint8_t lastkey8=1;
	uint8_t key9=0;static uint8_t lastkey9=1;

	key1 = digitalRead(KEY1_PIN);
	key2 = digitalRead(KEY2_PIN);
	key3 = digitalRead(KEY3_PIN);
	key4 = digitalRead(KEY4_PIN);
	key5 = digitalRead(KEY5_PIN);
	key6 = digitalRead(KEY6_PIN);
	key7 = digitalRead(KEY7_PIN);
	key8 = digitalRead(KEY8_PIN);
	key9 = digitalRead(KEY9_PIN);
	
    MoudleState.button = 0;
	//
	if(key1==0 && lastkey1==1)
	{
	  MoudleState.button |= 0X01; 
	  Light_DualBitState = MoudleState.LightBarState & 0X00003;
	  
	  switch(Light_DualBitState)
	  {
		  case 0:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X01<<(2*0)) & (~(0X02<<(2*0)));
		  break;
		  case 1:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X20<<(2*0)) & (~(0X01<<(2*0)));
		  break;
		  case 2:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X03<<(2*0));
		  break;
		  case 3:
		    MoudleState.LightBarState = (MoudleState.LightBarState & (~(0X03<<(2*0)));
		  break;
	  }
	}
	//
	if(key2==0 && lastkey2==1)
	{
	  MoudleState.button |= (0X01<<1); 
	  Light_DualBitState = MoudleState.LightBarState & 0X0000C;
	  
	  switch(Light_DualBitState)
	  {
		  case 0:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X01<<(2*1)) & (~(0X02<<(2*1)));
		  break;
		  case 1:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X20<<(2*1)) & (~(0X01<<(2*1)));
		  break;
		  case 2:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X03<<(2*1));
		  break;
		  case 3:
		    MoudleState.LightBarState = (MoudleState.LightBarState & (~(0X03<<(2*1)));
		  break;
	  }
	}
	//
	if(key3==0 && lastkey3==1)
	{
	  MoudleState.button |= (0X01<<2); 
	  Light_DualBitState = MoudleState.LightBarState & 0X00030;
	  
	  switch(Light_DualBitState)
	  {
		  case 0:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X01<<(2*2)) & (~(0X02<<(2*2)));
		  break;
		  case 1:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X20<<(2*2)) & (~(0X01<<(2*2)));
		  break;
		  case 2:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X03<<(2*2));
		  break;
		  case 3:
		    MoudleState.LightBarState = (MoudleState.LightBarState & (~(0X03<<(2*2)));
		  break;
	  }
	}
	//
	if(key4==0 && lastkey4==1)
	{
	  MoudleState.button |= (0X01<<3); 
	  Light_DualBitState = MoudleState.LightBarState & 0X000C0;
	  
	  switch(Light_DualBitState)
	  {
		  case 0:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X01<<(2*3)) & (~(0X02<<(2*3)));
		  break;
		  case 1:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X20<<(2*3)) & (~(0X01<<(2*3)));
		  break;
		  case 2:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X03<<(2*3));
		  break;
		  case 3:
		    MoudleState.LightBarState = (MoudleState.LightBarState & (~(0X03<<(2*3)));
		  break;
	  }
	}
	//
	if(key5==0 && lastkey5==1)
	{
	  MoudleState.button |= (0X01<<4); 
	  Light_DualBitState = MoudleState.LightBarState & 0X00300;
	  
	  switch(Light_DualBitState)
	  {
		  case 0:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X01<<(2*4)) & (~(0X02<<(2*4)));
		  break;
		  case 1:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X20<<(2*4)) & (~(0X01<<(2*4)));
		  break;
		  case 2:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X03<<(2*4));
		  break;
		  case 3:
		    MoudleState.LightBarState = (MoudleState.LightBarState & (~(0X03<<(2*4)));
		  break;
	  }
	}
	//
	if(key6 ==0 && lastkey6==1)
	{
	  MoudleState.button |= (0X01<<5); 
	  Light_DualBitState = MoudleState.LightBarState & 0X00C00;
	  
	  switch(Light_DualBitState)
	  {
		  case 0:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X01<<(2*5)) & (~(0X02<<(2*5)));
		  break;
		  case 1:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X20<<(2*5)) & (~(0X01<<(2*5)));
		  break;
		  case 2:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X03<<(2*5));
		  break;
		  case 3:
		    MoudleState.LightBarState = (MoudleState.LightBarState & (~(0X03<<(2*5)));
		  break;
	  }
	}
	//
	if(key7==0 && lastkey7==1)
	{
	  MoudleState.button |= (0X01<<6); 
	  Light_DualBitState = MoudleState.LightBarState & 0X03000;
	  
	  switch(Light_DualBitState)
	  {
		  case 0:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X01<<(2*6)) & (~(0X02<<(2*6)));
		  break;
		  case 1:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X20<<(2*6)) & (~(0X01<<(2*6)));
		  break;
		  case 2:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X03<<(2*6));
		  break;
		  case 3:
		    MoudleState.LightBarState = (MoudleState.LightBarState & (~(0X03<<(2*6)));
		  break;
	  }
	}
	//
	if(key8==0 && lastkey8==1)
	{
	  MoudleState.button |= (0X01<<7); 
	  Light_DualBitState = MoudleState.LightBarState & 0X0C000;
	  
	  switch(Light_DualBitState)
	  {
		  case 0:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X01<<(2*7)) & (~(0X02<<(2*7)));
		  break;
		  case 1:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X20<<(2*7)) & (~(0X01<<(2*7)));
		  break;
		  case 2:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X03<<(2*7));
		  break;
		  case 3:
		    MoudleState.LightBarState = (MoudleState.LightBarState & (~(0X03<<(2*7)));
		  break;
	  }
	}
	//
	if(key9==0 && lastkey9==1)
	{
	  MoudleState.button |= (0X01<<8); 
	  Light_DualBitState = MoudleState.LightBarState & 0X30000;
	  
	  switch(Light_DualBitState)
	  {
		  case 0:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X01<<(2*8)) & (~(0X02<<(2*8)));
		  break;
		  case 1:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X20<<(2*8)) & (~(0X01<<(2*8)));
		  break;
		  case 2:
		    MoudleState.LightBarState = (MoudleState.LightBarState | (0X03<<(2*8));
		  break;
		  case 3:
		    MoudleState.LightBarState = (MoudleState.LightBarState & (~(0X03<<(2*8)));
		  break;
	  }
	}
	
    lastkey1 = key1;
    lastkey2 = key2;
    lastkey3 = key3;
    lastkey4 = key4;
    lastkey5 = key5;
    lastkey6 = key6;
    lastkey7 = key7;
    lastkey8 = key8;
    lastkey9 = key9;
}

/*------------------------------------------------------------------
Light
*/

void MoudleClass::LightIntensityInit(void)
{
  _Light.Begin();
}


void MoudleClass::GetLightIntensity(void)
{
  MoudleState.LightIntensity = _Light.ReadVisible();
}

/*------------------------------------------------------------------
Loop

*/
void MoudleClass::MoudleInit(void)
{
  PIRInit();
  BuzzerInit();
  KeyInit();
  LightIntensityInit();
}

void MoudleClass::Loop(void)
{
	GetClock();
	KeyProc();
	GetLightIntensity();
	PIR_ClearState();
}




