// Line.cpp : CLine 클래스의 구현
// CLine : 직선 개체를 정의하는 클래스
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

/* 선 생성*/
void CLine::Create(PointF startingPoint)
{
	//나중에 상대 좌표를 사용할 꺼임
	this->m_StartingPoint = startingPoint;
	m_PointsList.AddHead(PointF(0,0));
}

/* 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지 */
CFigure::operationModeFlags CLine::cursorPosition(PointF point) {
	return None;
}

/* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
CFigure::operationModeFlags CLine::cursorPosition(CRect rect) {
	return None;
}

/* OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단) */
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

/* 생성 그리기 */
void CLine::creating(UINT nFlags, PointF point) {

	CRgn rgn;
	rgn.CreateRectRgn(m_StartingPoint.X, m_StartingPoint.Y, point.X, point.Y);

	InvalidateRgn(NULL, rgn, TRUE);

}

/* 이동 그리기 */
void CLine::moving(UINT nFlags, PointF point) {

}

/* 크기 변경 그리기 */
void CLine::resizing(UINT nFlags, PointF point) {

}

/* 점 추가 */
void CLine::addPoint(PointF point) {
	m_EndPoint = PointF((point.X - m_StartingPoint.X), (point.Y - m_StartingPoint.Y));
	m_PointsList.AddTail(m_EndPoint);
}

/* 개체 이동 */
void CLine::move(PointF Target) {

}

/* 선 크기(길이) 변경 */
void CLine::resize(PointF point, PointF* anchorPoint, int resizeFlags) {

}

/* 설정된 값으로 개체 속성 설정 */
void CLine::setProperties(CFigureProperties properties) {

}

/* 선 그리기 */
void CLine::draw() {

}

/* 선 삭제 */
void CLine::destroy() {

}


// 속성에 관한 부분은 Property class를 이용하기로 했음
/* 선 색 설정 */
void CLine::setLineColor(Color lineColor) {
	m_LineColor = lineColor;
}

/* 선 두께 설정 */
void CLine::setLineWidth(int lineWidth) {
	 m_LineWidth = lineWidth;
}

/* 선 패턴 설정 */
void CLine::setLinePattern(int linePattern) {
	m_LinePattern = linePattern;
}


CList<PointF, PointF&>& CLine::GetPointsList(){
	return m_PointsList;
}
