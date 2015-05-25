// Shape.h : CShape 클래스의 인터페이스
// CShape : 2차원 도형 개체를 정의하는 클래스
// 

#pragma once
#include "Figure.h"
//#include <gdiplus.h>

//using Gdiplus::Color;

// CShape 명령 대상입니다.

class CShape : public CFigure
{
public:
	CShape();
	virtual ~CShape();

// 작업
public:
	Pen* getPen();
	void setPen(const Pen* pen);		// 각 객체가 별도의 펜을 가지고 있어야 하므로 인자로 받은 Pen을 변경하지 않음
	Brush* getBrush();
	void setBrush(const Brush* brush);	// 각 객체가 별도의 브러시를 가지고 있어야 하므로 인자로 받은 Brush를 변경하지 않음

// 특성
protected:
	Pen* m_Pen;
	Brush* m_Brush;
};


