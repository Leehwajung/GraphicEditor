// Ellipse.cpp : CEllipse 클래스의 구현
// CEllipse : 타원 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Ellipse.h"


// CEllipse

IMPLEMENT_SERIAL(CEllipse, CShape, 1)


CEllipse::CEllipse()
: CShape()
{
}
CEllipse::CEllipse(IN CClientDC* lpClientDC) : CShape(lpClientDC)
{}
CEllipse::CEllipse(IN Graphics* lpGraphics) : CShape(lpGraphics)
{}
CEllipse::CEllipse(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush) : CShape(lpClientDC, pen, brush)
{}
CEllipse::CEllipse(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush)
	: CShape(lpGraphics, pen, brush)
{}
CEllipse::CEllipse(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush, IN RectF rect)
	: CShape(lpClientDC, pen, brush)
, m_Rect(rect)
{}

CEllipse::~CEllipse()
{
}

// CEllipse 멤버 함수

BOOL CEllipse::create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag = FREECREATE){}
void CEllipse::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE){}
void CEllipse::resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL){}
void CEllipse::destroy(){}
// Position: 타원 상의 점의 위치
CFigure::Position CEllipse::pointInFigure(IN PointF point){}
 void draw();

 void  CEllipse::creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag = FREECREATE)
 {}
 void  CEllipse::creating(void* param1, ...)
 {}
 void  CEllipse::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE)
 {}
 void  CEllipse::resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL)
 {}
 void  CEllipse::resetArea(){
 }

void CEllipse::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
