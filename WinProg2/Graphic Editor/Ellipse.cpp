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
/* 연산 */
BOOL CEllipse::create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag/* = FREECREATE*/)
{
	return create(&startingPoint, &endingPoint, createFlag);	 // 임시 반환 값
}
BOOL CEllipse::create(void* param1, ...)
{
	va_list vaList;
	va_start(vaList, param1);
	PointF* startingPoint = (PointF*)param1;
	PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	SizeF rectSize;
	rectSize.Width = startingPoint->X > endingPoint->X ? 
		startingPoint->X - endingPoint->X : endingPoint->X - startingPoint->X;
	rectSize.Height = startingPoint->Y > endingPoint->Y ? 
		startingPoint->Y - endingPoint->Y : endingPoint->Y - startingPoint->Y;

	if (startingPoint->X > endingPoint->X) {
		startingPoint->X = endingPoint->X;
	}

	if (startingPoint->Y > endingPoint->Y) {
		startingPoint->Y = endingPoint->Y;
	}

	m_Rect = RectF(*startingPoint, rectSize);

	resetArea();

	return FALSE;
}

void CEllipse::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	// originPoint: ButtonDown
	// targetPoint: ButtonUp

	PointF offset = targetPoint - originPoint;

	m_Rect.Offset(offset);
	resetArea();
}
void CEllipse::resize(IN Position selectedHandle, IN PointF targetPoint,
	IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	/*PointF AP;

	if (anchorPoint == NULL){
		getHandlePoint(getOppositeHandle(selectedHandle), &AP);
		anchorPoint = &AP;
	}*/
	switch (selectedHandle)
	{
	case CFigure::TOPLEFT:

		break;

	case CFigure::TOP:

		break;

	case CFigure::TOPRIGHT:

		break;

	case CFigure::RIGHT:

		break;

	case CFigure::BOTTOMRIGHT:

		break;

	case CFigure::BOTTOM:

		break;

	case CFigure::BOTTOMLEFT:

		break;

	case CFigure::LEFT:

		break;

	default:
		return;
	}

	resetArea();//area를리셋.
	

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
// Ellipse 외곽선 그리기 및 채우기
void CEllipse::draw(){
	m_lpGraphics->FillEllipse(m_FillBrush, m_Rect); // ellipse 채우기
	m_lpGraphics->DrawEllipse(m_OutlinePen, m_Rect); // 그래픽객체의 drawellipse 함수
}

// 생성 시에 보여줄 그리기
// - IN 매개변수
//		PointF startingPoint: 생성 시작 좌표
//		PointF targetPoint: 생성 시 선택 중인 좌표
//		CreateFlag createFlag = FREECREATE: 생성 설정 플래그
 void CEllipse::creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/)
 {
	 creating(&startingPoint, &targetPoint, createFlag);
 }

 void  CEllipse::creating(void* param1, ...)
 {
	 va_list vaList;
	 va_start(vaList, param1);
	 PointF* startingPoint = (PointF*)param1;
	 PointF* targetPoint = va_arg(vaList, PointF*);
	 CreateFlag createFlag = va_arg(vaList, CreateFlag);
	 va_end(vaList);
 }

 // 이동 그리기
 // 이동 중에 보여줄 그리기
 // - IN 매개변수
 //		PointF originPoint: 이동의 시작 좌표
 //		PointF targetPoint: 이동 중인 좌표
 //		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
 void  CEllipse::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
 {

 }

 // 크기 변경 그리기
 // 크기 변경 중에 보여줄 그리기
 // - IN 매개변수
 //		Position selectedHandle: 개체의 선택된 핸들
 //		PointF targetPoint: 선택된 핸들을 이동하고 있는 좌표
 //		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
 //		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
 void  CEllipse::resizing(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
 {

 }

 /* 개체 영역 관리 */
 // 개체 영역 갱신
 void  CEllipse::resetArea(){
	 m_Area = m_Rect;
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
