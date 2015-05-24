// Shape.h : CShape 클래스의 인터페이스
// CShape : 2차원 도형 개체를 정의하는 클래스
// @Author Lee Hwajung

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

// 특성
protected:
	Color m_FillColor;	// 채우기 색상
	int m_FillPattern;	// 채우기 패턴
};


