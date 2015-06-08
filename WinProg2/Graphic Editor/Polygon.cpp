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
CPolygon::~CPolygon()
{
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


// CPolyLine ��� �Լ�
//LButtonUp
void CPolygon::addPoint(IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){
	//if (m_CreatedFlag == FALSE)
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

}

/* �� ũ��(����) ���� */
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

	// 2. ���� ��ǥ�� ���� �ִ� ������ ���� �� INSIDE�̴�.
	pos = m_PointsList.GetHeadPosition();
	PointF first_point = m_PointsList.GetNext(pos);
	while (pos != NULL){
		PointF second_point = m_PointsList.GetNext(pos);

		REAL Gradient = (first_point.Y - second_point.Y) / (first_point.X - second_point.X);

		const int count = 4;

		REAL tmp_seta = atan(-1 / Gradient);
		REAL seta = 90 - tmp_seta;

		PointF points[count];
		GraphicsPath path;
		int width = (m_OutlinePen->GetWidth() > HANDLESIZE) ? m_OutlinePen->GetWidth() : HANDLESIZE;
		if (Gradient >= 0){
			points[0] = PointF(first_point.X + width / 2 * cos(seta), first_point.Y + width / 2 * sin(seta));
			points[1] = PointF(first_point.X - width / 2 * cos(seta), first_point.Y - width / 2 * sin(seta));
			points[2] = PointF(second_point.X - width / 2 * cos(seta), second_point.Y - width / 2 * sin(seta));
			points[3] = PointF(second_point.X + width / 2 * cos(seta), second_point.Y + width / 2 * sin(seta));
		}
		else if (Gradient < 0){
			points[0] = PointF(first_point.X - width / 2 * cos(seta), first_point.Y + width / 2 * sin(seta));
			points[1] = PointF(first_point.X + width / 2 * cos(seta), first_point.Y - width / 2 * sin(seta));
			points[2] = PointF(second_point.X + width / 2 * cos(seta), second_point.Y - width / 2 * sin(seta));
			points[3] = PointF(second_point.X - width / 2 * cos(seta), second_point.Y + width / 2 * sin(seta));
		}
		path.AddPolygon(points, count);

		Region rgn(&path);
		if (rgn.IsVisible(point)) {
			return INSIDE;
		}
		first_point = second_point;
	}

	// �ٱ� ����
	return OUTSIDE;
}


// OnDraw
/* �� �׸��� */
void CPolygon::draw(IN Graphics& graphics) {

	// polyLine�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	// Draw the lines.
	m_OutlinePen->SetDashStyle(DashStyleSolid);
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

	// ������ �׸��� �κ� 
	m_OutlinePen->SetDashStyle(DashStyleCustom);
	REAL aDash[] = { 5.0f, 5.0f };
	m_OutlinePen->SetDashPattern(aDash, sizeof(aDash) / sizeof(aDash[0]));

	graphics.DrawLine(m_OutlinePen, m_PointsList.GetTail(), *addingPoint);

	return drawnArea;
}

/* �̵� �׸��� */
RectF CPolygon::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {
	RectF drawnArea;

	/* ���� �̵� �� �� �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;

	// polyLine�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos) + RelativePoint);
	}

	// Draw the lines.
	m_OutlinePen->SetDashStyle(DashStyleCustom);
	REAL aDash[] = { 5.0f, 5.0f };
	m_OutlinePen->SetDashPattern(aDash, sizeof(aDash) / sizeof(aDash[0]));

	graphics.DrawLines(m_OutlinePen, pointsArray.GetData(), pointsArray.GetSize());


	///* ���� ��ǥ���� ��� ��ǥ�� ������ ���� �̵� ��� ��ǥ�� �ȴ�. */
	//CList <PointF, PointF&> tmp_List;

	//POSITION pos = m_PointsList.GetHeadPosition();
	//while (pos!=NULL){
	//	PointF  point = m_PointsList.GetNext(pos);
	//	graphics.DrawLine(m_OutlinePen, tmp_List.GetTail(), point + RelativePoint);

	//	// ������ �׸��� �κ� 
	//	tmp_List.AddTail(point+RelativePoint);
	//}

	return drawnArea;
}

// ���� ��ǥ �̵� �׸���
RectF CPolygon::pointMoving(Graphics& graphics, IN PointF originPoint, IN PointF targetPoint){

	RectF drawnArea;

	PointF  point;

	// polyLine�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
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

	// ������ �׸��� �κ� 
	m_OutlinePen->SetDashStyle(DashStyleCustom);
	REAL aDash[] = { 5.0f, 5.0f };
	m_OutlinePen->SetDashPattern(aDash, sizeof(aDash) / sizeof(aDash[0]));

	graphics.DrawLines(m_OutlinePen, pointsArray.GetData(), pointsArray.GetSize());

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

	REAL x_start = 0, y_start = 0, x_end = 0, y_end = 0;

	POSITION pos = m_PointsList.GetHeadPosition();
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
