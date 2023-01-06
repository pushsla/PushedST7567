/* Copyright (C) 2023 Svyatoslav Pushkerav
This file is part of PushedST7567.
PushedST7567 is free software, distributed without any warranty.
You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3, or (at your option) any later version.
See the GNU General Public License v3.
<https://www.gnu.org/licenses/gpl-3.0.html> */

#ifndef PUST7567_h
#define PUST7567_h

#include "PushedDisplay/displays/st7567/st7567_common.h"
#include "PushedDisplay/displays/st7567/st7567_sharedconfigurable.h"


#ifndef PUREADFONT
#define PUREADFONT

  #if defined(__PGMSPACE_H_)
    #include <avr/pgmspace.h>
    template <uint8_t FontWidth, uint8_t FontHeight>
    void pu_read_font_page(uint8_t* buffer, const uint8_t font[][FontHeight][FontWidth], uint8_t numchar, uint8_t numpage){
      memcpy_P(buffer, font[numchar][numpage], FontWidth);
    }
  #else
    template <uint8_t FontWidth, uint8_t FontHeight>
    void pu_read_font_page(uint8_t* buffer, const uint8_t font[][FontHeight][FontWidth], uint8_t numchar, uint8_t numpage){
      memcpy(buffer, font[numchar][numpage]);
    }
  #endif

#endif


#ifndef PUI2C_ADOPT
  #define PUI2C_ADOPT
  #if defined(TwoWire_h) || defined(USIWire_h)
    #include <Wire.h>
    void pui2c_begin(){
      Wire.begin();
    }
    void pui2c_transmit(uint8_t addr){
      Wire.beginTransmission(addr);
    }
    uint8_t pui2c_request(uint8_t addr, uint8_t wrbytes){
      return Wire.requestFrom(addr, wrbytes);
    }
    size_t pui2c_write(uint8_t wrbyte){
      return Wire.write(wrbyte);
    }
    int pui2c_read(){
      return Wire.read();
    }
    uint8_t pui2c_end(){
      return Wire.endTransmission();
    }
  #elif defined(TinyWireM_h)
    #include <TinyWireM.h>
    void pui2c_begin(){
      TinyWireM.begin();
    }
    void pui2c_transmit(uint8_t addr){
      TinyWireM.beginTransmission(addr);
    }
    uint8_t pui2c_request(uint8_t addr, uint8_t wrbytes){
      return TinyWireM.requestFrom(addr, wrbytes);
    }
    size_t pui2c_write(uint8_t wrbyte){
      return TinyWireM.write(wrbyte);
    }
    int pui2c_read(){
      return TinyWireM.read();
    }
    uint8_t pui2c_end(){
      return TinyWireM.endTransmission();
    }
  #else
    #error "No I2C provider included or adopted"
  #endif
#endif


#endif