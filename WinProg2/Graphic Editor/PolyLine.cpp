// PolyLine.cpp : CPolyLine Ŭ������ ����
// CPolyLine : �������� ��ü�� �����ϴ� Ŭ����
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "PolyLine.h"


// CPolyLine

IMPLEMENT_SERIAL(CPolyLine, CStrap, 1)

CPolyLine::CPolyLine()
:CStrap(), m_CreatedFlag(FALSE)
{
}

CPolyLine::CPolyLine(IN Pen* pen)
: CStrap(pen), m_CreatedFlag(FALSE)
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
	if (m_CreatedFlag == FALSE)
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

		m_CreatedFlag = TRUE;
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

}

/* �� ũ��(����) ���� */
void CPolyLine::resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {


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

		REAL tmp_seta = atan(-1 / Gradient);
		REAL seta = 90 - tmp_seta;

		PointF points[count];
		GraphicsPath path;
		if (Gradient >= 0){
			points[0] = PointF(first_point.X + HANDLESIZE / 2 * cos(seta), first_point.Y + HANDLESIZE / 2 * sin(seta));
			points[1] = PointF(first_point.X - HANDLESIZE / 2 * cos(seta), first_point.Y - HANDLESIZE / 2 * sin(seta));
			points[2] = PointF(second_point.X - HANDLESIZE / 2 * cos(seta), second_point.Y - HANDLESIZE / 2 * sin(seta));
			points[3] = PointF(second_point.X + HANDLESIZE / 2 * cos(seta), second_point.Y + HANDLESIZE / 2 * sin(seta));
		}
		else if (Gradient < 0){
			points[0] = PointF(first_point.X - HANDLESIZE / 2 * cos(seta), first_point.Y + HANDLESIZE / 2 * sin(seta));
			points[1] = PointF(first_point.X + HANDLESIZE / 2 * cos(seta), first_point.Y - HANDLESIZE / 2 * sin(seta));
			points[2] = PointF(second_point.X + HANDLESIZE / 2 * cos(seta), second_point.Y - HANDLESIZE / 2 * sin(seta));
			points[3] = PointF(second_point.X - HANDLESIZE / 2 * cos(seta), second_point.Y + HANDLESIZE / 2 * sin(seta));
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
void CPolyLine::draw(IN Graphics* lpGraphics) {

	// ��ȸ�� �ϸ鼭 PolyLine�� �׷��ش�. 
	//POSITION pos = m_PointsList.GetHeadPosition();
	//while (pos != NULL){
	//	PointF  point = m_PointsList.GetNext(pos);
	//	lpGraphics->DrawLine(m_OutlinePen, m_PointsList.GetAt(pos), point);
	//}

	//POSITION pos = m_PointsList.GetHeadPosition();	// ����Ʈ�� ó��
	////pDC->MoveTo(m_PointsList.GetHead());			// ��� ù ��ǥ�� �̵�
	//
	//CArray<PointF, PointF&> pointsArray;

	//for (POSITION pos = m_PointsList.GetHeadPosition(); !pos ; m_PointsList.GetNext(pos)) {
	//	pointsArray.Add(m_PointsList.GetAt(pos));
	//}

	//lpGraphics->DrawLines(m_OutlinePen, pointsArray.GetData(), pointsArray.GetSize());
	//while (pos ? lpGraphics->DrawLine(m_OutlinePen, m_PointsList.GetAt(pos), m_PointsList.GetNext(pos)) : FALSE);	// ���� ��ǥ�� �̵��ϸ� �� �׸���

	// Create an array of PointF objects that define the lines to draw.
	PointF point1(10.0f, 10.0f);
	PointF point2(10.0f, 100.0f);
	PointF point3(200.0f, 50.0f);
	PointF point4(250.0f, 300.0f);

	PointF points[4] = { point1, point2, point3, point4 };
	PointF* pPoints = points;
	////////////////////////////
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos ; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	// Draw the lines.
	lpGraphics->DrawLines(m_OutlinePen, pointsArray.GetData(), pointsArray.GetSize());

}

// OnMouseMove
/* ���� �׸��� */
RectF CPolyLine::creating(IN Graphics* lpGraphics, IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){

	return creating(lpGraphics, &addingPoint, createFlag);
}

/* ���� �׸��� */
RectF CPolyLine::creating(IN Graphics* lpGraphics, void* param1, ...) {
	va_list vaList;
	va_start(vaList, param1);
	PointF* addingPoint = (PointF*)param1;
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	RectF drawnArea;

	// ������ �׸��� �κ� 
	lpGraphics->DrawLine(m_OutlinePen, m_PointsList.GetTail(),*addingPoint);

	return drawnArea;
}

/* �̵� �׸��� */
RectF CPolyLine::moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	RectF drawnArea;

	/* ���� �̵� �� �� �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;

	/* ���� ��ǥ���� ��� ��ǥ�� ������ ���� �̵� ��� ��ǥ�� �ȴ�. */
	CList <PointF, PointF&> tmp_List;

	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos!=NULL){
		PointF  point = m_PointsList.GetNext(pos);
		lpGraphics->DrawLine(m_OutlinePen, tmp_List.GetTail(), point + RelativePoint);

		// ������ �׸��� �κ� 
		tmp_List.AddTail(point+RelativePoint);
	}

	return drawnArea;
}
	    
// ���� ��ǥ �̵� �׸���
RectF CPolyLine::pointMoving(Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint){
	
	RectF drawnArea;

	CList <PointF, PointF&> tmp_List;

	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  point = m_PointsList.GetNext(pos);

		RectF handleRect;
		handleRect = getHandleRect(point);

		if (handleRect.Contains(originPoint)){
			point = targetPoint;
			tmp_List.AddTail(point);

		}
		else tmp_List.AddTail(point);

		// ������ �׸��� �κ� 
		lpGraphics->DrawLine(m_OutlinePen, tmp_List.GetTail(), point);
	}		

	return drawnArea;
}

/* ũ�� ���� �׸��� */
RectF CPolyLine::resizing(IN Graphics* lpGraphics, IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	RectF drawnArea;



	return drawnArea;
}

// ���� �۾� �Ŀ� ȣ��
/* ��ü ���� ���� */
RectF CPolyLine::resetArea() {

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


	m_Area.X = x_start;
	m_Area.Y = y_start;
	m_Area.Width = abs(x_start - x_end);
	m_Area.Height = abs(y_start - y_end);

	return m_Area;
}

BOOL CPolyLine::GetCreatedFlag(){
	return m_CreatedFlag;
}


