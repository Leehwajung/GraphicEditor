// Curve.h : CCurve 클래스의 인터페이스
// CCurve : 곡선 개체를 정의하는 클래스
// 

#pragma once
#include "PolyLine.h"

// CCurve 명령 대상입니다.

class CCurve : public CPolyLine
{
public:
	CCurve();
	CCurve(IN Pen* pen);
	CCurve(IN Pen* pen, CList <PointF, PointF&>& list);
	DECLARE_SERIAL(CCurve)
	CFigure* clone();
	~CCurve();
	virtual void Serialize(CArchive& ar);
	virtual Position pointInFigure(IN PointF point);
	RectF creating(IN Graphics& graphics, IN PointF addingPoint, IN CreateFlag createFlag = FREECREATE);
protected:
	virtual RectF creating(IN Graphics& graphics, void* param1, ...);
public:
	virtual RectF moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	virtual RectF resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);
	virtual RectF pointMoving(Graphics& graphics, IN PointF originPoint, IN PointF targetPoint);
	virtual void draw(IN Graphics& graphics);
};


