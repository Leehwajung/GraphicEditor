// FigurePtrList.cpp : CFigurePtrList 클래스의 인터페이스
// CFigurePtrList : 개체들의 포인터를 저장하는 리스트 클래스
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Figure.h"

using namespace Gdiplus;

// CFigure

IMPLEMENT_SERIAL(CFigure, CObject, 1)

CFigure::CFigure()
	//: graphics(NULL)
	//, m_GraphicsDynamicAllocationFlag(FALSE)
{
	ID = IDcount++;
}

//CFigure::CFigure(CClientDC* lpClientDC)
//	: graphics(new Graphics(*lpClientDC))
//	, m_GraphicsDynamicAllocationFlag(TRUE)
//{
//}
//
//CFigure::CFigure(Graphics& graphics)
//	: graphics(graphics)
//	, m_GraphicsDynamicAllocationFlag(FALSE)
//{
//}

CFigure::~CFigure()
{
	//if (m_GraphicsDynamicAllocationFlag && graphics) {
	//	graphics.~Graphics();
	//}
}

CFigure* CFigure::clone(){
	return new CFigure();
}


// CFigure 멤버 변수
UINT CFigure::IDcount = 0;


// CFigure 멤버 함수

/** 직렬화 **/
// 직렬화 (순수가상함수로 바꿀지 검토)
void CFigure::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


/** 연산 **/
// 개체 위치 확인
// 개체가 사각형 안에 있는지 확인하고 그 위치를 반환함
// - IN 매개변수
//		RectF rect: 확인할 좌표
// - 반환 값 (BOOL)
//		TRUE: 개체가 사각형 내부에 존재할 때 (도형의 모든 점이 사각형 내부에 존재)
//		FALSE: 개체가 사각형 내부에 존재하지 않을 때
BOOL CFigure::figureInRect(IN RectF rect)
{
	if (rect.Contains(m_Area)) {
		return TRUE;
	}

	return FALSE;
}

// 개체 영역
// 개체 영역을 얻음
RectF CFigure::getArea()
{
	return m_Area;
}


/** 핸들 관리 **/
// 핸들의 좌표
// 핸들의 중앙 좌표를 얻음
// - IN 매개변수
//		Position handle: 좌표를 얻고자하는 핸들
// - OUT 매개변수
//		PointF* handlePoint:
//			주소 값: 매개변수의 Position이 핸들인 경우 핸들의 좌표
//			NULL: 매개변수의 Position이 핸들이 아닐 경우
// - 반환 값 (BOOL)
//		TRUE: 매개변수의 Position이 핸들이 아닐 경우
//		FALSE: 매개변수의 Position이 핸들인 경우
BOOL CFigure::getHandlePoint(IN Position handle, OUT PointF* handlePoint)
{
	switch (handle)
	{
	case CFigure::TOPLEFT:
		m_Area.GetLocation(handlePoint);
		break;
	case CFigure::TOP:
		handlePoint->X = (m_Area.GetLeft() + m_Area.GetRight()) / 2;
		handlePoint->Y = m_Area.GetTop();
		break;
	case CFigure::TOPRIGHT:
		handlePoint->X = m_Area.GetRight();
		handlePoint->Y = m_Area.GetTop();
		break;
	case CFigure::RIGHT:
		handlePoint->X = m_Area.GetRight();
		handlePoint->Y = (m_Area.GetTop() + m_Area.GetBottom()) / 2;
		break;
	case CFigure::BOTTOMRIGHT:
		handlePoint->X = m_Area.GetRight();
		handlePoint->Y = m_Area.GetBottom();
		break;
	case CFigure::BOTTOM:
		handlePoint->X = (m_Area.GetLeft() + m_Area.GetRight()) / 2;
		handlePoint->Y = m_Area.GetBottom();
		break;
	case CFigure::BOTTOMLEFT:
		handlePoint->X = m_Area.GetLeft();
		handlePoint->Y = m_Area.GetBottom();
		break;
	case CFigure::LEFT:
		handlePoint->X = m_Area.GetLeft();
		handlePoint->Y = (m_Area.GetTop() + m_Area.GetBottom()) / 2;
		break;
	default:
		handlePoint = NULL;
		return TRUE;
	}

	return FALSE;
}

// 핸들의 영역
// 핸들의 영역을 얻음
// - IN 매개변수
//		PointF handlePoint: 영역을 얻고자하는 핸들의 좌표
// - 반환 값 (RectF)
//		핸들의 영역
RectF CFigure::getHandleRect(IN PointF handlePoint)
{
	RectF handleRect;

	handleRect.X = handlePoint.X - HANDLESIZE / 2;
	handleRect.Y = handlePoint.Y - HANDLESIZE / 2;
	handleRect.Width = HANDLESIZE;
	handleRect.Height = HANDLESIZE;

	return handleRect;
}

// 핸들의 영역
// 핸들의 영역을 얻음
// - IN 매개변수
//		Position handle: 영역을 얻고자하는 핸들
// - OUT 매개변수
//		PointF* handlePoint:
//			주소 값: 매개변수의 Position이 핸들인 경우 핸들의 영역
//			NULL: 매개변수의 Position이 핸들이 아닐 경우
// - 반환 값 (BOOL)
//		TRUE: 매개변수의 Position이 핸들이 아닐 경우
//		FALSE: 매개변수의 Position이 핸들인 경우
BOOL CFigure::getHandleRect(IN Position handle, OUT RectF* handleRect)
{
	PointF handlePoint;

	if (getHandlePoint(handle, &handlePoint)) {
		handleRect = NULL;
		return TRUE;
	}

	*handleRect = getHandleRect(handlePoint);

	return FALSE;
}

// 정반대편 핸들
// 정반대편 핸들을 얻음
// - IN 매개변수
//		Position handle: 정반대편 핸들을 얻고자하는 핸들
// - 반환 값 (Position)
//		정반대편 핸들
CFigure::Position CFigure::getOppositeHandle(IN Position handle){

	switch (handle)
	{
	case CFigure::TOPLEFT:
		return CFigure::BOTTOMRIGHT;
	case CFigure::TOP:
		return CFigure::BOTTOM;
	case CFigure::TOPRIGHT:
		return CFigure::BOTTOMLEFT;
	case CFigure::RIGHT:
		return CFigure::LEFT;
	case CFigure::BOTTOMRIGHT:
		return CFigure::TOPLEFT;
	case CFigure::BOTTOM:
		return CFigure::TOP;
	case CFigure::BOTTOMLEFT:
		return CFigure::TOPRIGHT;
	case CFigure::LEFT:
		return CFigure::RIGHT;
	case CFigure::START:
		return CFigure::END;
	case CFigure::END:
		return CFigure::START;
	default:
		return handle;
	}
}


/** 개체 영역 관리 **/
// 개체 영역 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
void CFigure::drawArea(IN Graphics& graphics)
{
	Pen pen(Color::Gray);
	pen.SetDashStyle(DashStyleDot);
	graphics.DrawRectangle(&pen, m_Area);

	drawHandles(graphics);
}

// 개체 핸들 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
//		PointF handlePoint: 그리고자하는 핸들 좌표
// - 반환 값 (BOOL)
//		TRUE: 매개변수의 Position이 핸들이 아닐 경우
//		FALSE: 매개변수의 Position이 핸들인 경우
BOOL CFigure::drawHandle(IN Graphics& graphics, IN PointF handlePoint)
{
	RectF handleRect = getHandleRect(handlePoint);

	// 핸들을 그림
	SolidBrush handleBrush(Color::White);
	graphics.FillRectangle(&handleBrush, handleRect);

	Pen handlePen(Color::Gray);
	graphics.DrawRectangle(&handlePen, handleRect);

	return FALSE;
}

// 개체 핸들 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
//		Position handle: 그리고자하는 핸들
// - 반환 값 (BOOL)
//		TRUE: 매개변수의 Position이 핸들이 아닐 경우
//		FALSE: 매개변수의 Position이 핸들인 경우
BOOL CFigure::drawHandle(IN Graphics& graphics, IN Position handle)
{
	PointF handlePoint;
	
	// 핸들 좌표를 얻음
	if (getHandlePoint(handle, &handlePoint)) {
		return TRUE;
	}

	// 핸들을 그림
	drawHandle(graphics, handlePoint);

	return FALSE;
}

// 개체 핸들 전체 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
//		PointF* handlePoints: 핸들의 좌표 배열
//		count: 배열의 크기
void CFigure::drawHandles(IN Graphics& graphics, IN PointF* handlePoints, IN INT count)
{
	CArray<RectF, RectF&> handleRects;

	for (int i = 0; i < count; i++) {
		handleRects.Add(getHandleRect(handlePoints[i]));
	}

	// 전체 핸들을 그림
	SolidBrush handleBrush(Color::White);
	graphics.FillRectangles(&handleBrush, handleRects.GetData(), count);

	Pen handlePen(Color::Gray);
	graphics.DrawRectangles(&handlePen, handleRects.GetData(), count);
}

// 개체 핸들 전체 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
void CFigure::drawHandles(IN Graphics& graphics)
{
	RectF handleRects[8];
	const INT handleRectsSize = 8;

	// 8개 전체 핸들의 영역을 얻음
	for (int handleIndex = TOPLEFT; handleIndex <= LEFT; handleIndex++) {
		getHandleRect((Position)handleIndex, &handleRects[handleIndex - 8]);
	}

	// 전체 핸들을 그림
	SolidBrush handleBrush(Color::White);
	graphics.FillRectangles(&handleBrush, handleRects, handleRectsSize);

	Pen handlePen(Color::Gray);
	graphics.DrawRectangles(&handlePen, handleRects, handleRectsSize);
}


// 순수 가상함수로 바꿀 거라 지울 함수 구현들
BOOL CFigure::create(void* param1, ...){return TRUE;/* 임시 반환 값*/}
void CFigure::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/){}
void CFigure::resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/){}

void CFigure::destroy(){}
CFigure::Position CFigure::pointInFigure(IN PointF point){ return OUTSIDE; /* 임시 반환값 */ }
void CFigure::draw(IN Graphics& graphics){}
RectF CFigure::creating(IN Graphics& graphics, void* param1, ...){ return NULLRectF; /* 임시 반환값 */ }
RectF CFigure::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/){ return NULLRectF; /* 임시 반환값 */ }
RectF CFigure::resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/){ return NULLRectF; /* 임시 반환값 */ }
BOOL CFigure::setOutlineColor(IN const Color& outlineColor){ return TRUE; /* 임시 반환값 */ }
BOOL CFigure::setOutlineWidth(IN const REAL outlineWidth){ return TRUE; /* 임시 반환값 */ }
BOOL CFigure::setOutlinePattern(IN const DashStyle outlinePattern){ return TRUE; /* 임시 반환값 */ }
BOOL CFigure::setFillColor(IN const Color& fillColor){ return TRUE; /* 임시 반환값 */ }
BOOL CFigure::setFillSubcolor(IN const Color& fillSubcolor){ return TRUE; /* 임시 반환값 */ }
BOOL CFigure::setFillPattern(IN const HatchStyle fillPattern){ return TRUE; /* 임시 반환값 */ }
RectF CFigure::resetArea(){ return m_Area; /* 임시 반환값 */ }