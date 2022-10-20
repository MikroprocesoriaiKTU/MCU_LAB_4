#include "main.h"
#include "stdio.h"
#include "4DIG_7SEG_DISPLAY.h"

char mas[5] = {
  0,
  0,
  0,
  0,
	0
};
uint8_t temp1, temp2, temp3, temp4;

#ifdef COMMON_ANODE
// Segment numbers stored in the array
uint8_t segmentNumber[10] = {
  ~(Aseg | Bseg | Cseg | Dseg | Eseg | Fseg | DPseg), 			// 0
  ~(Bseg | Cseg | DPseg), 																	// 1
  ~(Aseg | Bseg | Gseg | Eseg | Dseg | DPseg), 							// 2
  ~(Aseg | Bseg | Cseg | Dseg | Gseg | DPseg), 							// 3
  ~(Bseg | Cseg | Fseg | Gseg | DPseg), 										// 4
  ~(Aseg | Fseg | Cseg | Dseg | Gseg | DPseg), 							// 5
  ~(Aseg | Eseg | Cseg | Dseg | Gseg | Fseg | DPseg),				// 6
  ~(Aseg | Bseg | Cseg | DPseg), 														// 7
  ~(Aseg | Bseg | Cseg | Dseg | Eseg | Fseg | Gseg | DPseg),// 8
  ~(Aseg | Bseg | Cseg | Dseg | Fseg | Gseg | DPseg)  			// 9
};
#endif
#ifdef COMMON_CATODE
uint8_t segmentNumber[10] = {
  (Aseg | Bseg | Cseg | Dseg | Eseg | Fseg), 				// 0
  (Bseg | Cseg), 																		// 1
  (Aseg | Bseg | Gseg | Eseg | Dseg), 							// 2
  (Aseg | Bseg | Cseg | Dseg | Gseg), 							// 3
  (Bseg | Cseg | Fseg | Gseg), 											// 4
  (Aseg | Fseg | Cseg | Dseg | Gseg), 							// 5
  (Aseg | Eseg | Cseg | Dseg | Gseg | Fseg), 				// 6
  (Aseg | Bseg | Cseg), 														// 7
  (Aseg | Bseg | Cseg | Dseg | Eseg | Fseg | Gseg), // 8
  (Aseg | Bseg | Cseg | Dseg | Fseg | Gseg) 				// 9
};
#endif

void SevenSegment_Update(uint8_t number) {
  HAL_GPIO_WritePin(GPIOC, Seg_G_Pin, ((number >> 0) & 0x01));
  HAL_GPIO_WritePin(GPIOC, Seg_D_Pin, ((number >> 1) & 0x01));
  HAL_GPIO_WritePin(GPIOC, Seg_E_Pin, ((number >> 2) & 0x01));
  HAL_GPIO_WritePin(GPIOC, Seg_C_Pin, ((number >> 3) & 0x01));
  HAL_GPIO_WritePin(GPIOC, Seg_B_Pin, ((number >> 4) & 0x01));
  HAL_GPIO_WritePin(GPIOC, Seg_F_Pin, ((number >> 5) & 0x01));
  HAL_GPIO_WritePin(GPIOC, Seg_A_Pin, ((number >> 6) & 0x01));
	HAL_GPIO_WritePin(GPIOC, Decimal_Point_Pin, ((number >> 7) & 0x01));
}


void SevenSegment_Display(float to_display) {
  sprintf(mas, "%4.0f", to_display);
  temp1 = mas[0] - 48; //1 - 1st digit
  temp2 = mas[1] - 48; //2 - 2nd digit
  temp3 = mas[2] - 48; //3 - 3rd digit
  temp4 = mas[3] - 48; //4 - 4th digit
	
	#ifdef COMMON_CATODE
	SevenSegment_Update(segmentNumber[temp1]);
  D1_LOW();
  HAL_Delay(refresh_rate);
  D1_HIGH();

  SevenSegment_Update(segmentNumber[temp2]);
  D2_LOW();
  HAL_Delay(refresh_rate);
  D2_HIGH();

  SevenSegment_Update(segmentNumber[temp3]);
  D3_LOW();
  HAL_Delay(refresh_rate);
  D3_HIGH();

  SevenSegment_Update(segmentNumber[temp4]);
  D4_LOW();
  HAL_Delay(refresh_rate);
  D4_HIGH();
	#endif
			
#ifdef COMMON_ANODE
  SevenSegment_Update(segmentNumber[temp1]);
	D1_HIGH();
  HAL_Delay(refresh_rate);
  D1_LOW();

  SevenSegment_Update(segmentNumber[temp2]);
	D2_HIGH();
  HAL_Delay(refresh_rate);
  D2_LOW();

  SevenSegment_Update(segmentNumber[temp3]);
	D3_HIGH();
  HAL_Delay(refresh_rate);
  D3_LOW();

  SevenSegment_Update(segmentNumber[temp4]);
	D4_HIGH();
  HAL_Delay(refresh_rate);
  D4_LOW();
	#endif
}