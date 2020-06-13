/*
 * logic.cpp
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#include "comhead.h"

CLogic::CLogic()
{
	GP_DBG->debug("Construct Logic");
	// Initialisierung der Member
	m_keyValue = new int[G_MAX_KEYS];
	m_pWindow = 0;
	m_pCanvas = 0;

	// Intialisierung der Key-Values
	m_keyValue[G_KEY_TOOL] = G_VALUE_TOOL_POINT;
	m_keyValue[G_KEY_COLOR] = G_VALUE_COLOR_BLACK;
	m_keyValue[G_KEY_STRENGTH] = G_VALUE_STRENGTH_A;
	m_keyValue[G_KEY_TEST] = 0;
}

void CLogic::run()
{
	GP_DBG->debug("Start Logic");
	init();
	loop();
	kill();
}

void CLogic::setKeyValue(int key, int value)
{
	m_keyValue[key] = value;
	GP_DBG->debug("Logic: Set key %d = %d", key, value);
}

int CLogic::getKeyValue(int key)
{
	return m_keyValue[key];
}

void CLogic::init()
{
	GP_DBG->debug("Init Logic");

	GP_DBG->debug("Logic: Create sections");
	CButton *btn11 = new CButton(20, 20, 50, 50, G_KEY_TOOL, G_VALUE_TOOL_POINT);
	CButton *btn12 = new CButton(90, 20, 50, 50, G_KEY_TOOL, G_VALUE_TOOL_BOX);
	CButton *btn13 = new CButton(160, 20, 50, 50, G_KEY_TOOL, G_VALUE_TOOL_RECT);
	CButton *btn14 = new CButton(20, 90, 50, 50, G_KEY_TOOL, G_VALUE_TOOL_CONTINUITY);
	CButton *btn1b1 = new CButton(90, 20, 50, 50, G_KEY_STRENGTH, G_VALUE_STRENGTH_A);
	CButton *btn1b2 = new CButton(20, 90, 50, 50, G_KEY_STRENGTH, G_VALUE_STRENGTH_B);
	CButton *btn1b3 = new CButton(90, 90, 50, 50, G_KEY_STRENGTH, G_VALUE_STRENGTH_C);
	CButton *btn15 = new CButton(90, 90, 50, 50, G_KEY_TOOL, G_VALUE_TOOL_LINE);
	CButton *btn21 = new CButton(20, 20, 50, 50, G_KEY_COLOR, G_VALUE_COLOR_BLACK);
	CButton *btn22 = new CButton(90, 20, 50, 50, G_KEY_COLOR, G_VALUE_COLOR_WHITE);
	CButton *btn23 = new CButton(160, 20, 50, 50, G_KEY_COLOR, G_VALUE_COLOR_RED);
	CButton *btn24 = new CButton(20, 90, 50, 50, G_KEY_COLOR, G_VALUE_COLOR_BLUE);
	CButton *btn25 = new CButton(90, 90, 50, 50, G_KEY_COLOR, G_VALUE_COLOR_GREEN);
	CButton *btn26 = new CButton(160, 90, 50, 50, G_KEY_COLOR, G_VALUE_COLOR_YELLOW);
	CSection *sctn1 = new CSection(0, 0, 230, 150);
	CSection *sctn1b = new CSection(230, 0, 170, 150);
	CSection *sctn2 = new CSection(400, 0, 400, 150);
	m_pCanvas = new CCanvas(0, 150, 800, 450);

	GP_DBG->debug("Logic: Create window");
	m_pWindow = new CWindow(800, 600);

	GP_DBG->debug("Logic: Compose sections");
	sctn1->addSection(btn11);
	sctn1->addSection(btn12);
	sctn1->addSection(btn13);
	sctn1->addSection(btn14);
	sctn1->addSection(btn15);
	sctn1b->addSection(btn1b1);
	sctn1b->addSection(btn1b2);
	sctn1b->addSection(btn1b3);
	sctn2->addSection(btn21);
	sctn2->addSection(btn22);
	sctn2->addSection(btn23);
	sctn2->addSection(btn24);
	sctn2->addSection(btn25);
	sctn2->addSection(btn26);
	m_pWindow->addSection(sctn1);
	m_pWindow->addSection(sctn1b);
	m_pWindow->addSection(sctn2);
	m_pWindow->addSection(m_pCanvas);

	GP_DBG->debug("Logic: Update window");
	m_pWindow->updateSurface();
}

void CLogic::loop()
{
	GP_DBG->debug("Run Logic loop");

	bool exit = false;

	// Main-Loop
	while( !exit )
	{
		SDL_Event *event = new SDL_Event;
		SDL_WaitEvent(event);

		// Events die zum regulären Ende führen sollen prüfen
		if(
				event->type == SDL_QUIT ||
				(event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE)
		)
		{
			GP_DBG->debug("Logic: Received SDL_QUIT or SDLK_ESCAPE");
			exit = true;
		}

		// Mausklicks an Window übergeben
		if( event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP )
		{
			GP_DBG->debug("Logic: Received SDL_MOUSEBUTTONDOWN/UP");
			m_pWindow->onEvent(&(event->button));
		}

		// Mausbewegunge an Window übergeben
		if( event->type == SDL_MOUSEMOTION )
		{
			//GP_DBG->debug("Logic: Received SDL_MOUSEMOTION");
			m_pWindow->onMouseMove(&(event->motion));
		}
	}
}

void CLogic::kill()
{
	GP_DBG->debug("Kill Logic");
}

int CLogic::getColorR()
{
	return G_COLOR[getKeyValue(G_KEY_COLOR)][0];
}

int CLogic::getColorG()
{
	return G_COLOR[getKeyValue(G_KEY_COLOR)][1];
}

int CLogic::getColorB()
{
	return G_COLOR[getKeyValue(G_KEY_COLOR)][2];
}

unsigned int CLogic::getColor()
{
	return (getColorR() << 24) + (getColorG() << 16) + (getColorB() << 8) + 255;
}

unsigned int CLogic::getColor(int colorCode)
{
	return getColor(colorCode, 255);
}

unsigned int CLogic::getColor(int colorCode, int alpha)
{
	return (G_COLOR[colorCode][0] << 24) + (G_COLOR[colorCode][1] << 16) + (G_COLOR[colorCode][2] << 8) + alpha;
}

void CLogic::updateCanvasRect(int x1, int y1, int x2, int y2)
{
	m_pWindow->updateCanvasRect(m_pCanvas, x1, y1, x2, y2);
}
