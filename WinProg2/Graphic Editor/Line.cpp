#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{

}


CLine::~CLine()
{

}

void CLine::Create(CPoint startingPoint)
{
	//나중에 상대 좌표를 사용할 꺼임
	this->m_startingPoint = startingPoint;
	m_PointsList.AddHead(CPoint(0,0));
}

// 속성에 관한 부분은 setting class를 이용하기로 했음
void CLine::setLineColor(Color lineColor) {
	m_lineColor = lineColor;
}

void CLine::setLineWidth(int lineWidth) {
	 m_lineWidth = lineWidth;
}

void CLine::setLinePattern(int linePattern) {
	m_linePattern = linePattern;
}


void CLine::move(CPoint target) {

}

void CLine::resize(CPoint point) {

}

void CLine::propResize(CPoint point) {

}

void CLine::destroy() {

}

CList<CPoint, CPoint&>& CLine::GetPointsList(){
	return m_PointsList;
}
