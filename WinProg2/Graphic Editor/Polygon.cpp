// Polygon.cpp : CPolygon Ŭ������ ����
// CPolygon : �ٰ��� ��ü�� �����ϴ� Ŭ����
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


// CPolygon ��� �Լ�


void CPolygon::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
