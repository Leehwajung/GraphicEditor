// Polygon.h : CPolygon 클래스의 인터페이스
// CPolygon : 다각형 개체를 정의하는 클래스
// 

#pragma once
#include "Shape.h"

// CPolygon 명령 대상입니다.

class CPolygon : public CShape
{
public:
	CPolygon();
	virtual ~CPolygon();
};


