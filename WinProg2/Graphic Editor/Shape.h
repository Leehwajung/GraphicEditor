// Shape.h : CShape Ŭ������ �������̽�
// CShape : 2���� ���� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Figure.h"

// CShape ��� ����Դϴ�.

class CShape : public CFigure
{
// ���� �� �Ҹ�
public:
	CShape();
	CShape(IN CClientDC* lpClientDC);
	CShape(IN Graphics* lpGraphics);
	CShape(IN CClientDC* lpClientDC, IN Pen* pen, IN Brush* brush);
	CShape(IN Graphics* lpGraphics, IN Pen* pen, IN Brush* brush);
	DECLARE_DYNAMIC(CShape)
	virtual ~CShape();

// �۾�
public:
	// �� ȹ��
	Pen* getPen();

	// �귯�� ȹ��
	Brush* getBrush();

	// �귯�� Ÿ�� ȹ��
	BrushType getBrushType();

	// ������ �� ȹ��
	Color getLineColor();

	// ������ �β� ȹ��
	REAL getLineWidth();

	// ������ ���� ȹ��
	DashStyle getLinePattern();

	// ä��� �� ȹ��
	Color getFillColor();

	// ä��� ���� ȹ��
	HatchStyle getFillPattern();
	
	// �� ����
	// �� ��ü�� ������ ���� ������ �־�� �ϹǷ� ���ڷ� ���� Pen�� �������� ����
	void setPen(IN const Pen* pen);

	// �귯�� ����
	// �� ��ü�� ������ �귯�ø� ������ �־�� �ϹǷ� ���ڷ� ���� Brush�� �������� ����
	void setBrush(IN const Brush* brush);

// ������
public:
	// ������ �� ����
	virtual void setOutlineColor(IN const Color& outlineColor);

	// ������ �β� ����
	virtual void setOutlineWidth(IN const REAL outlineWidth);

	// ������ ���� ����
	virtual void setOutlinePattern(IN const DashStyle outlinePattern);

	// ĥ�ϱ� �� ����
	virtual void setFillColor(IN const Color& fillColor);

	// ĥ�ϱ� ���� ����
	virtual void setFillPattern(IN const HatchStyle fillPattern);

// Ư��
protected:
	Pen* m_Pen;		// �׸��� ��
	Brush* m_Brush;	// �׸��� �귯��
};


