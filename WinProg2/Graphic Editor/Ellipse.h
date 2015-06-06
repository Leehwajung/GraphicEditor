// Ellipse.h : CEllipse 클래스의 인터페이스
// CEllipse : 타원 개체를 정의하는 클래스
// 

#pragma once
#include "Shape.h"

// CEllipse 명령 대상입니다.

class CEllipse : public CShape
{
public:
	CEllipse();
	CEllipse(IN Pen* pen, IN BrushPtr brush);
	CEllipse(IN Pen* pen, IN BrushPtr brush, IN RectF rect);

	DECLARE_SERIAL(CEllipse)
	virtual ~CEllipse();

public:
	// 직렬화
	virtual void Serialize(CArchive& ar);
	BOOL create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag = FREECREATE);
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	virtual void resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);
	virtual void destroy();
	// Position: 타원 상의 점의 위치
	virtual Position pointInFigure(IN PointF point);
	virtual void draw(IN Graphics* lpGraphics);

	void creating(IN Graphics* lpGraphics, IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag = FREECREATE);
	virtual void creating(IN Graphics* lpGraphics, void* param1, ...);
	virtual void moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	virtual void resizing(IN Graphics* lpGraphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);
	
	virtual RectF resetArea();// 개체영역 재정의

protected:
	RectF m_Rect;	// 타원이 내접할 사각형
private:
	virtual BOOL create(void* param1, ...);
};


