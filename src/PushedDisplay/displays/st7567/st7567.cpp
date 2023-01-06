/* Copyright (C) 2023 Svyatoslav Pushkerav
This file is part of PushedST7567.
PushedST7567 is free software, distributed without any warranty.
You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3, or (at your option) any later version.
See the GNU General Public License v3.
<https://www.gnu.org/licenses/gpl-3.0.html> */

#include "PushedDisplay/displays/st7567/st7567_common.h"

bool PUST7567::begin(uint8_t addr){
  pui2c_begin();  
  __i2c_addr = addr;

  __put_cmd(PUST7567_CMD_DISPLAY_OFF);
  __put_cmd(PUST7567_BEGIN_DISPLAY);

  reset();
  __put_cmd(PUST7567_BEGIN_BIAS);
  __put_cmd(PUST7567_BEGIN_COM);
  __put_cmd(PUST7567_CMD_REGULATION_RATIO | PUST7567_BEGIN_REGULATION_RATIO);
  __put_cmd(PUST7567_CMD_EV_DEFINE);
  __put_cmd(PUST7567_CMD_EV_IMPL | PUST7567_BEGIN_EV);
  __put_cmd(0x2F);
  clear();
  __put_cmd(PUST7567_CMD_DISPLAY_ON);
  return true;
}

uint8_t PUST7567::getAddress(){
  return __i2c_addr;
}

void PUST7567::powersave(bool mode){
  if (mode){
    __put_cmd(PUST7567_CMD_DISPLAY_OFF);
    __put_cmd(PUST7567_CMD_DISPLAY_ALLPIXEL);
  }else{
    __put_cmd(PUST7567_CMD_DISPLAY_NONPIXEL);
    __put_cmd(PUST7567_CMD_DISPLAY_ON);
  }
}

void PUST7567::reset(){
  __put_cmd(PUST7567_CMD_RESET);
}

void PUST7567::clear(){
  const uint8_t empty[] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
  for (uint8_t page = 0; page < 8; page++){
    setCursor(page, 0);
    for (uint8_t i = 0; i < 8; i++){
      __put_dat_seq(16, empty);
    }
  }
}

void PUST7567::setContrast(pu_st7567_contrast_e contrast){
  switch (contrast){
    case BrLow: 
      __put_cmd(PUST7567_CMD_REGULATION_RATIO | 0b00000011);
      break;
    case BrMed:
      __put_cmd(PUST7567_CMD_REGULATION_RATIO | 0b000000100);
      break;
    case BrHigh:
      __put_cmd(PUST7567_CMD_REGULATION_RATIO | 0b000000101);
      break;
    default: break;
  }
}

void PUST7567::test(){
  uint8_t label00[] = {0xf2,0x95,0xf0,0x0,0xf2,0x91,0xf2};

  for(int x=0; x<8; x++){
    for(int y=0; y<128; y++){
      setCursor(x, y);
      writeByte(0xff);
      }  
  }
  for(int x=0; x<8; x++){
    for(int y=0; y<128; y++){
      setCursor(x, y);
      writeByte(0x00);
      }  
  }

  clear();

  setCursor(0, 0);
  __put_dat_seq(7, label00);
}

void PUST7567::writeByte(uint8_t byte){
  __put_dat(byte);
}

void PUST7567::setCursor(uint8_t page, uint8_t col){
  __put_cmd(PUST7567_CMD_SET_PAGE + page);
  __put_cmd(PUST7567_CMD_SET_COLUMN_MSB + col/16);
  __put_cmd(PUST7567_CMD_SET_COLUMN_LSB + col%16);

  __cache_col = col;
  __cache_page = page;
}

void PUST7567::__put_dat_seq(uint8_t len, const uint8_t* datbytes){
  pui2c_transmit(__i2c_addr);
  for (unsigned int i = 0; i < len; i++){
    pui2c_write(PUST7567_BYTE_DAT_CONT);
    pui2c_write(datbytes[i]);
  }
  pui2c_end();
}

void PUST7567::__put_cmd(uint8_t cmdbyte){
  pui2c_transmit(__i2c_addr);
  pui2c_write(PUST7567_BYTE_CMD_ONE);
  pui2c_write(cmdbyte);
  pui2c_end();
}

void PUST7567::__put_dat(uint8_t datbyte){
  pui2c_transmit(__i2c_addr);
  pui2c_write(PUST7567_BYTE_DAT_ONE);
  pui2c_write(datbyte);
  pui2c_end();
}