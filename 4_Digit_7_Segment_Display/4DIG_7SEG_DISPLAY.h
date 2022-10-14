#include "main.h"
// sablonai priklauso nuo principines schemos pajungimo
#define COMMON_CATODE   //COMMON_ANODE  COMMON_CATODE
#define refresh_rate 2  // in ms

#define Aseg 0x40 // PC6
#define Bseg 0x10 // PC4
#define Cseg 0x08 // PC3
#define Dseg 0x02 // PC1
#define Eseg 0x04 // PC2
#define Fseg 0x20 // PC5
#define Gseg 0x01 // PC0
#define DPseg 0x80 // PC7

#ifdef COMMON_ANODE 
#define COM1 0x01
#define COM2 0x02
#define COM3 0x04
#define COM4 0x08
#endif
#ifdef COMMON_CATODE
#define COM1 ~0x08
#define COM2 ~0x04
#define COM3 ~0x02
#define COM4 ~0x01
#endif

#define D1_HIGH() HAL_GPIO_WritePin(COM1_GPIO_Port, COM1_Pin, GPIO_PIN_SET)
#define D1_LOW() HAL_GPIO_WritePin(COM1_GPIO_Port, COM1_Pin, GPIO_PIN_RESET)
#define D2_HIGH() HAL_GPIO_WritePin(COM2_GPIO_Port, COM2_Pin, GPIO_PIN_SET)
#define D2_LOW() HAL_GPIO_WritePin(COM2_GPIO_Port, COM2_Pin, GPIO_PIN_RESET)
#define D3_HIGH() HAL_GPIO_WritePin(COM3_GPIO_Port, COM3_Pin, GPIO_PIN_SET)
#define D3_LOW() HAL_GPIO_WritePin(COM3_GPIO_Port, COM3_Pin, GPIO_PIN_RESET)
#define D4_HIGH() HAL_GPIO_WritePin(COM4_GPIO_Port, COM4_Pin, GPIO_PIN_SET)
#define D4_LOW() HAL_GPIO_WritePin(COM4_GPIO_Port, COM4_Pin, GPIO_PIN_RESET)

void SevenSegment_Update(uint8_t number);
void SevenSegment_Display(float to_display);