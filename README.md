# ST7567 lcd driver library

## Description

PushedST7567 is a c++ library, mainly suited for lcd 128x64 displays driven by ST7567 with I2C.

It uses display driver in page addressing mode, allowing you to write strings and chars to any position with any compatible font.

You can also use some drawing functions defined in st7567_drawing header.

## Work in progress

- [x] Full custom font support
- [x] Custom I2C library support
- [x] Char and C-string writing
- [] Check whether driver was connected with given addres or not
- [] Drawing functionality
  - [x] Rectangles
  - [x] Single Pixels
  - [] More comples geometrical shapes
  - [] Diagrams and graphics
  - [] Custom pictures (you can just define custom font wih picture)

## Requirements

1. C++ compiler with support of C++14 or later
2. Following header files in standard library:
  1. stdint.h (uintX_t type definitions)
  2. stddef.h (size_t definition)

## Compatibility

PushedST7567 uses I2C to communicate with display driver.

It has built-in support for TwoWire and TinyWireM communication libraries.

But you can adpot and use almost any other library if you want (see adoption examples).

## Motivation

There are many nice, shiny and beautiful lcd libraries for avr/esp32 etc.

But I wanted to use one library for all combinations of board+I2Clibrary+platform

And it was a bit painly to figure out that yet another library uses only Wire.h, or defines fonts in PROGMEM (if you want to use esp32), or does not allow to define custom fonts, or contains 5-6 different fonts that compiles into resulting binary file.

So, here it is. Library for ST7567 independent from Arduino.h, that allows you to use const **or** PROGMEM fonts, any I2C library you like

## Examples

Check out the examples/ subfolder

## License

PushedSSD1306 is free software, distributed without any warranty.

You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3, or (at your option) any later version.

Some separate files not so somplex or contain only simple definitions and you are free to use them
as standalone without any conditions as long as you credit me somewhere

## Have fun!
If you find this code useful, I will be glad if you use it in your GPL3-or-later-compatible licensed project.

**"Why GPL-3. Author, are you too proud?"**
> Nope. Just join us now and share the software.
> My code is neither perfect nor revolutionary. But the world is crazy, you know

Any help and criticism is greatly appreciated.