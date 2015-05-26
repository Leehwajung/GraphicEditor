// Rectangle.cpp : CRectangle 클래스의 구현
// CRectangle : 직사각형 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Rectangle.h"


// CRectangle

CRectangle::CRectangle(CClientDC* lpClientDC)
	: CShape(lpClientDC)
	, m_Rect(*new defaultRectF)
{
}

CRectangle::CRectangle(Graphics* lpGraphics)
	: CShape(lpGraphics)
	, m_Rect(*new defaultRectF)
{
}

CRectangle::CRectangle(CClientDC* lpClientDC, RectF& rect)
	: CShape(lpClientDC)
	, m_Rect(*rect.Clone())
{
}

CRectangle::CRectangle(CClientDC* lpClientDC, RectF& rect, Pen* pen, SolidBrush* brush)
	: CShape(lpClientDC, pen, brush)
	, m_Rect(*rect.Clone())
{
	//m_Pen = pen->Clone();
	//m_Brush = (SolidBrush*) brush->Clone();
}

CRectangle::~CRectangle()
{
	if (&m_Rect) {
		m_Rect.~RectF();
	}
}


// CRectangle 멤버 함수

/* 개체 생성 */
void CRectangle::create(PointF StartingPoint) {
	this->m_StartingPoint = StartingPoint;
}

/* 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지) */
CFigure::operationModeFlags CRectangle::cursorPosition(PointF point) {
	return None;
}

/* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
CFigure::operationModeFlags CRectangle::cursorPosition(RectF rect) {
	return None;
}

/* OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단) */
void CRectangle::mouseMoveOperation(UINT nFlags, PointF point) {

}

/* 생성 그리기 */
void CRectangle::creating(UINT nFlags, PointF point) {

}

/* 이동 그리기 */
void CRectangle::moving(UINT nFlags, PointF point) {

}

/* 크기 변경 그리기 */
void CRectangle::resizing(UINT nFlags, PointF point) {

}

/* 생성 완료 */
void CRectangle::endCreate(PointF point) {
	m_Rect = *new RectF(0, 0, point.X - m_StartingPoint.X, point.Y - m_StartingPoint.Y);
}

/* 개체 이동 */
void CRectangle::move(PointF originPoint, PointF targetPoint) {
	// originPoint: ButtonDown
	// targetPoint: ButtonUp
	m_StartingPoint = m_StartingPoint + targetPoint - originPoint;
}

/* 개체 크기 변경 */
void CRectangle::resize(PointF Point, PointF* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {

	//if (!anchorPoint) {
	//	anchorPoint = &m_StartingPoint;
	//}

	if (!anchorPoint) {
		anchorPoint = &Point;
	}

}

/* 개체 그리기 */
void CRectangle::draw() {
	m_lpGraphics->DrawRectangle(m_Pen, m_Rect);
	m_lpGraphics->FillRectangle(m_Brush, m_Rect);
}

/* 개체 선택선 그리기 */
void CRectangle::drawSelect() {

}

/* 개체 삭제 */
void CRectangle::destroy() {

}

