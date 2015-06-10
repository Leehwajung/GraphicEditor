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
	// ������ �� ȹ��
	Pen* getOutlinePen();

	// ä��� �귯�� ȹ��
	Brush* getFillBrush();

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
	
	// ������ �� ����
	// �� ��ü�� ������ ���� ������ �־�� �ϹǷ� ���ڷ� ���� Pen�� �������� ����
	void setOutlinePen(IN const Pen* pen);

// ������
public:
	// ä��� �귯�� ����
	// �� ��ü�� ������ �귯�ø� ������ �־�� �ϹǷ� ���ڷ� ���� Brush�� �������� ����
	virtual void setFillBrush(IN const Brush* brush, IN BOOL PropertyMaintenanceFlag = FALSE);


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

	// �귯�� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	static BOOL setBrush(IN BrushPtr& brush, IN Brush* srcBrush, IN BOOL PropertyMaintenanceFlag = FALSE);

// Ư��
protected:
	PenPtr m_OutlinePen;	// �׸��� ��
	BrushPtr m_FillBrush;	// �׸��� �귯��
};


