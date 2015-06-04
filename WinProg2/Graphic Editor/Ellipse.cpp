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

BOOL CEllipse::create(void* param1, ...)
{
	va_list vaList;
	va_start(vaList, param1);
	PointF* startingPoint = (PointF*)param1;
	PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	SizeF rectSize;
	rectSize.Width = startingPoint->X > endingPoint->X ? startingPoint->X - endingPoint->X : endingPoint->X - startingPoint->X;
	rectSize.Height = startingPoint->Y > endingPoint->Y ? startingPoint->Y - endingPoint->Y : endingPoint->Y - startingPoint->Y;

	if (startingPoint->X > endingPoint->X) {
		startingPoint->X = endingPoint->X;
	}

	if (startingPoint->Y > endingPoint->Y) {
		startingPoint->Y = endingPoint->Y;
	}

	RectF* rect = new RectF(*startingPoint, rectSize);

	if (!rect) {
		return TRUE;
	}

	m_Rect = *rect;

	resetArea();

	return FALSE;
}

void CEllipse::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
}
void CEllipse::resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{

}
void CEllipse::destroy(){}
// Position: 타원 상의 점의 위치
CFigure::Position CEllipse::pointInFigure(IN PointF point){
	RectF handleRect;

	for (int handleIndex = TOPLEFT; handleIndex <= LEFT; handleIndex++) {

		getHandleRect((Position)handleIndex, &handleRect);
		if (handleRect.Contains(point)) {
			return (Position)handleIndex;
		}
	}

	if (m_Rect.Contains(point)) {
		return INSIDE;
	}

	return OUTSIDE;
}
void CEllipse::draw(){
	m_lpGraphics->FillRectangle(m_FillBrush, m_Rect);
	m_lpGraphics->DrawRectangle(m_OutlinePen, m_Rect);
}

 void CEllipse::creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/)
 {
	 creating(&startingPoint, &targetPoint, createFlag);
 }
 void  CEllipse::creating(void* param1, ...)
 {}
 void  CEllipse::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
 {

 }
 void  CEllipse::resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
 {

 }
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
