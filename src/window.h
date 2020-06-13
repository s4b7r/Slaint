/*
 * window.h
 *
 *  Created on: 13.11.2013
 *      Author: sbekemeier
 */

#ifndef WINDOW_H_
#define WINDOW_H_

class CWindow : public CSection
{

public:
	CWindow(int width, int height);

	// Rekursiv alle Kind-Sections updaten, auf eigenes Surface blitten
	// und flippen
	virtual void updateSurface();
	void updateCanvasRect(CCanvas *pCanvas, int x1, int y1, int x2, int y2);

};

#endif /* WINDOW_H_ */
