// Figure.cpp : CFigure Ŭ������ ����
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Figure.h"

using namespace Gdiplus;

// CFigure

CFigure::CFigure()
{
}

CFigure::CFigure(CDC* dc)
{
}

CFigure::~CFigure()
{
}


// CFigure ��� �Լ�

/* ��ü ���� */
void CFigure::create(CPoint StartingPoint) {
	this->m_startingPoint = StartingPoint;
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���) */
CFigure::operationModeFlags CFigure::cursorPosition(CPoint point) {
	return None;
}

/* OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�) */
void CFigure::mouseMoveOperation(UINT nFlags, CPoint point) {

}

/* ���� �׸��� */
void CFigure::creating(UINT nFlags, CPoint point) {

}

/* �̵� �׸��� */
void CFigure::moving(UINT nFlags, CPoint point) {

}

/* ũ�� ���� �׸��� */
void CFigure::resizing(UINT nFlags, CPoint point) {

}

/* �� �߰� */
void CFigure::addPoint(CPoint point) {

}

/* ��ü �̵� */
void CFigure::move(CPoint Target) {

}

/* ��ü ũ�� ���� */
void CFigure::resize(CPoint Point, int resizeFlags) {

}

/* ��ü �׸��� */
void CFigure::draw() {

}

/* ��ü ���� */
void CFigure::destroy() {

}

/* ������ �� ���� */
void CFigure::setLineColor(Color LineColor) {

}

/* ������ �β� ���� */
void CFigure::setLineWidth(int LineWidth) {

}

/* ������ ���� ���� */
void CFigure::setLinePattern(int LinePattern) {

}

/* ĥ�ϱ� �� ���� */
void CFigure::setFillColor(Color FillColor) {

}

/* ĥ�ϱ� ���� ���� */
void CFigure::setFillPattern(int FillPattern) {

}


/* Getter / Setter */

CDC* CFigure::getDC() {
	return this->m_lpdc;
}

void CFigure::setDC(CDC* dc) {
	this->m_lpdc = dc;
}

CPoint& CFigure::getStartingPoint() {
	return this->m_startingPoint;
}

void CFigure::setStartingPoint(CPoint StartingPoint) {
	this->m_startingPoint = StartingPoint;
}

CFigure::operationModeFlags CFigure::getOperationMode() {
	return this->m_OperationMode;
}

void CFigure::setOperationMode(operationModeFlags OperationMode) {
	this->m_OperationMode = OperationMode;
}