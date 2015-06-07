// Polygon.cpp : CPolygon 클래스의 구현
// CPolygon : 다각형 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Polygon.h"


IMPLEMENT_SERIAL(CPolygon, CShape, 1)

// CPolygon

CPolygon::CPolygon()
{
}

CPolygon::~CPolygon()
{
}


// CPolygon 멤버 함수


void CPolygon::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
