// Rectangle.h : CRectangle Ŭ������ �������̽�
// CRectangle : ���簢�� ��ü�� �����ϴ� Ŭ����
// @Author Lee Hwajung

#pragma once
#include "Shape.h"

// CRectangle ��� ����Դϴ�.

class CRectangle : public CShape
{
public:
	CRectangle();
	virtual ~CRectangle();

// Ư��
protected:
	RectF m_rect;	// �簢��
};

