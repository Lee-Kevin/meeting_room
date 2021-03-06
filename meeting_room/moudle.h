#ifndef _MOUDLE_H_
#define _MOUDLE_H_

#include "DS1307.h"
#include "SI114X.h"

typedef struct
{
  //Date and time
  uint16_t year;
  uint8_t  month;
  uint8_t  date;
  uint8_t  hour;
  uint8_t  min;
  uint8_t  sec;
  uint8_t  week;
  //button state
  uint16_t  button;
  //Light Intensity state
  uint16_t  LightIntensity;
  //PIR state
  uint8_t PIR_State;
  //LastPIR_State
  uint8_t LastPIR_State;
  //In Use Time
  uint8_t InUseTime;
  //Light Bar state
  uint32_t LightBarState;
  
  
}MoudleStateStruct;



  
class MoudleClass
{
  private:
  DS1307 _DateTime;
  SI114X _Light;
  void PIRInit(void);
  void BuzzerInit(void);
  void KeyInit(void);
  void LightIntensityInit(void);
  
  public:
  void SetClock(uint16_t year,uint8_t month,uint8_t date,uint8_t hour,uint8_t min,uint8_t sec,uint8_t week);
  void SetBuzzerOn(void);
 
  void MoudleInit(void);

  void KeyProc(void);
  void GetLightIntensity(void);
  void GetClock(void);
  void CheckState(void);
  void Loop(void);
};


extern MoudleStateStruct MoudleState;


#endif


