// PolyLine.cpp : CPolyLine Ŭ������ ����
// CPolyLine : �������� ��ü�� �����ϴ� Ŭ����
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "PolyLine.h"


// CPolyLine

IMPLEMENT_SERIAL(CPolyLine, CStrap, 1)

CPolyLine::CPolyLine()
{
}

CPolyLine::~CPolyLine()
{
}


// CPolyLine ��� �Լ�


void CPolyLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
