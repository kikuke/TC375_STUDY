#include "Module_I2C.h"
#include "SSD1306.h"

/* 9-1 Command Table */
/********************************/
/*     Fundamental Command      */
/********************************/
static void _SetContrastControl(uint8 value);
static void _EntireDisplayOn(uint8 bIgCon);
static void _SetNormalInverseDisplay(uint8 bInverse);
static void _SetDisplayOnOff(uint8 bOn);

/********************************/
/*       Scrolling Command      */
/********************************/
/**
 * @brief ContinuousHorizontalScrollSetup
 * 
 * @param bLHS Left Horizontal Scroll
 * @param spg Define Start Page Address
 * @param interval Set time interval between each scroll step in terms of frame frequency
 * @param epg Define End Page Addresss
 */
static void ContinuousHorizontalScrollSetup(uint8 bLHS, uint8 spg, uint8 interval, uint8 epg);
/**
 * @brief No Continuous Vertical Scrolling is available
 * 
 * @param VLHS Vertical and Left Horizontal Scroll (Horizontal scroll by 1 column)
 * @param spg Define Start Pahe Address
 * @param interval Set time interval between each scroll step in terms of frame frequency
 * @param epg Define End Page Address
 * @param vOffset Vertical Scrolling Offset
 */
static void ContinuousVerticalAndHorizontalScrollSetup(uint8 VLHS, uint8 spg, uint8 interval, uint8 epg, uint8 vOffset);
static void DeactivateScroll(void);
static void ActivateScroll(void);
/**
 * @brief Set the Vertical Scroll
 * 
 * @param fixedRows Set No. of rows in top fixed area
 * @param scrollRows Set No. of rows in scroll area
 */
static void SetVerticalScrollArea(uint8 fixedRows, uint8 scrollRows);

/********************************/
/*  Addressing Setting Command  */
/********************************/


static void _SendData(SSD1306_Packet_T type, const uint8 *data, Ifx_SizeT size);
static void _SendPacket(SSD1306_Packet_T type, const uint8 *packet, Ifx_SizeT size);
static void _MakePacket(uint8 *buffer, SSD1306_Packet_T type, const uint8 *data, Ifx_SizeT size);

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

void Init_SSD1306(void)
{
    Init_I2C(&ssd1306_inst, &ssd1306_config);

    _EntireDisplayOn(1);
}

static void _SetContrastControl(uint8 value)
{
    uint8 cmd[2] = {0x81, value};

    _SendData(SSD1306_Packet_COMMAND, cmd, 2);
}

static void _EntireDisplayOn(uint8 bIgCon)
{
    uint8 cmd[1] = {(0xA4 | (0x01 & bIgCon))};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void _SetNormalInverseDisplay(uint8 bInverse)
{
    uint8 cmd[1] = {(0xA6 | (0x01 & bInverse))};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void _SetDisplayOnOff(uint8 bOn)
{
    uint8 cmd[1] = {(0xAE | (0x01 & bOn))};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void ContinuousHorizontalScrollSetup(uint8 bLHS, uint8 spg, uint8 interval, uint8 epg)
{
    uint8 cmd[7] = {
            (0x26 | (0x01 & bLHS)),
            (0x00),
            (0x07 & spg),
            (0x07 & interval),
            (0x07 & epg),
            (0x00),
            (0xFF)
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 7);
}

static void ContinuousVerticalAndHorizontalScrollSetup(uint8 VLHS, uint8 spg, uint8 interval, uint8 epg, uint8 vOffset)
{
    uint8 cmd[6] = {
            (0x28 | (0x03 & VLHS)),
            (0x00),
            (0x07 & spg),
            (0x07 & interval),
            (0x07 & epg),
            (0x3F & vOffset)
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 6);
}

static void DeactivateScroll(void)
{
    uint8 cmd[1] = {0x2E};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void ActivateScroll(void)
{
    uint8 cmd[1] = {0x2F};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void SetVerticalScrollArea(uint8 fixedRows, uint8 scrollRows)
{
    uint8 cmd[3] = {
            (0xA3),
            (0x3F & fixedRows),
            (0x7F & scrollRows)
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 3);
}

static void _SendData(SSD1306_Packet_T type, const uint8 *data, Ifx_SizeT size)
{
    uint8 buffer[SSD1306_I2C_BUFF_MAX];

    _MakePacket(buffer, type, data, size);
    _SendPacket(type, buffer, size * 2); /* Control Byte + Data Byte */
}

static void _SendPacket(SSD1306_Packet_T type, const uint8 *packet, Ifx_SizeT size)
{
    I2c_write(&ssd1306_inst.dev, packet, size);
}

static void _MakePacket(uint8 *buffer, SSD1306_Packet_T type, const uint8 *data, Ifx_SizeT size)
{
    const uint8 cByte = (0x00 | (type << 6));

    for (int i=0; i < size; i++) {
        buffer[i * 2] = cByte;
        buffer[(i * 2) + 1] = data[i];
    }
}
