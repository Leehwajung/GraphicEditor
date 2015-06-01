// Line.cpp : CLine Ŭ������ ����
// CLine : ���� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Line.h"


IMPLEMENT_SERIAL(CLine, CStrap, 1)

CLine::CLine()
:CStrap()
, isStartingpoint(FALSE), isEndingpoint(FALSE)
{
	//m_LinePen	
}

CLine::CLine(IN CClientDC* lpClientDC)
	: CStrap(lpClientDC)
	, isStartingpoint(FALSE), isEndingpoint(FALSE)
{
}

CLine::CLine(IN Graphics* lpGraphics)
	: CStrap(lpGraphics)
	, isStartingpoint(FALSE), isEndingpoint(FALSE)
{
}

CLine::CLine(IN CClientDC* lpClientDC, IN Pen* pen)
	: CStrap(lpClientDC)
	, isStartingpoint(FALSE), isEndingpoint(FALSE)
{
}

CLine::CLine(IN Graphics* lpGraphics, IN Pen* pen)
	: CStrap(lpGraphics)
	, isStartingpoint(FALSE), isEndingpoint(FALSE)
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

	m_EndPoint = *endingPoint;
	m_Gradient = (startingPoint->Y - m_EndPoint.Y) / (startingPoint->X - m_EndPoint.X);

	m_Area.X = startingPoint->X;
	m_Area.Y = startingPoint->Y;
	m_Area.Width = abs(startingPoint->X - m_EndPoint.X);
	m_Area.Height = abs(startingPoint->Y - m_EndPoint.Y);

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

}

/* �� ũ��(����) ���� */
void CLine::resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	if (isStartingpoint == TRUE){
		m_StartingPoint = targetPoint;
		isStartingpoint = FALSE;
	}
	else if(isEndingpoint == TRUE){
		m_EndPoint = targetPoint;
		isEndingpoint = FALSE;
	}

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
	if (point.Equals(m_StartingPoint) == TRUE || point.Equals(m_EndPoint) == TRUE){

		if (point.Equals(m_StartingPoint) == TRUE)
			isStartingpoint = TRUE;

		else if (point.Equals(m_EndPoint) == TRUE)
			isEndingpoint = TRUE;

		return ONHANDLE;
	}

	// 2. ���� ��ǥ�� ���� �ִ� ������ ���� �� ������ ���� ����� ���� ���� INSIDE("Move���") �̴�.
	else if (m_Area.GetLeft() <= point.X && point.X <= m_Area.GetRight() || m_Area.GetRight() <= point.X && point.X <= m_Area.GetLeft()){
		if (m_Area.GetTop() <= point.Y && point.Y <= m_Area.GetBottom() || m_Area.GetBottom() <= point.Y && point.Y <= m_Area.GetTop()){

			// ���� ���� ��ǥ�� StartingPoint���� ���⸦ ���� ���̴�.
			int tmp_gradient = (m_StartingPoint.Y - point.Y) / (m_StartingPoint.X - point.X);

			if (tmp_gradient == m_Gradient)
				return INSIDE;
		}
		return OUTSIDE;

	}

	// �� ��: �ƹ� ��嵵 �ƴ�
	else OUTSIDE;
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
void CLine::draw() {
	m_lpGraphics->DrawLine(m_OutlinePen, m_StartingPoint, m_EndPoint);
}

// OnMouseMove
/* ���� �׸��� */
void CLine::creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/) {
	
	creating(&startingPoint,&targetPoint,createFlag);
	
}

/* ���� �׸��� */
void CLine::creating(void* param1, ...) {
	va_list vaList;
	va_start(vaList,param1);
	PointF* startingPoint = (PointF*)param1;
	PointF* targetPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	m_lpGraphics->DrawLine(m_OutlinePen, *startingPoint, *targetPoint);
}

/* �̵� �׸��� */
void CLine::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	/* ���� �̵� �� �� �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;

	/* ���� ��ǥ���� ��� ��ǥ�� ������ ���� �̵� ��� ��ǥ�� �ȴ�. */
	m_lpGraphics->DrawLine(m_OutlinePen, m_StartingPoint + RelativePoint, m_EndPoint + RelativePoint);
}

/* ũ�� ���� �׸��� */
void CLine::resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {
	if (isStartingpoint == TRUE){
		m_lpGraphics->DrawLine(m_OutlinePen, targetPoint, m_EndPoint);
}
	else{
		m_lpGraphics->DrawLine(m_OutlinePen, m_StartingPoint, targetPoint);
	}
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
void CLine::resetArea() {

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



