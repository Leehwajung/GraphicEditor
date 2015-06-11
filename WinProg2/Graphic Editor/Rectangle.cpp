// Rectangle.cpp : CRectangle Ŭ������ ����
// CRectangle : ���簢�� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Rectangle.h"


// CRectangle

IMPLEMENT_SERIAL(CRectangle, CShape, 1)


CRectangle::CRectangle()
	: CShape()
{
}

CRectangle::CRectangle(IN Pen* pen, IN BrushPtr brush)
	: CShape(pen, brush)
{
}

CRectangle::CRectangle(IN Pen* pen, IN BrushPtr brush, IN RectF rect)
	: CShape(pen, brush)
	, m_Rect(rect)
{
}

CRectangle::~CRectangle()
{
}



// CRectangle ��� �Լ�

/* ����ȭ */
// ����ȭ
void CRectangle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


/* ���� */
// ����
// ���� ��ǥ�� �� ��ǥ�� �������� �簢���� ������
// - IN �Ű�����
//		PointF startingPoint: ���� ���� ��ǥ
//		PointF endingPoint: ���� �� ��ǥ
//		CreateFlag createFlag = FREECREATE: ���� ���� �÷���
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CRectangle::create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag/* = FREECREATE*/)
{
	return create(&startingPoint, &endingPoint, createFlag);	 // �ӽ� ��ȯ ��
}

// ����
// ���� ��ǥ�� �� ��ǥ�� �������� �簢���� ������
// - IN �Ű�����
//		void* param1, ...: PointF*(startingPoint), PointF*(endingPoint), CreateFlag ������ �Է�
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CRectangle::create(void* param1, ...)
{
	va_list vaList;
	va_start(vaList, param1);
	PointF* fixedPoint = (PointF*)param1;
	PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	PointF startingPoint = *fixedPoint;

	SizeF rectSize;
	rectSize.Width = abs(fixedPoint->X - endingPoint->X);
	rectSize.Height = abs(fixedPoint->Y - endingPoint->Y);

	switch (createFlag)
	{
		case CFigure::FREECREATE: {
			if (fixedPoint->X > endingPoint->X) {
				startingPoint.X = endingPoint->X;
			}

			if (fixedPoint->Y > endingPoint->Y) {
				startingPoint.Y = endingPoint->Y;
			}
		} break;

		case CFigure::REGULAR: {
			REAL regularSize = max(rectSize.Width, rectSize.Height);

			rectSize.Width = regularSize;
			rectSize.Height = regularSize;

			if (fixedPoint->X > endingPoint->X) {
				startingPoint.X = fixedPoint->X - regularSize;
			}

			if (fixedPoint->Y > endingPoint->Y) {
				startingPoint.Y = fixedPoint->Y - regularSize;
			}
		} break;
	}

	m_Rect = RectF(startingPoint, rectSize);

	resetArea();

	return FALSE;
}

// �̵�
// ���� ��ǥ���� �� ��ǥ������ Offset�� �������� �簢���� �̵�
// - IN �Ű�����
//		PointF originPoint: �̵��� ���� ��ǥ
//		PointF targetPoint: �̵��� �� ��ǥ
//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
void CRectangle::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	// originPoint: ButtonDown
	// targetPoint: ButtonUp
	
	PointF offset = targetPoint - originPoint;

	switch (moveFlag)
	{
	case CFigure::FREEMOVE:
		// �߰� �۾� ����
		break;

	case CFigure::FOURWAY:
		if (abs(offset.X) > abs(offset.Y)) {
			offset.Y = 0;
		}
		else {
			offset.X = 0;
		}
		break;
	}

	m_Rect.Offset(offset);
	resetArea();
}

// ũ�� ����
// ������ �ڵ��� ��ǥ�� �����Ͽ� ũ�� ���� (���� ��ǥ�� �����ϸ� �̸� �������� �� ��ǥ�� �����Ͽ� ũ�� ����)
// - IN �Ű�����
//		Position selectedHandle: �簢���� ���õ� �ڵ�
//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
void CRectangle::resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	//PointF startingPoint;
	//getHandlePoint(selectedHandle, &startingPoint);
	//PointF oppositePoint;
	//getHandlePoint(getOppositeHandle(selectedHandle), &oppositePoint);
	//PointF fixedPoint;
	//if (anchorPoint) {
	//	fixedPoint = *anchorPoint;
	//}
	//else{
	//	fixedPoint = oppositePoint;
	//}
	//
	//SizeF anchorRectSize;
	//anchorRectSize.Width = abs(fixedPoint.X - oppositePoint.X);
	//anchorRectSize.Height = abs(fixedPoint.Y - oppositePoint.Y);

	//SizeF bigRectSize;
	//bigRectSize.Width = abs(fixedPoint.X - startingPoint.X);
	//bigRectSize.Height = abs(fixedPoint.Y - startingPoint.Y);

	//SizeF targetRectSize;
	//targetRectSize.Width = abs(fixedPoint.X - targetPoint.X);
	//targetRectSize.Height = abs(fixedPoint.Y - targetPoint.Y);

	//SizeF ratioRect;
	//ratioRect.Width = targetRectSize.Width / bigRectSize.Width;
	//ratioRect.Height = targetRectSize.Height / bigRectSize.Height;

	//SizeF newAnchorRectSize;
	//SizeF newBigRectSize;

	//switch (selectedHandle)
	//{
	//case CFigure::TOPLEFT:
	//case CFigure::TOPRIGHT:
	//case CFigure::BOTTOMRIGHT:
	//case CFigure::BOTTOMLEFT:
	//	newAnchorRectSize.Width = anchorRectSize.Width * ratioRect.Width;
	//	newAnchorRectSize.Height = anchorRectSize.Height * ratioRect.Height;

	//	if (fixedPoint.X > targetPoint.X) {
	//		startingPoint.X = targetPoint.X;
	//	}
	//	else {
	//		startingPoint.X = fixedPoint.X - m_Rect.X;
	//	}

	//	if (fixedPoint.Y > targetPoint.Y) {
	//		startingPoint.Y = targetPoint.Y;
	//	}
	//	else {
	//		startingPoint.Y = fixedPoint.Y;
	//	}

	//	break;

	//case CFigure::TOP:
	//case CFigure::BOTTOM:
	//	newAnchorRectSize.Height = anchorRectSize.Height;
	//	newAnchorRectSize.Height = anchorRectSize.Height * ratioRect.Height;

	//	startingPoint.X = m_Rect.X;

	//	if (fixedPoint.Y > targetPoint.Y) {
	//		startingPoint.Y = targetPoint.Y;
	//	}
	//	else {
	//		startingPoint.Y = fixedPoint.Y;
	//	}

	//	break;

	//case CFigure::RIGHT:
	//case CFigure::LEFT:
	//	newAnchorRectSize.Width = anchorRectSize.Width * ratioRect.Width;
	//	newAnchorRectSize.Height = anchorRectSize.Height;

	//	if (fixedPoint.X > targetPoint.X) {
	//		startingPoint.X = targetPoint.X;
	//	}
	//	else {
	//		startingPoint.X = fixedPoint.X;
	//	}

	//	startingPoint.Y = m_Rect.Y;

	//	break;

	//default:
	//	// �߸��� selectedHandle
	//	// �ƹ� ������ ���� ����
	//	return;
	//}



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
		rectSize.Width = abs(fixedPoint.X - targetPoint.X);
		rectSize.Height = abs(fixedPoint.Y - targetPoint.Y);

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
		rectSize.Height = abs(fixedPoint.Y - targetPoint.Y);

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
		rectSize.Width = abs(fixedPoint.X - targetPoint.X);
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

// ����
// �簢���� �����ϰ� �޸𸮸� ����
void CRectangle::destroy()
{

}

// ��ǥ ��ġ Ȯ��
// ���� �簢�� �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
// - IN �Ű�����
//		PointF point: Ȯ���� ��ǥ
// - ��ȯ �� (Position)
//		Position: �簢�� ���� ���� ��ġ
CFigure::Position CRectangle::pointInFigure(IN PointF point)
{
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


/* ��ü ���� ���� */
// ��ü ���� ����
RectF CRectangle::resetArea()
{
	m_Area = m_Rect;

	return m_Area;
}


/* �׸��� */
// ��ü �׸���
void CRectangle::draw(IN Graphics& graphics)
{
	graphics.FillRectangle(m_FillBrush, m_Rect);
	graphics.DrawRectangle(m_OutlinePen, m_Rect);
}

// ���� �׸���
// ���� �ÿ� ������ �׸���
// - IN �Ű�����
//		Graphics& graphics: �׸��� ��� Graphics
//		PointF startingPoint: ���� ���� ��ǥ
//		PointF targetPoint: ���� �� ���� ���� ��ǥ
//		CreateFlag createFlag = FREECREATE: ���� ���� �÷���
RectF CRectangle::creating(IN Graphics& graphics, IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/)
{
	return creating(graphics, &startingPoint, &targetPoint, createFlag);
}

// ���� �׸���
// ���� �ÿ� ������ �׸���
// - IN �Ű�����
//		Graphics& graphics: �׸��� ��� Graphics
//		void* param1, ...: PointF*(startingPoint), PointF*(targetPoint), CreateFlag ������ �Է�
RectF CRectangle::creating(IN Graphics& graphics, void* param1, ...)
{
	va_list vaList;
	va_start(vaList, param1);
	PointF* fixedPoint = (PointF*)param1;
	PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	PointF startingPoint = *fixedPoint;

	SizeF rectSize;
	rectSize.Width = abs(fixedPoint->X - endingPoint->X);
	rectSize.Height = abs(fixedPoint->Y - endingPoint->Y);

	switch (createFlag)
	{
		case CFigure::FREECREATE: {
			if (fixedPoint->X > endingPoint->X) {
				startingPoint.X = endingPoint->X;
			}

			if (fixedPoint->Y > endingPoint->Y) {
				startingPoint.Y = endingPoint->Y;
			}
		} break;

		case CFigure::REGULAR: {
			REAL regularSize = max(rectSize.Width, rectSize.Height);

			rectSize.Width = regularSize;
			rectSize.Height = regularSize;

			if (fixedPoint->X > endingPoint->X) {
				startingPoint.X = fixedPoint->X - regularSize;
			}

			if (fixedPoint->Y > endingPoint->Y) {
				startingPoint.Y = fixedPoint->Y - regularSize;
			}
		} break;
	}

	RectF drawnArea = RectF(startingPoint, rectSize);
	graphics.FillRectangle(CGlobal::crateIngBrush(m_FillBrush), drawnArea);
	graphics.DrawRectangle(CGlobal::crateIngPen(m_OutlinePen), drawnArea);

	return drawnArea;
}

// �̵� �׸���
// �̵� �߿� ������ �׸���
// - IN �Ű�����
//		Graphics& graphics: �׸��� ��� Graphics
//		PointF originPoint: �̵��� ���� ��ǥ
//		PointF targetPoint: �̵� ���� ��ǥ
//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
RectF CRectangle::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	PointF offset = targetPoint - originPoint;
	
	switch (moveFlag)
	{
	case CFigure::FREEMOVE:
		// �߰� �۾� ����
		break;

	case CFigure::FOURWAY:
		if (abs(offset.X) > abs(offset.Y)) {
			offset.Y = 0;
		}
		else {
			offset.X = 0;
		}
		break;
	}

	RectF drawnArea = m_Rect;
	drawnArea.Offset(offset);
	graphics.FillRectangle(CGlobal::crateIngBrush(m_FillBrush), drawnArea);
	graphics.DrawRectangle(CGlobal::crateIngPen(m_OutlinePen), drawnArea);

	return drawnArea;
}

// ũ�� ���� �׸���
// ũ�� ���� �߿� ������ �׸���
// - IN �Ű�����
//		Graphics& graphics: �׸��� ��� Graphics
//		Position selectedHandle: ��ü�� ���õ� �ڵ�
//		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
RectF CRectangle::resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	RectF drawnArea;
	RectF rect = m_Rect; //temp

	PointF startingPoint;
	PointF fixedPoint;
	PointF Gradeint;
	getHandlePoint(getOppositeHandle(selectedHandle), &fixedPoint);

	SizeF rectSize;

	if (resizeFlag == FREERESIZE){
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
			return NULLRectF;
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
			return NULLRectF;
		}
	}
	rect = RectF(startingPoint, rectSize);
	graphics.FillRectangle(CGlobal::crateIngBrush(m_FillBrush), rect);
	graphics.DrawRectangle(CGlobal::crateIngPen(m_OutlinePen), rect);

	return drawnArea;
}

CFigure* CRectangle::clone()
{
	return new CRectangle(m_OutlinePen, m_FillBrush, m_Rect);
}

