// PolyLine.cpp : CPolyLine Ŭ������ ����
// CPolyLine : �������� ��ü�� �����ϴ� Ŭ����
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
void CPolyLine::addPoint(PointF addingPoint){
	m_PointsList.AddTail(addingPoint);
}
//LButtonDlk
/* ���� �Ϸ� */
BOOL CPolyLine::create(IN CreateFlag createFlag/* = FREECREATE*/){
	return create(createFlag);
}

/* ���� �Ϸ� */
BOOL CPolyLine::create(void* param1, ...) {

	va_list vaList;
	va_start(vaList, param1);
	CreateFlag* createFlag = (CreateFlag*)param1;
	va_end(vaList);

	REAL x_start=0,y_start=0,width=0,height=0;

	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = m_PointsList.GetNext(pos);

		// m_Area ���� �� ����. List�� ���Ұ� �߰��� ������ ���� �Ǿ�� �Ѵ�. 
		if (x_start >= tmp_point.X)
			x_start = tmp_point.X;

		if (y_start >= tmp_point.Y)
			y_start = tmp_point.Y;

		// m_Area �ʺ�, ���� ���� 
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

/* ��ü �̵� */
void CPolyLine::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	/* �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;


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

		if (tmp_point.Equals(point) == TRUE)
			return ONHANDLE;
	}

	// 2. ���� ��ǥ�� ���� �ִ� ������ ���� �� INSIDE�̴�.
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

				// ���� ���� ��ǥ�� StartingPoint���� ���⸦ ���� ���̴�.
				int tmp_gradient = abs(first_point.Y - point.Y) / abs(first_point.X - point.X);

				if (tmp_gradient == Gradient)
					return INSIDE;
			}
		}

	}

	// �ٱ� ����
	return OUTSIDE;
}


// OnDraw
/* �� �׸��� */
void CPolyLine::draw(IN Graphics* lpGraphics) {
}

// OnMouseMove
/* ���� �׸��� */
void CPolyLine::creating(IN Graphics* lpGraphics, IN PointF addingPoint, IN CreateFlag createFlag/* = FREECREATE*/){
	creating(lpGraphics, &addingPoint, createFlag);
}

/* ���� �׸��� */
void CPolyLine::creating(IN Graphics* lpGraphics, void* param1, ...) {
	va_list vaList;
	va_start(vaList, param1);
	PointF* addingPoint = (PointF*)param1;
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	lpGraphics->DrawLine(m_OutlinePen, m_PointsList.GetTail(),*addingPoint);

}

/* �̵� �׸��� */
void CPolyLine::moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/) {

	/* ���� �̵� �� �� �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;

	/* ���� ��ǥ���� ��� ��ǥ�� ������ ���� �̵� ��� ��ǥ�� �ȴ�. */
	/*CList <PointF, PointF&> PolyLineList = m_PointsList;

	POSITION pos = PolyLineList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = PolyLineList.GetNext(pos);
	    
	}*/

}

/* ũ�� ���� �׸��� */
void CPolyLine::resizing(IN Graphics* lpGraphics, IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/) {

}

// ���� �۾� �Ŀ� ȣ��
/* ��ü ���� ���� */
void CPolyLine::resetArea() {


	
}

void addPoint(PointF addingpoint){

}

