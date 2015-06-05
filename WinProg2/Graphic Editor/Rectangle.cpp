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

CRectangle::CRectangle(IN CClientDC* lpClientDC)
	: CShape(lpClientDC)
{
}

CRectangle::CRectangle(IN Graphics* lpGraphics)
	: CShape(lpGraphics)
{
}

CRectangle::CRectangle(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush)
	: CShape(lpClientDC, pen, brush)
{
}

CRectangle::CRectangle(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush)
	: CShape(lpGraphics, pen, brush)
{
}

CRectangle::CRectangle(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush, IN RectF rect)
	: CShape(lpClientDC, pen, brush)
	, m_Rect(rect)
{
}

CRectangle::CRectangle(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush, IN RectF rect)
	: CShape(lpGraphics, pen, brush)
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
	PointF* startingPoint = (PointF*)param1;
	PointF* endingPoint = va_arg(vaList, PointF*);
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	SizeF rectSize;
	rectSize.Width = startingPoint->X > endingPoint->X ? startingPoint->X - endingPoint->X : endingPoint->X - startingPoint->X;
	rectSize.Height = startingPoint->Y > endingPoint->Y ? startingPoint->Y - endingPoint->Y : endingPoint->Y - startingPoint->Y;
	
	if (startingPoint->X > endingPoint->X) {
		startingPoint->X = endingPoint->X;
	}
	
	if (startingPoint->Y > endingPoint->Y) {
		startingPoint->Y = endingPoint->Y;
	}
	
	//RectF* rect = new RectF(*startingPoint, rectSize);

	//if (!rect) {
	//	return TRUE;
	//}

	//m_Rect = *rect;

	m_Rect = RectF(*startingPoint, rectSize);

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


/* �׸��� */
// ���� �׸���
void CRectangle::draw()
{
	m_lpGraphics->FillRectangle(m_FillBrush, m_Rect);
	m_lpGraphics->DrawRectangle(m_OutlinePen, m_Rect);
}

// ���� �׸���
// ���� �ÿ� ������ �׸���
// - IN �Ű�����
//		PointF startingPoint: ���� ���� ��ǥ
//		PointF targetPoint: ���� �� ���� ���� ��ǥ
//		CreateFlag createFlag = FREECREATE: ���� ���� �÷���
void CRectangle::creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag/* = FREECREATE*/)
{
	creating(&startingPoint, &targetPoint, createFlag);
}

// ���� �׸���
// ���� �ÿ� ������ �׸���
// - IN �Ű�����
//		void* param1, ...: PointF*(startingPoint), PointF*(targetPoint), CreateFlag ������ �Է�
void CRectangle::creating(void* param1, ...)
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
void CRectangle::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{

}

// ũ�� ���� �׸���
// ũ�� ���� �߿� ������ �׸���
// - IN �Ű�����
//		Position selectedHandle: ��ü�� ���õ� �ڵ�
//		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
void CRectangle::resizing(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{

}


/* ��ü ���� ���� */
// ��ü ���� ����
void CRectangle::resetArea()
{
	m_Area = m_Rect;
}





//CRectangle::CRectangle()
//	//: m_Rect(*new defaultRectF)
//{
//}
//
//CRectangle::CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/)
//	: CShape(lpClientDC/*, startingPoint*/)
//	//, m_Rect(*new defaultRectF)
//{
//}
//
//CRectangle::CRectangle(Graphics* lpGraphics/*, PointF startingPoint*/)
//	: CShape(lpGraphics/*, startingPoint*/)
//	//, m_Rect(*new defaultRectF)
//{
//}
//
////CRectangle::CRectangle(CClientDC* lpClientDC, RectF& rect)
////	: CShape(lpClientDC)
////	//, m_Rect(*rect.Clone())
////{
////}
//
//CRectangle::CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/, /*RectF& rect, */Pen* pen, SolidBrush* brush)
//	: CShape(lpClientDC/*, startingPoint*/, pen, brush)
//	//, m_Rect(*rect.Clone())
//{
//	//m_OutlinePen = pen->Clone();
//	//m_FillBrush = (SolidBrush*) brush->Clone();
//}
//
//CRectangle::~CRectangle()
//{
//	if (!&m_Rect) {
//		m_Rect.~RectF();
//	}
//}
//
//
//// CRectangle ��� �Լ�
//
///* ��ü ���� */
//void CRectangle::create(PointF StartingPoint) {
//	this->m_StartingPoint = StartingPoint;
//}
//
///* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���) */
//CFigure::operationModeFlags CRectangle::cursorPosition(PointF point) {
//	return None;
//}
//
///* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
//CFigure::operationModeFlags CRectangle::cursorPosition(RectF rect) {
//	return None;
//}
//
//
///* ���� �Ϸ� */
//void CRectangle::endCreate(PointF point) {
//
//	SizeF rectSize;
//	rectSize.Width = m_StartingPoint.X > point.X ? m_StartingPoint.X - point.X : point.X - m_StartingPoint.X;
//	rectSize.Height = m_StartingPoint.Y > point.Y ? m_StartingPoint.Y - point.Y : point.Y - m_StartingPoint.Y;
//
//	if (m_StartingPoint.X > point.X) {
//		m_StartingPoint.X = point.X;
//	}
//
//	if (m_StartingPoint.Y > point.Y) {
//		m_StartingPoint.Y = point.Y;
//	}
//
//	m_Rect = *new RectF(m_StartingPoint, rectSize);
//	resetArea();
//}
//
///* ��ü �̵� */
//void CRectangle::move(PointF originPoint, PointF targetPoint) {
//	// originPoint: ButtonDown
//	// targetPoint: ButtonUp
//
//	PointF offset = targetPoint - originPoint;
//	m_StartingPoint = m_StartingPoint + offset;
//	m_Rect.Offset(offset);
//	resetArea();
//}
//
///* ��ü ũ�� ���� */
//void CRectangle::resize(PointF Point, PointF* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {
//
//	//if (!anchorPoint) {
//	//	anchorPoint = &m_StartingPoint;
//	//}
//
//	if (!anchorPoint) {
//		anchorPoint = &Point;
//	}
//
//	resetArea();
//}
//
///* ��ü �׸��� */
//void CRectangle::draw() {
//	m_lpGraphics->FillRectangle(m_FillBrush, m_Rect);
//	m_lpGraphics->DrawRectangle(m_OutlinePen, m_Rect);
//}

