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

CEllipse::CEllipse(IN Pen* pen, IN BrushPtr brush)
	: CShape(pen, brush)
{}

CEllipse::CEllipse(IN Pen* pen, IN BrushPtr brush, IN RectF rect)
	: CShape(pen, brush)
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
	PointF startingPoint;
	PointF fixedPoint;
	getHandlePoint(getOppositeHandle(selectedHandle), &fixedPoint);

	SizeF rectSize;

	switch (selectedHandle)
	{
	case CFigure::TOPLEFT:
	case CFigure::TOPRIGHT:
	case CFigure::BOTTOMRIGHT:
	case CFigure::BOTTOMLEFT:
		rectSize.Width = fixedPoint.X > targetPoint.X ?
			fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
		rectSize.Height = fixedPoint.Y > targetPoint.Y ?
			fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;

		if (fixedPoint.X > targetPoint.X) {
			startingPoint.X = targetPoint.X;
		}
		else {
			startingPoint.X = fixedPoint.X;
		}

		if (fixedPoint.Y > targetPoint.Y) {
			startingPoint.Y = targetPoint.Y;
		}
		else {
			startingPoint.Y = fixedPoint.Y;
		}

		break;

	case CFigure::TOP:
	case CFigure::BOTTOM:
		rectSize.Width = m_Rect.Width;
		rectSize.Height = fixedPoint.Y > targetPoint.Y ?
			fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;

		startingPoint.X = m_Rect.X;

		if (fixedPoint.Y > targetPoint.Y) {
			startingPoint.Y = targetPoint.Y;
		}
		else {
			startingPoint.Y = fixedPoint.Y;
		}

		break;

	case CFigure::RIGHT:
	case CFigure::LEFT:
		rectSize.Width = fixedPoint.X > targetPoint.X ?
			fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
		rectSize.Height = m_Rect.Height;

		if (fixedPoint.X > targetPoint.X) {
			startingPoint.X = targetPoint.X;
		}
		else {
			startingPoint.X = fixedPoint.X;
		}

		startingPoint.Y = m_Rect.Y;

		break;

	default:
		// �߸��� selectedHandle
		// �ƹ� ������ ���� ����
		return;
	}

	m_Rect = RectF(startingPoint, rectSize);

	resetArea();
	
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
void CEllipse::draw(IN Graphics* lpGraphics){
	lpGraphics->FillEllipse(m_FillBrush, m_Rect); // ellipse ä���
	lpGraphics->DrawEllipse(m_OutlinePen, m_Rect); // �׷��Ȱ�ü�� drawellipse �Լ�
}

// ���� �ÿ� ������ �׸���
// - IN �Ű�����
//		PointF startingPoint: ���� ���� ��ǥ
//		PointF targetPoint: ���� �� ���� ���� ��ǥ
//		CreateFlag createFlag = FREECREATE: ���� ���� �÷���
void CEllipse::creating(IN Graphics* lpGraphics, IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/)
 {
	 creating(lpGraphics, &startingPoint, &targetPoint, createFlag);
 }

void  CEllipse::creating(IN Graphics* lpGraphics, void* param1, ...)
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
void  CEllipse::moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
 {
	 RectF rect = m_Rect;
	 if (moveFlag == FREEMOVE)//�����̵� case�� ��
	 {
		 PointF offset = targetPoint - originPoint;
		 rect.Offset(offset);
		 lpGraphics->FillEllipse(m_FillBrush, rect); // ellipse ä���
		 lpGraphics->DrawEllipse(m_OutlinePen, rect);
	 }
	 else//!=FREEMOVE�� case
	 {
		 PointF ratio;
		 ratio.X = rect.GetLeft();
		 ratio.Y = rect.GetTop();
		 // �¿� �̵�
		 if (targetPoint.X - ratio.X >= targetPoint.Y - ratio.Y){
			 PointF offset;
			 offset.X = targetPoint.X - originPoint.X;
			 offset.Y = originPoint.Y;
			 rect.Offset(offset);
			 lpGraphics->FillEllipse(m_FillBrush, rect); // ellipse ä���
			 lpGraphics->DrawEllipse(m_OutlinePen, rect);
		 }
		 else// �����̵�
		 {

			 PointF offset;
			 offset.X = originPoint.X;
			 offset.Y = targetPoint.Y - originPoint.Y;
			 rect.Offset(offset);
			 lpGraphics->FillEllipse(m_FillBrush, rect); // ellipse ä���
			 lpGraphics->DrawEllipse(m_OutlinePen, rect);
		 }
	 }
 }

 // ũ�� ���� �׸���
 // ũ�� ���� �߿� ������ �׸���
 // - IN �Ű�����
 //		Position selectedHandle: ��ü�� ���õ� �ڵ�
 //		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
 //		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
 //		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
void  CEllipse::resizing(IN Graphics* lpGraphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
 {
	 RectF rect = m_Rect; //temp

	 PointF startingPoint;
	 PointF fixedPoint;
	 PointF Gradeint;
	 getHandlePoint(getOppositeHandle(selectedHandle), &fixedPoint);

	 SizeF rectSize;

	 if(resizeFlag == FREERESIZE){
	switch (selectedHandle)
		 {
		 case CFigure::TOPLEFT:
		 case CFigure::TOPRIGHT:
		 case CFigure::BOTTOMRIGHT:
		 case CFigure::BOTTOMLEFT:
			 rectSize.Width = fixedPoint.X > targetPoint.X ?
				 fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
			 rectSize.Height = fixedPoint.Y > targetPoint.Y ?
				 fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;

			 if (fixedPoint.X > targetPoint.X) {
				 startingPoint.X = targetPoint.X;
			 }
			 else {
				 startingPoint.X = fixedPoint.X;
			 }

			 if (fixedPoint.Y > targetPoint.Y) {
				 startingPoint.Y = targetPoint.Y;
			 }
			 else {
				 startingPoint.Y = fixedPoint.Y;
			 }

			 break;

		 case CFigure::TOP:
		 case CFigure::BOTTOM:
			 rectSize.Width = m_Rect.Width;
			 rectSize.Height = fixedPoint.Y > targetPoint.Y ?
				 fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;

			 startingPoint.X = m_Rect.X;

			 if (fixedPoint.Y > targetPoint.Y) {
				 startingPoint.Y = targetPoint.Y;
			 }
			 else {
				 startingPoint.Y = fixedPoint.Y;
			 }

			 break;

		 case CFigure::RIGHT:
		 case CFigure::LEFT:
			 rectSize.Width = fixedPoint.X > targetPoint.X ?
				 fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
			 rectSize.Height = m_Rect.Height;

			 if (fixedPoint.X > targetPoint.X) {
				 startingPoint.X = targetPoint.X;
			 }
			 else {
				 startingPoint.X = fixedPoint.X;
			 }

			 startingPoint.Y = m_Rect.Y;

			 break;

		 default:
			 // �߸��� selectedHandle
			 // �ƹ� ������ ���� ����
			 return;
		 }
	 }
	 else{
		 switch (selectedHandle)
		 {
			 //
		 case CFigure::TOPLEFT:
		 case CFigure::TOPRIGHT:
		 case CFigure::BOTTOMRIGHT:
		 case CFigure::BOTTOMLEFT:
			 rectSize.Width = fixedPoint.X > targetPoint.X ?
				 fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
			 rectSize.Height = fixedPoint.Y > targetPoint.Y ?
				 fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;
			 
			 // ���Ⱑ ���Ѵ�� 0�� ���̽��� �ɷ���
			 if (targetPoint.X == fixedPoint.X || targetPoint.Y == fixedPoint.Y)
				 break;
			 float t_grad, h_grad, h_oppositegrad;
			 h_grad = rect.Y / rect.X;
			 if (h_grad < 0){
				 h_grad = -h_grad;//�Ʒ� ������ ����
			 }
			 h_oppositegrad = -h_grad;
			 Gradeint = fixedPoint - targetPoint;
			 t_grad = Gradeint.Y / Gradeint.X;

	 
			 if (t_grad <= h_grad && t_grad >= h_oppositegrad)// x����������
			 {
				 startingPoint.X = targetPoint.X;
				 startingPoint.Y = targetPoint.X*(1 / h_grad);
			 }
			 else
			 {
				 startingPoint.Y = targetPoint.Y;
				 startingPoint.X = targetPoint.Y*(1 / h_grad);
			 }
			 break;

			 // ����ȵǰ� �״��
		 case CFigure::TOP:
		 case CFigure::BOTTOM:
			 rectSize.Width = m_Rect.Width;
			 rectSize.Height = fixedPoint.Y > targetPoint.Y ?
				 fixedPoint.Y - targetPoint.Y : targetPoint.Y - fixedPoint.Y;

			 startingPoint.X = m_Rect.X;

			 if (fixedPoint.Y > targetPoint.Y) {
				 startingPoint.Y = targetPoint.Y;
			 }
			 else {
				 startingPoint.Y = fixedPoint.Y;
			 }

			 break;

			 // shift ����ȵǰ� �״��
		 case CFigure::RIGHT:
		 case CFigure::LEFT:
			 rectSize.Width = fixedPoint.X > targetPoint.X ?
				 fixedPoint.X - targetPoint.X : targetPoint.X - fixedPoint.X;
			 rectSize.Height = m_Rect.Height;

			 if (fixedPoint.X > targetPoint.X) {
				 startingPoint.X = targetPoint.X;
			 }
			 else {
				 startingPoint.X = fixedPoint.X;
			 }

			 startingPoint.Y = m_Rect.Y;

			 break;

		 default:
			 // �߸��� selectedHandle
			 // �ƹ� ������ ���� ����
			 return;
		 }
	 }
	 rect = RectF(startingPoint, rectSize);
	 lpGraphics->FillEllipse(m_FillBrush, rect); // ellipse ä���
	 lpGraphics->DrawEllipse(m_OutlinePen, rect);
 }

 /* ��ü ���� ���� */
 // ��ü ���� ����
RectF  CEllipse::resetArea(){
	 m_Area = m_Rect;

	 return m_Area;
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
