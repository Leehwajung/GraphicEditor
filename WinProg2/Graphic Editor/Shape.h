// Shape.h : CShape Ŭ������ �������̽�
// CShape : 2���� ���� ��ü�� �����ϴ� Ŭ����
// 

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

// �۾�
public:
	Pen& getPen();
	void setPen(const Pen& pen);		// �� ��ü�� ������ ���� ������ �־�� �ϹǷ� ���ڷ� ���� Pen�� �������� ����
	Brush getBrush();
	void setBrush(const Brush& brush);	// �� ��ü�� ������ �귯�ø� ������ �־�� �ϹǷ� ���ڷ� ���� Brush�� �������� ����

// Ư��
protected:
	Pen* m_Pen;
	Brush* m_Brush;
};


