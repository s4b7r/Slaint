/*
 * section.h
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#ifndef SECTION_H_
#define SECTION_H_

class CSection
{

public:
	CSection(int x, int y, int width, int height);
	virtual ~CSection() {}

	// Rekursiv alle Kind-Sections updaten und auf eigenes Surface blitten
	virtual void updateSurface();
	// Kind-Section hinzufügen
	virtual void addSection(CSection *section);
	// Mausklick entgegen nehmen
	virtual void onEvent(SDL_MouseButtonEvent *event);
	// Mausbewegung entgegen nehmen
	virtual void onMouseMove(SDL_MouseMotionEvent *event);
	// Infos auf welche Events reagiert wird zurück geben
	SListener getListener() { return m_myListener; }
	// Diese Section auf target blitten
	virtual void blitTo(CSection &target);
	SDL_Surface* getSurface() { return m_pSurface; }
	// Koordinaten (x,y) liegen in dieser Section
	bool containsCoordinates(int x, int y);
	virtual void fillSurface(int color);

	int getSectionId() { return m_sectionId; }

	SDL_Rect getRect() { return m_rect; }

	void unhighlightChilds();


protected:
	// Eigenes Surface
	SDL_Surface *m_pSurface;
	// Infos auf welche Events diese Section reagiert
	SListener m_myListener;

private:
	// Debug-Box in Section zeichnen
	void drawDebugBox();

	// Infos auf welche Events die Kind-Sections reagieren
	std::vector<SListener> m_childListener;
	// Kind-Sections
	std::vector<CSection*> m_sections;
	// Kind-Button
	std::vector<CButton*> m_buttons;
	// Ziel-Bereich dieser Section in Mutter-Section
	SDL_Rect m_rect;

	static int s_sectionCount;
	int m_sectionId;

};

#endif /* SECTION_H_ */
