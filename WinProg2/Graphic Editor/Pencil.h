// Pencil.h : CPencil Ŭ������ �������̽�
// CPencil : ���� �(����) ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "PolyLine.h"

// CPencil ��� ����Դϴ�.

class CPencil : public CPolyLine
{
public:
	CPencil();
	DECLARE_SERIAL(CPencil)

	virtual ~CPencil();
	virtual void Serialize(CArchive& ar);
};


