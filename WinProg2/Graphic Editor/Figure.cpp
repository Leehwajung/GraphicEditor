// Figure.cpp : CFigure 클래스의 구현
// CFigure : 클라이언트 영역에서 볼 수 있는 개체를 정의하는 클래스 (모든 개체의 조상 클래스)
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Figure.h"

using namespace Gdiplus;

// CFigure

IMPLEMENT_SERIAL(CFigure, CObject, 1)

CFigure::CFigure()
	: m_lpGraphics(NULL)
	, m_GraphicsDynamicAllocationFlag(FALSE)
{
}

CFigure::CFigure(CClientDC* lpClientDC)
	: m_lpGraphics(new Graphics(*lpClientDC))
	, m_GraphicsDynamicAllocationFlag(TRUE)
{
}

CFigure::CFigure(Graphics* lpGraphics)
	: m_lpGraphics(lpGraphics)
	, m_GraphicsDynamicAllocationFlag(FALSE)
{
}

CFigure::~CFigure()
{
	if (m_GraphicsDynamicAllocationFlag && m_lpGraphics) {
		m_lpGraphics->~Graphics();
	}
}


// CFigure 멤버 함수

/* 직렬화 */
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


/* 연산 */
// 생성
// 매개변수의 값을 기준으로 새로운 개체를 정의
// - IN 매개변수
//		...: 각 파생 클래스에서 필요한대로 정의
//		[CreateFlag createFlag = FREECREATE]: 생성 설정 플래그, 필요하면 추가하기
// - 반환 값 (BOOL)
//		TRUE: 생성 실패
//		FALSE: 생성 성공
BOOL CFigure::create(...)
{
	resetArea();
	return TRUE;	 // 임시 반환 값
}

// 이동
// 시작 좌표부터 끝 좌표까지의 Offset을 기준으로 개체를 이동
// - IN 매개변수
//		PointF originPoint: 이동의 시작 좌표
//		PointF targetPoint: 이동의 끝 좌표
//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
void CFigure::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	resetArea();
}

// 크기 변경
// 선택한 핸들의 좌표를 변경하여 크기 변경 (기준 좌표를 설정하면 이를 기준으로 각 좌표를 변경하여 크기 변경)
// - IN 매개변수
//		Position selcetedHandle: 개체의 선택된 핸들
//		PointF targetPoint: 선택된 핸들의 변경할 좌표
//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selcetedHandle을 통해 얻은 Default 기준 좌표 )
void CFigure::resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	resetArea();
}

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


/* Graphics 관리 */
// ClientDC 획득
CClientDC* CFigure::getClientDC()
{
	return (CClientDC*) CClientDC::FromHandle(m_lpGraphics->GetHDC());
}

// Graphics 획득
Graphics* CFigure::getGraphics()
{
	return m_lpGraphics;
}

// ClientDC 설정
void CFigure::setClientDC(CClientDC* lpClientDC)
{
	if (m_GraphicsDynamicAllocationFlag && m_lpGraphics) {
		m_lpGraphics->~Graphics();
	}

	m_lpGraphics = new Graphics(*lpClientDC);
	m_GraphicsDynamicAllocationFlag = TRUE;
}

// Graphics 설정
void CFigure::setGraphics(Graphics* lpGraphics)
{
	if (m_GraphicsDynamicAllocationFlag && m_lpGraphics) {
		m_lpGraphics->~Graphics();
	}

	m_lpGraphics = lpGraphics;
	m_GraphicsDynamicAllocationFlag = FALSE;
}


/* 개체 영역 관리 */
// 개체 영역 그리기
void CFigure::drawArea()
{


	drawHandles();
}


/* 핸들 관리 */
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

	handleRect->X = handlePoint.X - HANDLESIZE / 2;
	handleRect->Y = handlePoint.Y - HANDLESIZE / 2;
	handleRect->Width = HANDLESIZE;
	handleRect->Height = HANDLESIZE;

	return FALSE;
}

// 개체 핸들 그리기
// - IN 매개변수
//		Position handle: 그리고자하는 핸들
// - 반환 값 (BOOL)
//		TRUE: 매개변수의 Position이 핸들이 아닐 경우
//		FALSE: 매개변수의 Position이 핸들인 경우
BOOL CFigure::drawHandle(IN Position handle)
{
	RectF handleRect;
	
	// 핸들 영역을 얻음
	if (getHandleRect(handle, &handleRect)) {
		return TRUE;
	}

	// 핸들을 그림
	SolidBrush handleBrush(Color::White);
	m_lpGraphics->FillRectangle(&handleBrush, handleRect);

	Pen handlePen(Color::Gray);
	m_lpGraphics->DrawRectangle(&handlePen, handleRect);

	return FALSE;
}

// 개체 핸들 전체 그리기
void CFigure::drawHandles()
{
	RectF handleRects[8];
	const INT handleRectsSize = 8;

	// 8개 전체 핸들의 영역을 얻음
	for (int handleIndex = TOPLEFT; handleIndex <= LEFT; handleIndex++) {
		getHandleRect((Position)handleIndex, &handleRects[handleIndex - 8]);
	}

	// 전체 핸들을 그림
	SolidBrush handleBrush(Color::White);
	m_lpGraphics->FillRectangles(&handleBrush, handleRects, handleRectsSize);

	Pen handlePen(Color::Gray);
	m_lpGraphics->DrawRectangles(&handlePen, handleRects, handleRectsSize);
}


// 순수 가상함수로 바꿀 거라 지울 함수 구현들
void CFigure::destroy(){}
CFigure::Position CFigure::pointInFigure(IN PointF point){ return OUTSIDE; /* 임시 반환값 */}
void CFigure::draw(){}
void CFigure::creating(...){}
void CFigure::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/){}
void CFigure::resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/){}
BOOL CFigure::setOutlineColor(IN const Color& outlineColor){ return TRUE; /* 임시 반환값 */ }
BOOL CFigure::setOutlineWidth(IN const REAL outlineWidth){ return TRUE; /* 임시 반환값 */ }
BOOL CFigure::setOutlinePattern(IN const DashStyle outlinePattern){ return TRUE; /* 임시 반환값 */ }
BOOL CFigure::setFillColor(IN const Color& fillColor){ return TRUE; /* 임시 반환값 */ }
BOOL CFigure::setFillSubcolor(IN const Color& fillSubcolor){ return TRUE; /* 임시 반환값 */ }
BOOL CFigure::setFillPattern(IN const HatchStyle fillPattern){ return TRUE; /* 임시 반환값 */ }
void CFigure::resetArea(){}



// 구버젼

///* 개체 생성 */
//void CFigure::create(PointF StartingPoint) {
//	this->m_StartingPoint = StartingPoint;
//}
//
///* 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지) */
//CFigure::operationModeFlags CFigure::cursorPosition(PointF point) {
//	return None; 
//}
//
///* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
//CFigure::operationModeFlags CFigure::cursorPosition(RectF rect) {
//	return None;
//}
//
///* OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단) */
//void CFigure::mouseMoveOperation(UINT nFlags, PointF point) {
//
//}
//
///* 생성 그리기 */
//void CFigure::creating(UINT nFlags, PointF point) {
//
//}
//
///* 이동 그리기 */
//void CFigure::moving(UINT nFlags, PointF point) {
//
//}
//
///* 크기 변경 그리기 */
//void CFigure::resizing(UINT nFlags, PointF point) {
//
//}
//
///* 생성 완료 */
//void CFigure::endCreate(PointF point) {
//
//}
//
///* 개체 이동 */
//void CFigure::move(PointF originPoint, PointF targetPoint) {
//
//}
//
///* 개체 크기 변경 */
//void CFigure::resize(PointF Point, PointF* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {
//
//	//if (!anchorPoint) {
//	//	anchorPoint = &m_StartingPoint;
//	//}
//}
//
///* 개체 그리기 */
//void CFigure::draw() {
//	PROPORTIONAL == MK_SHIFT;
//}
//
///* 개체 선택선 그리기 */
//void CFigure::drawSelect() {
//	
//}
//
///* 개체 삭제 */
//void CFigure::destroy() {
//
//}
//
///* 윤곽선 색 설정 */
//void CFigure::setLineColor(const Color& LineColor) {
//
//}
//
///* 윤곽선 두께 설정 */
//void CFigure::setLineWidth(const REAL& LineWidth) {
//
//}
//
///* 윤곽선 패턴 설정 */
//void CFigure::setLinePattern(const DashStyle& LinePattern) {
//
//}
//
///* 주 채우기 색 설정 */
//void CFigure::setFillColor(const Color& FillColor) {
//	m_lpGraphics->FillEllipse(&SolidBrush(Color(0,0,0)), Rect());
//}
//
///* 채우기 패턴 설정 */
//void CFigure::setFillPattern(const int FillPattern) {
//
//}
//
//
///* Getter / Setter */
//
//Graphics* CFigure::getGraphics() {
//	return this->m_lpGraphics;
//}
//
//void CFigure::setGraphics(Graphics* lpGraphics) {
//	this->m_lpGraphics = lpGraphics;
//}
//
//PointF& CFigure::getStartingPoint() {
//	return this->m_StartingPoint;
//}
//
//void CFigure::setStartingPoint(PointF& StartingPoint) {
//	this->m_StartingPoint = StartingPoint;	// 복사 생성자 불림
//}
//
//CFigure::operationModeFlags CFigure::getOperationMode() {
//	return this->m_OperationMode;
//}
//
//void CFigure::setOperationMode(operationModeFlags OperationMode) {
//	this->m_OperationMode = OperationMode;
//}
//
//void CFigure::resetArea() {
//
//}

