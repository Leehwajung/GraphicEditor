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
	//���߿� ��� ��ǥ�� ����� ����
	this->m_startingPoint = startingPoint;
	m_PointsList.AddHead(CPoint(0,0));
}

// �Ӽ��� ���� �κ��� setting class�� �̿��ϱ�� ����
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
