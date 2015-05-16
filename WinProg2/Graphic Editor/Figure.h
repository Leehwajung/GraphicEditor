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
	virtual void Create(CPoint startingPoint);				// ���� ����

	virtual void setLineColor(Color lineColor);				// ������ �� ����
	virtual void setFillColor(Color FillColor);				// ĥ�ϱ� �� ����
	virtual void setLineWidth(int lineWidth);				// ������ �β� ����
	virtual void setLinePattern(int linePattern);			// ������ ���� ����
	virtual void setFillPattern(int fillPattern);			// ĥ�ϱ� ���� ����
	
	virtual void move(CPoint target);						// ���� �̵�
	virtual void resize(CPoint point, int resizeFlags);	// ���� ũ�� ����

	virtual void destroy();									// ���� ����

	void setDC(CDC* dc);
	CDC* getDC();

public:
	enum resizeFlags {
		Free = (int)0x00000,
		Proportional = (int)0x00001
	};

protected:
	CDC* m_lpdc;
	Color m_lineColor;
	CPoint m_startingPoint;
};
