// Sine.h : CSine Ŭ������ �������̽�
// CSine : Sine �׷��� �� � ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "PolyLine.h"

// CSine ��� ����Դϴ�.

class CSine : public CPolyLine
{
public:
	CSine();
	DECLARE_SERIAL(CSine)

	virtual ~CSine();
	virtual void Serialize(CArchive& ar);
};


