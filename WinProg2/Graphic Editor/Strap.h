// Strap.h : CStrap Ŭ������ �������̽�
// CStrap : �� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Figure.h"

// CStrap ��� ����Դϴ�.

class CStrap : public CFigure
{
public:
	CStrap();
	CStrap(IN Pen* pen);
	DECLARE_SERIAL(CStrap)
	virtual ~CStrap();

	virtual void Serialize(CArchive& ar);

	// �� �߰� (���� ����)
	//virtual void addPoint(PointF point);

	// ���� ��ǥ �̵�
	virtual void pointMove(IN PointF originPoint, IN PointF targetPoint);

	// ���� ��ǥ �̵� �׸���
	virtual void pointMoving(IN PointF originPoint, IN PointF targetPoint);

	// �� ȹ��
	Pen* getPen();

	// ������ �� ȹ��
	Color getOutlineColor();

	// ������ �β� ȹ��
	REAL getOutlineWidth();

	// ������ ���� ȹ��
	DashStyle getOutlinePattern();

	// �� ����
	// �� ��ü�� ������ ���� ������ �־�� �ϹǷ� ���ڷ� ���� Pen�� �������� ����
	void setPen(IN const Pen* pen);

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
	//		FALSE: ä��Ⱑ �����Ƿ� ������ ��ȯ (�������� ����)
	virtual BOOL setFillColor(IN const Color& fillColor) { return FALSE; }

	// ���� ä��� �� ����
	// - ��ȯ �� (BOOL)
	//		FALSE: ä��Ⱑ �����Ƿ� ������ ��ȯ (�������� ����)
	virtual BOOL setFillSubcolor(IN const Color& fillSubcolor) { return FALSE; }

	// ä��� ���� ����
	// - ��ȯ �� (BOOL)
	//		FALSE: ä��Ⱑ �����Ƿ� ������ ��ȯ (�������� ����)
	virtual BOOL setFillPattern(IN const HatchStyle fillPattern) { return FALSE; }


// Ư��
protected:
	PenPtr m_OutlinePen;
};


