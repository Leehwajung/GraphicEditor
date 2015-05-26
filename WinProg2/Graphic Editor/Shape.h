// Shape.h : CShape Ŭ������ �������̽�
// CShape : 2���� ���� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Figure.h"

// CShape ��� ����Դϴ�.

class CShape : public CFigure
{
public:
	CShape(CClientDC* lpClientDC);
	CShape(Graphics* lpGraphics);
	CShape(CClientDC* lpClientDC, Pen* pen, SolidBrush* brush);
	virtual ~CShape();

// �۾�
public:
	Pen* getPen();
	void setPen(const Pen* pen);		// �� ��ü�� ������ ���� ������ �־�� �ϹǷ� ���ڷ� ���� Pen�� �������� ����
	SolidBrush* getBrush();
	void setBrush(const SolidBrush* brush);	// �� ��ü�� ������ �귯�ø� ������ �־�� �ϹǷ� ���ڷ� ���� Brush�� �������� ����

// ������
	virtual void setLineColor(const Color& lineColor);			// ������ �� ����
	virtual void setLineWidth(const REAL& LineWidth);			// ������ �β� ����
	virtual void setLinePattern(const DashStyle& LinePattern);	// ������ ���� ����
	virtual void setFillColor(const Color& FillColor);			// ĥ�ϱ� �� ����
	virtual void setFillPattern(const int fillPattern);			// ĥ�ϱ� ���� ���� (���� ���� ����)

// Ư��
protected:
	Pen* m_Pen;
	SolidBrush* m_Brush;	// ���� ������ ���� SolidBrush�� ��, ���߿� Brush�� �ٲ� ���� (�ٸ� �귯�� ������ ����)

	
};


