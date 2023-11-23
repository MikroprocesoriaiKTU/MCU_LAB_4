/**
 ********************************************************************************
 * @file    :4DIG_7SEG_DISPLAY.c
 * @author  :Vytautas Daunoras
 * @date    :2022-10-20
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
//#include "main.h"

//#include "stdio.h"
#include "stm32l0xx_hal.h"

#include "4DIG_7SEG_DISPLAY.h"

/* Private variables ---------------------------------------------------------*/

unsigned char display_digits[NUMBER_OF_DISPLAY_DIGITS];

uint8_t DigitNumber[NUMBER_OF_DISPLAY_DIGITS] = {
  (COM1), //COM1 
  (COM2), //COM2
  (COM3), //COM3
  (COM4) //COM4
};

#ifdef COMMON_CATODE
uint8_t segmentNumber[10] = {
  (Aseg | Bseg | Cseg | Dseg | Eseg | Fseg), // 0
  (Bseg | Cseg), // 1
  (Aseg | Bseg | Gseg | Eseg | Dseg), // 2
  (Aseg | Bseg | Cseg | Dseg | Gseg), // 3
  (Bseg | Cseg | Fseg | Gseg), // 4
  (Aseg | Fseg | Cseg | Dseg | Gseg), // 5
  (Aseg | Eseg | Cseg | Dseg | Gseg | Fseg), // 6
  (Aseg | Bseg | Cseg), // 7
  (Aseg | Bseg | Cseg | Dseg | Eseg | Fseg | Gseg), // 8
  (Aseg | Bseg | Cseg | Dseg | Fseg | Gseg) // 9
};
#endif
#ifdef COMMON_ANODE
// Segment numbers stored in the array
uint8_t segmentNumber[10] = {
  (~(Aseg | Bseg | Cseg | Dseg | Eseg | Fseg)), // 0
  (~(Bseg | Cseg | DPseg)), // 1
  (~(Aseg | Bseg | Gseg | Eseg | Dseg)), // 2
  (~(Aseg | Bseg | Cseg | Dseg | Gseg)), // 3
  (~(Bseg | Cseg | Fseg | Gseg)), // 4
  (~(Aseg | Fseg | Cseg | Dseg | Gseg)), // 5
  (~(Aseg | Eseg | Cseg | Dseg | Gseg | Fseg)), // 6
  (~(Aseg | Bseg | Cseg)), // 7
  (~(Aseg | Bseg | Cseg | Dseg | Eseg | Fseg | Gseg)), // 8
  (~(Aseg | Bseg | Cseg | Dseg | Fseg | Gseg)) // 9
};
#endif

/* Private functions -------------------------------------------------------*/
void SevenSegment_DisplayDigit(uint8_t number, uint8_t digit) {

  GPIOC -> ODR = number | (digit << 8);
}

void SevenSegment_SymbolOff(uint8_t digit) {

  GPIOC -> ODR = 0 | (digit << 8);
}

void SevenSegment_Update() {
	static char dig_no=NUMBER_OF_DISPLAY_DIGITS-1,
	start_display=0; // nevaizduoti pries skaiciu esanciu nuliu	
	
		if ((display_digits[dig_no]==0) && (start_display==0))
		{	
		  SevenSegment_SymbolOff(display_digits[dig_no]);
		} else
		{
			SevenSegment_DisplayDigit(segmentNumber[display_digits[dig_no]], DigitNumber[dig_no]);
			start_display=1;
		}    
				
		if (dig_no==0)
		{ dig_no=NUMBER_OF_DISPLAY_DIGITS-1;
			start_display=0;
		} else
		dig_no--;	
}