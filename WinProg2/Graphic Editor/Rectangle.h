// Rectangle.h : CRectangle 클래스의 인터페이스
// CRectangle : 직사각형 개체를 정의하는 클래스
// 

#pragma once
#include "Shape.h"

// CRectangle 명령 대상입니다.

class CRectangle : public CShape
{
public:
	CRectangle();
	virtual ~CRectangle();
};

