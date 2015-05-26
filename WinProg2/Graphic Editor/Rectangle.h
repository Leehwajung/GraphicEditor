// Rectangle.h : CRectangle Ŭ������ �������̽�
// CRectangle : ���簢�� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Shape.h"

// CRectangle ��� ����Դϴ�.

class CRectangle : public CShape
{
public:
	CRectangle();
	CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/);
	CRectangle(Graphics* lpGraphics/*, PointF startingPoint*/);
	//CRectangle(CClientDC* lpClientDC, RectF& rect);
	CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/, /*RectF& rect,*/ Pen* pen, SolidBrush* brush);
	virtual ~CRectangle();

	// LButtonDown
	virtual void create(PointF startingPoint);					// ��ü ����
	virtual operationModeFlags cursorPosition(PointF point);	// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���)


	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
	virtual void creating(UINT nFlags, PointF point);			// ���� �׸���
	virtual void moving(UINT nFlags, PointF point);				// �̵� �׸���
	virtual void resizing(UINT nFlags, PointF point);			// ũ�� ���� �׸���

	// LButtonUp
	virtual void endCreate(PointF point);						// ���� �Ϸ�
	virtual void move(PointF originPoint, PointF targetPoint);							// ��ü �̵�
	virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// ��ü ũ�� ����
	virtual operationModeFlags cursorPosition(RectF rect);		// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���)

	// OnDraw / OnPaint
	virtual void draw();										// ��ü �׸���
	virtual void drawSelect();

	// Menu Item
	virtual void destroy();										// ��ü ����

// Ư��
protected:
	RectF m_Rect;	// �簢��
};

