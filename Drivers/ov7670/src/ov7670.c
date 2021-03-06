#include "ov7670.h"

#ifndef NULL
#define NULL 0
#endif

#define CAMERA_WR_ADR       ((unsigned char)0x42)
#define CAMERA_RD_ADR       ((unsigned char)0x43)

/* Registers */
#define REG_GAIN        0x00  /* Gain lower 8 bits (rest in vref) */
#define REG_BLUE        0x01  /* blue gain */
#define REG_RED         0x02  /* red gain */
#define REG_VREF        0x03  /* Pieces of GAIN, VSTART, VSTOP */
#define REG_COM1        0x04  /* Control 1 */
#define COM1_CCIR656    0x40  /* CCIR656 enable */
#define REG_BAVE        0x05  /* U/B Average level */
#define REG_GbAVE       0x06  /* Y/Gb Average level */
#define REG_AECHH       0x07  /* AEC MS 5 bits */
#define REG_RAVE        0x08  /* V/R Average level */
#define REG_COM2        0x09  /* Control 2 */
#define COM2_SSLEEP     0x10  /* Soft sleep mode */
#define REG_PID         0x0a  /* Product ID MSB */
#define REG_VER         0x0b  /* Product ID LSB */
#define REG_COM3        0x0c  /* Control 3 */
#define COM3_SWAP       0x40  /* Byte swap */
#define COM3_SCALEEN    0x08  /* Enable scaling */
#define COM3_DCWEN      0x04  /* Enable downsamp/crop/window */
#define REG_COM4        0x0d  /* Control 4 */
#define REG_COM5        0x0e  /* All "reserved" */
#define REG_COM6        0x0f  /* Control 6 */
#define REG_AECH        0x10  /* More bits of AEC value */
#define REG_CLKRC       0x11  /* Clocl control */
#define CLK_EXT         0x40  /* Use external clock directly */
#define CLK_SCALE       0x3f  /* Mask for internal clock scale */
#define REG_COM7        0x12  /* Control 7 */
#define COM7_RESET      0x80  /* Register reset */
#define COM7_FMT_MASK   0x38
#define COM7_FMT_VGA    0x00
#define COM7_FMT_CIF    0x20  /* CIF format */
#define COM7_FMT_QVGA   0x10  /* QVGA format */
#define COM7_FMT_QCIF   0x08  /* QCIF format */
#define COM7_RGB        0x04  /* bits 0 and 2 - RGB format */
#define COM7_YUV        0x00  /* YUV */
#define COM7_BAYER      0x01  /* Bayer format */
#define COM7_PBAYER     0x05  /* "Processed bayer" */
#define REG_COM8        0x13  /* Control 8 */
#define COM8_FASTAEC    0x80  /* Enable fast AGC/AEC */
#define COM8_AECSTEP    0x40  /* Unlimited AEC step size */
#define COM8_BFILT      0x20  /* Band filter enable */
#define COM8_AGC        0x04  /* Auto gain enable */
#define COM8_AWB        0x02  /* White balance enable */
#define COM8_AEC        0x01  /* Auto exposure enable */
#define REG_COM9        0x14  /* Control 9  - gain ceiling */
#define REG_COM10       0x15  /* Control 10 */
#define COM10_HSYNC     0x40  /* HSYNC instead of HREF */
#define COM10_PCLK_HB   0x20  /* Suppress PCLK on horiz blank */
#define COM10_HREF_REV  0x08  /* Reverse HREF */
#define COM10_VS_LEAD   0x04  /* VSYNC on clock leading edge */
#define COM10_VS_NEG    0x02  /* VSYNC negative */
#define COM10_HS_NEG    0x01  /* HSYNC negative */
#define REG_HSTART      0x17  /* Horiz start high bits */
#define REG_HSTOP       0x18  /* Horiz stop high bits */
#define REG_VSTART      0x19  /* Vert start high bits */
#define REG_VSTOP       0x1a  /* Vert stop high bits */
#define REG_PSHFT       0x1b  /* Pixel delay after HREF */
#define REG_MIDH        0x1c  /* Manuf. ID high */
#define REG_MIDL        0x1d  /* Manuf. ID low */
#define REG_MVFP        0x1e  /* Mirror / vflip */
#define MVFP_MIRROR     0x20  /* Mirror image */
#define MVFP_FLIP       0x10  /* Vertical flip */

#define REG_AEW         0x24  /* AGC upper limit */
#define REG_AEB         0x25  /* AGC lower limit */
#define REG_VPT         0x26  /* AGC/AEC fast mode op region */
#define REG_HSYST       0x30  /* HSYNC rising edge delay */
#define REG_HSYEN       0x31  /* HSYNC falling edge delay */
#define REG_HREF        0x32  /* HREF pieces */
#define REG_TSLB        0x3a  /* lots of stuff */
#define TSLB_YLAST      0x04  /* UYVY or VYUY - see com13 */
#define REG_COM11       0x3b  /* Control 11 */
#define COM11_NIGHT     0x80  /* NIght mode enable */
#define COM11_NMFR      0x60  /* Two bit NM frame rate */
#define COM11_HZAUTO    0x10  /* Auto detect 50/60 Hz */
#define COM11_50HZ      0x08  /* Manual 50Hz select */
#define COM11_EXP       0x02
#define REG_COM12       0x3c  /* Control 12 */
#define COM12_HREF      0x80  /* HREF always */
#define REG_COM13       0x3d  /* Control 13 */
#define COM13_GAMMA     0x80  /* Gamma enable */
#define COM13_UVSAT     0x40  /* UV saturation auto adjustment */
#define COM13_UVSWAP    0x01  /* V before U - w/TSLB */
#define REG_COM14       0x3e  /* Control 14 */
#define COM14_DCWEN     0x10  /* DCW/PCLK-scale enable */
#define REG_EDGE        0x3f  /* Edge enhancement factor */
#define REG_COM15       0x40  /* Control 15 */
#define COM15_R10F0     0x00  /* Data range 10 to F0 */
#define COM15_R01FE     0x80  /*   01 to FE */
#define COM15_R00FF     0xc0  /*   00 to FF */
#define COM15_RGB565    0x10  /* RGB565 output */
#define COM15_RGB555    0x30  /* RGB555 output */
#define REG_COM16       0x41  /* Control 16 */
#define COM16_AWBGAIN   0x08  /* AWB gain enable */
#define REG_COM17       0x42  /* Control 17 */
#define COM17_AECWIN    0xc0  /* AEC window - must match COM4 */
#define COM17_CBAR      0x08  /* DSP Color bar */

#define DEFAULT_PID     0x76
#define DEFAULT_VER     0x72

static Ov7670HwDependFunc_t hw_funcs = {NULL, NULL, NULL, NULL, NULL, NULL};

// -----------------------------------------------------------------------------
static void CamWriteReg(unsigned char reg_addr, unsigned char data) {
  if (hw_funcs.sccb_start != NULL) {
    hw_funcs.sccb_start();
  }
  hw_funcs.sccb_send_byte(CAMERA_WR_ADR);
  hw_funcs.sccb_send_byte((unsigned char)reg_addr);
  hw_funcs.sccb_send_byte(data);
  if (hw_funcs.sccb_end != NULL) {
    hw_funcs.sccb_end();
  }
}

// -----------------------------------------------------------------------------
static void CamReadReg(unsigned char reg_addr, unsigned char * data) {
  if (hw_funcs.sccb_start != NULL) {
    hw_funcs.sccb_start();
  }
  hw_funcs.sccb_send_byte(CAMERA_WR_ADR);
  hw_funcs.sccb_send_byte((unsigned char)reg_addr);
  if (hw_funcs.sccb_end != NULL) {
    hw_funcs.sccb_end();
  }

  if (hw_funcs.sccb_start != NULL) {
    hw_funcs.sccb_start();
  }
  hw_funcs.sccb_send_byte(CAMERA_RD_ADR);
  hw_funcs.sccb_rec_byte(data);
  if (hw_funcs.sccb_end != NULL) {
    hw_funcs.sccb_end();
  }
}

// -----------------------------------------------------------------------------
static void Rgb565Init480x272(void) {
  CamWriteReg(REG_COM7, COM7_RGB);
  CamWriteReg(0xB0, 0x84); // must be to propertly color display
  CamWriteReg(REG_COM15, 0xD0);
  CamWriteReg(REG_COM1, 0x0);
  CamWriteReg(REG_HSTART, 0x14); // start H
  CamWriteReg(REG_HSTOP, 0x50); // stop H
  CamWriteReg(REG_VSTART, 0x05); // start V
  CamWriteReg(REG_VSTOP, 0x49); // stop V
  CamWriteReg(REG_GAIN, 0xff);
  CamWriteReg(REG_BLUE, 0xff);
  CamWriteReg(REG_RED, 0xff);
}

// -----------------------------------------------------------------------------
void ov7670StandbyDisable(void) {
  CamWriteReg(REG_COM2, 0x01);
}

// -----------------------------------------------------------------------------
void ov7670StandbyEnable(void) {
  CamWriteReg(REG_COM2, 0x11);
}

// -----------------------------------------------------------------------------
void ov7670Reset(void) {
  CamWriteReg(REG_COM7, COM7_RESET);
  hw_funcs.sccb_delay_ms(1000);
}

// -----------------------------------------------------------------------------
void ov7670MirrorImage(void) {
  CamWriteReg(REG_MVFP, MVFP_FLIP);
}

// -----------------------------------------------------------------------------
int ov7670Init(Ov7670HwDependFunc_t * hw_sccb_funcs, Ov7670Res_t res) {
  unsigned char pid;
  unsigned char ver;

  if ((hw_sccb_funcs->sccb_delay_ms == NULL) || \
      (hw_sccb_funcs->sccb_init == NULL) || \
      (hw_sccb_funcs->sccb_rec_byte == NULL) || \
      (hw_sccb_funcs->sccb_send_byte == NULL)) {
        return 1;
  }

  hw_funcs.sccb_delay_ms = hw_sccb_funcs->sccb_delay_ms;
  hw_funcs.sccb_end = hw_sccb_funcs->sccb_end;
  hw_funcs.sccb_init = hw_sccb_funcs->sccb_init;
  hw_funcs.sccb_rec_byte = hw_sccb_funcs->sccb_rec_byte;
  hw_funcs.sccb_send_byte = hw_sccb_funcs->sccb_send_byte;
  hw_funcs.sccb_start = hw_sccb_funcs->sccb_start;

  // init hw 
  hw_funcs.sccb_init();

  // reset the device 
  CamWriteReg(REG_COM7, COM7_RESET);
  hw_funcs.sccb_delay_ms(1000);
  
  // HREF
  CamWriteReg(REG_COM10, 0x06);

  // reset all timing when format changes
  CamWriteReg(REG_COM6, 0x82);

  // image settings
  switch (res) {
    case RES480x272_RGB565:
      Rgb565Init480x272();
      break;

    default:
      break;
  }

  // detect device on DCMI bus
  CamReadReg(REG_PID, &pid);
  CamReadReg(REG_VER, &ver);

  if ((pid != (unsigned char)DEFAULT_PID) || \
      (ver != (unsigned char)DEFAULT_VER)) {
    return 1;
  }
  return 0;
}
