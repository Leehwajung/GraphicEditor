// Ellipse.h : CEllipse Ŭ������ �������̽�
// CEllipse : Ÿ�� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Shape.h"

// CEllipse ��� ����Դϴ�.

class CEllipse : public CShape
{
public:
	CEllipse();
	DECLARE_SERIAL(CEllipse)
	virtual ~CEllipse();

public:
	virtual void Serialize(CArchive& ar);
};


