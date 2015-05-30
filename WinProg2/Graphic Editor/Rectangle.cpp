// Rectangle.cpp : CRectangle Ŭ������ ����
// CRectangle : ���簢�� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Rectangle.h"


// CRectangle

IMPLEMENT_SERIAL(CRectangle, CShape, 1)

void CRectangle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


CRectangle::CRectangle()
	//: m_Rect(*new defaultRectF)
{
}

CRectangle::CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/)
	: CShape(lpClientDC/*, startingPoint*/)
	//, m_Rect(*new defaultRectF)
{
}

CRectangle::CRectangle(Graphics* lpGraphics/*, PointF startingPoint*/)
	: CShape(lpGraphics/*, startingPoint*/)
	//, m_Rect(*new defaultRectF)
{
}

//CRectangle::CRectangle(CClientDC* lpClientDC, RectF& rect)
//	: CShape(lpClientDC)
//	//, m_Rect(*rect.Clone())
//{
//}

CRectangle::CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/, /*RectF& rect, */Pen* pen, SolidBrush* brush)
	: CShape(lpClientDC/*, startingPoint*/, pen, brush)
	//, m_Rect(*rect.Clone())
{
	//m_Pen = pen->Clone();
	//m_Brush = (SolidBrush*) brush->Clone();
}

CRectangle::~CRectangle()
{
	if (!&m_Rect) {
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

	SizeF rectSize;
	rectSize.Width = m_StartingPoint.X > point.X ? m_StartingPoint.X - point.X : point.X - m_StartingPoint.X;
	rectSize.Height = m_StartingPoint.Y > point.Y ? m_StartingPoint.Y - point.Y : point.Y - m_StartingPoint.Y;

	if (m_StartingPoint.X > point.X) {
		m_StartingPoint.X = point.X;
	}

	if (m_StartingPoint.Y > point.Y) {
		m_StartingPoint.Y = point.Y;
	}

	m_Rect = *new RectF(m_StartingPoint, rectSize);
	resetArea();
}

/* ��ü �̵� */
void CRectangle::move(PointF originPoint, PointF targetPoint) {
	// originPoint: ButtonDown
	// targetPoint: ButtonUp

	PointF offset = targetPoint - originPoint;
	m_StartingPoint = m_StartingPoint + offset;
	m_Rect.Offset(offset);
	resetArea();
}

/* ��ü ũ�� ���� */
void CRectangle::resize(PointF Point, PointF* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {

	//if (!anchorPoint) {
	//	anchorPoint = &m_StartingPoint;
	//}

	if (!anchorPoint) {
		anchorPoint = &Point;
	}

	resetArea();
}

/* ��ü �׸��� */
void CRectangle::draw() {
	m_lpGraphics->FillRectangle(m_Brush, m_Rect);
	m_lpGraphics->DrawRectangle(m_Pen, m_Rect);
}

/* ��ü ���ü� �׸��� */
void CRectangle::drawSelect() {

}

/* ��ü ���� */
void CRectangle::destroy() {

}



