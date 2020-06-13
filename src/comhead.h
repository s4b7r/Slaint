/*
 * comhead.h
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#ifndef COMHEAD_H_
#define COMHEAD_H_

// Globale Zeiger auf Singletons
#define GP_DBG CDebug::get()
#define GP_LOGIC CLogic::get()

// System Includes
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <vector>
#include <list>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <typeinfo>
#include <string.h>

// Forward Deklaration
class CSection;
class CButton;

// Interne Includes
#include "singleton.h"
#include "debug.h"
#include "constants.h"
#include "listener.h"
#include "section.h"
#include "canvas.h"
#include "window.h"
#include "button.h"
#include "logic.h"


#endif /* COMHEAD_H_ */
