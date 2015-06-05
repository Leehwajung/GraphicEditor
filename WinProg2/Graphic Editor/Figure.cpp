// Figure.cpp : CFigure Ŭ������ ����
// CFigure : Ŭ���̾�Ʈ �������� �� �� �ִ� ��ü�� �����ϴ� Ŭ���� (��� ��ü�� ���� Ŭ����)
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Figure.h"

using namespace Gdiplus;

// CFigure

IMPLEMENT_SERIAL(CFigure, CObject, 1)

CFigure::CFigure()
	: m_lpGraphics(NULL)
	, m_GraphicsDynamicAllocationFlag(FALSE)
{
}

CFigure::CFigure(CClientDC* lpClientDC)
	: m_lpGraphics(new Graphics(*lpClientDC))
	, m_GraphicsDynamicAllocationFlag(TRUE)
{
}

CFigure::CFigure(Graphics* lpGraphics)
	: m_lpGraphics(lpGraphics)
	, m_GraphicsDynamicAllocationFlag(FALSE)
{
}

CFigure::~CFigure()
{
	if (m_GraphicsDynamicAllocationFlag && m_lpGraphics) {
		m_lpGraphics->~Graphics();
	}
}


// CFigure ��� �Լ�

/* ����ȭ */
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


/* ���� */
// ����
// �Ű������� ���� �������� ���ο� ��ü�� ����
// - IN �Ű�����
//		void* param1, ...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
//		[CreateFlag createFlag = FREECREATE]: ���� ���� �÷���, �ʿ��ϸ� �߰��ϱ�
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CFigure::create(void* param1, ...)
{
	resetArea();
	return TRUE;	 // �ӽ� ��ȯ ��
}

// �̵�
// ���� ��ǥ���� �� ��ǥ������ Offset�� �������� ��ü�� �̵�
// - IN �Ű�����
//		PointF originPoint: �̵��� ���� ��ǥ
//		PointF targetPoint: �̵��� �� ��ǥ
//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
void CFigure::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	resetArea();
}

// ũ�� ����
// ������ �ڵ��� ��ǥ�� �����Ͽ� ũ�� ���� (���� ��ǥ�� �����ϸ� �̸� �������� �� ��ǥ�� �����Ͽ� ũ�� ����)
// - IN �Ű�����
//		Position selectedHandle: ��ü�� ���õ� �ڵ�
//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
void CFigure::resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	resetArea();
}

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


/* Graphics ���� */
// ClientDC ȹ��
CClientDC* CFigure::getClientDC()
{
	return (CClientDC*) CClientDC::FromHandle(m_lpGraphics->GetHDC());
}

// Graphics ȹ��
Graphics* CFigure::getGraphics()
{
	return m_lpGraphics;
}

// ClientDC ����
void CFigure::setClientDC(CClientDC* lpClientDC)
{
	if (m_GraphicsDynamicAllocationFlag && m_lpGraphics) {
		m_lpGraphics->~Graphics();
	}

	m_lpGraphics = new Graphics(*lpClientDC);
	m_GraphicsDynamicAllocationFlag = TRUE;
}

// Graphics ����
void CFigure::setGraphics(Graphics* lpGraphics)
{
	if (m_GraphicsDynamicAllocationFlag && m_lpGraphics) {
		m_lpGraphics->~Graphics();
	}

	m_lpGraphics = lpGraphics;
	m_GraphicsDynamicAllocationFlag = FALSE;
}


/* ��ü ���� ���� */
// ��ü ���� �׸���
void CFigure::drawArea()
{


	drawHandles();
}


/* �ڵ� ���� */
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

	handleRect->X = handlePoint.X - HANDLESIZE / 2;
	handleRect->Y = handlePoint.Y - HANDLESIZE / 2;
	handleRect->Width = HANDLESIZE;
	handleRect->Height = HANDLESIZE;

	return FALSE;
}

CFigure::Position CFigure::getOppositeHandle(IN Position handle){
	
	switch (handle)
	{
	case CFigure::OUTSIDE:
		return handle;
	case CFigure::INSIDE:
		return handle;
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
	}

}
// ��ü �ڵ� �׸���
// - IN �Ű�����
//		Position handle: �׸������ϴ� �ڵ�
// - ��ȯ �� (BOOL)
//		TRUE: �Ű������� Position�� �ڵ��� �ƴ� ���
//		FALSE: �Ű������� Position�� �ڵ��� ���
BOOL CFigure::drawHandle(IN Position handle)
{
	RectF handleRect;
	
	// �ڵ� ������ ����
	if (getHandleRect(handle, &handleRect)) {
		return TRUE;
	}

	// �ڵ��� �׸�
	SolidBrush handleBrush(Color::White);
	m_lpGraphics->FillRectangle(&handleBrush, handleRect);

	Pen handlePen(Color::Gray);
	m_lpGraphics->DrawRectangle(&handlePen, handleRect);

	return FALSE;
}

// ��ü �ڵ� ��ü �׸���
void CFigure::drawHandles()
{
	RectF handleRects[8];
	const INT handleRectsSize = 8;

	// 8�� ��ü �ڵ��� ������ ����
	for (int handleIndex = TOPLEFT; handleIndex <= LEFT; handleIndex++) {
		getHandleRect((Position)handleIndex, &handleRects[handleIndex - 8]);
	}

	// ��ü �ڵ��� �׸�
	SolidBrush handleBrush(Color::White);
	m_lpGraphics->FillRectangles(&handleBrush, handleRects, handleRectsSize);

	Pen handlePen(Color::Gray);
	m_lpGraphics->DrawRectangles(&handlePen, handleRects, handleRectsSize);
}


// ���� �����Լ��� �ٲ� �Ŷ� ���� �Լ� ������
void CFigure::destroy(){}
CFigure::Position CFigure::pointInFigure(IN PointF point){ return OUTSIDE; /* �ӽ� ��ȯ�� */ }
void CFigure::draw(){}
void CFigure::creating(void* param1, ...){}
void CFigure::moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/){}
void CFigure::resizing(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/){}
BOOL CFigure::setOutlineColor(IN const Color& outlineColor){ return TRUE; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setOutlineWidth(IN const REAL outlineWidth){ return TRUE; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setOutlinePattern(IN const DashStyle outlinePattern){ return TRUE; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setFillColor(IN const Color& fillColor){ return TRUE; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setFillSubcolor(IN const Color& fillSubcolor){ return TRUE; /* �ӽ� ��ȯ�� */ }
BOOL CFigure::setFillPattern(IN const HatchStyle fillPattern){ return TRUE; /* �ӽ� ��ȯ�� */ }
void CFigure::resetArea(){}



// ������

///* ��ü ���� */
//void CFigure::create(PointF StartingPoint) {
//	this->m_StartingPoint = StartingPoint;
//}
//
///* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���) */
//CFigure::operationModeFlags CFigure::cursorPosition(PointF point) {
//	return None; 
//}
//
///* Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���) */
//CFigure::operationModeFlags CFigure::cursorPosition(RectF rect) {
//	return None;
//}
//
///* OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�) */
//void CFigure::mouseMoveOperation(UINT nFlags, PointF point) {
//
//}
//
///* ���� �׸��� */
//void CFigure::creating(UINT nFlags, PointF point) {
//
//}
//
///* �̵� �׸��� */
//void CFigure::moving(UINT nFlags, PointF point) {
//
//}
//
///* ũ�� ���� �׸��� */
//void CFigure::resizing(UINT nFlags, PointF point) {
//
//}
//
///* ���� �Ϸ� */
//void CFigure::endCreate(PointF point) {
//
//}
//
///* ��ü �̵� */
//void CFigure::move(PointF originPoint, PointF targetPoint) {
//
//}
//
///* ��ü ũ�� ���� */
//void CFigure::resize(PointF Point, PointF* anchorPoint /*= NULL*/, int resizeFlags /*= Free*/) {
//
//	//if (!anchorPoint) {
//	//	anchorPoint = &m_StartingPoint;
//	//}
//}
//
///* ��ü �׸��� */
//void CFigure::draw() {
//	PROPORTIONAL == MK_SHIFT;
//}
//
///* ��ü ���ü� �׸��� */
//void CFigure::drawSelect() {
//	
//}
//
///* ��ü ���� */
//void CFigure::destroy() {
//
//}
//
///* ������ �� ���� */
//void CFigure::setLineColor(const Color& LineColor) {
//
//}
//
///* ������ �β� ���� */
//void CFigure::setLineWidth(const REAL& LineWidth) {
//
//}
//
///* ������ ���� ���� */
//void CFigure::setLinePattern(const DashStyle& LinePattern) {
//
//}
//
///* �� ä��� �� ���� */
//void CFigure::setFillColor(const Color& FillColor) {
//	m_lpGraphics->FillEllipse(&SolidBrush(Color(0,0,0)), Rect());
//}
//
///* ä��� ���� ���� */
//void CFigure::setFillPattern(const int FillPattern) {
//
//}
//
//
///* Getter / Setter */
//
//Graphics* CFigure::getGraphics() {
//	return this->m_lpGraphics;
//}
//
//void CFigure::setGraphics(Graphics* lpGraphics) {
//	this->m_lpGraphics = lpGraphics;
//}
//
//PointF& CFigure::getStartingPoint() {
//	return this->m_StartingPoint;
//}
//
//void CFigure::setStartingPoint(PointF& StartingPoint) {
//	this->m_StartingPoint = StartingPoint;	// ���� ������ �Ҹ�
//}
//
//CFigure::operationModeFlags CFigure::getOperationMode() {
//	return this->m_OperationMode;
//}
//
//void CFigure::setOperationMode(operationModeFlags OperationMode) {
//	this->m_OperationMode = OperationMode;
//}
//
//void CFigure::resetArea() {
//
//}

