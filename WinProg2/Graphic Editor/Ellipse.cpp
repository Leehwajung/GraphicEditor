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

CEllipse::CEllipse(IN Pen* pen, IN BrushPtr brush)
	: CShape(pen, brush)
{}

CEllipse::CEllipse(IN Pen* pen, IN BrushPtr brush, IN RectF rect)
	: CShape(pen, brush)
, m_Rect(rect)
{}

CEllipse::~CEllipse()
{
}

CFigure* CEllipse::clone()
{
	return new CEllipse(m_OutlinePen, m_FillBrush, m_Rect);
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
	PointF startingPoint;
	PointF fixedPoint;
	getHandlePoint(getOppositeHandle(selectedHandle), &fixedPoint);

	SizeF rectSize;

	switch (selectedHandle)
	{
	case CFigure::TOPLEFT:
	case CFigure::TOPRIGHT:
	case CFigure::BOTTOMRIGHT:
	case CFigure::BOTTOMLEFT:
		rectSize.Width = fixedPoint.X > targetPoint.X ?
			fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
		rectSize.Height = fixedPoint.Y > targetPoint.Y ?
			fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;

		if (fixedPoint.X > targetPoint.X) {
			startingPoint.X = targetPoint.X;
		}
		else {
			startingPoint.X = fixedPoint.X;
		}

		if (fixedPoint.Y > targetPoint.Y) {
			startingPoint.Y = targetPoint.Y;
		}
		else {
			startingPoint.Y = fixedPoint.Y;
		}

		break;

	case CFigure::TOP:
	case CFigure::BOTTOM:
		rectSize.Width = m_Rect.Width;
		rectSize.Height = fixedPoint.Y > targetPoint.Y ?
			fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;

		startingPoint.X = m_Rect.X;

		if (fixedPoint.Y > targetPoint.Y) {
			startingPoint.Y = targetPoint.Y;
		}
		else {
			startingPoint.Y = fixedPoint.Y;
		}

		break;

	case CFigure::RIGHT:
	case CFigure::LEFT:
		rectSize.Width = fixedPoint.X > targetPoint.X ?
			fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
		rectSize.Height = m_Rect.Height;

		if (fixedPoint.X > targetPoint.X) {
			startingPoint.X = targetPoint.X;
		}
		else {
			startingPoint.X = fixedPoint.X;
		}

		startingPoint.Y = m_Rect.Y;

		break;

	default:
		// 잘못된 selectedHandle
		// 아무 동작을 하지 않음
		return;
	}

	m_Rect = RectF(startingPoint, rectSize);

	resetArea();
	
}

void CEllipse::destroy(){
	if (this) {
		this->~CEllipse();
	}
}
// Position: 타원 상의 점의 위치
CFigure::Position CEllipse::pointInFigure(IN PointF point){
	RectF handleRect;

	for (int handleIndex = TOPLEFT; handleIndex <= LEFT; handleIndex++) {

		getHandleRect((Position)handleIndex, &handleRect);
		if (handleRect.Contains(point)) {
			return (Position)handleIndex;
		}
	}

	GraphicsPath Ellipse;
	Ellipse.AddEllipse(m_Rect);

	if (Ellipse.IsVisible(point)) {
		return INSIDE;
	}

	return OUTSIDE;
}
// Ellipse 외곽선 그리기 및 채우기
void CEllipse::draw(IN Graphics& graphics){
	graphics.FillEllipse(m_FillBrush, m_Rect); // ellipse 채우기
	graphics.DrawEllipse(m_OutlinePen, m_Rect); // 그래픽객체의 drawellipse 함수
}

// 생성 시에 보여줄 그리기
// - IN 매개변수
//		PointF startingPoint: 생성 시작 좌표
//		PointF targetPoint: 생성 시 선택 중인 좌표
//		CreateFlag createFlag = FREECREATE: 생성 설정 플래그
RectF CEllipse::creating(IN Graphics& graphics, IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/)
 {
	 return creating(graphics, &startingPoint, &targetPoint, createFlag);
 }

RectF  CEllipse::creating(IN Graphics& graphics, void* param1, ...)
 {
	va_list vaList;
	va_start(vaList, param1);
	PointF startingPoint = *(PointF*)param1;
	PointF targetPoint = *va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	RectF drawnArea;

	SizeF rectSize;
	rectSize.Width = startingPoint.X > targetPoint.X ? startingPoint.X - targetPoint.X : targetPoint.X - startingPoint.X;
	rectSize.Height = startingPoint.Y > targetPoint.Y ? startingPoint.Y - targetPoint.Y : targetPoint.Y - startingPoint.Y;

	if (startingPoint.X > targetPoint.X) {
		startingPoint.X = targetPoint.X;
	}

	if (startingPoint.Y > targetPoint.Y) {
		startingPoint.Y = targetPoint.Y;
	}

	RectF rect = RectF(startingPoint, rectSize);
	 graphics.FillEllipse(CGlobal::crateIngBrush(m_FillBrush), rect);
	 graphics.DrawEllipse(CGlobal::crateIngPen(m_OutlinePen), rect);


	 return drawnArea;
 }

 // 이동 그리기
 // 이동 중에 보여줄 그리기
 // - IN 매개변수
 //		PointF originPoint: 이동의 시작 좌표
 //		PointF targetPoint: 이동 중인 좌표
 //		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
RectF  CEllipse::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
 {
	 RectF drawnArea;

	 RectF rect = m_Rect;
	 PointF offset;
	 if (moveFlag == FREEMOVE)//자유이동 case일 때
	 {
		 offset = targetPoint - originPoint;
	 }
	 else//!=FREEMOVE인 case
	 {
		 PointF ratio;
		 ratio.X = rect.GetLeft();
		 ratio.Y = rect.GetTop();
		 // 좌우 이동
		 if (targetPoint.X - ratio.X >= targetPoint.Y - ratio.Y){
			 offset.X = targetPoint.X - originPoint.X;
			 offset.Y = originPoint.Y;
		 }
		 else// 상하이동
		 {
			 offset.X = originPoint.X;
			 offset.Y = targetPoint.Y - originPoint.Y;
		 }
	 }

	 rect.Offset(offset);
	 graphics.FillEllipse(CGlobal::crateIngBrush(m_FillBrush), rect); // ellipse 채우기
	 graphics.DrawEllipse(CGlobal::crateIngPen(m_OutlinePen), rect);

	 return drawnArea;
 }

 // 크기 변경 그리기
 // 크기 변경 중에 보여줄 그리기
 // - IN 매개변수
 //		Position selectedHandle: 개체의 선택된 핸들
 //		PointF targetPoint: 선택된 핸들을 이동하고 있는 좌표
 //		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
 //		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
RectF  CEllipse::resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
 {
	 RectF drawnArea;

	 RectF rect = m_Rect; //temp

	 PointF startingPoint;
	 PointF fixedPoint;
	 PointF Gradeint;
	 getHandlePoint(getOppositeHandle(selectedHandle), &fixedPoint);

	 SizeF rectSize;

	 if(resizeFlag == FREERESIZE){
	switch (selectedHandle)
		 {
		 case CFigure::TOPLEFT:
		 case CFigure::TOPRIGHT:
		 case CFigure::BOTTOMRIGHT:
		 case CFigure::BOTTOMLEFT:
			 rectSize.Width = fixedPoint.X > targetPoint.X ?
				 fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
			 rectSize.Height = fixedPoint.Y > targetPoint.Y ?
				 fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;

			 if (fixedPoint.X > targetPoint.X) {
				 startingPoint.X = targetPoint.X;
			 }
			 else {
				 startingPoint.X = fixedPoint.X;
			 }

			 if (fixedPoint.Y > targetPoint.Y) {
				 startingPoint.Y = targetPoint.Y;
			 }
			 else {
				 startingPoint.Y = fixedPoint.Y;
			 }

			 break;

		 case CFigure::TOP:
		 case CFigure::BOTTOM:
			 rectSize.Width = m_Rect.Width;
			 rectSize.Height = fixedPoint.Y > targetPoint.Y ?
				 fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;

			 startingPoint.X = m_Rect.X;

			 if (fixedPoint.Y > targetPoint.Y) {
				 startingPoint.Y = targetPoint.Y;
			 }
			 else {
				 startingPoint.Y = fixedPoint.Y;
			 }

			 break;

		 case CFigure::RIGHT:
		 case CFigure::LEFT:
			 rectSize.Width = fixedPoint.X > targetPoint.X ?
				 fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
			 rectSize.Height = m_Rect.Height;

			 if (fixedPoint.X > targetPoint.X) {
				 startingPoint.X = targetPoint.X;
			 }
			 else {
				 startingPoint.X = fixedPoint.X;
			 }

			 startingPoint.Y = m_Rect.Y;

			 break;

		 default:
			 // 잘못된 selectedHandle
			 // 아무 동작을 하지 않음
			 return NULLRectF;
		 }
	 }
	 else{
		 switch (selectedHandle)
		 {
			 //
		 case CFigure::TOPLEFT:
		 case CFigure::TOPRIGHT:
		 case CFigure::BOTTOMRIGHT:
		 case CFigure::BOTTOMLEFT:
			 rectSize.Width = fixedPoint.X > targetPoint.X ?
				 fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
			 rectSize.Height = fixedPoint.Y > targetPoint.Y ?
				 fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;
			 
			 // 기울기가 무한대와 0인 케이스를 걸러냄
			 if (targetPoint.X == fixedPoint.X || targetPoint.Y == fixedPoint.Y)
				 break;
			 float t_grad, h_grad, h_oppositegrad;
			 h_grad = rect.Y / rect.X;
			 if (h_grad < 0){
				 h_grad = -h_grad;//아래 연산을 위해
			 }
			 h_oppositegrad = -h_grad;
			 Gradeint = fixedPoint - targetPoint;
			 t_grad = Gradeint.Y / Gradeint.X;

	 
			 if (t_grad <= h_grad && t_grad >= h_oppositegrad)// x를기준으로
			 {
				 startingPoint.X = targetPoint.X;
				 startingPoint.Y = targetPoint.X*(1 / h_grad);
			 }
			 else
			 {
				 startingPoint.Y = targetPoint.Y;
				 startingPoint.X = targetPoint.Y*(1 / h_grad);
			 }
			 break;

			 // 적용안되고 그대로
		 case CFigure::TOP:
		 case CFigure::BOTTOM:
			 rectSize.Width = m_Rect.Width;
			 rectSize.Height = fixedPoint.Y > targetPoint.Y ?
				 fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;

			 startingPoint.X = m_Rect.X;

			 if (fixedPoint.Y > targetPoint.Y) {
				 startingPoint.Y = targetPoint.Y;
			 }
			 else {
				 startingPoint.Y = fixedPoint.Y;
			 }

			 break;

			 // shift 적용안되고 그대로
		 case CFigure::RIGHT:
		 case CFigure::LEFT:
			 rectSize.Width = fixedPoint.X > targetPoint.X ?
				 fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
			 rectSize.Height = m_Rect.Height;

			 if (fixedPoint.X > targetPoint.X) {
				 startingPoint.X = targetPoint.X;
			 }
			 else {
				 startingPoint.X = fixedPoint.X;
			 }

			 startingPoint.Y = m_Rect.Y;

			 break;

		 default:
			 // 잘못된 selectedHandle
			 // 아무 동작을 하지 않음
			 return NULLRectF;
		 }
	 }
	 rect = RectF(startingPoint, rectSize);
	 graphics.FillEllipse(CGlobal::crateIngBrush(m_FillBrush), rect); // ellipse 채우기
	 graphics.DrawEllipse(CGlobal::crateIngPen(m_OutlinePen), rect);

	 return drawnArea;
 }

 /* 개체 영역 관리 */
 // 개체 영역 갱신
RectF  CEllipse::resetArea(){
	 m_Area = m_Rect;

	 return m_Area;
 }

void CEllipse::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_FillBrush;
		ar << m_OutlinePen;
		ar << m_Rect.X;
		ar << m_Rect.Y;
		ar << m_Rect.Width;
	}
	else
	{	// loading code
		ar >> m_Rect.X;
		ar >> m_Rect.Y;
		ar >> m_Rect.Width;
	}
}
