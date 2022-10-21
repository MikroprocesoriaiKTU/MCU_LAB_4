/**
 ********************************************************************************
 * @file    :4DIG_7SEG_DISPLAY.c
 * @author  :Vytautas Daunoras
 * @date    :2022-10-20
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "4DIG_7SEG_DISPLAY.h"

/* Private variables ---------------------------------------------------------*/
char mas[5] = {
  0,
  0,
  0,
  0,
  0
};
uint8_t temp1, temp2, temp3, temp4; //skaitmenys ekrane
int mux_counter = 1;

uint8_t DigitNumber[4] = {
  (COM1), //COM1 
  (COM2), //COM2
  (COM3), //COM3
  (COM4)  //COM4
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
void SevenSegment_Update(uint8_t number, uint8_t digit) {

  GPIOC -> ODR = number | (digit << 8);
}

void SevenSegment_Display(float to_display) {
  sprintf(mas, "%4.0f", to_display);
  temp1 = mas[0] - 48; //1 - 1st digit
  temp2 = mas[1] - 48; //2 - 2nd digit
  temp3 = mas[2] - 48; //3 - 3rd digit
  temp4 = mas[3] - 48; //4 - 4th digit

  if (mux_counter == (REFRESH_RATE)) 					//1 skaitmuo
    SevenSegment_Update(segmentNumber[temp1], DigitNumber[0]);
  else if (mux_counter == (REFRESH_RATE*2)) 	//2 skaitmuo
  {
    SevenSegment_Update(segmentNumber[temp2], DigitNumber[1]);
  } else if (mux_counter == (REFRESH_RATE*3)) //3 skaitmuo
  {
    SevenSegment_Update(segmentNumber[temp3], DigitNumber[2]);
  } else if (mux_counter >= (REFRESH_RATE*4)) //4 skaitmuo
  {
    SevenSegment_Update(segmentNumber[temp4], DigitNumber[3]);
    mux_counter = 1;
  }

}