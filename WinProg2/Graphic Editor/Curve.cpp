// Curve.cpp : CCurve Ŭ������ ����
// CCurve : � ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Curve.h"


// CCurve

IMPLEMENT_SERIAL(CCurve, CPolyLine, 1)

CCurve::CCurve()
	: CPolyLine()
{
}

CCurve::~CCurve()
{
}


// CCurve ��� �Լ�


void CCurve::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
