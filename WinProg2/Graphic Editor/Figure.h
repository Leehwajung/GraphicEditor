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
	virtual void Create(CPoint startingPoint);				// 도형 생성

	virtual void setLineColor(Color lineColor);				// 윤곽선 색 설정
	virtual void setFillColor(Color FillColor);				// 칠하기 색 설정
	virtual void setLineWidth(int lineWidth);				// 윤곽선 두께 설정
	virtual void setLinePattern(int linePattern);			// 윤곽선 패턴 설정
	virtual void setFillPattern(int fillPattern);			// 칠하기 패턴 설정
	
	virtual void move(CPoint target);						// 도형 이동
	virtual void resize(CPoint point, int resizeFlags);	// 도형 크기 변경

	virtual void destroy();									// 도형 삭제

	void setDC(CDC* dc);
	CDC* getDC();

public:
	enum resizeFlags {
		Free			= (int)0x00000,
		Proportional	= (int)0x00001
	};

protected:
	CDC* m_lpdc;
	Color m_lineColor;
	CPoint m_startingPoint;
};

