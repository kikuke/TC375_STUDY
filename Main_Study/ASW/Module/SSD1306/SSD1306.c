#include "Module_I2C.h"
#include "SSD1306.h"

static const Module_I2C_Config ssd1306_config = {
    .p_i2c = &MODULE_I2C0,
    .MCP_PINS = {
        .scl = &IfxI2c0_SCL_P13_1_INOUT,
        .sda = &IfxI2c0_SDA_P13_2_INOUT,
        .padDriver = IfxPort_PadDriver_ttlSpeed1
    },
    .baudrate = SSD1306_I2C_BAUDRATE,
    .addr = GET_SSD1306_ADDR(0)
};

static Module_I2C_Inst ssd1306_inst;

static void SendPacket(SSD1306_Packet_T type, uint8 data);

void Init_SSD1306(void)
{
    Init_I2C(&ssd1306_inst, &ssd1306_config);

    SendPacket(SSD1306_Packet_COMMAND, 0xA8);
}

static void SendPacket(SSD1306_Packet_T type, uint8 data)
{
    uint8 packet[SSD1306_I2C_PACKET_LEN] = {
        (0x00 | (type << 6)),
        data
    };

    I2c_write(&ssd1306_inst.dev, packet, SSD1306_I2C_PACKET_LEN);
}