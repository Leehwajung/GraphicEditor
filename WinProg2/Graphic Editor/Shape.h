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
	CShape(Pen* pen, Brush* brush);
	virtual ~CShape();

// �۾�
public:
	Pen* getPen();
	void setPen(const Pen* pen);		// �� ��ü�� ������ ���� ������ �־�� �ϹǷ� ���ڷ� ���� Pen�� �������� ����
	Brush* getBrush();
	void setBrush(const Brush* brush);	// �� ��ü�� ������ �귯�ø� ������ �־�� �ϹǷ� ���ڷ� ���� Brush�� �������� ����

// ������
	virtual void setLineColor(const Color& lineColor);			// ������ �� ����
	virtual void setLineWidth(const REAL& LineWidth);			// ������ �β� ����
	virtual void setLinePattern(const DashStyle& LinePattern);	// ������ ���� ����
	virtual void setFillColor(const Color& FillColor);			// ĥ�ϱ� �� ����
	virtual void setFillPattern(const int fillPattern);			// ĥ�ϱ� ���� ����

// Ư��
protected:
	Pen* m_Pen;
	Brush* m_Brush;
};


