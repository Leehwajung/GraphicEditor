// Ellipse.cpp : CEllipse Ŭ������ ����
// CEllipse : Ÿ�� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Ellipse.h"


// CEllipse

IMPLEMENT_SERIAL(CEllipse, CShape, 1)


CEllipse::CEllipse()
: CShape()
{
}
CEllipse::CEllipse(IN CClientDC* lpClientDC) : CShape(lpClientDC)
{}
CEllipse::CEllipse(IN Graphics* lpGraphics) : CShape(lpGraphics)
{}
CEllipse::CEllipse(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush) : CShape(lpClientDC, pen, brush)
{}
CEllipse::CEllipse(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush)
	: CShape(lpGraphics, pen, brush)
{}
CEllipse::CEllipse(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush, IN RectF rect)
	: CShape(lpClientDC, pen, brush)
, m_Rect(rect)
{}

CEllipse::~CEllipse()
{
}

// CEllipse ��� �Լ�
/* ���� */
BOOL CEllipse::create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag/* = FREECREATE*/)
{
	return create(&startingPoint, &endingPoint, createFlag);	 // �ӽ� ��ȯ ��
}
BOOL CEllipse::create(void* param1, ...)
{
	va_list vaList;
	va_start(vaList, param1);
	PointF* startingPoint = (PointF*)param1;
	PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	SizeF rectSize;
	rectSize.Width = startingPoint->X > endingPoint->X ? 
		startingPoint->X - endingPoint->X : endingPoint->X - startingPoint->X;
	rectSize.Height = startingPoint->Y > endingPoint->Y ? 
		startingPoint->Y - endingPoint->Y : endingPoint->Y - startingPoint->Y;

	if (startingPoint->X > endingPoint->X) {
		startingPoint->X = endingPoint->X;
	}

	if (startingPoint->Y > endingPoint->Y) {
		startingPoint->Y = endingPoint->Y;
	}

	m_Rect = RectF(*startingPoint, rectSize);

	resetArea();

	return FALSE;
}

void CEllipse::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	// originPoint: ButtonDown
	// targetPoint: ButtonUp

	PointF offset = targetPoint - originPoint;

	m_Rect.Offset(offset);
	resetArea();
}
void CEllipse::resize(IN Position selectedHandle, IN PointF targetPoint,
	IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	/*PointF AP;

	if (anchorPoint == NULL){
		getHandlePoint(getOppositeHandle(selectedHandle), &AP);
		anchorPoint = &AP;
	}*/
	switch (selectedHandle)
	{
	case CFigure::TOPLEFT:

		break;

	case CFigure::TOP:

		break;

	case CFigure::TOPRIGHT:

		break;

	case CFigure::RIGHT:

		break;

	case CFigure::BOTTOMRIGHT:

		break;

	case CFigure::BOTTOM:

		break;

	case CFigure::BOTTOMLEFT:

		break;

	case CFigure::LEFT:

		break;

	default:
		return;
	}

	resetArea();//area������.
	

}

void CEllipse::destroy(){}
// Position: Ÿ�� ���� ���� ��ġ
CFigure::Position CEllipse::pointInFigure(IN PointF point){
	RectF handleRect;

	for (int handleIndex = TOPLEFT; handleIndex <= LEFT; handleIndex++) {

		getHandleRect((Position)handleIndex, &handleRect);
		if (handleRect.Contains(point)) {
			return (Position)handleIndex;
		}
	}

	if (m_Rect.Contains(point)) {
		return INSIDE;
	}

	return OUTSIDE;
}
// Ellipse �ܰ��� �׸��� �� ä���
void CEllipse::draw(){
	m_lpGraphics->FillEllipse(m_FillBrush, m_Rect); // ellipse ä���
	m_lpGraphics->DrawEllipse(m_OutlinePen, m_Rect); // �׷��Ȱ�ü�� drawellipse �Լ�
}

// ���� �ÿ� ������ �׸���
// - IN �Ű�����
//		PointF startingPoint: ���� ���� ��ǥ
//		PointF targetPoint: ���� �� ���� ���� ��ǥ
//		CreateFlag createFlag = FREECREATE: ���� ���� �÷���
 void CEllipse::creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/)
 {
	 creating(&startingPoint, &targetPoint, createFlag);
 }

 void  CEllipse::creating(void* param1, ...)
 {
	 va_list vaList;
	 va_start(vaList, param1);
	 PointF* startingPoint = (PointF*)param1;
	 PointF* targetPoint = va_arg(vaList, PointF*);
	 CreateFlag createFlag = va_arg(vaList, CreateFlag);
	 va_end(vaList);
 }

 // �̵� �׸���
 // �̵� �߿� ������ �׸���
 // - IN �Ű�����
 //		PointF originPoint: �̵��� ���� ��ǥ
 //		PointF targetPoint: �̵� ���� ��ǥ
 //		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
 void  CEllipse::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
 {

 }

 // ũ�� ���� �׸���
 // ũ�� ���� �߿� ������ �׸���
 // - IN �Ű�����
 //		Position selectedHandle: ��ü�� ���õ� �ڵ�
 //		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
 //		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
 //		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
 void  CEllipse::resizing(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
 {

 }

 /* ��ü ���� ���� */
 // ��ü ���� ����
 void  CEllipse::resetArea(){
	 m_Area = m_Rect;
 }

void CEllipse::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
