// Curve.cpp : CCurve 클래스의 구현
// CCurve : 곡선 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Curve.h"


IMPLEMENT_SERIAL(CCurve, CPolyLine, 1)

// CCurve

CCurve::CCurve()
{
}

CCurve::~CCurve()
{
}


// CCurve 멤버 함수


void CCurve::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
