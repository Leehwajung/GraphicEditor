// Rectangle.h : RectFangle 클래스의 인터페이스
// RectFangle : 직사각형 개체를 정의하는 클래스
// 

#pragma once
#include "Shape.h"

// RectFangle 명령 대상입니다.

class RectFangle : public CShape
{
public:
	RectFangle();
	virtual ~RectFangle();

// 특성
protected:
	RectF m_rect;	// 사각형
};

