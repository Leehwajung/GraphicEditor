// Sine.cpp : CSine 클래스의 구현
// CSine : Sine 그래프 형 곡선 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Sine.h"


// CSine

IMPLEMENT_SERIAL(CSine, CPolyLine, 1)

CSine::CSine()
	: CPolyLine()
{
}

CSine::~CSine()
{
}


// CSine 멤버 함수


void CSine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
