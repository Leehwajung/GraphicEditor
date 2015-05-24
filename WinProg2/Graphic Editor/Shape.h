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
	CRgn m_Shape;		// ���� ����

	Color m_LineColor;	// ������ ��
	int m_LinePattern;	// ������ ����
	int m_LineWidth;	// ������ �β�

	Color m_FillColor;	// ä��� ����
	int m_FillPattern;	// ä��� ����
};


