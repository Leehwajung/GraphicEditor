// Group.cpp : CGroup 클래스의 구현
// CGroup : 그룹화된 도형 개체들을 저장하는 클래스
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Group.h"


// CGroup

IMPLEMENT_SERIAL(CGroup, CFigure, 1)


CGroup::CGroup()
{
}

CGroup::~CGroup()
{
}


// CGroup 멤버 함수


void CGroup::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
