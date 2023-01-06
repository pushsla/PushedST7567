/* Copyright (C) 2023 Svyatoslav Pushkerav
This file is part of PushedST7567.
This particular file is provided to you for any use you see fit.
If used as part of the project within which it is published, see the project license.
However, this particular file may be used independently by you in full freedom of action without restrictions.
The only condition is that you will credit me in modified or copied version of this file.
If this file is modified, please also add a note that the file has been modified.
If you include the contents of this file in another project, please credit me to your new file.
*/
#ifndef PUST7567_CMD_h
#define PUST7567_CMD_h

#define PUST7567_BYTE_CMD_ONE     0x00
#define PUST7567_BYTE_DAT_ONE     0x40
#define PUST7567_BYTE_CMD_CONT    0x80
#define PUST7567_BYTE_DAT_CONT    0xc0

#define PUST7567_CMD_DISPLAY_ON        0xAF
#define PUST7567_CMD_DISPLAY_OFF       0xAE
#define PUST7567_CMD_DISPLAY_INVERSE   0xA7
#define PUST7567_CMD_DISPLAY_NORMAL    0xA6
#define PUST7567_CMD_DISPLAY_ALLPIXEL  0xA5
#define PUST7567_CMD_DISPLAY_NONPIXEL  0xA4
#define PUST7567_CMD_SET_COLUMN_MSB    0x10  // it's a prefix. need to be | with 4-bit MSB part of column number
#define PUST7567_CMD_SET_COLUMN_LSB    0x00  // it's a prefix. need to be | with 4-bit LSB part of column number
#define PUST7567_CMD_SET_PAGE          0xB0  // it's a prefix. need to be | with 4-bit page number
#define PUST7567_CMD_SEG_NORMAL        0xA0
#define PUST7567_CMD_SEG_REVERSE       0xA1
#define PUST7567_CMD_BIAS_1_9          0xA2
#define PUST7567_CMD_BIAS_1_7          0xA3
#define PUST7567_CMD_READ_MODIFY_WRITE 0xE0
#define PUST7567_CMD_END               0xEE
#define PUST7567_CMD_RESET             0xE2
#define PUST7567_CMD_COM_REVERSE       0xC8
#define PUST7567_CMD_COM_NORMAL        0xC0
#define PUST7567_CMD_NOP               0xE3
#define PUST7567_CMD_POWER_CONTROL     0x28  // it's a prefix. need to be | with on-end 3-bit VB,VR,VF
#define PUST7567_CMD_REGULATION_RATIO  0x20  // it's a prefix. need to be | with on-end 3-bit RR2,RR1,RR0
#define PUST7567_CMD_EV_DEFINE         0x81  // its a first command. After it should be PUST7567_CMD_EV_IMPL
#define PUST7567_CMD_EV_IMPL           0x00  // its a prefix. need to be | with on-end 6-bit EV5,EV4,EV3,EV2,EV1,EV0

#ifndef PUST7567_BEGIN_BIAS
    #define PUST7567_BEGIN_BIAS PUST7567_CMD_BIAS_1_9
#endif

#ifndef PUST7567_BEGIN_COM
    #define PUST7567_BEGIN_COM PUST7567_CMD_COM_REVERSE
#endif

#ifndef PUST7567_BEGIN_REGULATION_RATIO
    #define PUST7567_BEGIN_REGULATION_RATIO 0b00000100
#endif

#ifndef PUST7567_BEGIN_EV
    #define PUST7567_BEGIN_EV 0b00101011
#endif

#ifndef PUST7567_BEGIN_DISPLAY
    #define PUST7567_BEGIN_DISPLAY PUST7567_CMD_DISPLAY_NORMAL
#endif

#endif