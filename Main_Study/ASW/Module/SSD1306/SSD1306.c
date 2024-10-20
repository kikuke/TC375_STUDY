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

/**
 * @brief Set the lower nibble of the column start address register for Page Mode
 * 
 * @param nibble lower nibble
 */
static void SetLowColStartAddrPageMode(uint8 nibble);

/**
 * @brief Set the higher nibble of the column start address register for Page Addressing Mode
 * 
 * @param nibble higher nibble
 */
static void SetHighColStartAddrPageMode(uint8 nibble);
static void SetMemoryAddressingMode(uint8 mode);
static void SetComlumnAddress(uint8 startAddr, uint8 endAddr);
static void SetPageAddress(uint8 startAddr, uint8 endAddr);
/**
 * @brief Set GDDRAM Page Start Address(PAGE0 ~ PAGE7) for Page Addressing Mode
 * 
 * @param page 
 */
static void SetPageStartForPageMode(uint8 page);

/*************************************/
/*  Hardware Configuration Command   */
/* Panel resolution & layout related */
/*************************************/

static void SetDisplayStartLine(uint8 line);
static void SetSegmentReMap(uint8 b127);
/**
 * @brief Set MUX ratio to N+1 MUX
 * 
 * @param mux 
 */
static void SetMultiplexRatio(uint8 mux);
static void SetComOutputScanDirection(uint8 bRemap);
static void SetDisplayOffset(uint8 com);
static void SetComPinsHardwareConfig(uint8 config);

/*******************************************/
/* Timing & Driving Scheme Setting Command */
/*******************************************/

/**
 * @brief Set Display Clock Divide Ratio / Oscilator Frequency
 * 
 * @param divRatio 
 * @param oscFreq 
 */
static void SetDisplayClockRatioFreq(uint8 divRatio, uint8 oscFreq);
static void SetPreChargePeriod(uint8 phase1, uint8 phase2);
static void VcomhDeselectLevel(uint8 level);
static void NOP_CMD(void);

/*******************************************/
/*              Read Command               */
/*******************************************/

/**
 * @brief return display On Off
 * 
 * @return uint8 1 for display OFF / 0 for display ON
 */
static uint8 StatusRegisterRead(void); // TODO: Need To Implement

/*******************************************/
/*       I2C Communication Function        */
/*******************************************/
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

static void SetLowColStartAddrPageMode(uint8 nibble)
{
    uint8 cmd[1] = {(0x00 | (0x0F & nibble))};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void SetHighColStartAddrPageMode(uint8 nibble)
{
    uint8 cmd[1] = {(0x10 | (0x0F & nibble))};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void SetMemoryAddressingMode(uint8 mode)
{
    uint8 cmd[2] = {
            (0x20),
            (0x03 & mode)
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 2);
}

static void SetComlumnAddress(uint8 startAddr, uint8 endAddr)
{
    uint8 cmd[3] = {
            (0x21),
            (0x7F & startAddr),
            (0x7F & endAddr)
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 3);
}

static void SetPageAddress(uint8 startAddr, uint8 endAddr)
{
    uint8 cmd[3] = {
            (0x22),
            (0x07 & startAddr),
            (0x07 & endAddr)
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 3);
}

static void SetPageStartForPageMode(uint8 page)
{
    uint8 cmd[1] = {(0xB0 | (0x07 & page))};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void SetDisplayStartLine(uint8 line)
{
    uint8 cmd[1] = {(0x40 | (0x3F & line))};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void SetSegmentReMap(uint8 b127)
{
    uint8 cmd[1] = {(0xA0 | (0x01 & b127))};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void SetMultiplexRatio(uint8 mux)
{
    uint8 cmd[2] = {
            (0xA8),
            (0x3F & mux)
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 2);
}

static void SetComOutputScanDirection(uint8 bRemap)
{
    uint8 cmd[1] = {(0xC0 | (0x08 & (bRemap << 3)))};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static void SetDisplayOffset(uint8 com)
{
    uint8 cmd[2] = {
            (0xD3),
            (0x3F & com)
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 2);
}

static void SetComPinsHardwareConfig(uint8 config)
{
    uint8 cmd[2] = {
            (0xDA),
            ((0x30 & (config << 4)) | (0x02))
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 2);
}

static void SetDisplayClockRatioFreq(uint8 divRatio, uint8 oscFreq)
{
    uint8 cmd[2] = {
            (0xD5),
            ((0xF0 & (oscFreq << 4)) | (0x0F & divRatio))
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 2);
}

static void SetPreChargePeriod(uint8 phase1, uint8 phase2)
{
    uint8 cmd[2] = {
            (0xD9),
            ((0xF0 & (phase2 << 4)) | (0x0F & phase1))
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 2);
}

static void VcomhDeselectLevel(uint8 level)
{
    uint8 cmd[2] = {
            (0xDB),
            (0x70 & (level << 4))
        };

    _SendData(SSD1306_Packet_COMMAND, cmd, 2);
}

static void NOP_CMD(void)
{
    uint8 cmd[1] = {0xE3};

    _SendData(SSD1306_Packet_COMMAND, cmd, 1);
}

static uint8 StatusRegisterRead(void)
{
    return 0;
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
