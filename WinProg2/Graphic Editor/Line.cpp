// Line.cpp : CLine 클래스의 구현
// CLine : 직선 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Line.h"


IMPLEMENT_SERIAL(CLine, CStrap, 1)

CLine::CLine()
	:CStrap()
{
	//m_LinePen	
}

CLine::CLine(IN CClientDC* lpClientDC)
	: CStrap(lpClientDC)
{

}

CLine::CLine(IN Graphics* lpGraphics)
	: CStrap(lpGraphics)
{

}

CLine::CLine(IN CClientDC* lpClientDC, IN Pen* pen)
	: CStrap(lpClientDC, pen)
{

}

CLine::CLine(IN Graphics* lpGraphics, IN Pen* pen)
	: CStrap(lpGraphics, pen)
{

}

CLine::~CLine()
{

}

void CLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


// LButtonUp
/* 생성 완료 */
BOOL CLine::create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag/* = FREECREATE*/) {
	return create(&startingPoint, &endingPoint, createFlag);
}

/* 생성 완료 */
BOOL CLine::create(void* param1, ...) {

	va_list vaList;
	va_start(vaList, param1);
	PointF* startingPoint = (PointF*)param1;
	PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	m_EndPoint = *endingPoint;
	m_Gradient = (startingPoint->Y - m_EndPoint.Y) / (startingPoint->X - m_EndPoint.X);

	m_Area.X = startingPoint->X;
	m_Area.Y = startingPoint->Y;
	m_Area.Width = abs(startingPoint->X - m_EndPoint.X);
	m_Area.Height = abs(startingPoint->Y - m_EndPoint.Y);
	resetArea();

	return FALSE;
}

/* 생성 완료 */
//void CLine::endCreate(PointF point) {
//	m_EndPoint = point;
//	m_Gradient = (m_StartingPoint.Y - m_EndPoint.Y) / (m_StartingPoint.X - m_EndPoint.X);
//
//	m_Area.X = m_StartingPoint.X;
//	m_Area.Y = m_StartingPoint.Y;
//	m_Area.Width = abs(m_StartingPoint.X - m_EndPoint.X);
//	m_Area.Height = abs(m_StartingPoint.Y - m_EndPoint.Y);
//}

/* 개체 이동 */
void CLine::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	/* 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = targetPoint - originPoint;

	m_StartingPoint = m_StartingPoint + RelativePoint;
	m_EndPoint = m_EndPoint + RelativePoint;
	resetArea();
}

/* 선 크기(길이) 변경 */
void CLine::resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	if (selectedHandle == START)
		m_StartingPoint = targetPoint;

	else if (selectedHandle == END)
		m_EndPoint = targetPoint;

	resetArea();

}

// Menu Item
/* 선 삭제 */
void CLine::destroy() {

	if (this) {
		this->~CLine();
	}
	//invalidate 다른 것들은 일단 보류
}


// LButtonDown 
/* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
CFigure::Position CLine::pointInFigure(IN PointF point) {

	// 1. 현재 좌표가  선의 StartingPoint나 EndPoint이면 ONHANDLE("Resize모드") 이다. 
	if (point.Equals(m_StartingPoint) == TRUE)
		return START;

	else if (point.Equals(m_EndPoint) == TRUE)
		return END;

	// 2. 현재 좌표가 선이 있는 영역에 있을 때 원래의 선의 기울기와 같을 때는 INSIDE("Move모드") 이다.
	else if (m_Area.GetLeft() <= point.X && point.X <= m_Area.GetRight() || m_Area.GetRight() <= point.X && point.X <= m_Area.GetLeft()){
		if (m_Area.GetTop() <= point.Y && point.Y <= m_Area.GetBottom() || m_Area.GetBottom() <= point.Y && point.Y <= m_Area.GetTop()){

			// 현재 찍은 좌표와 StartingPoint과의 기울기를 비교할 것이다.
			int tmp_gradient = (m_StartingPoint.Y - point.Y) / (m_StartingPoint.X - point.X);

			if (tmp_gradient == m_Gradient)
				return INSIDE;
		}
		return OUTSIDE;

	}

	// 그 외: 아무 모드도 아님
	else return OUTSIDE;
}

///* 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지 */
// pointInFigure에 대응하는 함수
//CFigure::operationModeFlags CLine::cursorPosition(PointF point) {
//
//	// 1. 현재 좌표가  선의 StartingPoint나 EndPoint이면 "Resize모드" 이다. 
//	if (point.Equals(m_StartingPoint) == TRUE || point.Equals(m_EndPoint) == TRUE){
//		if (point.Equals(m_StartingPoint) == TRUE)
//			isStartingpoint = TRUE;
//
//		return Resize;
//	}
//
//	// 2. 현재 좌표가 선이 있는 영역에 있을 때 원래의 선의 기울기와 같을 때는 "Move모드" 이다.
//	else if (m_Area.GetLeft() <= point.X && point.X <= m_Area.GetRight() || m_Area.GetRight() <= point.X && point.X <= m_Area.GetLeft()){
//		if (m_Area.GetTop() <= point.Y && point.Y <= m_Area.GetBottom() || m_Area.GetBottom() <= point.Y && point.Y <= m_Area.GetTop()){
//
//			// 현재 찍은 좌표와 StartingPoint과의 기울기를 비교할 것이다.
//			int tmp_gradient = (m_StartingPoint.Y - point.Y) / (m_StartingPoint.X - point.X);
//
//			if (tmp_gradient == m_Gradient)
//				return Move;
//
//		}
//		return None;
//
//	}
//		
//	// 그 외: 아무 모드도 아님
//	else None;
//}

/* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
//CFigure::operationModeFlags CLine::cursorPosition(RectF rect) {
//	return None;
//}

/* 선 생성*/
//void CLine::create(PointF startingPoint)
//{
//		// 어차피 선은 점을 두 개만 사용할 꺼기때문에 절대 좌표를 사용하기로 함.
//		this->m_StartingPoint = startingPoint;
//}


// OnDraw
/* 선 그리기 */
void CLine::draw() {
	m_lpGraphics->DrawLine(m_OutlinePen, m_StartingPoint, m_EndPoint);
}

// OnMouseMove
/* 생성 그리기 */
void CLine::creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/) {
	
	creating(&startingPoint,&targetPoint,createFlag);
	
}

/* 생성 그리기 */
void CLine::creating(void* param1, ...) {
	va_list vaList;
	va_start(vaList,param1);
	PointF* startingPoint = (PointF*)param1;
	PointF* targetPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	m_lpGraphics->DrawLine(m_OutlinePen, *startingPoint, *targetPoint);
}

/* 이동 그리기 */
void CLine::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	/* 끌고 이동 할 때 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = targetPoint - originPoint;

	/* 원래 좌표에서 상대 좌표를 더해준 것이 이동 결과 좌표가 된다. */
	m_lpGraphics->DrawLine(m_OutlinePen, m_StartingPoint + RelativePoint, m_EndPoint + RelativePoint);
}

/* 크기 변경 그리기 */
void CLine::resizing(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	if (selectedHandle == START){
		m_lpGraphics->DrawLine(m_OutlinePen, targetPoint, m_EndPoint);
}
	else if (selectedHandle == END){
		m_lpGraphics->DrawLine(m_OutlinePen, m_StartingPoint, targetPoint);
	}
}

/* OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단) */
//void CLine::mouseMoveOperation(UINT nFlags, PointF point) {
//
//	m_OperationMode = cursorPosition(point);
//
//	switch (m_OperationMode){
//	case operationModeFlags::Create:
//		creating(nFlags, point);
//		break;
//
//	case operationModeFlags::Move:
//		moving(nFlags, point);
//		break;
//
//	case operationModeFlags::Resize:
//		resizing(nFlags, point);
//		break;
//	}
//}

// 도형 작업 후에 호출
/* 개체 영역 갱신 */
void CLine::resetArea() {

	Pen pen(Color::Black);
	pen.SetDashStyle(DashStyleCustom);

	m_lpGraphics->DrawRectangle(&pen, m_Area);
}




// 속성에 관한 부분은 Property class를 이용하기로 했음
// 이 부분은 CStrap에서 재정의 및 구현함
///* 선 색 설정 */
//BOOL CLine::setLineColor(const Color& LineColor) {
//	m_LineColor = LineColor;
//}
//
///* 선 두께 설정 */
//BOOL CLine::setLineWidth(const REAL& LineWidth) {
//	 m_LineWidth = LineWidth;
//}
//
///* 선 패턴 설정 */
//BOOL CLine::setLinePattern(const DashStyle& LinePattern) {
//	m_LinePattern = LinePattern;
//}



