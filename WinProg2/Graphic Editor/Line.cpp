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
		// ������ ���� ���� �� ���� ����� ���⶧���� ���� ��ǥ�� ����ϱ�� ��.
		this->m_StartingPoint = startingPoint;
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ��� */
CFigure::operationModeFlags CLine::cursorPosition(PointF point) {

	// 1. ���� ��ǥ��  ���� StartingPoint�� EndPoint�̸� "Resize���" �̴�. 
	if (point.Equals(m_StartingPoint) == TRUE || point.Equals(m_EndPoint) == TRUE){
		return Resize;
	}

	// 2. ���� ��ǥ�� ���� �ִ� ������ ���� �� ������ ���� ����� ���� ���� "Move���" �̴�.
	else if (m_Rect.GetLeft() <= point.X && point.X <= m_Rect.GetRight() || m_Rect.GetRight() <= point.X && point.X <= m_Rect.GetLeft()){
		if (m_Rect.GetTop() <= point.Y && point.Y <= m_Rect.GetBottom()|| m_Rect.GetBottom()<= point.Y && point.Y <= m_Rect.GetTop()){

			// ���� ���� ��ǥ�� StartingPoint���� ���⸦ ���� ���̴�.
			int tmp_gradient = (m_StartingPoint.Y - point.Y) / (m_StartingPoint.X - point.X);

			if (tmp_gradient == m_Gradient)
				return Move;

		}
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

	switch (m_OperationMode){
	case operationModeFlags::Create:
		creating(nFlags, point);
		break;

	case operationModeFlags::Move:
		moving(nFlags, point);
		break;

	case operationModeFlags::Resize:
		resizing(nFlags, point);
		break;
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


// LButtonUp
/* �� �߰� */
void CLine::addPoint(PointF point) {
	m_EndPoint = point;
	m_Gradient = (m_StartingPoint.Y - m_EndPoint.Y) / (m_StartingPoint.X - m_EndPoint.X);

	m_Rect.X = m_StartingPoint.X;
	m_Rect.Y = m_StartingPoint.Y;
	m_Rect.Width = abs(m_StartingPoint.X - m_EndPoint.X);
	m_Rect.Height = abs(m_StartingPoint.Y - m_EndPoint.Y);
}

/* ��ü �̵� */
void CLine::move(PointF Target) {

	/* �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = PointF(Target - m_StartingPoint);

	m_StartingPoint = m_StartingPoint + RelativePoint;
	m_EndPoint = m_EndPoint + RelativePoint;

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

