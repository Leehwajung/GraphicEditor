// Figure.cpp : CFigure Ŭ������ ����
// CFigure : Ŭ���̾�Ʈ �������� �� �� �ִ� ��ü�� �����ϴ� Ŭ���� (��� ��ü�� ���� Ŭ����)
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Figure.h"

using namespace Gdiplus;

// CFigure

CFigure::CFigure()
{
}

CFigure::CFigure(Graphics* lpGraphics)
{
}

CFigure::~CFigure()
{
}


// CFigure ��� �Լ�

/* ��ü ���� */
void CFigure::create(PointF StartingPoint) {
	this->m_StartingPoint = StartingPoint;
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���) */
CFigure::operationModeFlags CFigure::cursorPosition(PointF point) {
	return None; 
}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
CFigure::operationModeFlags CFigure::cursorPosition(RectF rect) {
	return None;
}

/* OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�) */
void CFigure::mouseMoveOperation(UINT nFlags, PointF point) {

}

/* ���� �׸��� */
void CFigure::creating(UINT nFlags, PointF point) {

}

/* �̵� �׸��� */
void CFigure::moving(UINT nFlags, PointF point) {

}

/* ũ�� ���� �׸��� */
void CFigure::resizing(UINT nFlags, PointF point) {

}

/* �� �߰� */
void CFigure::addPoint(PointF point) {

}

/* ��ü �̵� */
void CFigure::move(PointF Target) {

}

/* ��ü ũ�� ���� */
void CFigure::resize(PointF Point, PointF* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {

	//if (!anchorPoint) {
	//	anchorPoint = &m_StartingPoint;
	//}
}

/* ������ ������ ��ü �Ӽ� ���� */
void CFigure::setProperties(CFigureProperties properties) {

}

/* ��ü �׸��� */
void CFigure::draw() {

}

/* ��ü ���ü� �׸��� */
void CFigure::drawSelect() {
	
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

Graphics* CFigure::getGraphics() {
	return this->m_lpGraphics;
}

void CFigure::setGraphics(Graphics* lpGraphics) {
	this->m_lpGraphics = lpGraphics;
}

PointF& CFigure::getStartingPoint() {
	return this->m_StartingPoint;
}

void CFigure::setStartingPoint(PointF StartingPoint) {
	this->m_StartingPoint = StartingPoint;
}

CFigure::operationModeFlags CFigure::getOperationMode() {
	return this->m_OperationMode;
}

void CFigure::setOperationMode(operationModeFlags OperationMode) {
	this->m_OperationMode = OperationMode;
}