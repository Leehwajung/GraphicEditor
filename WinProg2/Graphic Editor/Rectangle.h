// Rectangle.h : RectFangle Ŭ������ �������̽�
// RectFangle : ���簢�� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Shape.h"

// RectFangle ��� ����Դϴ�.

class RectFangle : public CShape
{
public:
	RectFangle();
	virtual ~RectFangle();

// Ư��
protected:
	RectF m_rect;	// �簢��
};

