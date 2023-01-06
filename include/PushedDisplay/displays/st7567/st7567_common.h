/* Copyright (C) 2023 Svyatoslav Pushkerav
This file is part of PushedST7567.
PushedST7567 is free software, distributed without any warranty.
You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3, or (at your option) any later version.
See the GNU General Public License v3.
<https://www.gnu.org/licenses/gpl-3.0.html> */

#ifndef PUST7567_COMMON_h
#define PUST7567_COMMON_h

#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "PushedDisplay/displays/st7567/st7567_cmd.h"
#include "PushedDisplay/displays/st7567/st7567_sharedconfigurable.h"



enum pu_st7567_contrast_e {
  BrLow,
  BrMed,
  BrHigh
};


class PUST7567{
  public:
    PUST7567(){}

    /**
     * Begin connection with I2C
     * @param addr uint8_t, address of display
     * @return bool, true if connected
    */
    bool begin(uint8_t addr);

    /**
     * Get current display address
     * @return uint8_t address byte
    */
    uint8_t getAddress();

    /**
     * Soft-reset display.
     * See datasheet for driver to know which settings will be erased.
    */
    void reset(void);

    /**
     * Set display contrast value.
    */
    void setContrast(pu_st7567_contrast_e contrast);

    /**
     * Enter powersave mode.
     * @param mode bool, true - go to powersave, false - go out from powersave
    */
    void powersave(bool mode);

    /**
     * Run simple display tests.
     * Test includes: sequential pixel enable/disable, writing at 0page,0col
    */
    void test(void);

    /**
     * Toggle one single pixel
     * @param pixel bool, true - pixel ON, false - pixel OFF
    */
    void setPixel(uint8_t x, uint8_t y, bool pixel);

    /**
     * Clear display by writing 0x00 to DRAM
    */
    void clear(void);

    /**
     * Set one songle byte
     * @param page uint8_t page index
     * @param col uint8_t column in page index
     * @param byte uint8_t byte to write
    */
    void writeByte(uint8_t byte);

    /**
     * Set display DRAM cursor on given position.
     * @param page uint8_t page index
     * @param col uint8_t column in page index
    */
    void setCursor(uint8_t page, uint8_t col);

    /**
     * Write ASCII char to cursor position.
     * After writing DRAM cursor will automatically move to the end of written data index
     * @tparam FontWidth amount of bytes per page used by symbol
     * @tparam FontHeight amount of pages used by symbol
     * @param font font to use
     * @param char char to write
    */
    template <uint8_t FontWidth=5, uint8_t FontHeight=1>
    void writeChar(const uint8_t font[][FontHeight][FontWidth], char c, uint8_t char_spacing = 1)
    {
      uint8_t symbolbuffer[FontWidth];
      c -= 32;
      if (c > 127) c = 0;
      switch (FontHeight){
        case 1:
          pu_read_font_page(symbolbuffer, font, c, 0);
          __put_dat_seq(FontWidth, symbolbuffer);
          break;
        default:
          {
            uint8_t origin_page = __cache_page;
            for (uint8_t ipage = 0; ipage < FontHeight; ipage++){
                pu_read_font_page(symbolbuffer, font, c, ipage);
                __put_dat_seq(FontWidth, symbolbuffer);
              for (uint8_t sp = 0; sp < char_spacing; sp++) writeByte(0x00);
              setCursor(__cache_page+1, __cache_col);
            }
            setCursor(origin_page, __cache_col+FontWidth+char_spacing);
          }
          break;
      }
    }
  
    /**
     * Write ASCII text from cursor position.
     * If text length in bytes is longer than page, text tail will be lost.
     * @tparam FontWidth amount of bytes per page used by symbol
     * @tparam FontHeight amount of pages used by symbol
     * @param font font to use
     * @param text text to write
     * @param char_spacing spacing between symbols in string
    */
    template <uint8_t FontWidth=5, uint8_t FontHeight=1>
    void writeString(const uint8_t font[][FontHeight][FontWidth], const char *text, uint8_t char_spacing=1)
    {
      for (size_t i = 0; i < strlen(text); i++){
        if (text[i] == '\0') break;
        writeChar<FontWidth, FontHeight>(font, text[i], char_spacing);
      }
    }

    /**
     * Fill specified rectangle with pixels.
     * If rectangle takes not full page, other page content will be erased.
     * @param x0 top-x position
     * @param y0 left-y position
     * @param x1 bottom-x position
     * @param y1 right-y position
     * @param pixeltype true - pixel ON, false - pixel OFF
    */
    void fillRect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool pixeltype = true);

  private:
    uint8_t __cache_col;  // Last col set by setCursor
    uint8_t __cache_page; // Last page set by setCursor
    uint8_t __i2c_addr;
    /**
     * Send one command byte to driver.
     * Use only for commands.
     * @param cmdbyte command byte (see driver docs)
    */
    void __put_cmd(uint8_t cmdbyte);
    /**
     * Send one data byte to display DRAM.
     * Use only for data.
     * @param datbyte data byte (one column of selected page)
    */
    void __put_dat(uint8_t datbyte);
    /**
     * Send many data bytes at once.
     * Use only for data.
     * Do not send more than 16 bytes as once. Bigger sequences may be trimmed by display driver.
     * @param len length of byte sequence
     * @param datbytes bytes to send
    */
    void __put_dat_seq(uint8_t len, const uint8_t* datbytes);
};


#endif