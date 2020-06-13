/*
 * canvas.h
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#ifndef CANVAS_H_
#define CANVAS_H_

class CCanvas : public CSection
{

public:
	CCanvas(int x, int y, int width, int height);
	virtual ~CCanvas() {}

	// Wird von Parent-Section bei MouseButtonDown/Up ausgeführt
	virtual void onEvent(SDL_MouseButtonEvent *event);
	// Wird von Parent-Section bei MouseMotion ausgeführt
	virtual void onMouseMove(SDL_MouseMotionEvent *event);

	virtual void blitTo(CSection &target);
	virtual void updateSurface();
	void updateCanvasRect(CSection &target, int x1, int y1, int x2, int y2);


private:
	// Surface das tatsächlich im Fenster angezeigt wird
	// Das von CSection geerbte m_pSurface ist die eigentliche Zeichenoberfläche
	SDL_Surface *m_pVisibleSurface;
	// Surface z.B. für die Aufzieh-Animation von Rechtecken
	SDL_Surface *m_pOverlay;

	void pixelColorS(SDL_Surface *surface, int x, int y, int color, int strength);
	void boxColorS(SDL_Surface *surface, int x1, int y1, int x2, int y2, int color, int strength);
	void rectangleColorS(SDL_Surface *surface, int x1, int y1, int x2, int y2, int color, int strength);
	void lineColorS(SDL_Surface *surface, int x1, int y1, int x2, int y2, int color, int strength);

	bool m_inAction;
	int m_startX;
	int m_startY;

};

#endif /* CANVAS_H_ */
