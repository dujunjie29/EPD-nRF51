#include "EPD_Test.h"
#include "EPD_4in2.h"

const unsigned char EPD_4IN2_4Gray_lut_vcom[] =
{
    0x00 ,0x0A ,0x00 ,0x00 ,0x00 ,0x01,
    0x60 ,0x14 ,0x14 ,0x00 ,0x00 ,0x01,
    0x00 ,0x14 ,0x00 ,0x00 ,0x00 ,0x01,
    0x00 ,0x13 ,0x0A ,0x01 ,0x00 ,0x01,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00
};

const unsigned char EPD_4IN2_4Gray_lut_ww[] ={
    0x40 ,0x0A ,0x00 ,0x00 ,0x00 ,0x01,
    0x90 ,0x14 ,0x14 ,0x00 ,0x00 ,0x01,
    0x10 ,0x14 ,0x0A ,0x00 ,0x00 ,0x01,
    0xA0 ,0x13 ,0x01 ,0x00 ,0x00 ,0x01,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
};

const unsigned char EPD_4IN2_4Gray_lut_bw[] ={
    0x40 ,0x0A ,0x00 ,0x00 ,0x00 ,0x01,
    0x90 ,0x14 ,0x14 ,0x00 ,0x00 ,0x01,
    0x00 ,0x14 ,0x0A ,0x00 ,0x00 ,0x01,
    0x99 ,0x0C ,0x01 ,0x03 ,0x04 ,0x01,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
};

const unsigned char EPD_4IN2_4Gray_lut_wb[] ={
    0x40 ,0x0A ,0x00 ,0x00 ,0x00 ,0x01,
    0x90 ,0x14 ,0x14 ,0x00 ,0x00 ,0x01,
    0x00 ,0x14 ,0x0A ,0x00 ,0x00 ,0x01,
    0x99 ,0x0B ,0x04 ,0x04 ,0x01 ,0x01,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
};

const unsigned char EPD_4IN2_4Gray_lut_bb[] ={
    0x80 ,0x0A ,0x00 ,0x00 ,0x00 ,0x01,
    0x90 ,0x14 ,0x14 ,0x00 ,0x00 ,0x01,
    0x20 ,0x14 ,0x0A ,0x00 ,0x00 ,0x01,
    0x50 ,0x13 ,0x01 ,0x00 ,0x00 ,0x01,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
    0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,
};

static void EPD_4IN2_4Gray_lut(void)
{
	unsigned int count;

    EPD_4IN2_SendCommand(0x20);							//vcom
    for(count=0;count<42;count++)
        {EPD_4IN2_SendData(EPD_4IN2_4Gray_lut_vcom[count]);}
    
    EPD_4IN2_SendCommand(0x21);							//red not use
    for(count=0;count<42;count++)
        {EPD_4IN2_SendData(EPD_4IN2_4Gray_lut_ww[count]);}

    EPD_4IN2_SendCommand(0x22);							//bw r
    for(count=0;count<42;count++)
        {EPD_4IN2_SendData(EPD_4IN2_4Gray_lut_bw[count]);}

    EPD_4IN2_SendCommand(0x23);							//wb w
    for(count=0;count<42;count++)
        {EPD_4IN2_SendData(EPD_4IN2_4Gray_lut_wb[count]);}

    EPD_4IN2_SendCommand(0x24);							//bb b
    for(count=0;count<42;count++)
        {EPD_4IN2_SendData(EPD_4IN2_4Gray_lut_bb[count]);}

    EPD_4IN2_SendCommand(0x25);							//vcom
    for(count=0;count<42;count++)
        {EPD_4IN2_SendData(EPD_4IN2_4Gray_lut_ww[count]);}
}

static void drawNormal(void)
{
    UWORD Width, Height;
    Width = (EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1);
    Height = EPD_4IN2_HEIGHT;

    EPD_4IN2_SendCommand(0x10);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_4IN2_SendData(0xFF);
        }
    }

    EPD_4IN2_SendCommand(0x13);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_4IN2_SendData(((j + 1)*2 > Height) ? 0x00 : 0xFF);
        }
    }

    EPD_4IN2_TurnOnDisplay();
}

static void draw4Gray(void)
{
    UWORD Width, Height;
    Width = (EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1);
    Height = EPD_4IN2_HEIGHT;

    EPD_4IN2_SendCommand(0x10);
    for (UWORD i = 0; i < Width * Height; i++) {
        UWORD idx = (i % 50) / 12;
        if (idx > 3) idx = 3;
        if (idx == 0 || idx == 1) {
            EPD_4IN2_SendData(0x00);
        } else if (idx == 2 || idx == 3) {
            EPD_4IN2_SendData(0xFF);
        }
    }

    EPD_4IN2_SendCommand(0x13);
    for (UWORD i = 0; i < Width * Height; i++) {
        UWORD idx = (i % 50) / 12;
        if (idx > 3) idx = 3;
        if (idx == 0 || idx == 2) {
            EPD_4IN2_SendData(0x00);
        } else if (idx == 1 || idx == 3) {
            EPD_4IN2_SendData(0xFF);
        }
    }

    EPD_4IN2_4Gray_lut();
    EPD_4IN2_TurnOnDisplay();
}

void EPD_4in2_test(void)
{
    DEV_Module_Init();

    EPD_4IN2_Init();
    EPD_4IN2_Clear();
    DEV_Delay_ms(500);

    drawNormal();
    DEV_Delay_ms(3000);

    EPD_4IN2_Clear();
    DEV_Delay_ms(500);

    draw4Gray();
    DEV_Delay_ms(500);
    
    EPD_4IN2_Sleep();
    DEV_Delay_ms(500);
    DEV_Module_Exit();
}

