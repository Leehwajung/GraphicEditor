// Shape.h : CShape Ŭ������ �������̽�
// @Author Lee Hwajung

#pragma once
#include "Figure.h"

// CShape ��� ����Դϴ�.

class CShape : public CFigure
{
public:
	CShape();
	virtual ~CShape();

// Ư��
protected:
	CRgn m_Region;		// ���� ���� https://msdn.microsoft.com/en-us/library/6y4t32t5(v=vs.120).aspx

	Color m_FillColor;	// ä��� ����
	int m_FillPattern;	// ä��� ����
};


