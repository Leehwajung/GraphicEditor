// Line.cpp : CLine 클래스의 구현
// CLine : 직선 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Line.h"


CLine::CLine() 
	: m_LinePen(Pen(Color(255, 0, 0, 0), 1)) // 펜 속성  임시 설정 입니당~ //
{
	//m_LinePen
	
	
}


CLine::~CLine()
{

}

/* 선 생성*/
void CLine::Create(PointF startingPoint)
{
	// 상속 구조가 달라짐에 따라서 Line이 상대좌표로 해야할 필요가 없어짐. Line은 어차피 점이 두 개이기 때문에 절대 좌표를 따르기로 함.
	this->m_StartingPoint = startingPoint;
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
	m_lpGraphics->DrawLine(&m_LinePen, m_StartingPoint, point);

}

/* 이동 그리기 */
void CLine::moving(UINT nFlags, PointF point) {

	/* 끌고 이동 할 때 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = PointF(point  - m_StartingPoint);

	m_lpGraphics->DrawLine(&m_LinePen, m_StartingPoint + RelativePoint, m_EndPoint + RelativePoint);
}

/* 크기 변경 그리기 */
void CLine::resizing(UINT nFlags, PointF point) {

}

/* 점 추가 */
void CLine::addPoint(PointF point) {
	m_EndPoint = point;
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
