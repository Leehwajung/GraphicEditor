// Line.cpp : CLine Ŭ������ ����
// CLine : ���� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Line.h"
#define _USE_MATH_DEFINES
#include "math.h"
#define INFINITE 100000


IMPLEMENT_SERIAL(CLine, CStrap, 1)

CLine::CLine()
	: CStrap()
{
	//m_LinePen	
}

CLine::CLine(IN Pen* pen)
	: CStrap(pen)
{

}

CLine::CLine(IN Pen* pen, PointF startingPoint, PointF endingPoint)
	: CStrap(pen)
	, m_StartingPoint(startingPoint)
	, m_EndPoint(endingPoint)
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
/* ���� �Ϸ� */
BOOL CLine::create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag/* = FREECREATE*/) {
	return create(&startingPoint, &endingPoint, createFlag);
}

/* ���� �Ϸ� */
BOOL CLine::create(void* param1, ...) {

	va_list vaList;
	va_start(vaList, param1);
	PointF* startingPoint = (PointF*)param1;
	PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	m_StartingPoint = *startingPoint;
	m_EndPoint = *endingPoint;
	m_Gradient = (startingPoint->X == m_EndPoint.X) ? INFINITE:(startingPoint->Y - m_EndPoint.Y) / (startingPoint->X - m_EndPoint.X);

	resetArea();

	return FALSE;
}

/* ���� �Ϸ� */
//void CLine::endCreate(PointF point) {
//	m_EndPoint = point;
//	m_Gradient = (m_StartingPoint.Y - m_EndPoint.Y) / (m_StartingPoint.X - m_EndPoint.X);
//
//	m_Area.X = m_StartingPoint.X;
//	m_Area.Y = m_StartingPoint.Y;
//	m_Area.Width = abs(m_StartingPoint.X - m_EndPoint.X);
//	m_Area.Height = abs(m_StartingPoint.Y - m_EndPoint.Y);
//}

/* ��ü �̵� */
void CLine::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {
	/* �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;

	m_StartingPoint = m_StartingPoint + RelativePoint;
	m_EndPoint = m_EndPoint + RelativePoint;

	m_Gradient = (m_StartingPoint.X == m_EndPoint.X) ? INFINITE : (m_StartingPoint.Y - m_EndPoint.Y) / (m_StartingPoint.X - m_EndPoint.X);
}

// ���� ��ǥ �̵�
void CLine::pointMove(IN PointF originPoint, IN PointF targetPoint)
{
	RectF handleRect;

	getHandleRect(START, &handleRect);
	if (handleRect.Contains(originPoint))
		m_StartingPoint = targetPoint;

	getHandleRect(END, &handleRect);
	if (handleRect.Contains(originPoint))
		m_EndPoint = targetPoint;

	m_Gradient = (m_StartingPoint.X == m_EndPoint.X) ? INFINITE : (m_StartingPoint.Y - m_EndPoint.Y) / (m_StartingPoint.X - m_EndPoint.X);
}

/* �� ũ��(����) ���� */
void CLine::resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {

}

// Menu Item
/* �� ���� */
void CLine::destroy() {

	if (this) {
		this->~CLine();
	}
	//invalidate �ٸ� �͵��� �ϴ� ����
}


// LButtonDown 
/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
CFigure::Position CLine::pointInFigure(IN PointF point) {

	// 1. ���� ��ǥ��  ���� StartingPoint�� EndPoint�̸� ONHANDLE("Resize���") �̴�. 
	RectF handleRect;
	getHandleRect(START, &handleRect);
	if (handleRect.Contains(point))
		return START;

	getHandleRect(END, &handleRect);
	if (handleRect.Contains(point))
		return END;

	// 2. ���� ��ǥ�� ���� �ִ� ������ ���� �� ������ ���� ����� ���� ���� INSIDE("Move���") �̴�.		


	const int count = 4;


	REAL tmp_seta = atan(-1 / m_Gradient);
	REAL seta = 90 - tmp_seta;

	PointF points[count];
	GraphicsPath path;
	int width = (m_OutlinePen->GetWidth() > HANDLESIZE) ? m_OutlinePen->GetWidth() : HANDLESIZE;
	if (m_Gradient >= 0){
	points[0] = PointF(m_StartingPoint.X + width / 2 * cos(seta), m_StartingPoint.Y + width / 2 * sin(seta));
	points[1] = PointF(m_StartingPoint.X - width / 2 * cos(seta), m_StartingPoint.Y - width / 2 * sin(seta));
	points[2] = PointF(m_EndPoint.X - width / 2 * cos(seta), m_EndPoint.Y - width / 2 * sin(seta));
	points[3] = PointF(m_EndPoint.X + width / 2 * cos(seta), m_EndPoint.Y + width / 2 * sin(seta));
	}
	else if (m_Gradient < 0){
		points[0] = PointF(m_StartingPoint.X - width / 2 * cos(seta), m_StartingPoint.Y + width / 2 * sin(seta));
		points[1] = PointF(m_StartingPoint.X + width / 2 * cos(seta), m_StartingPoint.Y - width / 2 * sin(seta));
		points[2] = PointF(m_EndPoint.X + width / 2 * cos(seta), m_EndPoint.Y - width / 2 * sin(seta));
		points[3] = PointF(m_EndPoint.X - width / 2 * cos(seta), m_EndPoint.Y + width / 2 * sin(seta));
	}
    path.AddPolygon(points, count);
	Region rgn(&path);
	if (rgn.IsVisible(point)) {
		return INSIDE;
	}

	return OUTSIDE;
}

///* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ��� */
// pointInFigure�� �����ϴ� �Լ�
//CFigure::operationModeFlags CLine::cursorPosition(PointF point) {
//
//	// 1. ���� ��ǥ��  ���� StartingPoint�� EndPoint�̸� "Resize���" �̴�. 
//	if (point.Equals(m_StartingPoint) == TRUE || point.Equals(m_EndPoint) == TRUE){
//		if (point.Equals(m_StartingPoint) == TRUE)
//			isStartingpoint = TRUE;
//
//		return Resize;
//	}
//
//	// 2. ���� ��ǥ�� ���� �ִ� ������ ���� �� ������ ���� ����� ���� ���� "Move���" �̴�.
//	else if (m_Area.GetLeft() <= point.X && point.X <= m_Area.GetRight() || m_Area.GetRight() <= point.X && point.X <= m_Area.GetLeft()){
//		if (m_Area.GetTop() <= point.Y && point.Y <= m_Area.GetBottom() || m_Area.GetBottom() <= point.Y && point.Y <= m_Area.GetTop()){
//
//			// ���� ���� ��ǥ�� StartingPoint���� ���⸦ ���� ���̴�.
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
//	// �� ��: �ƹ� ��嵵 �ƴ�
//	else None;
//}

/* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
//CFigure::operationModeFlags CLine::cursorPosition(RectF rect) {
//	return None;
//}

/* �� ����*/
//void CLine::create(PointF startingPoint)
//{
//		// ������ ���� ���� �� ���� ����� ���⶧���� ���� ��ǥ�� ����ϱ�� ��.
//		this->m_StartingPoint = startingPoint;
//}


// OnDraw
/* �� �׸��� */
void CLine::draw(IN Graphics* lpGraphics) {
	m_OutlinePen->SetDashStyle(DashStyleSolid);
	lpGraphics->DrawLine(m_OutlinePen, m_StartingPoint, m_EndPoint);
}

// OnMouseMove
/* ���� �׸��� */
RectF CLine::creating(IN Graphics* lpGraphics, IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/) {
	
	return creating(lpGraphics, &startingPoint, &targetPoint, createFlag);
	
}

/* ���� �׸��� */
RectF CLine::creating(IN Graphics* lpGraphics, void* param1, ...) {
	
	RectF drawnArea;

	va_list vaList;
	va_start(vaList,param1);
	PointF* startingPoint = (PointF*)param1;
	PointF* targetPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);


	drawnArea.Width = abs(startingPoint->X - targetPoint->X);
	drawnArea.Height = abs(startingPoint->Y - targetPoint->Y);

	if (startingPoint->X > targetPoint->X) {
		drawnArea.X = targetPoint->X;
	}
	else {
		drawnArea.X = startingPoint->X;
	}

	if (startingPoint->Y > targetPoint->Y) {
		drawnArea.Y = targetPoint->Y;
	}
	else {
		drawnArea.Y = startingPoint->Y;
	}

	lpGraphics->DrawLine(m_OutlinePen, *startingPoint, *targetPoint);
	return drawnArea;
}

/* �̵� �׸��� */
RectF CLine::moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	RectF drawnArea;

	/* ���� �̵� �� �� �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;

	/* ���� ��ǥ���� ��� ��ǥ�� ������ ���� �̵� ��� ��ǥ�� �ȴ�. */
	m_OutlinePen->SetDashStyle(DashStyleCustom);
	REAL aDash[] = { 5.0f, 5.0f };
	m_OutlinePen->SetDashPattern(aDash,sizeof(aDash)/sizeof(aDash[0]));
	lpGraphics->DrawLine(m_OutlinePen, m_StartingPoint + RelativePoint, m_EndPoint + RelativePoint);

	return drawnArea;
}

/* ũ�� ���� �׸��� */
RectF CLine::resizing(IN Graphics* lpGraphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	RectF drawnArea;



	return drawnArea;
}

/* ���� ��ǥ �̵� �׸��� */
RectF CLine::pointMoving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint)
{
	RectF drawnArea;

	RectF handleRect;

	m_OutlinePen->SetDashStyle(DashStyleCustom);
	REAL aDash[] = { 5.0f, 5.0f };
	m_OutlinePen->SetDashPattern(aDash, sizeof(aDash) / sizeof(aDash[0]));

	getHandleRect(START, &handleRect);
	if (handleRect.Contains(originPoint))
		lpGraphics->DrawLine(m_OutlinePen, targetPoint, m_EndPoint);

	getHandleRect(END, &handleRect);
	if (handleRect.Contains(originPoint))
		lpGraphics->DrawLine(m_OutlinePen, m_StartingPoint, targetPoint);

	return drawnArea;
}

BOOL CLine::getHandleRect(IN Position handle, OUT RectF* handleRect)
{
	PointF handlePoint;

	switch (handle)
	{
	case CFigure::START:
		handlePoint = m_StartingPoint;
		break;
	case CFigure::END:
		handlePoint = m_EndPoint;
		break;
	default:
		return TRUE;
	}

	*handleRect = CFigure::getHandleRect(handlePoint);

	return FALSE;
}

/* OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�) */
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

// ���� �۾� �Ŀ� ȣ��
/* ��ü ���� ���� */
RectF CLine::resetArea() {

	m_Area.Width = abs(m_StartingPoint.X - m_EndPoint.X);
	m_Area.Height = abs(m_StartingPoint.Y - m_EndPoint.Y);

	if (m_StartingPoint.X > m_EndPoint.X) {
		m_Area.X = m_EndPoint.X;
	}
	else {
		m_Area.X = m_StartingPoint.X;
	}

	if (m_StartingPoint.Y > m_EndPoint.Y) {
		m_Area.Y = m_EndPoint.Y;
	}
	else {
		m_Area.Y = m_StartingPoint.Y;
	}

	return m_Area;
}




// �Ӽ��� ���� �κ��� Property class�� �̿��ϱ�� ����
// �� �κ��� CStrap���� ������ �� ������
///* �� �� ���� */
//BOOL CLine::setLineColor(const Color& LineColor) {
//	m_LineColor = LineColor;
//}
//
///* �� �β� ���� */
//BOOL CLine::setLineWidth(const REAL& LineWidth) {
//	 m_LineWidth = LineWidth;
//}
//
///* �� ���� ���� */
//BOOL CLine::setLinePattern(const DashStyle& LinePattern) {
//	m_LinePattern = LinePattern;
//}



