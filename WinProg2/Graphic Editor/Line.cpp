// Line.cpp : CLine Ŭ������ ����
// CLine : ���� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Line.h"

CLine::CLine()
	:CStrap()
{
	//m_LinePen
}


CLine::~CLine()
{

}


// LButtonDown
/* �� ����*/
void CLine::create(PointF startingPoint)
{
	//���߿� ��� ��ǥ�� ����� ����
	this->m_StartingPoint = startingPoint;
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ��� */
CFigure::operationModeFlags CLine::cursorPosition(PointF point) {
	return None;

	}
		
	// �� ��: �ƹ� ��嵵 �ƴ�
	else None;
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
CFigure::operationModeFlags CLine::cursorPosition(RectF rect) {
	return None;
}


// OnMouseMove
/* OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�) */
void CLine::mouseMoveOperation(UINT nFlags, PointF point) {

	operationModeFlags mode = cursorPosition(point);

	switch (mode){
	case operationModeFlags::Create:
		creating(nFlags, point);

	case operationModeFlags::Move:
		moving(nFlags, point);

	case operationModeFlags::Resize:
		resizing(nFlags, point);
	}
}

/* ���� �׸��� */
void CLine::creating(UINT nFlags, PointF point) {
	m_lpGraphics->DrawLine(&m_Pen, m_StartingPoint, point);

}

/* �̵� �׸��� */
void CLine::moving(UINT nFlags, PointF point) {

	/* ���� �̵� �� �� �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = PointF(point  - m_StartingPoint);

	/* ���� ��ǥ���� ��� ��ǥ�� ������ ���� �̵� ��� ��ǥ�� �ȴ�. */
	m_lpGraphics->DrawLine(&m_Pen, m_StartingPoint + RelativePoint, m_EndPoint + RelativePoint);
}

/* ũ�� ���� �׸��� */
void CLine::resizing(UINT nFlags, PointF point) {

}


// LButtonUp / LButtonDlk
/* �� �߰� */
void CLine::addPoint(PointF point) {
	m_EndPoint = PointF((point.X - m_StartingPoint.X), (point.Y - m_StartingPoint.Y));
	m_PointsList.AddTail(m_EndPoint);
}

/* ��ü �̵� */
void CLine::move(PointF Target) {
}

/* �� ũ��(����) ���� */
void CLine::resize(PointF point, PointF* anchorPoint, int resizeFlags) {

}

/* ������ ������ ��ü �Ӽ� ���� */
void CLine::setProperties(CFigureProperties properties) {

}

// OnDraw / OnPaint
/* �� �׸��� */
void CLine::draw() {

}


// Menu Item
/* �� ���� */
void CLine::destroy() {

}


// �Ӽ��� ���� �κ��� Property class�� �̿��ϱ�� ����
/* �� �� ���� */
void CLine::setLineColor(Color lineColor) {
	m_LineColor = lineColor;
}

/* �� �β� ���� */
void CLine::setLineWidth(int lineWidth) {
	 m_LineWidth = lineWidth;
}

/* �� ���� ���� */
void CLine::setLinePattern(int linePattern) {
	m_LinePattern = linePattern;
}
