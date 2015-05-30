// Ellipse.cpp : CEllipse 클래스의 구현
// CEllipse : 타원 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Ellipse.h"


// CEllipse

IMPLEMENT_SERIAL(CEllipse, CShape, 1)


CEllipse::CEllipse()
{
}

CEllipse::~CEllipse()
{
}


// CEllipse 멤버 함수


void CEllipse::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
