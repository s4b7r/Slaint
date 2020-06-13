/*
 * section.cpp
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#include "comhead.h"

int CSection::s_sectionCount = 0;

CSection::CSection(int x, int y, int width, int height)
{
	// Section ID zuweisen
	m_sectionId = s_sectionCount;
	s_sectionCount++;

	GP_DBG->debug("Create section %d : %d x%d @(%d ,%d )", m_sectionId, width, height, x, y);

	// Neues Surface für diese Section erstellen
	// 32 = 32 Bit Farbtiefe
	m_pSurface = SDL_CreateRGBSurface(G_CREATESURFACE_FLAGS, width, height, 32, G_MASK_RED, G_MASK_GREEN, G_MASK_BLUE, G_MASK_ALPHA);
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = width;
	m_rect.h = height;

	fillSurface(GP_LOGIC->getColor(G_VALUE_COLOR_GREYLIGHT));
	//drawDebugBox();
}

void CSection::updateSurface()
{
	std::vector<CSection*>::iterator it = m_sections.begin();
	while( it != m_sections.end() )
	{
		(*it)->updateSurface();
		(*it)->blitTo(*this);
		it++;
	}
}

bool CSection::containsCoordinates(int x, int y)
{
	//GP_DBG->hidbg("Check (%d ,%d ) in x1=%d y1=%d x2=%d y2=%d", x, y, m_rect.x, m_rect.y, m_rect.x + m_rect.w, m_rect.y + m_rect.h);
	//GP_DBG->hidbg("left:%d right:%d top:%d bottom:%d", x > m_rect.x, x < m_rect.x + m_rect.w, y > m_rect.y, y < m_rect.y + m_rect.h);

	return x > m_rect.x &&
			x < m_rect.x + m_rect.w &&
			y > m_rect.y &&
			y < m_rect.y + m_rect.h;
}


void CSection::blitTo(CSection &target)
{
	SDL_BlitSurface(m_pSurface, NULL, target.getSurface(), &m_rect);
	// Vorsicht: SDL_BlitSurface hält Destination-Rect nicht konstant
	// Nochmal genau nachlesen
}

void CSection::addSection(CSection *section)
{
	// Prüfen ob section CButton ist
	// dann extra hinterlegen für de-highlighting
	const char *typestr = typeid(*section).name();
	const char *typecls = strchr(typestr, 'C');
	GP_DBG->hidbg("%s ,%s", typestr, typecls);
	if( !strcmp(typecls, "CButton") ) {
		GP_DBG->hidbg("... is button");
		m_buttons.push_back((CButton*)section);
		((CButton*)section)->setParent(this);
	}


	// Neue Kind-Section in Vektor aufnehmen
	m_sections.push_back(section);
	// Listener des Kinds in Vektor aufnehmen
	m_childListener.push_back(section->getListener());
	// Eigene Listener anpassen
	m_myListener.listenMouseDown |= section->getListener().listenMouseDown;
	m_myListener.listenMouseUp |= section->getListener().listenMouseUp;
	m_myListener.listenMouseMove |= section->getListener().listenMouseMove;
}

void CSection::onEvent(SDL_MouseButtonEvent *event)
{
	GP_DBG->debug("Section %d got event", getSectionId());

	// Alle Kind-Sections auf Übereinstimmung mit dem Event prüfen
	std::vector<CSection*>::iterator it = m_sections.begin();
	std::vector<SListener>::iterator listenerIt = m_childListener.begin();
	while( it != m_sections.end() )
	{
		GP_DBG->hidbg("Section %d: Check event listener of section %d", getSectionId(), (*it)->getSectionId());
		GP_DBG->hidbg("Event @(%d ,%d)", event->x, event->y);
		// Übereinstimmung der Position prüfen
		if( (*it)->containsCoordinates(event->x, event->y) )
		{
			GP_DBG->hidbg("Section %d contains coordinates", (*it)->getSectionId());
			// Listener prüfen
			if( (event->type == SDL_MOUSEBUTTONDOWN && listenerIt->listenMouseDown) ||
					(event->type == SDL_MOUSEBUTTONUP && listenerIt->listenMouseUp) )
			{
				// SDL_MouseButtonEvent für Übergabe erzeugen
				SDL_MouseButtonEvent *tmpEvent = new SDL_MouseButtonEvent;
				tmpEvent->button = event->button;
				tmpEvent->state = event->state;
				tmpEvent->type = event->type;
				tmpEvent->which = event->which;
				tmpEvent->x = event->x - (*it)->getRect().x;
				tmpEvent->y = event->y - (*it)->getRect().y;
				// Event übergeben
				(*it)->onEvent(tmpEvent);
			}
		}
		it++;
		listenerIt++;
	}
}

void CSection::onMouseMove(SDL_MouseMotionEvent *event)
{
	//GP_DBG->debug("Section %d got mouse move", getSectionId());

	// Alle Kind-Sections auf Übereinstimmung mit dem Event prüfen
	std::vector<CSection*>::iterator it = m_sections.begin();
	std::vector<SListener>::iterator listenerIt = m_childListener.begin();
	while( it != m_sections.end() )
	{
		// Übereinstimmung der Position prüfen
		if( (*it)->containsCoordinates(event->x - m_rect.x, event->y - m_rect.y) )
		{
			// Listener prüfen
			if( (event->type == SDL_MOUSEMOTION && listenerIt->listenMouseMove) )
			{
				// SDL_MouseMotionEvent für Übergabe erzeugen
				SDL_MouseMotionEvent *tmpEvent = new SDL_MouseMotionEvent;
				tmpEvent->state = event->state;
				tmpEvent->type = event->type;
				tmpEvent->which = event->which;
				tmpEvent->x = event->x - (*it)->getRect().x;
				tmpEvent->y = event->y - (*it)->getRect().y;
				tmpEvent->xrel = event->xrel;
				tmpEvent->yrel = event->yrel;
				// Event übergeben
				(*it)->onMouseMove(tmpEvent);
			}
		}
		it++;
		listenerIt++;
	}
}


void CSection::drawDebugBox()
{
	boxRGBA(m_pSurface, 0, 0, m_rect.w - 1, m_rect.h - 1, 0, 0, 0, 255);
	lineRGBA(m_pSurface, 0, 0, m_rect.w - 1, m_rect.h - 1, 255, 255, 255, 255);
	rectangleRGBA(m_pSurface, 0, 0, m_rect.w - 1, m_rect.h - 1, 255, 255, 255, 255);
}

void CSection::fillSurface(int color)
{
	boxColor(m_pSurface, 0, 0, m_rect.w, m_rect.h, color);
}

void CSection::unhighlightChilds()
{
	std::vector<CButton*>::iterator it = m_buttons.begin();
	while( it != m_buttons.end() )
	{
		(*it)->setHighlighted(false);
		it++;
	}
}
