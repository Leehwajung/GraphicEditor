// Strap.cpp : CStrap 클래스의 구현
// CStrap : 선 개체를 정의하는 클래스
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Strap.h"
#include "Global.h"


// CStrap

CStrap::CStrap()
	//: m_Pen(defaultPen)	// 기본 펜, 수정할것!
{
}

CStrap::CStrap(Graphics* lpGraphics)
	:CFigure(lpGraphics)
{
}

CStrap::~CStrap()
{
}


// CStrap 멤버 함수
