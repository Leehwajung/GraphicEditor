// FigurePtrList.cpp : CFigurePtrList Ŭ������ �������̽�
// CFigurePtrList : ��ü���� �����͸� �����ϴ� ����Ʈ Ŭ����
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Figure.h"

using namespace Gdiplus;

// CFigure

IMPLEMENT_SERIAL(CFigure, CObject, 1)

CFigure::CFigure()
	//: graphics(NULL)
	//, m_GraphicsDynamicAllocationFlag(FALSE)
{
}

//CFigure::CFigure(CClientDC* lpClientDC)
//	: graphics(new Graphics(*lpClientDC))
//	, m_GraphicsDynamicAllocationFlag(TRUE)
//{
//}
//
//CFigure::CFigure(Graphics& graphics)
//	: graphics(graphics)
//	, m_GraphicsDynamicAllocationFlag(FALSE)
//{
//}

CFigure::~CFigure()
{
	//if (m_GraphicsDynamicAllocationFlag && graphics) {
	//	graphics.~Graphics();
	//}
}


// CFigure ��� �Լ�

/** ����ȭ **/
// ����ȭ (���������Լ��� �ٲ��� ����)
void CFigure::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


/** ���� **/
// ��ü ��ġ Ȯ��
// ��ü�� �簢�� �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
// - IN �Ű�����
//		RectF rect: Ȯ���� ��ǥ
// - ��ȯ �� (BOOL)
//		TRUE: ��ü�� �簢�� ���ο� ������ �� (������ ��� ���� �簢�� ���ο� ����)
//		FALSE: ��ü�� �簢�� ���ο� �������� ���� ��
BOOL CFigure::figureInRect(IN RectF rect)
{
	if (rect.Contains(m_Area)) {
		return TRUE;
	}

	return FALSE;
}

// ��ü ����
// ��ü ������ ����
RectF CFigure::getArea()
{
	return m_Area;
}


/** �ڵ� ���� **/
// �ڵ��� ��ǥ
// �ڵ��� �߾� ��ǥ�� ����
// - IN �Ű�����
//		Position handle: ��ǥ�� ������ϴ� �ڵ�
// - OUT �Ű�����
//		PointF* handlePoint:
//			�ּ� ��: �Ű������� Position�� �ڵ��� ��� �ڵ��� ��ǥ
//			NULL: �Ű������� Position�� �ڵ��� �ƴ� ���
// - ��ȯ �� (BOOL)
//		TRUE: �Ű������� Position�� �ڵ��� �ƴ� ���
//		FALSE: �Ű������� Position�� �ڵ��� ���
BOOL CFigure::getHandlePoint(IN Position handle, OUT PointF* handlePoint)
{
	switch (handle)
	{
	case CFigure::TOPLEFT:
		m_Area.GetLocation(handlePoint);
		break;
	case CFigure::TOP:
		handlePoint->X = (m_Area.GetLeft() + m_Area.GetRight()) / 2;
		handlePoint->Y = m_Area.GetTop();
		break;
	case CFigure::TOPRIGHT:
		handlePoint->X = m_Area.GetRight();
		handlePoint->Y = m_Area.GetTop();
		break;
	case CFigure::RIGHT:
		handlePoint->X = m_Area.GetRight();
		handlePoint->Y = (m_Area.GetTop() + m_Area.GetBottom()) / 2;
		break;
	case CFigure::BOTTOMRIGHT:
		handlePoint->X = m_Area.GetRight();
		handlePoint->Y = m_Area.GetBottom();
		break;
	case CFigure::BOTTOM:
		handlePoint->X = (m_Area.GetLeft() + m_Area.GetRight()) / 2;
		handlePoint->Y = m_Area.GetBottom();
		break;
	case CFigure::BOTTOMLEFT:
		handlePoint->X = m_Area.GetLeft();
		handlePoint->Y = m_Area.GetBottom();
		break;
	case CFigure::LEFT:
		handlePoint->X = m_Area.GetLeft();
		handlePoint->Y = (m_Area.GetTop() + m_Area.GetBottom()) / 2;
		break;
	default:
		handlePoint = NULL;
		return TRUE;
	}

	return FALSE;
}

// �ڵ��� ����
// �ڵ��� ������ ����
// - IN �Ű�����
//		PointF handlePoint: ������ ������ϴ� �ڵ��� ��ǥ
// - ��ȯ �� (RectF)
//		�ڵ��� ����
RectF CFigure::getHandleRect(IN PointF handlePoint)
{
	RectF handleRect;

	handleRect.X = handlePoint.X - HANDLESIZE / 2;
	handleRect.Y = handlePoint.Y - HANDLESIZE / 2;
	handleRect.Width = HANDLESIZE;
	handleRect.Height = HANDLESIZE;

	return handleRect;
}

// �ڵ��� ����
// �ڵ��� ������ ����
// - IN �Ű�����
//		Position handle: ������ ������ϴ� �ڵ�
// - OUT �Ű�����
//		PointF* handlePoint:
//			�ּ� ��: �Ű������� Position�� �ڵ��� ��� �ڵ��� ����
//			NULL: �Ű������� Position�� �ڵ��� �ƴ� ���
// - ��ȯ �� (BOOL)
//		TRUE: �Ű������� Position�� �ڵ��� �ƴ� ���
//		FALSE: �Ű������� Position�� �ڵ��� ���
BOOL CFigure::getHandleRect(IN Position handle, OUT RectF* handleRect)
{
	PointF handlePoint;

	if (getHandlePoint(handle, &handlePoint)) {
		handleRect = NULL;
		return TRUE;
	}

	*handleRect = getHandleRect(handlePoint);

	return FALSE;
}

// ���ݴ��� �ڵ�
// ���ݴ��� �ڵ��� ����
// - IN �Ű�����
//		Position handle: ���ݴ��� �ڵ��� ������ϴ� �ڵ�
// - ��ȯ �� (Position)
//		���ݴ��� �ڵ�
CFigure::Position CFigure::getOppositeHandle(IN Position handle){

	switch (handle)
	{
	case CFigure::TOPLEFT:
		return CFigure::BOTTOMRIGHT;
	case CFigure::TOP:
		return CFigure::BOTTOM;
	case CFigure::TOPRIGHT:
		return CFigure::BOTTOMLEFT;
	case CFigure::RIGHT:
		return CFigure::LEFT;
	case CFigure::BOTTOMRIGHT:
		return CFigure::TOPLEFT;
	case CFigure::BOTTOM:
		return CFigure::TOP;
	case CFigure::BOTTOMLEFT:
		return CFigure::TOPRIGHT;
	case CFigure::LEFT:
		return CFigure::RIGHT;
	case CFigure::START:
		return CFigure::END;
	case CFigure::END:
		return CFigure::START;
	default:
		return handle;
	}
}


/** �׸��� **/
// ���� ��ü �׸���
void CFigure::drawSelect(IN Graphics& graphics)
{
	draw(graphics);
	drawHandles(graphics);
}


/** ��ü ���� ���� **/
// ��ü ���� �׸���
// - IN �Ű�����
//		Graphics& graphics: �׸��� ��� Graphics
void CFigure::drawArea(IN Graphics& graphics)
{
	Pen pen(Color::Gray);
	pen.SetDashStyle(DashStyleDot);
	graphics.DrawRectangle(&pen, m_Area);

	drawHandles(graphics);
}

// ��ü �ڵ� �׸���
// - IN �Ű�����
//		Graphics& graphics: �׸��� ��� Graphics
//		PointF handlePoint: �׸������ϴ� �ڵ� ��ǥ
// - ��ȯ �� (BOOL)
//		TRUE: �Ű������� Position�� �ڵ��� �ƴ� ���
//		FALSE: �Ű������� Position�� �ڵ��� ���
BOOL CFigure::drawHandle(IN Graphics& graphics, IN PointF handlePoint)
{
	RectF handleRect = getHandleRect(handlePoint);

	// �ڵ��� �׸�
	SolidBrush handleBrush(Color::White);
	graphics.FillRectangle(&handleBrush, handleRect);

	Pen handlePen(Color::Gray);
	graphics.DrawRectangle(&handlePen, handleRect);

	return FALSE;
}

// ��ü �ڵ� �׸���
// - IN �Ű�����
//		Graphics& graphics: �׸��� ��� Graphics
//		Position handle: �׸������ϴ� �ڵ�
// - ��ȯ �� (BOOL)
//		TRUE: �Ű������� Position�� �ڵ��� �ƴ� ���
//		FALSE: �Ű������� Position�� �ڵ��� ���
BOOL CFigure::drawHandle(IN Graphics& graphics, IN Position handle)
{
	PointF handlePoint;
	
	// �ڵ� ��ǥ�� ����
	if (getHandlePoint(handle, &handlePoint)) {
		return TRUE;
	}

	// �ڵ��� �׸�
	drawHandle(graphics, handlePoint);

	return FALSE;
}

// ��ü �ڵ� ��ü �׸���
// - IN �Ű�����
//		Graphics& graphics: �׸��� ��� Graphics
//		PointF* handlePoints: �ڵ��� ��ǥ �迭
//		count: �迭�� ũ��
void CFigure::drawHandles(IN Graphics& graphics, IN PointF* handlePoints, IN INT count)
{
	CArray<RectF, RectF&> handleRects;

	for (int i = 0; i < count; i++) {
		handleRects.Add(getHandleRect(handlePoints[i]));
	}

	// ��ü �ڵ��� �׸�
	SolidBrush handleBrush(Color::White);
	graphics.FillRectangles(&handleBrush, handleRects.GetData(), count);

	Pen handlePen(Color::Gray);
	graphics.DrawRectangles(&handlePen, handleRects.GetData(), count);
}

// ��ü �ڵ� ��ü �׸���
// - IN �Ű�����
//		Graphics& graphics: �׸��� ��� Graphics
void CFigure::drawHandles(IN Graphics& graphics)
{
	RectF handleRects[8];
	const INT handleRectsSize = 8;

	// 8�� ��ü �ڵ��� ������ ����
	for (int handleIndex = TOPLEFT; handleIndex <= LEFT; handleIndex++) {
		getHandleRect((Position)handleIndex, &handleRects[handleIndex - 8]);
	}

	// ��ü �ڵ��� �׸�
	SolidBrush handleBrush(Color::White);
	graphics.FillRectangles(&handleBrush, handleRects, handleRectsSize);

	Pen handlePen(Color::Gray);
	graphics.DrawRectangles(&handlePen, handleRects, handleRectsSize);
}


// ���� �����Լ��� �ٲ� �Ŷ� ���� �Լ� ������
BOOL CFigure::create(void* param1, ...){return TRUE;/* �ӽ� ��ȯ ��*/}
void CFigure::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/){}
void CFigure::resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/){}
void CFigure::destroy(){}
CFigure::Position CFigure::pointInFigure(IN PointF point){ return OUTSIDE; /* �ӽ� ��ȯ�� */ }
void CFigure::draw(IN Graphics& graphics){}
RectF CFigure::creating(IN Graphics& graphics, void* param1, ...){ return NULLRectF; /* �ӽ� ��ȯ�� */ }
RectF CFigure::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/){ return NULLRectF; /* �ӽ� ��ȯ�� */ }
RectF CFigure::resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/){ return NULLRectF; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setOutlineColor(IN const Color& outlineColor){ return TRUE; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setOutlineWidth(IN const REAL outlineWidth){ return TRUE; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setOutlinePattern(IN const DashStyle outlinePattern){ return TRUE; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setFillColor(IN const Color& fillColor){ return TRUE; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setFillSubcolor(IN const Color& fillSubcolor){ return TRUE; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setFillPattern(IN const HatchStyle fillPattern){ return TRUE; /* �ӽ� ��ȯ�� */ }
RectF CFigure::resetArea(){ return m_Area; /* �ӽ� ��ȯ�� */ }