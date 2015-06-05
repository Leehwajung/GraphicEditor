// PolyLine.cpp : CPolyLine 클래스의 구현
// CPolyLine : 폴리라인 개체를 정의하는 클래스
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "PolyLine.h"


// CPolyLine

IMPLEMENT_SERIAL(CPolyLine, CStrap, 1)

CPolyLine::CPolyLine()
{
}

CPolyLine::~CPolyLine()
{
}


// CPolyLine 멤버 함수


void CPolyLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

//LButtonUp
void CPolyLine::addPoint(PointF addingPoint){
	m_PointsList.AddTail(addingPoint);
}
//LButtonDlk
/* 생성 완료 */
BOOL CPolyLine::create(IN CreateFlag createFlag/* = FREECREATE*/){
	return create(createFlag);
}

/* 생성 완료 */
BOOL CPolyLine::create(void* param1, ...) {

	va_list vaList;
	va_start(vaList, param1);
	CreateFlag* createFlag = (CreateFlag*)param1;
	va_end(vaList);

	REAL x_start=0,y_start=0,width=0,height=0;

	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = m_PointsList.GetNext(pos);

		// m_Area 시작 점 설정. List에 원소가 추가될 때마다 갱신 되어야 한다. 
		if (x_start >= tmp_point.X)
			x_start = tmp_point.X;

		if (y_start >= tmp_point.Y)
			y_start = tmp_point.Y;

		// m_Area 너비, 높이 설정 
		if (width <= tmp_point.X)
			width = tmp_point.X;

		if (height <= tmp_point.Y)
			height = tmp_point.Y;
	}

	m_Area.X = x_start;
	m_Area.Y = y_start;
	m_Area.Width = width;
	m_Area.Height = height;

	return FALSE;
}

/* 개체 이동 */
void CPolyLine::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	/* 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = targetPoint - originPoint;


}

/* 선 크기(길이) 변경 */
void CPolyLine::resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {


}

// Menu Item
/* 선 삭제 */
void CPolyLine::destroy() {

	if (this) {
		this->~CPolyLine();
	}
	//invalidate 다른 것들은 일단 보류
}


// LButtonDown 
/* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
CFigure::Position CPolyLine::pointInFigure(IN PointF point) {

	// 1. 현재 좌표가 ONHANDLE 일 때
	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = m_PointsList.GetNext(pos);

		if (tmp_point.Equals(point) == TRUE)
			return ONHANDLE;
	}

	// 2. 현재 좌표가 선이 있는 영역에 있을 때 INSIDE이다.
	pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF first_point = m_PointsList.GetNext(pos);
		PointF second_point = m_PointsList.GetNext(pos);

		int Gradient = abs(first_point.Y - second_point.Y) / abs(first_point.X - second_point.X);

		m_SubArea.X = first_point.X;
		m_SubArea.Y = first_point.Y;
		m_SubArea.Width = abs(first_point.X - second_point.X);
		m_SubArea.Height = abs(first_point.Y - second_point.Y);

		if (m_SubArea.GetLeft() <= point.X && point.X <= m_SubArea.GetRight() || m_SubArea.GetRight() <= point.X && point.X <= m_SubArea.GetLeft()){
			if (m_SubArea.GetTop() <= point.Y && point.Y <= m_SubArea.GetBottom() || m_SubArea.GetBottom() <= point.Y && point.Y <= m_SubArea.GetTop()){

				// 현재 찍은 좌표와 StartingPoint과의 기울기를 비교할 것이다.
				int tmp_gradient = abs(first_point.Y - point.Y) / abs(first_point.X - point.X);

				if (tmp_gradient == Gradient)
					return INSIDE;
			}
		}

	}

	// 바깥 영역
	return OUTSIDE;
}


// OnDraw
/* 선 그리기 */
void CPolyLine::draw() {
}

// OnMouseMove
/* 생성 그리기 */
void CPolyLine::creating(IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){
	creating(&addingPoint, createFlag);
}

/* 생성 그리기 */
void CPolyLine::creating(void* param1, ...) {
	va_list vaList;
	va_start(vaList, param1);
	PointF* addingPoint = (PointF*)param1;
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	m_lpGraphics->DrawLine(m_OutlinePen, m_PointsList.GetTail(),*addingPoint);

}

/* 이동 그리기 */
void CPolyLine::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	/* 끌고 이동 할 때 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = targetPoint - originPoint;

	/* 원래 좌표에서 상대 좌표를 더해준 것이 이동 결과 좌표가 된다. */
	/*CList <PointF, PointF&> PolyLineList = m_PointsList;

	POSITION pos = PolyLineList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = PolyLineList.GetNext(pos);
	    
	}*/

}

/* 크기 변경 그리기 */
void CPolyLine::resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {

}

// 도형 작업 후에 호출
/* 개체 영역 갱신 */
void CPolyLine::resetArea() {

	Pen pen(Color::Black);
	pen.SetDashStyle(DashStyleCustom);

	m_lpGraphics->DrawRectangle(&pen, m_Area);
}

void addPoint(PointF addingpoint){

}

