/*
 * button.cpp
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#include "comhead.h"

CButton::CButton(int x, int y, int width, int height, int key, int value)
: CSection(x, y, width, height)
{
	GP_DBG->debug("Create button %d [%d =%d ]", getSectionId(), key, value, width, height, x, y);

	m_key = key;
	m_value = value;
	m_myListener.listenMouseDown = true;
	m_myListener.listenMouseUp = true;

	m_pHighlight = SDL_CreateRGBSurface(G_CREATESURFACE_FLAGS, width, height, 32, G_MASK_RED, G_MASK_GREEN, G_MASK_BLUE, G_MASK_ALPHA);
	m_pBackground = SDL_CreateRGBSurface(G_CREATESURFACE_FLAGS, width, height, 32, G_MASK_RED, G_MASK_GREEN, G_MASK_BLUE, G_MASK_ALPHA);

	fillSurface(GP_LOGIC->getColor(G_VALUE_COLOR_WHITE));

	if( m_key == G_KEY_TOOL ) {
		switch(m_value){
		case G_VALUE_TOOL_POINT:
			pixelColor(m_pBackground, getRect().w / 2, getRect().h / 2, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			break;
		case G_VALUE_TOOL_BOX:
			boxColor(m_pBackground, getRect().w / 10, getRect().h / 10, getRect().w / 10 * 9, getRect().h / 10 * 9, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			break;
		case G_VALUE_TOOL_RECT:
			rectangleColor(m_pBackground, getRect().w / 10, getRect().h / 10, getRect().w / 10 * 9, getRect().h / 10 * 9, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			break;
		case G_VALUE_TOOL_CONTINUITY:
			lineColor(m_pBackground, 12, 14, 10, 10, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			lineColor(m_pBackground, 10, 10, 14,  8, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			lineColor(m_pBackground, 14,  8, 20, 15, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			lineColor(m_pBackground, 20, 15, 17, 37, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			lineColor(m_pBackground, 17, 37, 24, 37, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			lineColor(m_pBackground, 24, 37, 20, 20, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			lineColor(m_pBackground, 20, 20, 38, 44, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			lineColor(m_pBackground, 38, 44, 15, 39, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			break;
		case G_VALUE_TOOL_LINE:
			lineColor(m_pBackground, 10, 10, 40, 40, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
			break;
		}
	}else if( m_key == G_KEY_COLOR ) {
		fillSurface(GP_LOGIC->getColor(m_value));
	}else if( m_key == G_KEY_STRENGTH ) {
		boxColor(m_pBackground, (getRect().w - m_value) / 2, (getRect().h - m_value) / 2, (getRect().w + m_value) / 2, (getRect().h + m_value) / 2, GP_LOGIC->getColor(G_VALUE_COLOR_BLACK));
	}

	initHighlight();

}

void CButton::addSection(CSection &section)
{
	// Section hinzufügen bei Button nicht gewünscht
	GP_DBG->warn("No adding sections to buttons");
}

void CButton::setKeyValue(int key, int value)
{
	m_key = key;
	m_value = value;
}

void CButton::updateSurface()
{
	SDL_BlitSurface(m_pBackground, NULL, getSurface(), NULL);
	if(m_highlighted) SDL_BlitSurface(m_pHighlight, NULL, getSurface(), NULL);
}

void CButton::onEvent(SDL_MouseButtonEvent *event)
{
	if( event->state == SDL_RELEASED )
	{
		GP_DBG->debug("Button pressed: %d =%d", m_key, m_value);
		// Speicher in Logik modifizieren
		GP_LOGIC->setKeyValue(m_key, m_value);
		m_pParent->unhighlightChilds();
		setHighlighted(true);
	}
}

void CButton::initHighlight()
{
	unsigned int highlightColor = m_key==G_KEY_COLOR ? ~(GP_LOGIC->getColor(m_value, 0)) : GP_LOGIC->getColor(G_VALUE_COLOR_RED);

	rectangleColor(m_pHighlight, 0, 0, getRect().w-1, getRect().h-1, highlightColor);
	rectangleColor(m_pHighlight, 1, 1, getRect().w-2, getRect().h-2, highlightColor);
}

void CButton::setHighlighted(bool highlighted)
{
	m_highlighted = highlighted;
	GP_LOGIC->updateWindow();
}

void CButton::fillSurface(int color)
{
	boxColor(m_pBackground, 0, 0, getRect().w, getRect().h, color);
}

void CButton::setParent(CSection *parent)
{
	m_pParent = parent;
}
