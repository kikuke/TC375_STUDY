#include "Module_I2C.h"

void Init_I2C(Module_I2C_Inst *inst, const Module_I2C_Config *config)
{
    /* Initialize module */
    IfxI2c_I2c_Config i2cConfig;                                    /* Create configuration structure               */
    IfxI2c_I2c_deviceConfig i2cDeviceConfig;                        /* Create device configuration                  */
    IfxI2c_I2c_initConfig(&i2cConfig, config->p_i2c);               /* Fill structure with default values and Module
                                                                       address                                      */

    i2cConfig.pins = &config->MCP_PINS;
    i2cConfig.baudrate = config->baudrate;
    IfxI2c_I2c_initModule(&inst->handle, &i2cConfig);               /* Initialize module */

    /* Initialize device */
    IfxI2c_I2c_initDeviceConfig(&i2cDeviceConfig, &inst->handle);   /* Fill structure with default values and I2C
                                                                       Handler                                      */

    /* Because it is 7 bit long and bit 0 is R/W bit, the device address has to be shifted by 1 */
    i2cDeviceConfig.deviceAddress = config->addr << 1;
    IfxI2c_I2c_initDevice(&inst->dev, &i2cDeviceConfig);            /* Initialize the I2C device handle             */
}

IfxI2c_I2c_Status I2c_write(IfxI2c_I2c_Device *i2cDevice, volatile uint8 *data, Ifx_SizeT size)
{
    IfxI2c_I2c_Status ret = 0;
    while((ret = IfxI2c_I2c_write(i2cDevice, data, size)) == IfxI2c_I2c_Status_nak);

    return ret;
}
