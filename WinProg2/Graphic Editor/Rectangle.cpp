// Rectangle.cpp : CRectangle 클래스의 구현
// CRectangle : 직사각형 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Rectangle.h"


// CRectangle

IMPLEMENT_SERIAL(CRectangle, CShape, 1)


CRectangle::CRectangle()
	: CShape()
{
}

CRectangle::CRectangle(IN Pen* pen, IN BrushPtr brush)
	: CShape(pen, brush)
{
}

CRectangle::CRectangle(IN Pen* pen, IN BrushPtr brush, IN RectF rect)
	: CShape(pen, brush)
	, m_Rect(rect)
{
}

CRectangle::~CRectangle()
{
}



// CRectangle 멤버 함수

/* 직렬화 */
// 직렬화
void CRectangle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


/* 연산 */
// 생성
// 시작 좌표와 끝 좌표를 기준으로 사각형을 생성함
// - IN 매개변수
//		PointF startingPoint: 생성 시작 좌표
//		PointF endingPoint: 생성 끝 좌표
//		CreateFlag createFlag = FREECREATE: 생성 설정 플래그
// - 반환 값 (BOOL)
//		TRUE: 생성 실패
//		FALSE: 생성 성공
BOOL CRectangle::create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag/* = FREECREATE*/)
{
	return create(&startingPoint, &endingPoint, createFlag);	 // 임시 반환 값
}

// 생성
// 시작 좌표와 끝 좌표를 기준으로 사각형을 생성함
// - IN 매개변수
//		void* param1, ...: PointF*(startingPoint), PointF*(endingPoint), CreateFlag 순으로 입력
// - 반환 값 (BOOL)
//		TRUE: 생성 실패
//		FALSE: 생성 성공
BOOL CRectangle::create(void* param1, ...)
{
	va_list vaList;
	va_start(vaList, param1);
	PointF* fixedPoint = (PointF*)param1;
	PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	PointF startingPoint = *fixedPoint;

	SizeF rectSize;
	rectSize.Width = abs(fixedPoint->X - endingPoint->X);
	rectSize.Height = abs(fixedPoint->Y - endingPoint->Y);

	switch (createFlag)
	{
		case CFigure::FREECREATE: {
			if (fixedPoint->X > endingPoint->X) {
				startingPoint.X = endingPoint->X;
			}

			if (fixedPoint->Y > endingPoint->Y) {
				startingPoint.Y = endingPoint->Y;
			}
		} break;

		case CFigure::REGULAR: {
			REAL regularSize = max(rectSize.Width, rectSize.Height);

			rectSize.Width = regularSize;
			rectSize.Height = regularSize;

			if (fixedPoint->X > endingPoint->X) {
				startingPoint.X = fixedPoint->X - regularSize;
			}

			if (fixedPoint->Y > endingPoint->Y) {
				startingPoint.Y = fixedPoint->Y - regularSize;
			}
		} break;
	}

	m_Rect = RectF(startingPoint, rectSize);

	resetArea();

	return FALSE;
}

// 이동
// 시작 좌표부터 끝 좌표까지의 Offset을 기준으로 사각형을 이동
// - IN 매개변수
//		PointF originPoint: 이동의 시작 좌표
//		PointF targetPoint: 이동의 끝 좌표
//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
void CRectangle::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	// originPoint: ButtonDown
	// targetPoint: ButtonUp
	
	PointF offset = targetPoint - originPoint;

	switch (moveFlag)
	{
	case CFigure::FREEMOVE:
		// 추가 작업 없음
		break;

	case CFigure::FOURWAY:
		if (abs(offset.X) > abs(offset.Y)) {
			offset.Y = 0;
		}
		else {
			offset.X = 0;
		}
		break;
	}

	m_Rect.Offset(offset);
	resetArea();
}

// 크기 변경
// 선택한 핸들의 좌표를 변경하여 크기 변경 (기준 좌표를 설정하면 이를 기준으로 각 좌표를 변경하여 크기 변경)
// - IN 매개변수
//		Position selectedHandle: 사각형의 선택된 핸들
//		PointF targetPoint: 선택된 핸들의 변경할 좌표
//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
void CRectangle::resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	//PointF startingPoint;
	//getHandlePoint(selectedHandle, &startingPoint);
	//PointF oppositePoint;
	//getHandlePoint(getOppositeHandle(selectedHandle), &oppositePoint);
	//PointF fixedPoint;
	//if (anchorPoint) {
	//	fixedPoint = *anchorPoint;
	//}
	//else{
	//	fixedPoint = oppositePoint;
	//}
	//
	//SizeF anchorRectSize;
	//anchorRectSize.Width = abs(fixedPoint.X - oppositePoint.X);
	//anchorRectSize.Height = abs(fixedPoint.Y - oppositePoint.Y);

	//SizeF bigRectSize;
	//bigRectSize.Width = abs(fixedPoint.X - startingPoint.X);
	//bigRectSize.Height = abs(fixedPoint.Y - startingPoint.Y);

	//SizeF targetRectSize;
	//targetRectSize.Width = abs(fixedPoint.X - targetPoint.X);
	//targetRectSize.Height = abs(fixedPoint.Y - targetPoint.Y);

	//SizeF ratioRect;
	//ratioRect.Width = targetRectSize.Width / bigRectSize.Width;
	//ratioRect.Height = targetRectSize.Height / bigRectSize.Height;

	//SizeF newAnchorRectSize;
	//SizeF newBigRectSize;

	//switch (selectedHandle)
	//{
	//case CFigure::TOPLEFT:
	//case CFigure::TOPRIGHT:
	//case CFigure::BOTTOMRIGHT:
	//case CFigure::BOTTOMLEFT:
	//	newAnchorRectSize.Width = anchorRectSize.Width * ratioRect.Width;
	//	newAnchorRectSize.Height = anchorRectSize.Height * ratioRect.Height;

	//	if (fixedPoint.X > targetPoint.X) {
	//		startingPoint.X = targetPoint.X;
	//	}
	//	else {
	//		startingPoint.X = fixedPoint.X - m_Rect.X;
	//	}

	//	if (fixedPoint.Y > targetPoint.Y) {
	//		startingPoint.Y = targetPoint.Y;
	//	}
	//	else {
	//		startingPoint.Y = fixedPoint.Y;
	//	}

	//	break;

	//case CFigure::TOP:
	//case CFigure::BOTTOM:
	//	newAnchorRectSize.Height = anchorRectSize.Height;
	//	newAnchorRectSize.Height = anchorRectSize.Height * ratioRect.Height;

	//	startingPoint.X = m_Rect.X;

	//	if (fixedPoint.Y > targetPoint.Y) {
	//		startingPoint.Y = targetPoint.Y;
	//	}
	//	else {
	//		startingPoint.Y = fixedPoint.Y;
	//	}

	//	break;

	//case CFigure::RIGHT:
	//case CFigure::LEFT:
	//	newAnchorRectSize.Width = anchorRectSize.Width * ratioRect.Width;
	//	newAnchorRectSize.Height = anchorRectSize.Height;

	//	if (fixedPoint.X > targetPoint.X) {
	//		startingPoint.X = targetPoint.X;
	//	}
	//	else {
	//		startingPoint.X = fixedPoint.X;
	//	}

	//	startingPoint.Y = m_Rect.Y;

	//	break;

	//default:
	//	// 잘못된 selectedHandle
	//	// 아무 동작을 하지 않음
	//	return;
	//}



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
		rectSize.Width = abs(fixedPoint.X - targetPoint.X);
		rectSize.Height = abs(fixedPoint.Y - targetPoint.Y);

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
		rectSize.Height = abs(fixedPoint.Y - targetPoint.Y);

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
		rectSize.Width = abs(fixedPoint.X - targetPoint.X);
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

// 삭제
// 사각형을 삭제하고 메모리를 해제
void CRectangle::destroy()
{

}

// 좌표 위치 확인
// 점이 사각형 안에 있는지 확인하고 그 위치를 반환함
// - IN 매개변수
//		PointF point: 확인할 좌표
// - 반환 값 (Position)
//		Position: 사각형 상의 점의 위치
CFigure::Position CRectangle::pointInFigure(IN PointF point)
{
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


/* 개체 영역 관리 */
// 개체 영역 갱신
RectF CRectangle::resetArea()
{
	m_Area = m_Rect;

	return m_Area;
}


/* 그리기 */
// 개체 그리기
void CRectangle::draw(IN Graphics& graphics)
{
	graphics.FillRectangle(m_FillBrush, m_Rect);
	graphics.DrawRectangle(m_OutlinePen, m_Rect);
}

// 생성 그리기
// 생성 시에 보여줄 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
//		PointF startingPoint: 생성 시작 좌표
//		PointF targetPoint: 생성 시 선택 중인 좌표
//		CreateFlag createFlag = FREECREATE: 생성 설정 플래그
RectF CRectangle::creating(IN Graphics& graphics, IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/)
{
	return creating(graphics, &startingPoint, &targetPoint, createFlag);
}

// 생성 그리기
// 생성 시에 보여줄 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
//		void* param1, ...: PointF*(startingPoint), PointF*(targetPoint), CreateFlag 순으로 입력
RectF CRectangle::creating(IN Graphics& graphics, void* param1, ...)
{
	va_list vaList;
	va_start(vaList, param1);
	PointF* fixedPoint = (PointF*)param1;
	PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	PointF startingPoint = *fixedPoint;

	SizeF rectSize;
	rectSize.Width = abs(fixedPoint->X - endingPoint->X);
	rectSize.Height = abs(fixedPoint->Y - endingPoint->Y);

	switch (createFlag)
	{
		case CFigure::FREECREATE: {
			if (fixedPoint->X > endingPoint->X) {
				startingPoint.X = endingPoint->X;
			}

			if (fixedPoint->Y > endingPoint->Y) {
				startingPoint.Y = endingPoint->Y;
			}
		} break;

		case CFigure::REGULAR: {
			REAL regularSize = max(rectSize.Width, rectSize.Height);

			rectSize.Width = regularSize;
			rectSize.Height = regularSize;

			if (fixedPoint->X > endingPoint->X) {
				startingPoint.X = fixedPoint->X - regularSize;
			}

			if (fixedPoint->Y > endingPoint->Y) {
				startingPoint.Y = fixedPoint->Y - regularSize;
			}
		} break;
	}

	RectF drawnArea = RectF(startingPoint, rectSize);
	graphics.FillRectangle(CGlobal::crateIngBrush(m_FillBrush), drawnArea);
	graphics.DrawRectangle(CGlobal::crateIngPen(m_OutlinePen), drawnArea);

	return drawnArea;
}

// 이동 그리기
// 이동 중에 보여줄 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
//		PointF originPoint: 이동의 시작 좌표
//		PointF targetPoint: 이동 중인 좌표
//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
RectF CRectangle::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	PointF offset = targetPoint - originPoint;
	
	switch (moveFlag)
	{
	case CFigure::FREEMOVE:
		// 추가 작업 없음
		break;

	case CFigure::FOURWAY:
		if (abs(offset.X) > abs(offset.Y)) {
			offset.Y = 0;
		}
		else {
			offset.X = 0;
		}
		break;
	}

	RectF drawnArea = m_Rect;
	drawnArea.Offset(offset);
	graphics.FillRectangle(CGlobal::crateIngBrush(m_FillBrush), drawnArea);
	graphics.DrawRectangle(CGlobal::crateIngPen(m_OutlinePen), drawnArea);

	return drawnArea;
}

// 크기 변경 그리기
// 크기 변경 중에 보여줄 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
//		Position selectedHandle: 개체의 선택된 핸들
//		PointF targetPoint: 선택된 핸들을 이동하고 있는 좌표
//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
RectF CRectangle::resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	RectF drawnArea;
	RectF rect = m_Rect; //temp

	PointF startingPoint;
	PointF fixedPoint;
	PointF Gradeint;
	getHandlePoint(getOppositeHandle(selectedHandle), &fixedPoint);

	SizeF rectSize;

	if (resizeFlag == FREERESIZE){
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
	graphics.FillRectangle(CGlobal::crateIngBrush(m_FillBrush), rect);
	graphics.DrawRectangle(CGlobal::crateIngPen(m_OutlinePen), rect);

	return drawnArea;
}

CFigure* CRectangle::clone()
{
	return new CRectangle(m_OutlinePen, m_FillBrush, m_Rect);
}

