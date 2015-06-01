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

CRectangle::CRectangle(IN CClientDC* lpClientDC)
	: CShape(lpClientDC)
{
}

CRectangle::CRectangle(IN Graphics* lpGraphics)
	: CShape(lpGraphics)
{
}

CRectangle::CRectangle(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush)
	: CShape(lpClientDC, pen, brush)
{
}

CRectangle::CRectangle(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush)
	: CShape(lpGraphics, pen, brush)
{
}

CRectangle::CRectangle(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush, IN RectF rect)
	: CShape(lpClientDC, pen, brush)
	, m_Rect(rect)
{
}

CRectangle::CRectangle(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush, IN RectF rect)
	: CShape(lpGraphics, pen, brush)
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
	return TRUE;	 // 임시 반환 값
}

// 생성
// 시작 좌표와 끝 좌표를 기준으로 사각형을 생성함
// - IN 매개변수
//		void* param1, ...: PointF*(startingPoint), PointF*(endingPoint), CreateFlag* 순으로 입력
// - 반환 값 (BOOL)
//		TRUE: 생성 실패
//		FALSE: 생성 성공
BOOL CRectangle::create(void* param1, ...)
{
	va_list vaList;
	va_start(vaList, param1);

	SizeF rectSize;
	rectSize.Width = startingPoint.X > endingPoint.X ? startingPoint.X - endingPoint.X : endingPoint.X - startingPoint.X;
	rectSize.Height = startingPoint.Y > endingPoint.Y ? startingPoint.Y - endingPoint.Y : endingPoint.Y - startingPoint.Y;
	
	if (startingPoint.X > endingPoint.X) {
		startingPoint.X = endingPoint.X;
	}
	
	if (startingPoint.Y > endingPoint.Y) {
		startingPoint.Y = endingPoint.Y;
	}
	
	m_Rect = *new RectF(startingPoint, rectSize);
	resetArea();

	return TRUE;	 // 임시 반환 값
}

// 이동
// 시작 좌표부터 끝 좌표까지의 Offset을 기준으로 사각형을 이동
// - IN 매개변수
//		PointF originPoint: 이동의 시작 좌표
//		PointF targetPoint: 이동의 끝 좌표
//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
void CRectangle::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{

}

// 크기 변경
// 선택한 핸들의 좌표를 변경하여 크기 변경 (기준 좌표를 설정하면 이를 기준으로 각 좌표를 변경하여 크기 변경)
// - IN 매개변수
//		Position selcetedHandle: 사각형의 선택된 핸들
//		PointF targetPoint: 선택된 핸들의 변경할 좌표
//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selcetedHandle을 통해 얻은 Default 기준 좌표 )
void CRectangle::resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{

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
	return OUTSIDE;	// 임시 반환 값
}


/* 그리기 */
// 도형 그리기
void CRectangle::draw()
{

}

// 생성 그리기
// 생성 시에 보여줄 그리기
// - IN 매개변수
//		PointF startingPoint: 생성 시작 좌표
//		PointF targetPoint: 생성 시 선택 중인 좌표
//		CreateFlag createFlag = FREECREATE: 생성 설정 플래그
void CRectangle::creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/)
{

}

// 생성 그리기
// 생성 시에 보여줄 그리기
// - IN 매개변수
//		...: PointF(startingPoint), PointF(endingPoint), CreateFlag 순으로 입력
void CRectangle::creating(void* param1, ...)
{

}

// 이동 그리기
// 이동 중에 보여줄 그리기
// - IN 매개변수
//		PointF originPoint: 이동의 시작 좌표
//		PointF targetPoint: 이동 중인 좌표
//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
void CRectangle::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{

}

// 크기 변경 그리기
// 크기 변경 중에 보여줄 그리기
// - IN 매개변수
//		Position selcetedHandle: 개체의 선택된 핸들
//		PointF targetPoint: 선택된 핸들을 이동하고 있는 좌표
//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selcetedHandle을 통해 얻은 Default 기준 좌표 )
void CRectangle::resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{

}


/* 개체 영역 관리 */
// 개체 영역 갱신
void CRectangle::resetArea()
{

}





//CRectangle::CRectangle()
//	//: m_Rect(*new defaultRectF)
//{
//}
//
//CRectangle::CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/)
//	: CShape(lpClientDC/*, startingPoint*/)
//	//, m_Rect(*new defaultRectF)
//{
//}
//
//CRectangle::CRectangle(Graphics* lpGraphics/*, PointF startingPoint*/)
//	: CShape(lpGraphics/*, startingPoint*/)
//	//, m_Rect(*new defaultRectF)
//{
//}
//
////CRectangle::CRectangle(CClientDC* lpClientDC, RectF& rect)
////	: CShape(lpClientDC)
////	//, m_Rect(*rect.Clone())
////{
////}
//
//CRectangle::CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/, /*RectF& rect, */Pen* pen, SolidBrush* brush)
//	: CShape(lpClientDC/*, startingPoint*/, pen, brush)
//	//, m_Rect(*rect.Clone())
//{
//	//m_OutlinePen = pen->Clone();
//	//m_FillBrush = (SolidBrush*) brush->Clone();
//}
//
//CRectangle::~CRectangle()
//{
//	if (!&m_Rect) {
//		m_Rect.~RectF();
//	}
//}
//
//
//// CRectangle 멤버 함수
//
///* 개체 생성 */
//void CRectangle::create(PointF StartingPoint) {
//	this->m_StartingPoint = StartingPoint;
//}
//
///* 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지) */
//CFigure::operationModeFlags CRectangle::cursorPosition(PointF point) {
//	return None;
//}
//
///* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
//CFigure::operationModeFlags CRectangle::cursorPosition(RectF rect) {
//	return None;
//}
//
//
///* 생성 완료 */
//void CRectangle::endCreate(PointF point) {
//
//	SizeF rectSize;
//	rectSize.Width = m_StartingPoint.X > point.X ? m_StartingPoint.X - point.X : point.X - m_StartingPoint.X;
//	rectSize.Height = m_StartingPoint.Y > point.Y ? m_StartingPoint.Y - point.Y : point.Y - m_StartingPoint.Y;
//
//	if (m_StartingPoint.X > point.X) {
//		m_StartingPoint.X = point.X;
//	}
//
//	if (m_StartingPoint.Y > point.Y) {
//		m_StartingPoint.Y = point.Y;
//	}
//
//	m_Rect = *new RectF(m_StartingPoint, rectSize);
//	resetArea();
//}
//
///* 개체 이동 */
//void CRectangle::move(PointF originPoint, PointF targetPoint) {
//	// originPoint: ButtonDown
//	// targetPoint: ButtonUp
//
//	PointF offset = targetPoint - originPoint;
//	m_StartingPoint = m_StartingPoint + offset;
//	m_Rect.Offset(offset);
//	resetArea();
//}
//
///* 개체 크기 변경 */
//void CRectangle::resize(PointF Point, PointF* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {
//
//	//if (!anchorPoint) {
//	//	anchorPoint = &m_StartingPoint;
//	//}
//
//	if (!anchorPoint) {
//		anchorPoint = &Point;
//	}
//
//	resetArea();
//}
//
///* 개체 그리기 */
//void CRectangle::draw() {
//	m_lpGraphics->FillRectangle(m_FillBrush, m_Rect);
//	m_lpGraphics->DrawRectangle(m_OutlinePen, m_Rect);
//}

