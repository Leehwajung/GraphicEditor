// Line.cpp : CLine 클래스의 구현
// CLine : 직선 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Line.h"


CLine::CLine() 
	:CStrap()
{
	//m_LinePen	
}


CLine::~CLine()
{

}

/* 선 생성*/
void CLine::Create(PointF startingPoint)
{
	// 어차피 선은 점을 두 개만 사용할 꺼기때문에 절대 좌표를 사용하기로 함.
	this->m_StartingPoint = startingPoint;
}

/* 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지 */
CFigure::operationModeFlags CLine::cursorPosition(PointF point) {

	// 1. 현재 좌표가 StaringPoint인 
	if ((point.Equals(m_StartingPoint) == FALSE || point.Equals(m_EndPoint) == FALSE)){	
		
		
	}

	// 2. 현재 좌표가  선의 StartingPoint나 EndPoint이면 "Resize모드" 이다. 
	else if (point.Equals(m_StartingPoint) == TRUE || point.Equals(m_EndPoint) == TRUE){
		return Resize;
	}

	// 3. 현재 좌표가 선의 사이에 있을 때는 "Move모드" 이다.
	else if ((point.Equals(m_StartingPoint) == FALSE || point.Equals(m_EndPoint) == FALSE)){

		// 현재 찍은 좌표와 StartingPoint과의 기울기를 비교할 것이다.
		int tmp_gradient = (m_StartingPoint.Y - point.Y) / (m_StartingPoint.X - point.X);

		if (tmp_gradient == gradient){
			return Move;
		}
		return None;

	}
		
	// 그 외: 아무 모드도 아님
	else None;
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
	m_lpGraphics->DrawLine(&m_Pen, m_StartingPoint, point);

}

/* 이동 그리기 */
void CLine::moving(UINT nFlags, PointF point) {

	/* 끌고 이동 할 때 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = PointF(point  - m_StartingPoint);

	/* 원래 좌표에서 상대 좌표를 더해준 것이 이동 결과 좌표가 된다. */
	m_lpGraphics->DrawLine(&m_Pen, m_StartingPoint + RelativePoint, m_EndPoint + RelativePoint);
}

/* 크기 변경 그리기 */
void CLine::resizing(UINT nFlags, PointF point) {

}


// LButtonUp / LButtonDlk
/* 점 추가 */
void CLine::addPoint(PointF point) {
	m_EndPoint = point;
	gradient = (m_StartingPoint.Y - m_EndPoint.Y) / (m_StartingPoint.X - m_EndPoint.X);
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

