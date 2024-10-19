#ifndef MODULE_I2C_H
#define MODULE_I2C_H

#include "Ifx_Types.h"
#include "IfxI2c_I2c.h"

typedef struct _Module_I2C_Config {
    Ifx_I2C *p_i2c;
    IfxI2c_Pins MCP_PINS;
    float32 baudrate;
    uint16 addr;
} Module_I2C_Config;

typedef struct _Module_I2C_Inst {
    IfxI2c_I2c handle;                                   /* I2C handle                                       */
    IfxI2c_I2c_Device dev;                               /* I2C Slave device handle to Microchip 24AA02E48   */
} Module_I2C_Inst;

extern void Init_I2C(Module_I2C_Inst *inst, const Module_I2C_Config *config);
extern IfxI2c_I2c_Status I2c_write(IfxI2c_I2c_Device *i2cDevice, volatile uint8 *data, Ifx_SizeT size);

#endif