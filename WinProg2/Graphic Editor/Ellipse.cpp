// Ellipse.cpp : CEllipse Ŭ������ ����
// CEllipse : Ÿ�� ��ü�� �����ϴ� Ŭ����
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


// CEllipse ��� �Լ�


void CEllipse::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
