/*
 * constants.h
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// Standard Debug Level
const DebugLevel G_DEF_DBG_LVL = Critical;
// Standard Einstellung: Log in Datei
const bool G_DEF_DBG_LOGTOFILE = false;
// Fenster Titel
const char G_WINDOW_TITLE[] = "Slaint";
// Fenster Titel in High Debug Level
const char G_WINDOW_TITLE_DEV[] = "Slaint - (::) HIGH DEBUG";

// Max. Anzahl der KeyValue Keys
const int G_MAX_KEYS = 255;

// Speicher Keys
const int G_KEY_TOOL = 0;
const int G_KEY_COLOR = 1;
const int G_KEY_STRENGTH = 2;
const int G_KEY_TEST = 254;

// Speicher Values
// für G_KEY_TOOL
const int G_VALUE_TOOL_POINT = 0;
const int G_VALUE_TOOL_BOX = 1;
const int G_VALUE_TOOL_RECT = 2;
const int G_VALUE_TOOL_CONTINUITY = 3;
const int G_VALUE_TOOL_LINE = 4;
// für G_KEY_COLOR
const int G_VALUE_COLOR_BLACK = 0;
const int G_VALUE_COLOR_WHITE = 1;
const int G_VALUE_COLOR_GREYLIGHT = 2;
const int G_VALUE_COLOR_RED = 3;
const int G_VALUE_COLOR_BLUE = 4;
const int G_VALUE_COLOR_GREEN = 5;
const int G_VALUE_COLOR_YELLOW = 6;
// für G_KEY_STRENGTH
const int G_VALUE_STRENGTH_A = 1;
const int G_VALUE_STRENGTH_B = 5;
const int G_VALUE_STRENGTH_C = 9;

// Farbwerte für die verschiedenen Color-Codes
const int G_COLOR[7][3] = {
		{0, 0, 0},
		{255, 255, 255},
		{200, 200, 200},
		{255, 0, 0},
		{0, 0, 255},
		{0, 255, 0},
		{255, 255, 0}
};


// RGBA Masken
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
const Uint32 G_MASK_RED = 0xff000000;
const Uint32 G_MASK_GREEN = 0x00ff0000;
const Uint32 G_MASK_BLUE = 0x0000ff00;
const Uint32 G_MASK_ALPHA = 0x000000ff;
#else
const Uint32 G_MASK_RED = 0x000000ff;
const Uint32 G_MASK_GREEN = 0x0000ff00;
const Uint32 G_MASK_BLUE = 0x00ff0000;
const Uint32 G_MASK_ALPHA = 0xff000000;
#endif

// Flags für CreateSurface und SetVideoMode
const Uint32 G_CREATESURFACE_FLAGS = SDL_SWSURFACE | SDL_SRCALPHA;

#endif /* CONSTANTS_H_ */
