// PolyLine.cpp : CPolyLine Ŭ������ ����
// CPolyLine : �������� ��ü�� �����ϴ� Ŭ����
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


// CPolyLine ��� �Լ�


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
/* ���� �Ϸ� */
BOOL CPolyLine::create(IN CreateFlag createFlag/* = FREECREATE*/){
	return create(&createFlag);
}

/* ���� �Ϸ� */
BOOL CPolyLine::create(void* param1, ...) {
		va_list vaList;
		va_start(vaList, param1);
		CreateFlag* createFlag = (CreateFlag*)param1;
		va_end(vaList);

		//m_CreatedFlag = TRUE;
		resetArea();

		return FALSE;
}

/* ��ü �̵� */
void CPolyLine::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

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
	resetArea();
}

// ���� ��ǥ ����
void CPolyLine::RemovePoint(IN PointF originPoint){
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

void CPolyLine::InsertPoint(IN PointF originPoint){

	POSITION pos = m_PointsList.GetHeadPosition();
	POSITION prevpos = m_PointsList.GetHeadPosition();
	PointF first_point = m_PointsList.GetNext(pos);

	while (pos != NULL){
		prevpos = pos;
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
		if (rgn.IsVisible(originPoint)){
			m_PointsList.InsertBefore(prevpos, originPoint);
			resetArea();
			return;
		}
		first_point = second_point;
		
	}

}

/* �� ũ��(����) ���� */
void CPolyLine::resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	/*m_Area.;

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
	resetArea();*/
}

// Menu Item
/* �� ���� */
void CPolyLine::destroy() {

	if (this) {
		this->~CPolyLine();
	}
	//invalidate �ٸ� �͵��� �ϴ� ����
}


// LButtonDown 
/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
CFigure::Position CPolyLine::pointInFigure(IN PointF point) {

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

	// �ٱ� ����
	return OUTSIDE;
}


// OnDraw
/* �� �׸��� */
void CPolyLine::draw(IN Graphics& graphics) {

	// polyLine�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos ; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	// Draw the lines.
	graphics.DrawLines(m_OutlinePen, pointsArray.GetData(), pointsArray.GetSize());

}

// OnMouseMove
/* ���� �׸��� */
RectF CPolyLine::creating(IN Graphics& graphics, IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){

	return creating(graphics, &addingPoint, &createFlag);
}

/* ���� �׸��� */
RectF CPolyLine::creating(IN Graphics& graphics, void* param1, ...) {
	va_list vaList;
	va_start(vaList, param1);
	PointF* addingPoint = (PointF*)param1;
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	RectF drawnArea;

	// ������ �׸��� �κ� 
		
	graphics.DrawLine(CGlobal::crateIngPen(m_OutlinePen), m_PointsList.GetTail(), *addingPoint);

	return drawnArea;
}

/* �̵� �׸��� */
RectF CPolyLine::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {
	RectF drawnArea;

	/* ���� �̵� �� �� �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;

	// polyLine�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos) + RelativePoint);
	}

	// Draw the lines.
	graphics.DrawLines(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());

	return drawnArea;
}
	    
// ���� ��ǥ �̵� �׸���
RectF CPolyLine::pointMoving(Graphics& graphics, IN PointF originPoint, IN PointF targetPoint){

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

		for (int i = 0; i < HandleRectArray.GetSize()-1; i++){
			for (int j = i+1; j < HandleRectArray.GetSize();j++)
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

	graphics.DrawLines(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());

	return drawnArea;
}

/* ũ�� ���� �׸��� */
RectF CPolyLine::resizing(IN Graphics& graphics, IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	RectF drawnArea;

	// �׸��� �� ���� �� ���� �Ͽ��ϵ���: CGlobal::crateIngPen(m_OutlinePen)
	
	return drawnArea;
}

/* ���� (�ڵ�) �׸��� */
void CPolyLine::drawArea(IN Graphics& graphics) {
	CFigure::drawArea(graphics);
}

void CPolyLine::drawLineHandle(IN Graphics& graphics){
	CArray <PointF, PointF&> pointsArray;

	Pen pen(Color::Gray);
	pen.SetDashStyle(DashStyleDot);

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	graphics.DrawLines(&pen, pointsArray.GetData(), pointsArray.GetSize());

	drawHandles(graphics, pointsArray.GetData(), pointsArray.GetSize());
}

// ���� �۾� �Ŀ� ȣ��
/* ��ü ���� ���� */
RectF CPolyLine::resetArea() {

	REAL x_start, y_start, x_end = 0, y_end = 0;
	
	POSITION pos = m_PointsList.GetHeadPosition();
	x_start= m_PointsList.GetHead().X;
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

CList <PointF, PointF&>& CPolyLine::GetPointsList(){
	return m_PointsList;
}

