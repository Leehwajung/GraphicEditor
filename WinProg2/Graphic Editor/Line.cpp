// Line.cpp : CLine Ŭ������ ����
// CLine : ���� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Line.h"


CLine::CLine()
	:CStrap()
	, m_Pen(new defaultPen)
	, isStartingpoint(FALSE)
{
	//m_LinePen	
}

CLine::~CLine()
{
	if (m_Pen) {
		m_Pen->~Pen();
	}
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
		if (point.Equals(m_StartingPoint) == TRUE)
			isStartingpoint = TRUE;

		return Resize;
	}

	// 2. ���� ��ǥ�� ���� �ִ� ������ ���� �� ������ ���� ����� ���� ���� "Move���" �̴�.
	else if (m_Area.GetLeft() <= point.X && point.X <= m_Area.GetRight() || m_Area.GetRight() <= point.X && point.X <= m_Area.GetLeft()){
		if (m_Area.GetTop() <= point.Y && point.Y <= m_Area.GetBottom() || m_Area.GetBottom() <= point.Y && point.Y <= m_Area.GetTop()){

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

	m_OperationMode = cursorPosition(point);

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
	m_lpGraphics->DrawLine(m_Pen, m_StartingPoint, point);
}

/* �̵� �׸��� */
void CLine::moving(UINT nFlags, PointF point) {

	/* ���� �̵� �� �� �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = PointF(point  - m_StartingPoint);

	/* ���� ��ǥ���� ��� ��ǥ�� ������ ���� �̵� ��� ��ǥ�� �ȴ�. */
	m_lpGraphics->DrawLine(m_Pen, m_StartingPoint + RelativePoint, m_EndPoint + RelativePoint);
}

/* ũ�� ���� �׸��� */
void CLine::resizing(UINT nFlags, PointF point) {
	if (isStartingpoint == TRUE){
		m_lpGraphics->DrawLine(m_Pen, point, m_EndPoint);
	}
	else{
		m_lpGraphics->DrawLine(m_Pen, m_StartingPoint, point);
	}
}


// LButtonUp
/* �� �߰� */
void CLine::endCreate(PointF point) {
	m_EndPoint = point;
	m_Gradient = (m_StartingPoint.Y - m_EndPoint.Y) / (m_StartingPoint.X - m_EndPoint.X);

	m_Area.X = m_StartingPoint.X;
	m_Area.Y = m_StartingPoint.Y;
	m_Area.Width = abs(m_StartingPoint.X - m_EndPoint.X);
	m_Area.Height = abs(m_StartingPoint.Y - m_EndPoint.Y);
}

/* ��ü �̵� */
void CLine::move(PointF originPoint, PointF targetPoint) {

	/* �̵��� ��� ���� ���ϱ� ���� */
	//PointF RelativePoint = PointF(Target - m_StartingPoint);

	//m_StartingPoint = m_StartingPoint + RelativePoint;
	//m_EndPoint = m_EndPoint + RelativePoint;

}

/* �� ũ��(����) ���� */
void CLine::resize(PointF point, PointF* anchorPoint, int resizeFlags) {
	if (isStartingpoint == TRUE){
		m_StartingPoint = point;
		isStartingpoint = FALSE;
	}
	else{
		m_EndPoint = point;
	}

}

// OnDraw / OnPaint
/* �� �׸��� */
void CLine::draw() {
	m_lpGraphics->DrawLine(m_Pen,m_StartingPoint, m_EndPoint);
}


// Menu Item
/* �� ���� */
void CLine::destroy() {
	
	if (this) {
		this->~CLine();
	}
	//invalidate �ٸ� �͵��� �ϴ� ����
}

// �Ӽ��� ���� �κ��� Property class�� �̿��ϱ�� ����
/* �� �� ���� */
void CLine::setLineColor(const Color& LineColor) {
	m_LineColor = LineColor;
}

/* �� �β� ���� */
void CLine::setLineWidth(const REAL& LineWidth) {
	 m_LineWidth = LineWidth;
}

/* �� ���� ���� */
void CLine::setLinePattern(const DashStyle& LinePattern) {
	m_LinePattern = LinePattern;
}

