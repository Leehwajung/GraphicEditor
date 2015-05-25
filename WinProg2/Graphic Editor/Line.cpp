// Line.cpp : CLine Ŭ������ ����
// CLine : �� ��ü�� �����ϴ� Ŭ���� (CPolyLine / CPencil�� ��� Ŭ����)
// 

#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
	//m_LinePen
}


CLine::~CLine()
{

}

/* �� ����*/
void CLine::Create(PointF startingPoint)
{

	// �� �Ӽ� ���� �ӽ�. 
	m_Pen.SetColor(Color(255, 0, 0, 0));

	//���߿� ��� ��ǥ�� ����� ����
	this->m_StartingPoint = startingPoint;
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ��� */
CFigure::operationModeFlags CLine::cursorPosition(PointF point) {
	return None;
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
CFigure::operationModeFlags CLine::cursorPosition(CRect rect) {
	return None;
}

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

	/*CRgn rgn;
	rgn.CreateRectRgn(m_StartingPoint.X, m_StartingPoint.Y, point.X, point.Y);

	InvalidateRgn(NULL, rgn, TRUE);
*/
}

/* �̵� �׸��� */
void CLine::moving(UINT nFlags, PointF point) {
	PointF RelativePoint = PointF((point.X - m_StartingPoint.X), (point.Y - m_StartingPoint.Y));
	//m_lpGraphics->DrawLine(&m_Pen, m_PointsList[0]+ m_StartingPoint + RelativePoint, m_PointsList+ m_StartingPoint + RelativePoint);
}

/* ũ�� ���� �׸��� */
void CLine::resizing(UINT nFlags, PointF point) {

}

/* �� �߰� */
void CLine::addPoint(PointF point) {
	//m_PointsList.AddTail(point-m_StartingPoint);
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

/* �� �׸��� */
void CLine::draw() {

}

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


CList<PointF, PointF&>& CLine::GetPointsList(){
	return m_PointsList;
}
