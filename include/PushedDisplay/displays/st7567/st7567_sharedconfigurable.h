/* Copyright (C) 2023 Svyatoslav Pushkerav
This file is part of PushedST7567.
This particular file is provided to you for any use you see fit.
If used as part of the project within which it is published, see the project license.
However, this particular file may be used independently by you in full freedom of action without restrictions.
The only condition is that you will credit me in modified or copied version of this file.
If this file is modified, please also add a note that the file has been modified.
If you include the contents of this file in another project, please credit me to your new file.
*/

#ifndef PUST7567_SHAREDCONFIGURABLE_h
#define PUST7567_SHAREDCONFIGURABLE_h

#include <stdint.h>
#include <stddef.h>

void pui2c_begin(void);
void pui2c_transmit(uint8_t addr);
uint8_t pui2c_request(uint8_t addr, uint8_t wrbytes);
size_t pui2c_write(uint8_t wrbyte);
int pui2c_read(void);
uint8_t pui2c_end(void);


template <uint8_t FontWidth, uint8_t FontHeight>
void pu_read_font_page(uint8_t *buffer, const uint8_t font[][FontHeight][FontWidth], uint8_t numchar, uint8_t numpage);

#endif