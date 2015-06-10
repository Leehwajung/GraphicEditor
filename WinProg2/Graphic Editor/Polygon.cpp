// Polygon.cpp : CPolygon 클래스의 구현
// CPolygon : 다각형 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Polygon.h"


// CPolygon

IMPLEMENT_SERIAL(CPolygon, CShape, 1)

CPolygon::CPolygon()
	: CShape()
{
}
CPolygon::CPolygon(IN Pen* pen, IN BrushPtr brush)
	: CShape(pen, brush)
{
}

CPolygon::CPolygon(IN Pen* pen, IN BrushPtr brush, CList <PointF, PointF&>& list)
   : CShape(pen,brush)
{
	for (POSITION pos = list.GetHeadPosition(); pos; list.GetNext(pos)) {
		m_PointsList.AddTail(list.GetAt(pos));
	}
}

CPolygon::~CPolygon()
{
}

CFigure* CPolygon::clone(){
	return new CPolygon(m_OutlinePen,m_FillBrush, m_PointsList);
}

void CPolygon::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


// CPolygon 멤버 함수
//LButtonUp
void CPolygon::addPoint(IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){
	m_PointsList.AddTail(addingPoint);
}
//LButtonDlk
/* 생성 완료 */
BOOL CPolygon::create(IN CreateFlag createFlag/* = FREECREATE*/){
	return create(&createFlag);
}

/* 생성 완료 */
BOOL CPolygon::create(void* param1, ...) {
	va_list vaList;
	va_start(vaList, param1);
	CreateFlag* createFlag = (CreateFlag*)param1;
	va_end(vaList);

	resetArea();

	return FALSE;
}

/* 개체 이동 */
void CPolygon::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

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

	resetArea();
}

// 개별 좌표 이동
void CPolygon::pointMove(IN PointF originPoint, IN PointF targetPoint){

	PointF  point = m_PointsList.GetHead();
	POSITION pos = m_PointsList.GetHeadPosition(), prevpos = m_PointsList.GetHeadPosition();

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
	resetArea();
}

// 개별 좌표 삭제
void CPolygon::RemovePoint(IN PointF originPoint){
	PointF  point = m_PointsList.GetHead();
	POSITION pos = m_PointsList.GetHeadPosition(), prevpos = m_PointsList.GetHeadPosition();

	while (pos != NULL){
		point = m_PointsList.GetNext(pos);

		RectF handleRect;
		handleRect = getHandleRect(point);

		if (handleRect.Contains(originPoint)) {
			m_PointsList.RemoveAt(prevpos);
			break;
		}

		prevpos = pos;
	}
	resetArea();
}

void CPolygon::InsertPoint(IN PointF originPoint){

	POSITION pos = m_PointsList.GetHeadPosition();
	POSITION prevpos = m_PointsList.GetHeadPosition();
	PointF first_point = m_PointsList.GetNext(pos);
	PointF second_point;
	REAL Gradient;

	while (pos != NULL){
		prevpos = pos;
		second_point = m_PointsList.GetNext(pos);
		Gradient = (first_point.Y - second_point.Y) / (first_point.X - second_point.X);

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
		if (rgn.IsVisible(originPoint)){
			m_PointsList.InsertBefore(prevpos, originPoint);
			resetArea();
			return;
		}
		first_point = second_point;
	}

	// Polygon이기때문에 마지막 좌표에대한 작업을 해주어야 한다.
	first_point = m_PointsList.GetTail();
	second_point = m_PointsList.GetHead();
	Gradient = (first_point.Y - second_point.Y) / (first_point.X - second_point.X);

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
	if (rgn.IsVisible(originPoint)){
		m_PointsList.AddTail(originPoint);
		resetArea();
		return;
	}
}

/* 크기(길이) 변경 */
void CPolygon::resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {


}

// Menu Item
/* 선 삭제 */
void CPolygon::destroy() {

	if (this) {
		this->~CPolygon();
	}
	//invalidate 다른 것들은 일단 보류
}


// LButtonDown 
/* 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지) */
CFigure::Position CPolygon::pointInFigure(IN PointF point) {

	// 1. 현재 좌표가 ONHANDLE 일 때
	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = m_PointsList.GetNext(pos);

		RectF handleRect;
		handleRect = getHandleRect(tmp_point);

		if (handleRect.Contains(point))
			return ONHANDLE;
	}

	// 2. 현재 좌표가 내부 영역에 있을 때 INSIDE이다.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	GraphicsPath gp;
	gp.AddPolygon(pointsArray.GetData(), pointsArray.GetSize());
	if (gp.IsVisible(point)) {
		return INSIDE;
	}

	// 바깥 영역
	return OUTSIDE;
}


// OnDraw
/* 선 그리기 */
void CPolygon::draw(IN Graphics& graphics) {

	// polygon을 그려주기 전에 CList를 CArray로 바꿔주는 방법을 사용하기로 한다.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	// Draw the Ploygon.
	graphics.FillPolygon(m_FillBrush, pointsArray.GetData(), pointsArray.GetSize());
	graphics.DrawPolygon(m_OutlinePen, pointsArray.GetData(), pointsArray.GetSize());

}

// OnMouseMove
/* 생성 그리기 */
RectF CPolygon::creating(IN Graphics& graphics, IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){

	return creating(graphics, &addingPoint, &createFlag);
}

/* 생성 그리기 */
RectF CPolygon::creating(IN Graphics& graphics, void* param1, ...) {
	va_list vaList;
	va_start(vaList, param1);
	PointF* addingPoint = (PointF*)param1;
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	RectF drawnArea;

	graphics.DrawLine(CGlobal::crateIngPen(m_OutlinePen), m_PointsList.GetTail(), *addingPoint);

	return drawnArea;
}

/* 이동 그리기 */
RectF CPolygon::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {
	RectF drawnArea;
	POSITION pos;
	/* 끌고 이동 할 때 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = targetPoint - originPoint;

	// Ploygon을 그려주기 전에 CList를 CArray로 바꿔주는 방법을 사용하기로 한다.
	CArray<PointF, PointF&> pointsArray;

	for (pos= m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos) + RelativePoint);
	}
	PointF head = m_PointsList.GetHead();
	pointsArray.Add(head + RelativePoint);

	// Draw the Ploygon.

	graphics.FillPolygon(CGlobal::crateIngBrush(m_FillBrush), pointsArray.GetData(), pointsArray.GetSize());
	graphics.DrawLines(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());

	return drawnArea;
}

// 개별 좌표 이동 그리기
RectF CPolygon::pointMoving(Graphics& graphics, IN PointF originPoint, IN PointF targetPoint){

	RectF drawnArea;

	PointF  point;


	BOOL SameHandle = FALSE;

	// Ploygon을 그려주기 전에 CList를 CArray로 바꿔주는 방법을 사용하기로 한다.
	CArray<PointF, PointF&> pointsArray;
	CArray<RectF, RectF&> HandleRectArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		point = m_PointsList.GetAt(pos);

		RectF handleRect;
		handleRect = getHandleRect(point);
		HandleRectArray.Add(handleRect);

		for (int i = 0; i < HandleRectArray.GetSize() - 1; i++){
			for (int j = i + 1; j < HandleRectArray.GetSize(); j++)
			if (HandleRectArray[i].Contains(originPoint) && HandleRectArray[j].Contains(originPoint))
				SameHandle = TRUE;
		}
		if (SameHandle == FALSE){
			if (handleRect.Contains(originPoint)){
				point = targetPoint;
				pointsArray.Add(point);
			}
			else pointsArray.Add(point);
		}
	}
	PointF head = m_PointsList.GetHead();
	PointF tail = m_PointsList.GetTail();

	if (getHandleRect(head).Contains(originPoint))
		pointsArray.Add(targetPoint);
	else if (getHandleRect(tail).Contains(originPoint))
		pointsArray.Add(head);

	graphics.DrawLines(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());
	return drawnArea;
}

/* 크기 변경 그리기 */
RectF CPolygon::resizing(IN Graphics& graphics, IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	RectF drawnArea;



	return drawnArea;
}

// 도형 작업 후에 호출
/* 개체 영역 갱신 */
RectF CPolygon::resetArea() {


	REAL x_start, y_start, x_end = 0, y_end = 0;

	POSITION pos = m_PointsList.GetHeadPosition();
	x_start = m_PointsList.GetHead().X;
	y_start = m_PointsList.GetHead().Y;
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

// CPolygon 멤버 함수
/* 영역 (핸들) 그리기 */
void CPolygon::drawLineHandle(IN Graphics& graphics){
	CArray <PointF, PointF&> pointsArray;

	Pen pen(Color::Gray);
	pen.SetDashStyle(DashStyleDot);

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	graphics.DrawLines(&pen, pointsArray.GetData(), pointsArray.GetSize());

	drawHandles(graphics, pointsArray.GetData(), pointsArray.GetSize());
}


CList <PointF, PointF&>& CPolygon::GetPointsList(){
	return m_PointsList;
}
