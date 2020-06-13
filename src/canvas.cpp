/*
 * canvas.cpp
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#include "comhead.h"

CCanvas::CCanvas(int x, int y, int width, int height)
: CSection(x, y, width, height)
{
	GP_DBG->debug("Create canvas %d", getSectionId(), width, height, x, y);

	// Member initialisieren
	m_myListener.listenMouseDown = true;
	m_myListener.listenMouseUp = true;
	m_myListener.listenMouseMove = true;
	m_startX = 0;
	m_startY = 0;
	m_inAction = false;

	m_pVisibleSurface = SDL_CreateRGBSurface(G_CREATESURFACE_FLAGS, width, height, 32, G_MASK_RED, G_MASK_GREEN, G_MASK_BLUE, G_MASK_ALPHA);
	m_pOverlay = SDL_CreateRGBSurface(G_CREATESURFACE_FLAGS, width, height, 32, G_MASK_RED, G_MASK_GREEN, G_MASK_BLUE, G_MASK_ALPHA);

	// Canvas grundsätzlich weiß
	boxColor(m_pSurface, 0, 0, width, height, GP_LOGIC->getColor(G_VALUE_COLOR_WHITE));
	boxColor(m_pVisibleSurface, 0, 0, width, height, GP_LOGIC->getColor(G_VALUE_COLOR_WHITE));
	// Overlay grundsätzlich transparent
	SDL_FillRect(m_pOverlay, NULL, SDL_MapRGBA(m_pOverlay->format, 0, 0, 0, 0));
}

void CCanvas::onEvent(SDL_MouseButtonEvent *event)
{
	GP_DBG->debug("Canvas %d got event", getSectionId());
	if( event->state == SDL_PRESSED )
	{
		m_startX = event->x;
		m_startY = event->y;
	}
	if( event->button == SDL_BUTTON_LEFT )
	{
		switch( GP_LOGIC->getKeyValue(G_KEY_TOOL) )
		{
		case G_VALUE_TOOL_POINT:
			if( event->state == SDL_PRESSED )
			{
				GP_DBG->debug("Point @ %d ,%d", event->x, event->y);
				pixelColorS(m_pSurface, event->x, event->y, GP_LOGIC->getColor(), GP_LOGIC->getKeyValue(G_KEY_STRENGTH));
				GP_LOGIC->updateWindow(); // TODO canvas rect statt upd
				//GP_LOGIC->updateCanvasRect(event->x, event->y, event->x, event->y);
			}
			break;
		case G_VALUE_TOOL_BOX:
			if( event->state == SDL_PRESSED)
			{
				// Start des Rechtecks
				m_inAction = true;
			}
			else if( event->state == SDL_RELEASED && m_inAction )
			{
				// Ende des Rechtecks
				SDL_FillRect(m_pOverlay, NULL, SDL_MapRGBA(m_pOverlay->format, 0, 0, 0, 0));
				boxColorS(m_pSurface, m_startX, m_startY, event->x, event->y, GP_LOGIC->getColor(), GP_LOGIC->getKeyValue(G_KEY_STRENGTH));
				GP_LOGIC->updateWindow(); // TODO canvas rect statt upd
				//GP_LOGIC->updateCanvasRect(m_startX, m_startY, event->x, event->y);
				m_inAction = false;
			}
			break;
		case G_VALUE_TOOL_RECT:
			if( event->state == SDL_PRESSED)
			{
				// Start des Rechtecks
				m_inAction = true;
			}
			else if( event->state == SDL_RELEASED && m_inAction )
			{
				// Ende des Rechtecks
				SDL_FillRect(m_pOverlay, NULL, SDL_MapRGBA(m_pOverlay->format, 0, 0, 0, 0));
				rectangleColorS(m_pSurface, m_startX, m_startY, event->x, event->y, GP_LOGIC->getColor(), GP_LOGIC->getKeyValue(G_KEY_STRENGTH));
				GP_LOGIC->updateWindow(); // TODO canvas rect statt upd
				//GP_LOGIC->updateCanvasRect(m_startX, m_startY, event->x, event->y);
				m_inAction = false;
			}
			break;
		case G_VALUE_TOOL_CONTINUITY:
			if( event->state == SDL_PRESSED )
			{
				m_inAction = true;
			}
			else if( event->state == SDL_RELEASED && m_inAction )
			{
				m_inAction = false;
			}
			break;
		case G_VALUE_TOOL_LINE:
			if( event->state == SDL_PRESSED )
			{
				m_startX = event->x;
				m_startY = event->y;
				m_inAction = true;
			}
			else if( event->state == SDL_RELEASED && m_inAction )
			{
				m_inAction = false;
				SDL_FillRect(m_pOverlay, NULL, SDL_MapRGBA(m_pOverlay->format, 0, 0, 0, 0));
				lineColorS(m_pSurface, m_startX, m_startY, event->x, event->y, GP_LOGIC->getColor(), GP_LOGIC->getKeyValue(G_KEY_STRENGTH));
				GP_LOGIC->updateWindow(); // TODO canvas rect statt upd
				//GP_LOGIC->updateCanvasRect(m_startX, m_startY, event->x, event->y);
			}
			break;
		}
	}
}

void CCanvas::onMouseMove(SDL_MouseMotionEvent *event)
{
	if( m_inAction )
	{
		switch (GP_LOGIC->getKeyValue(G_KEY_TOOL)) {
		case G_VALUE_TOOL_BOX:
		case G_VALUE_TOOL_RECT:
			SDL_FillRect(m_pOverlay, NULL, SDL_MapRGBA(m_pOverlay->format, 0, 0, 0, 0));
			rectangleColorS(m_pOverlay, m_startX, m_startY, event->x, event->y, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK), GP_LOGIC->getKeyValue(G_KEY_STRENGTH));
			break;
		case G_VALUE_TOOL_CONTINUITY:
			lineColorS(m_pSurface, m_startX, m_startY, event->x, event->y, GP_LOGIC->getColor(), GP_LOGIC->getKeyValue(G_KEY_STRENGTH));
			GP_LOGIC->updateCanvasRect(m_startX, m_startY, event->x, event->y);
			m_startX = event->x;
			m_startY = event->y;
			break;
		case G_VALUE_TOOL_LINE:
			SDL_FillRect(m_pOverlay, NULL, SDL_MapRGBA(m_pOverlay->format, 0, 0, 0, 0));
			lineColorS(m_pOverlay, m_startX, m_startY, event->x, event->y, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK), GP_LOGIC->getKeyValue(G_KEY_STRENGTH));
			break;
		}
		//GP_LOGIC->updateWindow(); // TODO canvas rect statt upd
		GP_LOGIC->updateCanvasRect(m_startX, m_startY, event->x, event->y);
	}
}

void CCanvas::blitTo(CSection &target)
{
	SDL_Rect *dstRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	dstRect->x = getRect().x;
	dstRect->y = getRect().y;
	dstRect->w = getRect().w;
	dstRect->h = getRect().h;
	SDL_BlitSurface(m_pVisibleSurface, NULL, target.getSurface(), dstRect);
	free(dstRect);
}

void CCanvas::updateSurface()
{
	SDL_BlitSurface(getSurface(), NULL, m_pVisibleSurface, NULL);
	SDL_BlitSurface(m_pOverlay, NULL, m_pVisibleSurface, NULL);
}

void CCanvas::updateCanvasRect(CSection &target, int x1, int y1, int x2, int y2)
{
	SDL_Rect *blitRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	SDL_Rect *dstRect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	blitRect->x = x1 < x2 ? x1 : x2; // TODO xy2 statt wh
	blitRect->y = y1 < y2 ? y1 : y2;
	blitRect->w = x1 < x2 ? x2 - x1 : x1 - x2;
	blitRect->h = y1 < y2 ? y2 - y1 : y1 - y2;
	dstRect->x = getRect().x + blitRect->x;
	dstRect->y = getRect().y + blitRect->y;
	dstRect->w = blitRect->w;
	dstRect->h = blitRect->h;
	SDL_BlitSurface(getSurface(), blitRect, m_pVisibleSurface, blitRect);
	SDL_BlitSurface(m_pOverlay, blitRect, m_pVisibleSurface, blitRect);
	SDL_BlitSurface(m_pVisibleSurface, blitRect, target.getSurface(), dstRect);
	free(blitRect);
	free(dstRect);
}

void CCanvas::pixelColorS(SDL_Surface *surface, int x, int y, int color, int strength)
{
	for( int dx = -strength / 2 - 1; dx <= strength / 2 + 1; dx++ ){
		for( int dy = -strength / 2 - 1; dy <= strength / 2 + 1; dy++ ){
			pixelColor(surface, x + dx, y + dy, color);
		}
	}
}

void CCanvas::boxColorS(SDL_Surface *surface, int x1, int y1, int x2, int y2, int color, int strength)
{
	for( int dx = -strength / 2 - 1; dx <= strength / 2 + 1; dx++ ){
		for( int dy = -strength / 2 - 1; dy <= strength / 2 + 1; dy++ ){
			boxColor(surface, x1 + dx, y1 + dy, x2 + dx, y2 + dy, color);
		}
	}
}

void CCanvas::rectangleColorS(SDL_Surface *surface, int x1, int y1, int x2, int y2, int color, int strength)
{
	for( int dx = -strength / 2 - 1; dx <= strength / 2 + 1; dx++ ){
		for( int dy = -strength / 2 - 1; dy <= strength / 2 + 1; dy++ ){
			rectangleColor(surface, x1 + dx, y1 + dy, x2 + dx, y2 + dy, color);
		}
	}
}

void CCanvas::lineColorS(SDL_Surface *surface, int x1, int y1, int x2, int y2, int color, int strength)
{
	for( int dx = -strength / 2 - 1; dx <= strength / 2 + 1; dx++ ){
		for( int dy = -strength / 2 - 1; dy <= strength / 2 + 1; dy++ ){
			lineColor(surface, x1 + dx, y1 + dy, x2 + dx, y2 + dy, color);
		}
	}
}
