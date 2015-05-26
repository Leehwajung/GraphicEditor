// Rectangle.cpp : CRectangle Ŭ������ ����
// CRectangle : ���簢�� ��ü�� �����ϴ� Ŭ����
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


// CRectangle ��� �Լ�

/* ��ü ���� */
void CRectangle::create(PointF StartingPoint) {
	this->m_StartingPoint = StartingPoint;
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���) */
CFigure::operationModeFlags CRectangle::cursorPosition(PointF point) {
	return None;
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
CFigure::operationModeFlags CRectangle::cursorPosition(RectF rect) {
	return None;
}

/* OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�) */
void CRectangle::mouseMoveOperation(UINT nFlags, PointF point) {

}

/* ���� �׸��� */
void CRectangle::creating(UINT nFlags, PointF point) {

}

/* �̵� �׸��� */
void CRectangle::moving(UINT nFlags, PointF point) {

}

/* ũ�� ���� �׸��� */
void CRectangle::resizing(UINT nFlags, PointF point) {

}

/* ���� �Ϸ� */
void CRectangle::endCreate(PointF point) {
	m_Rect = *new RectF(0, 0, point.X - m_StartingPoint.X, point.Y - m_StartingPoint.Y);
}

/* ��ü �̵� */
void CRectangle::move(PointF originPoint, PointF targetPoint) {
	// originPoint: ButtonDown
	// targetPoint: ButtonUp
	m_StartingPoint = m_StartingPoint + targetPoint - originPoint;
}

/* ��ü ũ�� ���� */
void CRectangle::resize(PointF Point, PointF* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {

	//if (!anchorPoint) {
	//	anchorPoint = &m_StartingPoint;
	//}

	if (!anchorPoint) {
		anchorPoint = &Point;
	}

}

/* ��ü �׸��� */
void CRectangle::draw() {
	m_lpGraphics->DrawRectangle(m_Pen, m_Rect);
	m_lpGraphics->FillRectangle(m_Brush, m_Rect);
}

/* ��ü ���ü� �׸��� */
void CRectangle::drawSelect() {

}

/* ��ü ���� */
void CRectangle::destroy() {

}

