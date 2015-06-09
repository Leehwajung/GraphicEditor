// Polygon.cpp : CPolygon Ŭ������ ����
// CPolygon : �ٰ��� ��ü�� �����ϴ� Ŭ����
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


// CPolygon ��� �Լ�
//LButtonUp
void CPolygon::addPoint(IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){
	m_PointsList.AddTail(addingPoint);
}
//LButtonDlk
/* ���� �Ϸ� */
BOOL CPolygon::create(IN CreateFlag createFlag/* = FREECREATE*/){
	return create(&createFlag);
}

/* ���� �Ϸ� */
BOOL CPolygon::create(void* param1, ...) {
	va_list vaList;
	va_start(vaList, param1);
	CreateFlag* createFlag = (CreateFlag*)param1;
	va_end(vaList);

	//m_CreatedFlag = TRUE;
	resetArea();

	return FALSE;
}

/* ��ü �̵� */
void CPolygon::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	/* �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;

	/* ���� ��ǥ���� ��� ��ǥ�� ������ ���� �̵� ��� ��ǥ�� �ȴ�. */
	POSITION pos = m_PointsList.GetHeadPosition();
	POSITION prevpos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  point = m_PointsList.GetNext(pos);
		m_PointsList.SetAt(prevpos, point + RelativePoint);
		prevpos = pos;
	}

	resetArea();
}

// ���� ��ǥ �̵�
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

// ���� ��ǥ ����
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

	// Polygon�̱⶧���� ������ ��ǥ������ �۾��� ���־�� �Ѵ�.
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

/* ũ��(����) ���� */
void CPolygon::resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {


}

// Menu Item
/* �� ���� */
void CPolygon::destroy() {

	if (this) {
		this->~CPolygon();
	}
	//invalidate �ٸ� �͵��� �ϴ� ����
}


// LButtonDown 
/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
CFigure::Position CPolygon::pointInFigure(IN PointF point) {

	// 1. ���� ��ǥ�� ONHANDLE �� ��
	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = m_PointsList.GetNext(pos);

		RectF handleRect;
		handleRect = getHandleRect(tmp_point);

		if (handleRect.Contains(point))
			return ONHANDLE;
	}

	// 2. ���� ��ǥ�� ���� ������ ���� �� INSIDE�̴�.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	GraphicsPath gp;
	gp.AddPolygon(pointsArray.GetData(), pointsArray.GetSize());
	if (gp.IsVisible(point)) {
		return INSIDE;
	}

	// �ٱ� ����
	return OUTSIDE;
}


// OnDraw
/* �� �׸��� */
void CPolygon::draw(IN Graphics& graphics) {

	// polygon�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	// Draw the lines.
	m_OutlinePen->SetDashStyle(DashStyleSolid);
	graphics.FillPolygon(m_FillBrush, pointsArray.GetData(), pointsArray.GetSize());
	graphics.DrawPolygon(m_OutlinePen, pointsArray.GetData(), pointsArray.GetSize());

}

// OnMouseMove
/* ���� �׸��� */
RectF CPolygon::creating(IN Graphics& graphics, IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){

	return creating(graphics, &addingPoint, &createFlag);
}

/* ���� �׸��� */
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

/* �̵� �׸��� */
RectF CPolygon::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {
	RectF drawnArea;
	POSITION pos;
	/* ���� �̵� �� �� �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;

	// polyLine�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
	CArray<PointF, PointF&> pointsArray;

	for (pos= m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos) + RelativePoint);
	}
	PointF head = m_PointsList.GetHead();
	pointsArray.Add(head + RelativePoint);

	// Draw the lines.

	graphics.FillPolygon(CGlobal::crateIngBrush(m_FillBrush), pointsArray.GetData(), pointsArray.GetSize());
	graphics.DrawLines(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());

	return drawnArea;
}

// ���� ��ǥ �̵� �׸���
RectF CPolygon::pointMoving(Graphics& graphics, IN PointF originPoint, IN PointF targetPoint){

	RectF drawnArea;

	PointF  point;


	BOOL SameHandle = FALSE;

	// polyLine�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
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

/* ũ�� ���� �׸��� */
RectF CPolygon::resizing(IN Graphics& graphics, IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	RectF drawnArea;



	return drawnArea;
}

// ���� �۾� �Ŀ� ȣ��
/* ��ü ���� ���� */
RectF CPolygon::resetArea() {


	REAL x_start, y_start, x_end = 0, y_end = 0;

	POSITION pos = m_PointsList.GetHeadPosition();
	x_start = m_PointsList.GetHead().X;
	y_start = m_PointsList.GetHead().Y;
	while (pos != NULL){
		PointF  tmp_point = m_PointsList.GetNext(pos);

		// m_Area ���� �� ����. List�� ���Ұ� �߰��� ������ ���� �Ǿ�� �Ѵ�. 
		if (x_start >= tmp_point.X)
			x_start = tmp_point.X;

		if (y_start >= tmp_point.Y)
			y_start = tmp_point.Y;

		// m_Area �ʺ�, ���� ���� 
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

// CPolygon ��� �Լ�
/* ���� (�ڵ�) �׸��� */
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
