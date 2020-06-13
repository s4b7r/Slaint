/*
 * window.cpp
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#include "comhead.h"

CWindow::CWindow(int width, int height)
: CSection(0, 0, width, height)
{
	GP_DBG->debug("Create window %d x%d", width, height);

	GP_DBG->debug("Init SDL-Video-System...");
	// SDL initialisieren
	// SDL_INIT_VIDEO initialisiert Video- und Event-System
	SDL_Init(SDL_INIT_VIDEO);
	GP_DBG->debug("SDL-Video initialised");

	// Geerbtes Surface löschen
	delete(m_pSurface);
	GP_DBG->debug("Set SDL-Video-Mode...");
	// Neues Fenster als Surface setzen
	// SDL_SWSURFACE erzeugt Surface im RAM
	// 32 = 32 Bit Farbtiefe
	m_pSurface = SDL_SetVideoMode(width, height, 32, G_CREATESURFACE_FLAGS);
	GP_DBG->debug("SDL-Video-Mode set");

	// Fenster-Titel setzen
	SDL_WM_SetCaption(G_WINDOW_TITLE, "");
	if(GP_DBG->isActive(HighDebug)) SDL_WM_SetCaption(G_WINDOW_TITLE_DEV, "");

}

void CWindow::updateSurface()
{
	GP_DBG->debug("Update window");
	CSection::updateSurface();
	GP_DBG->debug("Flip...");
	SDL_Flip(m_pSurface);
	GP_DBG->debug("Flipped");
}

void CWindow::updateCanvasRect(CCanvas *pCanvas, int x1, int y1, int x2, int y2)
{
	pCanvas->updateCanvasRect(*this, x1, y1, x2, y2);
	SDL_UpdateRect(m_pSurface, (x1 < x2 ? x1 : x2) + pCanvas->getRect().x, (y1 < y2 ? y1 : y2) + pCanvas->getRect().y, x1 < x2 ? x2 - x1 : x1 - x2, y1 < y2 ? y2 - y1 : y1 - y2); // TODO xy2 statt wh
}
