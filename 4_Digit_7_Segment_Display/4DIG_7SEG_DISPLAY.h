/**
 ********************************************************************************
 * @file    4DIG_7SEG_DISPLAY.h
 * @author  :Vytautas Daunoras
 * @date    :2022-10-20
 ********************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private defines -----------------------------------------------------------*/
/**
 * pasirenkama priklausomai nuo 7sementu ekrano tipo  
 * Kamami makete naudojamas COMMON_CATODE 
 * Galimi variantai:
 * @param COMMON_CATODE arba COMMON_ANODE
 * 
*/
#define COMMON_CATODE   
#define REFRESH_RATE 5  // in ms

// sablonai priklauso nuo principines schemos pajungimo
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
extern int mux_counter;
/* Private function prototypes -----------------------------------------------*/
void SevenSegment_Update(uint8_t number, uint8_t digit);
void SevenSegment_Display(float to_display);