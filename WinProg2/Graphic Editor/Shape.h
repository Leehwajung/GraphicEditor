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
	CShape(IN Pen* pen, IN Brush* brush);
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
	static Color getBrushColor(IN BrushPtr brush);

	// ������ ȹ��
	static Color getBrushSubcolor(IN BrushPtr brush);

	// ���� ȹ��
	static HatchStyle getBrushPattern(IN BrushPtr brush);

	// �ֻ� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	static BOOL setBrushColor(IN BrushPtr& brush, IN const Color& fillColor);

	// ������ ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	static BOOL setBrushSubcolor(IN BrushPtr& brush, IN const Color& fillSubcolor);

	// ���� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	static BOOL setBrushPattern(IN BrushPtr& brush, IN const HatchStyle fillPattern);

// Ư��
protected:
	PenPtr m_OutlinePen;	// �׸��� ��
	BrushPtr m_FillBrush;	// �׸��� �귯��
};


