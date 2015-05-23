#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{

}


CLine::~CLine()
{

}

/* 선 생성*/
void CLine::Create(CPoint startingPoint)
{
	//나중에 상대 좌표를 사용할 꺼임
	this->m_startingPoint = startingPoint;
	m_PointsList.AddHead(CPoint(0,0));
}

/* 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지 */
CLine::operationModeFlags CLine::cursorPosition(CPoint point) {
	return None;
}

/* OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단) */
void CLine::mouseMoveOperation(UINT nFlags, CPoint point) {

}

/* 생성 그리기 */
void CLine::creating(UINT nFlags, CPoint point) {

}

/* 이동 그리기 */
void CLine::moving(UINT nFlags, CPoint point) {

}

/* 크기 변경 그리기 */
void CLine::resizing(UINT nFlags, CPoint point) {

}

/* 점 추가 */
void CLine::addPoint(CPoint point) {

}

/* 개체 이동 */
void CLine::move(CPoint Target) {

}

/* 선 크기(길이) 변경 */
void CLine::resize(CPoint Point, int resizeFlags) {

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
	m_lineColor = lineColor;
}

/* 선 두께 설정 */
void CLine::setLineWidth(int lineWidth) {
	 m_lineWidth = lineWidth;
}

/* 선 패턴 설정 */
void CLine::setLinePattern(int linePattern) {
	m_linePattern = linePattern;
}


CList<CPoint, CPoint&>& CLine::GetPointsList(){
	return m_PointsList;
}
