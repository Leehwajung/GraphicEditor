#pragma once
#include "afx.h"
#include <gdiplus.h>

using namespace Gdiplus;

class CFigure : public CObject
{
public:
	CFigure();
	CFigure(CDC* dc);
	~CFigure();

public:
	virtual void Create(CPoint startingPoint);

	virtual void setLineColor(Color lineColor);
	virtual void setFillColor(Color FillColor);
	virtual void setLineWidth(int lineWidth);
	virtual void setLinePattern(int linePattern);
	virtual void setFillPattern(int fillPattern);

	virtual void move(CPoint target);
	virtual void resize(CPoint point);
	virtual void propResize(CPoint point);

	virtual void destroy();

protected:
	CDC* m_lpdc;
	Color m_lineColor;
	CPoint m_startingPoint;
};

