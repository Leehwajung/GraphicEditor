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
	//���߿� ��� ��ǥ�� ����� ����
	this->m_StartingPoint = startingPoint;
	m_PointsList.AddHead(PointF(0,0));
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

}

/* ���� �׸��� */
void CLine::creating(UINT nFlags, PointF point) {

}

/* �̵� �׸��� */
void CLine::moving(UINT nFlags, PointF point) {

}

/* ũ�� ���� �׸��� */
void CLine::resizing(UINT nFlags, PointF point) {

}

/* �� �߰� */
void CLine::addPoint(PointF point) {

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
