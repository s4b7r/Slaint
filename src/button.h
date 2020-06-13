/*
 * button.h
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#ifndef BUTTON_H_
#define BUTTON_H_

class CButton : public CSection
{

public:
	CButton(int x, int y, int width, int height, int key, int value);

	virtual void addSection(CSection &section);
	// Speichermodifikation für Klick festlegen
	void setKeyValue(int key, int value);
	virtual void updateSurface();
	// Wird von Parent-Section bei MouseButtonDown/Up ausgeführt
	virtual void onEvent(SDL_MouseButtonEvent *event);

	void setHighlighted(bool highlighted);

	virtual void fillSurface(int color);

	void setParent(CSection *parent);

private:
	void initHighlight();

	SDL_Surface *m_pHighlight;
	SDL_Surface *m_pBackground;

	// Speichermodifikation für Klick
	int m_key;
	int m_value;

	bool m_highlighted;

	CSection *m_pParent;

};

#endif /* BUTTON_H_ */
