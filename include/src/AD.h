#ifndef AD_H_
#define AD_H_
#include "stdint.h"
extern uint16_t AD_Data0;
extern uint16_t AD_Data1;
extern float AD_V0;
extern float AD_V1;
extern double Height_P;

extern void AD_Read();
extern void Pressure_Read();
extern void Temp_Read();
extern uint16_t SWITCH5V_Input();
extern void SWITCH5V_Output(uint16_t Outputdata);
extern void SWITCH28V_Output(uint16_t Outputdata);

#endif /* RS232_PROCESS_H_ */
