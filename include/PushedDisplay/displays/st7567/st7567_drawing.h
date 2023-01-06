/* Copyright (C) 2023 Svyatoslav Pushkerav
This file is part of PushedST7567.
PushedST7567 is free software, distributed without any warranty.
You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3, or (at your option) any later version.
See the GNU General Public License v3.
<https://www.gnu.org/licenses/gpl-3.0.html> */

#ifndef PUST7567_DRAWING_h
#define PUST7567_DRAWING_h

#include "PushedDisplay/displays/st7567/st7567_common.h"

void PUST7567::setPixel(unsigned char x, unsigned char y, bool pixel){
  unsigned char current_byte;

  setCursor(x, y);

  __put_cmd(PUST7567_CMD_READ_MODIFY_WRITE);
  pui2c_request((int)__i2c_addr, 2);
  pui2c_read();
  pui2c_read();
  pui2c_request((int)__i2c_addr, 2);
  pui2c_read();
  current_byte = pui2c_read();
  current_byte |= ((unsigned char)pixel) << (y%8);
  __put_dat(current_byte);
  __put_cmd(PUST7567_CMD_END);
}

void PUST7567::fillRect(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, bool pixeltype){
  char first_page, last_page;
  char first_page_byte = 0xff, last_page_byte = 0xff;
  unsigned char pagebuffer1[y1-y0], pagebuffer2[y1-y0], pagebuffer3[y1-y0];

  if (y1 - y0 == 0 || x1 - x0 == 0) return;

  first_page = (y0/8)-1;
  last_page = (y1/8)-1;

  if (y0%8 != 0){
    first_page += 1;
    first_page_byte = 0x00;
    for (unsigned char i = 0; i < 8 - (y0%8); i++) first_page_byte |= (0b10000000 >> i);
  }
  if (y1%8 != 0){
    last_page += 1;
    last_page_byte = 0x00;
    for (unsigned char i = 0; i < y1%8; i++) last_page_byte |= (0b00000001 << i);
  }

  for (unsigned char i = 0; i < x1-x0; i++){
    pagebuffer1[i] = first_page_byte;
    pagebuffer2[i] = last_page_byte;
    pagebuffer3[i] = 0xff;
  }

  for (unsigned char p = first_page+1; p < last_page; p++){
    setCursor(p, x0);
    __put_dat_seq(y1-y0, pagebuffer3);
  }
  setCursor(last_page, x0);
  __put_dat_seq(x1-x0, pagebuffer2);
  setCursor(first_page, x0);
  __put_dat_seq(x1-x0, pagebuffer1);
}

#endif