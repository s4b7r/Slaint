/*
 * logic.h
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#ifndef LOGIC_H_
#define LOGIC_H_

class CLogic : public TSingleton<CLogic>
{

public:
	CLogic();

	// Funktion zum Starten
	void run();
	// Speicher setzen
	void setKeyValue(int key, int value);
	// Speicher auslesen
	int getKeyValue(int key);

	void updateWindow() { return m_pWindow->updateSurface(); }
	void updateCanvasRect(int x1, int y1, int x2, int y2);

	int getColorR();
	int getColorG();
	int getColorB();
	unsigned int getColor();
	unsigned int getColor(int colorCode);
	unsigned int getColor(int colorCode, int alpha);

private:
	// Initialisierung der Programmteile
	void init();
	// Main-Loop
	void loop();
	// Deinitialisierung
	void kill();

	// Hauptfenster der Anwendung
	CWindow *m_pWindow;
	// Speicher-Array
	int *m_keyValue;

	CCanvas *m_pCanvas;

};

#endif /* LOGIC_H_ */
