// Strap.h : CStrap Ŭ������ �������̽�
// CStrap : �� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Figure.h"

// CStrap ���� ����Դϴ�.

class CStrap : public CFigure
{
public:
	CStrap();
	virtual ~CStrap();

	// LButtonDown
	virtual void Create(PointF startingPoint);					// �� ����
	virtual operationModeFlags cursorPosition(PointF point);	// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���)
	virtual operationModeFlags cursorPosition(CRect rect);		// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���)

	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
	virtual void creating(UINT nFlags, PointF point);			// ���� �׸���
	virtual void moving(UINT nFlags, PointF point);				// �̵� �׸���
	virtual void resizing(UINT nFlags, PointF point);			// ũ�� ���� �׸���

	// LButtonUp / LButtonDlk
	virtual void addPoint(PointF point);						// �� �߰�
	virtual void move(PointF target);							// ��ü �̵�
	virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// ��ü ũ�� ����

	// OnDraw / OnPaint
	virtual void draw();										// ��ü �׸���

	// Menu Item
	virtual void destroy();										// ��ü ����

	virtual void setLineColor(Color lineColor);					// �� �� ����
	virtual void setLineWidth(int lineWidth);					// �� �β� ����
	virtual void setLinePattern(int linePattern);				// �� ���� ����
	virtual void setProperties(CFigureProperties properties);	// ������ ������ ��ü �Ӽ� ����

	// Getter / Setter
	Pen& getPen();
	void setPen(const Pen& pen);		// �� ��ü�� ������ ���� ������ �־�� �ϹǷ� ���ڷ� ���� Pen�� �������� ����

// Ư��
protected:
	Pen m_Pen;
};

