// Sine.cpp : CSine Ŭ������ ����
// CSine : Sine �׷��� �� � ��ü�� �����ϴ� Ŭ����
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


// CSine ��� �Լ�


void CSine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
