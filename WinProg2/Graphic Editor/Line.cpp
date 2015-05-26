// Line.cpp : CLine 클래스의 구현
// CLine : 직선 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Line.h"


CLine::CLine()
	:CStrap()
	, m_Pen(new defaultPen)
	, isStartingpoint(FALSE)
{
	//m_LinePen	
}


CLine::~CLine()
{
	if (m_Pen) {
		m_Pen->~Pen();
	}
}

// LButtonDown 
/* 선 생성*/
void CLine::create(PointF startingPoint)
{
		// 어차피 선은 점을 두 개만 사용할 꺼기때문에 절대 좌표를 사용하기로 함.
		this->m_StartingPoint = startingPoint;
}

/* 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지 */
CFigure::operationModeFlags CLine::cursorPosition(PointF point) {

	// 1. 현재 좌표가  선의 StartingPoint나 EndPoint이면 "Resize모드" 이다. 
	if (point.Equals(m_StartingPoint) == TRUE || point.Equals(m_EndPoint) == TRUE){
		if (point.Equals(m_StartingPoint) == TRUE)
			isStartingpoint = TRUE;

		return Resize;
	}

	// 2. 현재 좌표가 선이 있는 영역에 있을 때 원래의 선의 기울기와 같을 때는 "Move모드" 이다.
	else if (m_Rect.GetLeft() <= point.X && point.X <= m_Rect.GetRight() || m_Rect.GetRight() <= point.X && point.X <= m_Rect.GetLeft()){
		if (m_Rect.GetTop() <= point.Y && point.Y <= m_Rect.GetBottom()|| m_Rect.GetBottom()<= point.Y && point.Y <= m_Rect.GetTop()){

			// 현재 찍은 좌표와 StartingPoint과의 기울기를 비교할 것이다.
			int tmp_gradient = (m_StartingPoint.Y - point.Y) / (m_StartingPoint.X - point.X);

			if (tmp_gradient == m_Gradient)
				return Move;

		}
		return None;

	}
		
	// 그 외: 아무 모드도 아님
	else None;
}

/* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
CFigure::operationModeFlags CLine::cursorPosition(RectF rect) {
	return None;
}


// OnMouseMove
/* OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단) */
void CLine::mouseMoveOperation(UINT nFlags, PointF point) {

	m_OperationMode = cursorPosition(point);

	switch (m_OperationMode){
	case operationModeFlags::Create:
		creating(nFlags, point);
		break;

	case operationModeFlags::Move:
		moving(nFlags, point);
		break;

	case operationModeFlags::Resize:
		resizing(nFlags, point);
		break;
	}
}

/* 생성 그리기 */
void CLine::creating(UINT nFlags, PointF point) {
	m_lpGraphics->DrawLine(m_Pen, m_StartingPoint, point);
}

/* 이동 그리기 */
void CLine::moving(UINT nFlags, PointF point) {

	/* 끌고 이동 할 때 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = PointF(point  - m_StartingPoint);

	/* 원래 좌표에서 상대 좌표를 더해준 것이 이동 결과 좌표가 된다. */
	m_lpGraphics->DrawLine(m_Pen, m_StartingPoint + RelativePoint, m_EndPoint + RelativePoint);
}

/* 크기 변경 그리기 */
void CLine::resizing(UINT nFlags, PointF point) {
	if (isStartingpoint == TRUE){
		m_lpGraphics->DrawLine(m_Pen, point, m_EndPoint);
	}
	else{
		m_lpGraphics->DrawLine(m_Pen, m_StartingPoint, point);
	}
}


// LButtonUp
/* 점 추가 */
void CLine::addPoint(PointF point) {
	m_EndPoint = point;
	m_Gradient = (m_StartingPoint.Y - m_EndPoint.Y) / (m_StartingPoint.X - m_EndPoint.X);

	m_Rect.X = m_StartingPoint.X;
	m_Rect.Y = m_StartingPoint.Y;
	m_Rect.Width = abs(m_StartingPoint.X - m_EndPoint.X);
	m_Rect.Height = abs(m_StartingPoint.Y - m_EndPoint.Y);
}

/* 개체 이동 */
void CLine::move(PointF originPoint, PointF targetPoint) {

	/* 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = PointF(Target - m_StartingPoint);

	m_StartingPoint = m_StartingPoint + RelativePoint;
	m_EndPoint = m_EndPoint + RelativePoint;

}

/* 선 크기(길이) 변경 */
void CLine::resize(PointF point, PointF* anchorPoint, int resizeFlags) {
	if (isStartingpoint == TRUE){
		m_StartingPoint = point;
		isStartingpoint == FALSE;
	}
	else{
		m_EndPoint = point;
	}

}

// OnDraw / OnPaint
/* 선 그리기 */
void CLine::draw() {
	m_lpGraphics->DrawLine(m_Pen,m_StartingPoint, m_EndPoint);
}


// Menu Item
/* 선 삭제 */
void CLine::destroy() {
	
	if (this) {
		this->~CLine();
	}
	//invalidate 다른 것들은 일단 보류
}

// 속성에 관한 부분은 Property class를 이용하기로 했음
/* 선 색 설정 */
void CLine::setLineColor(const Color& LineColor) {
	m_LineColor = LineColor;
}

/* 선 두께 설정 */
void CLine::setLineWidth(const REAL& LineWidth) {
	 m_LineWidth = LineWidth;
}

/* 선 패턴 설정 */
void CLine::setLinePattern(const DashStyle& LinePattern) {
	m_LinePattern = LinePattern;
}

