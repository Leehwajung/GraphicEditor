// Rectangle.cpp : CRectangle Ŭ������ ����
// CRectangle : ���簢�� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Rectangle.h"


// CRectangle

CRectangle::CRectangle()
	: CShape()
	, m_Rect(defaultRectF)
{
}

CRectangle::CRectangle(RectF& rect)
	: CShape()
	, m_Rect(rect)
{
}

CRectangle::CRectangle(RectF& rect, Pen* pen, SolidBrush* brush)
	: m_Rect(rect)
{
	m_Pen = pen->Clone();
	m_Brush = (SolidBrush*) brush->Clone();
}

CRectangle::~CRectangle()
{
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

/* �� �߰� */
void CRectangle::addPoint(PointF point) {

}

/* ��ü �̵� */
void CRectangle::move(PointF originPoint, PointF targetPoint) {

}

/* ��ü ũ�� ���� */
void CRectangle::resize(PointF Point, PointF* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {

	//if (!anchorPoint) {
	//	anchorPoint = &m_StartingPoint;
	//}
}

/* ������ ������ ��ü �Ӽ� ���� */
void CRectangle::setProperties(CFigureProperties properties) {

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

