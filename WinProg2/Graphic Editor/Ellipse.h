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
	CEllipse(IN Pen* pen, IN BrushPtr brush);
	CEllipse(IN Pen* pen, IN BrushPtr brush, IN RectF rect);

	DECLARE_SERIAL(CEllipse)
	virtual ~CEllipse();

public:
	// ����ȭ
	virtual void Serialize(CArchive& ar);
	BOOL create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag = FREECREATE);
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	virtual void resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);
	virtual void destroy();
	// Position: Ÿ�� ���� ���� ��ġ
	virtual Position pointInFigure(IN PointF point);
	virtual void draw(IN Graphics* lpGraphics);

	RectF creating(IN Graphics* lpGraphics, IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag = FREECREATE);
	virtual RectF creating(IN Graphics* lpGraphics, void* param1, ...);
	virtual RectF moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	virtual RectF resizing(IN Graphics* lpGraphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);
	
	virtual RectF resetArea();// ��ü���� ������

protected:
	RectF m_Rect;	// Ÿ���� ������ �簢��
private:
	virtual BOOL create(void* param1, ...);
};


