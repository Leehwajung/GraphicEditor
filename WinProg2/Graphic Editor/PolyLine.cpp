// PolyLine.cpp : CPolyLine 클래스의 구현
// CPolyLine : 폴리라인 개체를 정의하는 클래스
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "PolyLine.h"


// CPolyLine

IMPLEMENT_SERIAL(CPolyLine, CStrap, 1)

CPolyLine::CPolyLine()
:CStrap()//, m_CreatedFlag(FALSE)
{

}

CPolyLine::CPolyLine(IN Pen* pen)
: CStrap(pen)//, m_CreatedFlag(FALSE)
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
void CPolyLine::addPoint(IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){
	//if (m_CreatedFlag == FALSE)
	m_PointsList.AddTail(addingPoint);
}
//LButtonDlk
/* 생성 완료 */
BOOL CPolyLine::create(IN CreateFlag createFlag/* = FREECREATE*/){
	return create(&createFlag);
}

/* 생성 완료 */
BOOL CPolyLine::create(void* param1, ...) {
		va_list vaList;
		va_start(vaList, param1);
		CreateFlag* createFlag = (CreateFlag*)param1;
		va_end(vaList);

		//m_CreatedFlag = TRUE;
		resetArea();

		return FALSE;
}

/* 개체 이동 */
void CPolyLine::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	/* 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = targetPoint - originPoint;

	/* 원래 좌표에서 상대 좌표를 더해준 것이 이동 결과 좌표가 된다. */
	POSITION pos = m_PointsList.GetHeadPosition();
	POSITION prevpos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  point = m_PointsList.GetNext(pos);
		m_PointsList.SetAt(prevpos, point + RelativePoint);
		prevpos = pos;
	}


}

// 개별 좌표 이동
void CPolyLine::pointMove(IN PointF originPoint, IN PointF targetPoint){

	PointF  point = m_PointsList.GetHead();
	POSITION pos = m_PointsList.GetHeadPosition() , prevpos = m_PointsList.GetHeadPosition();

	while (pos != NULL){
		point = m_PointsList.GetNext(pos);

		RectF handleRect;
		handleRect = getHandleRect(point);

		if (handleRect.Contains(originPoint)) {
			m_PointsList.SetAt(prevpos, targetPoint);
			break;
		}
			
			
		prevpos = pos;	
	}

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

		RectF handleRect;
		handleRect = getHandleRect(tmp_point);

		if (handleRect.Contains(point))
			return ONHANDLE;
	}

	// 2. 현재 좌표가 선이 있는 영역에 있을 때 INSIDE이다.
	pos = m_PointsList.GetHeadPosition();
	PointF first_point = m_PointsList.GetNext(pos);
	while (pos != NULL){
		PointF second_point = m_PointsList.GetNext(pos);

		REAL Gradient = (first_point.Y - second_point.Y) / (first_point.X - second_point.X);

		const int count = 4;

		REAL tmp_theta = atan(-1 / Gradient);
		REAL theta = 90 - tmp_theta;

		PointF points[count];
		GraphicsPath path;
		int width = (m_OutlinePen->GetWidth() > HANDLESIZE) ? m_OutlinePen->GetWidth() : HANDLESIZE;
		if (Gradient >= 0){
			points[0] = PointF(first_point.X + width / 2 * cos(theta), first_point.Y + width / 2 * sin(theta));
			points[1] = PointF(first_point.X - width / 2 * cos(theta), first_point.Y - width / 2 * sin(theta));
			points[2] = PointF(second_point.X - width / 2 * cos(theta), second_point.Y - width / 2 * sin(theta));
			points[3] = PointF(second_point.X + width / 2 * cos(theta), second_point.Y + width / 2 * sin(theta));
		}
		else if (Gradient < 0){
			points[0] = PointF(first_point.X - width / 2 * cos(theta), first_point.Y + width / 2 * sin(theta));
			points[1] = PointF(first_point.X + width / 2 * cos(theta), first_point.Y - width / 2 * sin(theta));
			points[2] = PointF(second_point.X + width / 2 * cos(theta), second_point.Y - width / 2 * sin(theta));
			points[3] = PointF(second_point.X - width / 2 * cos(theta), second_point.Y + width / 2 * sin(theta));
		}
		path.AddPolygon(points, count);

		Region rgn(&path);
		if (rgn.IsVisible(point)) {
			return INSIDE;
		}
		first_point = second_point;
	}

	// 바깥 영역
	return OUTSIDE;
}


// OnDraw
/* 선 그리기 */
void CPolyLine::draw(IN Graphics& graphics) {

	// polyLine을 그려주기 전에 CList를 CArray로 바꿔주는 방법을 사용하기로 한다.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos ; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	// Draw the lines.
	graphics.DrawLines(m_OutlinePen, pointsArray.GetData(), pointsArray.GetSize());

}

// OnMouseMove
/* 생성 그리기 */
RectF CPolyLine::creating(IN Graphics& graphics, IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){

	return creating(graphics, &addingPoint, &createFlag);
}

/* 생성 그리기 */
RectF CPolyLine::creating(IN Graphics& graphics, void* param1, ...) {
	va_list vaList;
	va_start(vaList, param1);
	PointF* addingPoint = (PointF*)param1;
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	RectF drawnArea;

	// 실제로 그리는 부분 
		
	graphics.DrawLine(CGlobal::crateIngPen(m_OutlinePen), m_PointsList.GetTail(), *addingPoint);

	return drawnArea;
}

/* 이동 그리기 */
RectF CPolyLine::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {
	RectF drawnArea;

	/* 끌고 이동 할 때 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = targetPoint - originPoint;

	// polyLine을 그려주기 전에 CList를 CArray로 바꿔주는 방법을 사용하기로 한다.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos) + RelativePoint);
	}

	// Draw the lines.
	graphics.DrawLines(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());


	///* 원래 좌표에서 상대 좌표를 더해준 것이 이동 결과 좌표가 된다. */
	//CList <PointF, PointF&> tmp_List;

	//POSITION pos = m_PointsList.GetHeadPosition();
	//while (pos!=NULL){
	//	PointF  point = m_PointsList.GetNext(pos);
	//	graphics.DrawLine(m_OutlinePen, tmp_List.GetTail(), point + RelativePoint);

	//	// 실제로 그리는 부분 
	//	tmp_List.AddTail(point+RelativePoint);
	//}

	return drawnArea;
}
	    
// 개별 좌표 이동 그리기
RectF CPolyLine::pointMoving(Graphics& graphics, IN PointF originPoint, IN PointF targetPoint){

	RectF drawnArea;

	PointF  point;

	// polyLine을 그려주기 전에 CList를 CArray로 바꿔주는 방법을 사용하기로 한다.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		point = m_PointsList.GetAt(pos);
		
		RectF handleRect;
		handleRect = getHandleRect(point);

		if (handleRect.Contains(originPoint)){
			point = targetPoint;
			pointsArray.Add(point);

		}
		else pointsArray.Add(point);
	}

	/*CList <PointF, PointF&> tmp_List;

	PointF  point = m_PointsList.GetHead();
	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		point = m_PointsList.GetNext(pos);

		RectF handleRect;
		handleRect = getHandleRect(point);

		if (handleRect.Contains(originPoint)){
			point = targetPoint;
			tmp_List.AddTail(point);

		}
		else tmp_List.AddTail(point);
		*/

	graphics.DrawLines(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());

	return drawnArea;
}

/* 크기 변경 그리기 */
RectF CPolyLine::resizing(IN Graphics& graphics, IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	RectF drawnArea;

	// 그리기 용 펜은 이 펜을 하용하도록: CGlobal::crateIngPen(m_OutlinePen)
	
	return drawnArea;
}

/* 영역 (핸들) 그리기 */
void CPolyLine::drawArea(IN Graphics& graphics) {
	
	CArray <PointF, PointF&> pointsArray;

	Pen pen(Color::Gray);
	pen.SetDashStyle(DashStyleDot);

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	graphics.DrawLines(&pen, pointsArray.GetData(), pointsArray.GetSize());

	drawHandles(graphics, pointsArray.GetData(), pointsArray.GetSize());
}

// 도형 작업 후에 호출
/* 개체 영역 갱신 */
RectF CPolyLine::resetArea() {

	REAL x_start = 0, y_start = 0, x_end = 0, y_end = 0;

	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = m_PointsList.GetNext(pos);

		// m_Area 시작 점 설정. List에 원소가 추가될 때마다 갱신 되어야 한다. 
		if (x_start >= tmp_point.X)
			x_start = tmp_point.X;

		if (y_start >= tmp_point.Y)
			y_start = tmp_point.Y;

		// m_Area 너비, 높이 설정 
		if (x_end <= tmp_point.X)
			x_end = tmp_point.X;

		if (y_end <= tmp_point.Y)
			y_end = tmp_point.Y;
}

	m_Area.Width = abs(x_start - x_end);
	m_Area.Height = abs(y_start - y_end);

	if (x_start > x_end) {
		m_Area.X = x_end;
	}
	else {
		m_Area.X = x_start;
	}

	if (y_start > y_end) {
		m_Area.Y = y_end;
	}
	else {
		m_Area.Y = y_start;
	}
	return m_Area;
}

//BOOL CPolyLine::GetCreatedFlag(){
//	return m_CreatedFlag;
//}


