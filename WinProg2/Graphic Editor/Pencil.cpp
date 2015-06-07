// Pencil.cpp : CPencil 클래스의 구현
// CPencil : 자유 곡선(연필) 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Pencil.h"


IMPLEMENT_SERIAL(CPencil, CPolyLine, 1)

// CPencil

CPencil::CPencil()
{
}

CPencil::~CPencil()
{
}


// CPencil 멤버 함수


void CPencil::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
