

/*
 *
 * Switzerland
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : Switzerland.h
 * Date                : 24.12.2011
 * Font size in bytes  : 24357
 * Font width          : 10
 * Font height         : 21
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef SWITZERLAND_H
#define SWITZERLAND_H

#define SWITZERLAND_WIDTH 10
#define SWITZERLAND_HEIGHT 21

static uint8_t Switzerland[] PROGMEM = {
    0x5F, 0x25, // size
    0x0A, // width
    0x15, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x05, 0x07, 0x0C, 0x0D, 0x15, 0x12, 0x04, 0x06, 0x06, 
    0x0A, 0x0B, 0x05, 0x07, 0x05, 0x06, 0x0E, 0x09, 0x0D, 0x0D, 
    0x0D, 0x0D, 0x0D, 0x0D, 0x0E, 0x0E, 0x05, 0x05, 0x0C, 0x0C, 
    0x0C, 0x0B, 0x0F, 0x11, 0x0F, 0x10, 0x0F, 0x0E, 0x0D, 0x11, 
    0x10, 0x06, 0x0D, 0x11, 0x0D, 0x13, 0x11, 0x11, 0x0E, 0x11, 
    0x10, 0x0F, 0x0E, 0x10, 0x11, 0x16, 0x11, 0x11, 0x0F, 0x07, 
    0x06, 0x07, 0x0B, 0x0B, 0x06, 0x0F, 0x0D, 0x0E, 0x0E, 0x0E, 
    0x09, 0x0D, 0x0D, 0x05, 0x06, 0x0E, 0x05, 0x14, 0x0D, 0x0D, 
    0x0D, 0x0E, 0x09, 0x0B, 0x09, 0x0D, 0x0D, 0x14, 0x0E, 0x0D, 
    0x0C, 0x08, 0x03, 0x08, 0x0C, 0x0C, 
    
    // font data
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xE0, 0xE7, 0xE7, 0xE7, 0xE0, 0x08, 0x08, 0x08, 0x08, 0x08, // 33
    0x7E, 0x7E, 0x7E, 0x00, 0x7E, 0x7E, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 34
    0x00, 0xC0, 0xC0, 0xE0, 0xFE, 0xFE, 0xC0, 0xC0, 0xFE, 0xFE, 0xC2, 0xC0, 0x0C, 0x0C, 0xFC, 0xFF, 0x1F, 0x0C, 0xEC, 0xFF, 0x7F, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 35
    0xF8, 0xFC, 0xFC, 0xDE, 0x8E, 0xFF, 0xFF, 0x8E, 0x1E, 0x3E, 0x3C, 0x38, 0x30, 0x70, 0xF1, 0xF3, 0xE3, 0xC7, 0xFF, 0xFF, 0xC7, 0xCF, 0xFF, 0xFE, 0xFE, 0x3C, 0x00, 0x00, 0x00, 0x08, 0x08, 0x38, 0x38, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // 36
    0x70, 0xFC, 0xFC, 0xDE, 0x8E, 0x8E, 0xDE, 0xFC, 0xFC, 0x70, 0x00, 0xC0, 0xF0, 0x3C, 0x0E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0xC1, 0xF1, 0x3C, 0x0F, 0x03, 0x78, 0xFE, 0xFE, 0xCF, 0x87, 0x87, 0xFE, 0xFE, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x18, 0x18, 0x18, 0x08, 0x08, 0x00, // 37
    0x00, 0x00, 0x78, 0xFC, 0xFC, 0xFE, 0xCE, 0x8E, 0xCE, 0xFE, 0xFC, 0xFC, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xFE, 0xFE, 0xFF, 0xFF, 0xC7, 0xC7, 0xCF, 0xFF, 0xFF, 0xFD, 0xF8, 0xFC, 0xFE, 0xFE, 0xCE, 0x82, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 38
    0x9E, 0xDE, 0xFE, 0x7E, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 39
    0xC0, 0xF8, 0xFE, 0xFE, 0x3E, 0x06, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x38, 0xF8, 0xF8, 0xF8, 0x80, // 40
    0x02, 0x3E, 0xFE, 0xFE, 0xF8, 0xC0, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xF8, 0xF8, 0xF8, 0x38, 0x00, // 41
    0x20, 0x38, 0xB0, 0xF0, 0xFE, 0xFE, 0xF0, 0xB0, 0x38, 0x10, 0x00, 0x02, 0x07, 0x03, 0x01, 0x00, 0x07, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1C, 0x1C, 0x1C, 0xFF, 0xFF, 0xFF, 0x1C, 0x1C, 0x1C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 43
    0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xC8, 0xE8, 0x78, 0x78, 0x18, // 44
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 45
    0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x08, 0x08, 0x08, 0x08, 0x08, // 46
    0x00, 0x00, 0xC0, 0xF8, 0xFE, 0x3E, 0xC0, 0xFC, 0xFF, 0x1F, 0x03, 0x00, 0x38, 0x38, 0x08, 0x00, 0x00, 0x00, // 47
    0xE0, 0xF0, 0xFC, 0xFC, 0xFE, 0x1E, 0x0E, 0x0E, 0x1E, 0xFE, 0xFC, 0xFC, 0xF8, 0xE0, 0x0F, 0x3F, 0xFF, 0xFF, 0xFF, 0xE0, 0xC0, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 48
    0xE0, 0xE0, 0xE0, 0xF0, 0xF8, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // 49
    0x00, 0xF0, 0xFC, 0xFC, 0x3E, 0x0E, 0x0E, 0x8E, 0xFE, 0xFE, 0xFC, 0xFC, 0xF0, 0x80, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xDF, 0xCF, 0xCF, 0xC7, 0xC3, 0xC0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 50
    0x20, 0x38, 0x3C, 0x3C, 0x1E, 0x0E, 0x0E, 0x8E, 0xFE, 0xFC, 0xFC, 0xF8, 0x20, 0x70, 0xF0, 0xF0, 0xF0, 0xE0, 0xC0, 0xC7, 0xC7, 0xFF, 0xFF, 0xFF, 0x7C, 0x3C, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // 51
    0x00, 0x00, 0xC0, 0xE0, 0xF0, 0x7C, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x3E, 0x3F, 0x3F, 0x3B, 0x38, 0x38, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, // 52
    0x00, 0xF8, 0xFC, 0xFC, 0xFC, 0x9C, 0x9C, 0x9C, 0x9C, 0x9C, 0x1C, 0x1C, 0x00, 0x66, 0xE7, 0xE7, 0xE7, 0xC7, 0xC3, 0xC3, 0xE7, 0xFF, 0xFF, 0xFF, 0x7F, 0x3E, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 53
    0xC0, 0xF8, 0xFC, 0xFC, 0xFE, 0x1E, 0x8E, 0x8E, 0x9E, 0x9E, 0x1C, 0x18, 0x20, 0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xE3, 0xC3, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // 54
    0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x9C, 0xDC, 0xFC, 0xFC, 0xFC, 0x3C, 0x1C, 0x00, 0x00, 0x00, 0xE0, 0xFC, 0xFE, 0xFF, 0xFF, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0x00, 0xF8, 0xFC, 0xFC, 0xFE, 0x9E, 0x0E, 0x0E, 0x9E, 0xFE, 0xFC, 0xFC, 0xF8, 0x00, 0x38, 0x7C, 0xFF, 0xFF, 0xFF, 0xE7, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF, 0xFF, 0x7E, 0x38, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // 56
    0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0x1E, 0x0E, 0x0E, 0x1E, 0xFE, 0xFC, 0xFC, 0xF0, 0xE0, 0x21, 0x63, 0xE7, 0xEF, 0xEF, 0xCF, 0xCE, 0xCE, 0xE7, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 57
    0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0x08, 0x08, 0x08, 0x08, 0x08, // 58
    0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0xC8, 0xE8, 0x78, 0x78, 0x18, // 59
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xE0, 0x0C, 0x1E, 0x1E, 0x3E, 0x3F, 0x33, 0x73, 0x63, 0xE1, 0xE1, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, // 60
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0xE0, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xE1, 0xE1, 0x63, 0x73, 0x33, 0x3F, 0x3E, 0x1E, 0x1E, 0x0C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x38, 0x3C, 0x3C, 0x3E, 0x0E, 0x8E, 0xFE, 0xFE, 0xFC, 0xFC, 0x78, 0x00, 0x00, 0x00, 0xE6, 0xE7, 0xE7, 0xE3, 0xE1, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // 63
    0xC0, 0xF0, 0x38, 0x1C, 0xCC, 0xE6, 0xE6, 0x66, 0x66, 0xC6, 0xEE, 0x6C, 0x38, 0xF0, 0xE0, 0x0F, 0x3F, 0x70, 0xEF, 0xDF, 0xBF, 0xB8, 0xB0, 0x90, 0xBF, 0xBF, 0xE0, 0x58, 0x4F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 64
    0x00, 0x00, 0x00, 0x80, 0xE0, 0xFC, 0xFE, 0xFE, 0x3E, 0xFE, 0xFE, 0xFC, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFC, 0xFF, 0xFF, 0xFF, 0x7F, 0x71, 0x70, 0x73, 0x7F, 0xFF, 0xFF, 0xFF, 0xFC, 0xE0, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // 65
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x8E, 0x8E, 0x8E, 0xFE, 0xFE, 0xFE, 0xFC, 0x78, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0xE7, 0xFF, 0xFF, 0xFF, 0xFE, 0x3C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // 66
    0xC0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0x7E, 0x1E, 0x1E, 0x1E, 0x1E, 0x7E, 0x7C, 0x7C, 0x78, 0x60, 0x0F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xF0, 0xE0, 0xE0, 0xE0, 0xE0, 0xF8, 0xF8, 0xF8, 0x78, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 67
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x1E, 0xFE, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, // 68
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x8E, 0x0E, 0x0E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC0, 0xC0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 69
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 70
    0xC0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0x7E, 0x1E, 0x1E, 0x1E, 0x1E, 0x3E, 0x7C, 0x7C, 0x78, 0x70, 0x00, 0x0F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xF0, 0xE0, 0xE0, 0xE0, 0xE7, 0xF7, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, // 71
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x80, 0x80, 0x80, 0x80, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x07, 0x07, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 72
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 73
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x3C, 0x7C, 0xFC, 0xFC, 0xFC, 0xE0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // 74
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xC0, 0xF0, 0xF8, 0xFC, 0xFE, 0x3E, 0x1E, 0x0E, 0x06, 0x02, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x07, 0x1F, 0x7F, 0xFF, 0xFE, 0xFC, 0xF0, 0xE0, 0x80, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 75
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 76
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xF0, 0x00, 0x00, 0x80, 0xF0, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x1F, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0x1F, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // 77
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFC, 0xF0, 0xE0, 0x80, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x07, 0x1F, 0x3F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 78
    0xC0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0x3E, 0x1E, 0x1E, 0x1E, 0x3E, 0xFE, 0xFC, 0xFC, 0xF8, 0xF0, 0xC0, 0x0F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xF0, 0xE0, 0xE0, 0xE0, 0xF0, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, // 79
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0xFE, 0xFE, 0xFE, 0xFC, 0xF8, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0E, 0x0E, 0x0F, 0x0F, 0x0F, 0x07, 0x07, 0x01, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0xC0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0x3E, 0x1E, 0x1E, 0x1E, 0x3E, 0xFE, 0xFC, 0xFC, 0xF8, 0xF0, 0xC0, 0x0F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xF0, 0xE0, 0xE8, 0xFE, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x9F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x18, 0x18, 0x08, 0x08, // 81
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x0E, 0x1E, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x07, 0x07, 0x0F, 0xFF, 0xFF, 0xFF, 0xFD, 0xF8, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 82
    0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0xCE, 0xCE, 0x9E, 0x9E, 0x9E, 0x1C, 0x1C, 0x18, 0x20, 0x30, 0x71, 0xF1, 0xF3, 0xF3, 0xF3, 0xE7, 0xC7, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 83
    0x1E, 0x1E, 0x1E, 0x1E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x1E, 0x1E, 0x1E, 0x1E, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 84
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xE0, 0xE0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 85
    0x02, 0x1E, 0xFE, 0xFE, 0xFE, 0xFE, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0xFE, 0xFE, 0xFE, 0xFE, 0x1E, 0x02, 0x00, 0x00, 0x00, 0x07, 0x3F, 0xFF, 0xFF, 0xFF, 0xF0, 0xFF, 0xFF, 0xFF, 0x1F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 86
    0x7E, 0xFE, 0xFE, 0xFE, 0xFC, 0x80, 0x00, 0xE0, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xE0, 0x00, 0x80, 0xFC, 0xFE, 0xFE, 0xFE, 0x7E, 0x06, 0x00, 0x07, 0x7F, 0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0x0F, 0x00, 0x1F, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0xFF, 0x7F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 87
    0x02, 0x0E, 0x1E, 0x7E, 0xFE, 0xFE, 0xFC, 0xF0, 0xE0, 0xF8, 0xFE, 0xFE, 0x7E, 0x3E, 0x0E, 0x06, 0x02, 0x80, 0xC0, 0xF0, 0xF8, 0xFE, 0xFF, 0x7F, 0x1F, 0x1F, 0x7F, 0xFF, 0xFE, 0xF8, 0xF0, 0xE0, 0x80, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 88
    0x02, 0x06, 0x1E, 0x7E, 0xFE, 0xFE, 0xFC, 0xF0, 0xE0, 0xC0, 0xF8, 0xFE, 0xFE, 0xFE, 0x3E, 0x0E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, // 89
    0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x8E, 0xCE, 0xEE, 0xFE, 0xFE, 0xFE, 0xFE, 0x7E, 0x1E, 0x0E, 0xE0, 0xF0, 0xF8, 0xFC, 0xFF, 0xFF, 0xFF, 0xDF, 0xCF, 0xC3, 0xC1, 0xC0, 0xC0, 0xC0, 0xC0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 90
    0xFE, 0xFE, 0xFE, 0xFE, 0x0E, 0x0E, 0x0E, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xE0, 0xE0, 0xE0, // 91
    0x3E, 0xFE, 0xF8, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1F, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 92
    0x0E, 0x0E, 0x0E, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xE0, 0xE0, 0xF8, 0xF8, 0xF8, 0xF8, // 93
    0x00, 0x80, 0xE0, 0xFC, 0x3E, 0x0E, 0x3E, 0xFC, 0xF0, 0x80, 0x00, 0x02, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, // 95
    0x06, 0x06, 0x0E, 0x0E, 0x0C, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 96
    0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x70, 0xF9, 0xF9, 0xFD, 0xFD, 0xDD, 0x9C, 0x8C, 0xCE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 97
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xE1, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // 98
    0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x3E, 0x7F, 0xFF, 0xFF, 0xFF, 0xE1, 0xC0, 0xC0, 0xE1, 0xF3, 0xF3, 0xF3, 0x73, 0x33, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 99
    0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xE1, 0xC0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // 100
    0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x1E, 0x7F, 0xFF, 0xFF, 0xFF, 0xED, 0xCC, 0xCC, 0xCC, 0xED, 0xEF, 0xEF, 0x6F, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 101
    0xE0, 0xE0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFE, 0xEE, 0xEE, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, // 102
    0x00, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x1F, 0x7F, 0x7F, 0xFF, 0xFF, 0xF0, 0xE0, 0x61, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x30, 0x70, 0x70, 0xF0, 0xF0, 0xE0, 0xE0, 0xF8, 0xF8, 0x78, 0x78, 0x18, // 103
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // 104
    0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x08, 0x08, // 105
    0x00, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xF8, 0xF8, 0xF8, 0x78, 0x38, // 106
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0x60, 0x20, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x3F, 0xFF, 0xFF, 0xFD, 0xF0, 0xE0, 0x80, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 107
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x08, 0x08, // 108
    0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // 109
    0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // 110
    0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xE1, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 111
    0xE0, 0xE0, 0xE0, 0xE0, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // 112
    0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0xE0, 0xE0, 0xE0, 0xE0, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xE1, 0xC0, 0xC0, 0xE1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, // 113
    0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xE0, 0xE0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x03, 0x03, 0x03, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 114
    0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0x60, 0x60, 0xE0, 0xE0, 0xC0, 0x80, 0x63, 0xE7, 0xE7, 0xEF, 0xEF, 0xCF, 0xDE, 0xFE, 0xFE, 0xFC, 0x7C, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // 115
    0xE0, 0xE0, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xE0, 0xE0, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 116
    0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // 117
    0xE0, 0xE0, 0xE0, 0xE0, 0x80, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0x20, 0x01, 0x0F, 0x7F, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0xFF, 0x7F, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 118
    0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0x60, 0x03, 0x1F, 0xFF, 0xFF, 0xFF, 0xF0, 0xFE, 0xFF, 0x3F, 0x03, 0x3F, 0xFF, 0xFE, 0xE0, 0xFE, 0xFF, 0xFF, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 119
    0x20, 0x60, 0xE0, 0xE0, 0xE0, 0xE0, 0x80, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0x60, 0x20, 0x00, 0x80, 0xE0, 0xF3, 0xFF, 0xFF, 0x7F, 0x7F, 0xFF, 0xFF, 0xF3, 0xE0, 0x80, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 120
    0xE0, 0xE0, 0xE0, 0xE0, 0x80, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0x20, 0x01, 0x0F, 0x7F, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0xFF, 0x7F, 0x0F, 0x01, 0x00, 0x00, 0xE0, 0xE0, 0xF8, 0xF8, 0xF8, 0x78, 0x78, 0x18, 0x00, 0x00, 0x00, 0x00, // 121
    0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xE0, 0xF0, 0xFC, 0xFE, 0xFF, 0xFF, 0xDF, 0xCF, 0xC3, 0xC1, 0xC0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, // 122
    0x00, 0x00, 0xFC, 0xFE, 0xFE, 0xFE, 0x02, 0x02, 0x08, 0x0C, 0xFF, 0xFF, 0xFF, 0xF3, 0x00, 0x00, 0x00, 0x00, 0x78, 0xF8, 0xF8, 0xF8, 0x80, 0x80, // 123
    0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0x08, 0x08, 0x08, // 124
    0x02, 0x02, 0xFE, 0xFE, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xF3, 0xFF, 0xFF, 0xFF, 0x04, 0x08, 0x80, 0x80, 0xF8, 0xF8, 0xF8, 0x78, 0x00, 0x00, // 125
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x3C, 0x1E, 0x0E, 0x0E, 0x1C, 0x1C, 0x38, 0x38, 0x38, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xF8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xF8, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 // 127
    
};

#endif