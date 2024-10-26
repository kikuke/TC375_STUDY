#ifndef SSD1306_H
#define SSD1306_H

#include "Platform_Types.h"

/**
 * @brief 
 * Reference : [SSD1780 DataSheet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
 */

#define SSD1306_I2C_BAUDRATE            1000000                                         /* Table 13-6 : tIdle = 1.3us
                                                                                          Maximum Baudrate = 1.3 * 8(bps) * 1000*1000(us to s) = 1040000 */
#define SSD1306_SEG_LEN                 8
#define SSD1306_MAX_SEG                 128
#define SSD1306_MAX_PAGE                8
#define SSD1306_I2C_BUFF_MAX            (SSD1306_MAX_SEG * 2)

#if 0
#define SSD1306_MAX_SEND_DATA           8
#else
#define SSD1306_MAX_SEND_DATA           2
#endif
#define SSD1306_MAX_SEND_SIZE           SSD1306_MAX_SEND_DATA * 2                       /* Max Send Data: 16Byte (Control 8Byte, Data 8Byte) */

#define SSD1306_ADDR_128_32             0
#define SSD1306_ADDR_128_64             1
#define GET_SSD1306_ADDR(bSA0) (uint8)( (0x3C) | (0x01 & bSA0) )                        /* 0x3C for 128 * 32, 0x3D for 128 * 64 */

typedef enum eSSD1306_Packet_T {
    SSD1306_Packet_COMMAND = 0,
    SSD1306_Packet_DATA = 1
} SSD1306_Packet_T;

extern void Init_SSD1306(void);
extern void SSD1306_SetDisplay(uint8 *buff, uint8 startPage, uint8 pageLen, uint8 startColumn, uint8 columnLen);
extern void SSD1306_ClearDisplay(void);

#endif