// Pencil.cpp : CPencil Ŭ������ ����
// CPencil : ���� �(����) ��ü�� �����ϴ� Ŭ����
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


// CPencil ��� �Լ�


void CPencil::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
