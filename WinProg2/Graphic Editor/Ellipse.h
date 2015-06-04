// Ellipse.h : CEllipse Ŭ������ �������̽�
// CEllipse : Ÿ�� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Shape.h"

// CEllipse ��� ����Դϴ�.

class CEllipse : public CShape
{
public:
	CEllipse();
	CEllipse(IN CClientDC* lpClientDC);
	CEllipse(IN Graphics* lpGraphics);
	CEllipse(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush);
	CEllipse(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush);
	CEllipse(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush, IN RectF rect);
	CEllipse(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush, IN RectF rect);

	DECLARE_SERIAL(CEllipse)
	virtual ~CEllipse();

public:
	// ����ȭ
	virtual void Serialize(CArchive& ar);
	BOOL create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag = FREECREATE);
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	virtual void resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);
	virtual void destroy();
	// Position: Ÿ�� ���� ���� ��ġ
	virtual Position pointInFigure(IN PointF point);
	virtual void draw();

	void creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag = FREECREATE);
	virtual void creating(void* param1, ...);
	virtual void moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	virtual void resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);
	virtual void resetArea();

protected:
	RectF m_Rect;	// ������ �簢��
};


