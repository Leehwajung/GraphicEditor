// Group.cpp : CGroup Ŭ������ ����
// CGroup : �׷�ȭ�� ���� ��ü���� �����ϴ� Ŭ����
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


// CGroup ��� �Լ�


void CGroup::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
