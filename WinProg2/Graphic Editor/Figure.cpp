#include "stdafx.h"
#include "Figure.h"


CFigure::CFigure()
{
}

CFigure::CFigure(CDC* dc)
{
}

CFigure::~CFigure()
{
}

void CFigure::Create(CPoint StartingPoint) {
	this->m_startingPoint = StartingPoint;
}

void CFigure::setLineColor(Color LineColor) {

}

void CFigure::setFillColor(Color FillColor) {

}

void CFigure::setLineWidth(int LineWidth) {

}

void CFigure::setLinePattern(int LinePattern) {

}

void CFigure::setFillPattern(int FillPattern) {

}

void CFigure::move(CPoint Target) {

}

void CFigure::resize(CPoint Point, int resizeFlags) {

}

void CFigure::destroy() {

}

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