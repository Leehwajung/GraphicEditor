// Shape.h : CShape 클래스의 인터페이스
// @Author Lee Hwajung

#pragma once
#include "Figure.h"

// CShape 명령 대상입니다.

class CShape : public CFigure
{
public:
	CShape();
	virtual ~CShape();
};


