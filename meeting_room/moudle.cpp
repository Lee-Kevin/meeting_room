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

#define PIR_CLEAR_TIME 60

MoudleStateStruct MoudleState;
uint16_t IRQ_Time = 0;
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
   IRQ_Time = MoudleState.min*60+MoudleState.sec;
   Serial.println("pir ...");
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

}

void MoudleClass::KeyProc(void)
{
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
  
	if(key1==0 && lastkey1==1)
	{
	  MoudleState.button |= 0X01; 
	}
	if(key2==0 && lastkey2==1)
	{
	  MoudleState.button |= (0X01<<1); 
	}
	if(key3==0 && lastkey3==1)
	{
	  MoudleState.button |= (0X01<<2); 
	}
	if(key4==0 && lastkey4==1)
	{
	  MoudleState.button |= (0X01<<3); 
	}
	if(key5==0 && lastkey5==1)
	{
	  MoudleState.button |= (0X01<<4); 
	}
	if(key6 ==0 && lastkey6==1)
	{
	  MoudleState.button |= (0X01<<5); 
	}
	if(key7==0 && lastkey7==1)
	{
	  MoudleState.button |= (0X01<<6); 
	}
	if(key8==0 && lastkey8==1)
	{
	  MoudleState.button |= (0X01<<7); 
	}
	if(key8==0 && lastkey8==1)
	{
	  MoudleState.button |= (0X01<<8); 
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

void MoudleClass::LightInit(void)
{
  _Light.Begin();
}


void MoudleClass::GetLight(void)
{
  MoudleState.light = _Light.ReadVisible();
}

void MoudleClass::PIR_ClearState(void)
{
	uint16_t timetmp;
	timetmp = MoudleState.min*60+MoudleState.sec;
	
	if(timetmp - IRQ_Time >= PIR_CLEAR_TIME)
	{
	  MoudleState.PIR_State = 0;
	}
}
/*------------------------------------------------------------------
Loop

*/
void MoudleClass::MoudleInit(void)
{
  PIRInit();
  BuzzerInit();
  KeyInit();
  LightInit();
}

void MoudleClass::Loop(void)
{
	GetClock();
	KeyProc();
	GetLight();
}




