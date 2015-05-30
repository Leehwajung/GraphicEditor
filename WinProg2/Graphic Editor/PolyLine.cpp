// PolyLine.cpp : CPolyLine 클래스의 구현
// CPolyLine : 폴리라인 개체를 정의하는 클래스
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


// CPolyLine 멤버 함수


void CPolyLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
