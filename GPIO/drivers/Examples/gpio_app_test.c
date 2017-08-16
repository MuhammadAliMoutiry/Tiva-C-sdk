/*
 * main.c
 */
#include "../APP/app_gpio.h"
#include "../SL/NVICInterruptHandler.h"
gGPIOObj_t port;
void interr(void){
	digitalPortWrite(&port,RGB_GREEN);
}


int main(void) {

	uint8 data;

	port.base = BASE_F;
	port.configPadObj.currentVal = CURRENT_2MA;
	port.configPadObj.lockFlag = FALSE;
	//port.configPadObj.resType = PULL_UP_RES;
	port.pin_num = 0;
    port.interruptObj.interruptIndex = GPIOF_IRQ;
    port.interruptObj.interruptSense = LOW_LEVEL;
    port.interruptObj.pendingFlag = FALSE;
    port.interruptObj.priority = 4;
    port.interruptObj.enableInterrupt = TRUE;


	initPort(&port,0b11101110);
	installNIVCISRFunction(GPIOF_IRQ,interr);


	while(1){
		digitalPinRead(&port,&data);
if(data == LOW){
	digitalPortWrite(&port,RGB_RED);
}else
			digitalPortWrite(&port,RGB_BLUE);


	}

	return 0;
}
