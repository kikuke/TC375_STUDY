#ifndef SSD1306_H
#define SSD1306_H

#include "Platform_Types.h"

/**
 * @brief 
 * Reference : [SSD1780 DataSheet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
 */

#define SSD1306_I2C_BAUDRATE            1000000                 /* Table 13-6 : tIdle = 1.3us
                                                                   Maximum Baudrate = 1.3 * 8(bps) * 1000*1000(us to s) = 1040000 */
#define SSD1306_I2C_CONTROL_LEN         1                        
#define SSD1306_I2C_DATA_LEN            1
#define SSD1306_I2C_PACKET_LEN          (SSD1306_I2C_CONTROL_LEN + SSD1306_I2C_DATA_LEN)

#define GET_SSD1306_ADDR(bSA0) (uint8)( (0x3C) | (0x01 & bSA0) )

typedef enum eSSD1306_Packet_T {
    SSD1306_Packet_COMMAND = 0,
    SSD1306_Packet_DATA = 1
} SSD1306_Packet_T;

extern void Init_SSD1306(void);

#endif