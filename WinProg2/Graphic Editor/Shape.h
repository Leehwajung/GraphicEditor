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
	DECLARE_SERIAL(CShape)
	virtual ~CShape();

public:
	// ����ȭ
	virtual void Serialize(CArchive& ar);

// �۾�
public:
	// �� ȹ��
	Pen* getPen();

	// �귯�� ȹ��
	Brush* getBrush();

	// �귯�� Ÿ�� ȹ��
	BrushType getBrushType();

	// ������ �� ȹ��
	Color getOutlineColor();

	// ������ �β� ȹ��
	REAL getOutlineWidth();

	// ������ ���� ȹ��
	DashStyle getOutlinePattern();

	// �� ä��� �� ȹ��
	Color getFillColor();

	// ���� ä��� �� ȹ��
	Color getFillSubcolor();

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
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setOutlineColor(IN const Color& outlineColor);

	// ������ �β� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setOutlineWidth(IN const REAL outlineWidth);

	// ������ ���� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setOutlinePattern(IN const DashStyle outlinePattern);

	// �� ä��� �� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setFillColor(IN const Color& fillColor);

	// ���� ä��� �� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setFillSubcolor(IN const Color& fillSubcolor);

	// ä��� ���� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setFillPattern(IN const HatchStyle fillPattern);



// ���� �۾�
protected:
	// �ֻ� ȹ��
	static Color getBrushColor(IN Brush* brush);

	// ������ ȹ��
	static Color getBrushSubcolor(IN Brush* brush);

	// ���� ȹ��
	static HatchStyle getBrushPattern(IN Brush* brush);

	// �ֻ� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	static BOOL setBrushColor(IN Brush* brush, IN const Color& fillColor);

	// ������ ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	static BOOL setBrushSubcolor(IN Brush* brush, IN const Color& fillSubcolor);

	// ���� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	static BOOL setBrushPattern(IN Brush* brush, IN const HatchStyle fillPattern);

// Ư��
protected:
	Pen* m_OutlinePen;	// �׸��� ��
	Brush* m_FillBrush;	// �׸��� �귯��
};


