#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{

}


CLine::~CLine()
{

}

/* �� ����*/
void CLine::Create(CPoint startingPoint)
{
	//���߿� ��� ��ǥ�� ����� ����
	this->m_StartingPoint = startingPoint;
	m_PointsList.AddHead(CPoint(0,0));
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ��� */
CFigure::operationModeFlags CLine::cursorPosition(CPoint point) {
	return None;
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
CFigure::operationModeFlags CLine::cursorPosition(CRect rect) {
	return None;
}

/* OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�) */
void CLine::mouseMoveOperation(UINT nFlags, CPoint point) {

}

/* ���� �׸��� */
void CLine::creating(UINT nFlags, CPoint point) {

}

/* �̵� �׸��� */
void CLine::moving(UINT nFlags, CPoint point) {

}

/* ũ�� ���� �׸��� */
void CLine::resizing(UINT nFlags, CPoint point) {

}

/* �� �߰� */
void CLine::addPoint(CPoint point) {

}

/* ��ü �̵� */
void CLine::move(CPoint Target) {

}

/* �� ũ��(����) ���� */
void CLine::resize(CPoint Point, int resizeFlags) {

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


CList<CPoint, CPoint&>& CLine::GetPointsList(){
	return m_PointsList;
}
