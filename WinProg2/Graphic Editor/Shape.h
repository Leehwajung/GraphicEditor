// Shape.h : CShape Ŭ������ �������̽�
// CShape : 2���� ���� ��ü�� �����ϴ� Ŭ����
// @Author Lee Hwajung

#pragma once
#include "Figure.h"
//#include <gdiplus.h>

//using Gdiplus::Color;

// CShape ��� ����Դϴ�.

class CShape : public CFigure
{
public:
	CShape();
	virtual ~CShape();

// Ư��
protected:
	Color m_FillColor;	// ä��� ����
	int m_FillPattern;	// ä��� ����
};


