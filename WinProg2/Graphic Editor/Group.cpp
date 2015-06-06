// Group.cpp : CGroup Ŭ������ ����
// CGroup : �׷�ȭ�� ���� ��ü���� �����ϴ� Ŭ����
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Group.h"


// CGroup

IMPLEMENT_SERIAL(CGroup, CFigure, 1)


CGroup::CGroup()
{
}

CGroup::~CGroup()
{
}


// CGroup ��� �Լ�


/** ����ȭ **/
// ����ȭ (���������Լ��� �ٲ��� ����)
void CGroup::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


/** ���� **/
// ����
// �Ű������� ���� �������� ���ο� ��ü�� ����
// - IN �Ű�����
//		void* param1, ...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::create(IN CFigurePtrList& figurePtrList)
{
	m_FiguresList = figurePtrList;

	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		m_Area.Intersect(m_FiguresList.GetAt(pos)->getArea());
	}

	return FALSE;
}

// ����
// �Ű������� ���� �������� ���ο� ��ü�� ����
// - IN �Ű�����
//		int count: �������̷� ���� ��ü �������� ����
//		CFigure* figure1, ...: ��ü �������� ���� ���� ����Ʈ
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::create(IN const int count, IN CFigure* figure1, ...)
{
	m_Area = NULLRectF;
	m_FiguresList.RemoveAll();

	va_list vaList;
	va_start(vaList, figure1);
	if (!figure1) {
		return TRUE;
	}
	m_FiguresList.AddTail(figure1);

	CFigure* figure;
	
	for (int i = 1; i < count; i++) {
		figure = va_arg(vaList, CFigure*);
		if (!figure) {
			return TRUE;
		}
		m_FiguresList.AddTail(figure);
		m_Area.Intersect(figure->getArea());
	}

	va_end(vaList);

	return FALSE;
}

// ����
// �Ű������� ���� �������� ���ο� ��ü�� ����
// - IN �Ű�����
//		void* param1, ...: int*(count), CFigure*(figure1), CFigure*(...) ������ �Է�
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::create(void* param1, ...)
{
	m_Area = NULLRectF;
	va_list vaList;
	va_start(vaList, param1);
	int count = *(int*)param1;
	CFigure* figure;

	m_FiguresList.RemoveAll();
	for (int i = 0; i < count; i++) {
		figure = va_arg(vaList, CFigure*);
		if (!figure) {
			return TRUE;
		}
		m_FiguresList.AddTail(figure);
		m_Area.Intersect(figure->getArea());
	}

	va_end(vaList);

	return FALSE;
}

// �̵�
// ���� ��ǥ���� �� ��ǥ������ Offset�� �������� ��ü�� �̵�
// - IN �Ű�����
//		PointF originPoint: �̵��� ���� ��ǥ
//		PointF targetPoint: �̵��� �� ��ǥ
//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
void CGroup::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	m_Area = NULLRectF;
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		m_FiguresList.GetAt(pos)->move(originPoint, targetPoint, moveFlag);
		m_Area.Intersect(m_FiguresList.GetAt(pos)->getArea());
	}
}

// ũ�� ����
// ������ �ڵ��� ��ǥ�� �����Ͽ� ũ�� ���� (���� ��ǥ�� �����ϸ� �̸� �������� �� ��ǥ�� �����Ͽ� ũ�� ����)
// - IN �Ű�����
//		Position selectedHandle: ��ü�� ���õ� �ڵ�
//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
void CGroup::resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	m_Area = NULLRectF;
	PointF handlePoint;
	getHandlePoint(getOppositeHandle(selectedHandle), &handlePoint);

	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		m_FiguresList.GetAt(pos)->resize(selectedHandle, targetPoint, resizeFlag, &handlePoint);
		m_Area.Intersect(m_FiguresList.GetAt(pos)->getArea());
	}
}

// ����
// ��ü�� �����ϰ� �޸𸮸� ����
void CGroup::destroy()
{

}

// ��ǥ ��ġ Ȯ��
// ���� ��ü �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
// - IN �Ű�����
//		PointF point: Ȯ���� ��ǥ
// - ��ȯ �� (Position)
//		Position: ��ü ���� ���� ��ġ
CFigure::Position CGroup::pointInFigure(IN PointF point)
{
	RectF handleRect;

	for (int handleIndex = TOPLEFT; handleIndex <= LEFT; handleIndex++) {

		getHandleRect((Position)handleIndex, &handleRect);
		if (handleRect.Contains(point)) {
			return (Position)handleIndex;
		}
	}

	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->pointInFigure(point) == INSIDE)
			return INSIDE;
	}

	return OUTSIDE;	// �ӽ� ��ȯ��
}

/** ��ü ���� ���� **/
// ��ü ���� ����
RectF CGroup::resetArea()
{
	m_Area = NULLRectF;

	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		m_Area.Intersect(m_FiguresList.GetAt(pos)->resetArea());
	}

	return m_Area;
}

/** �׸��� **/
// ��ü �׸���
void CGroup::draw(IN Graphics* lpGraphics)
{
	m_FiguresList.draw(lpGraphics);
}

// ���� �׸���
// ���� �ÿ� ������ �׸���
// - IN �Ű�����
//		Graphics* lpGraphics: �׸��� ��� Graphics
//		void* param1, ...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
//		[CreateFlag createFlag = FREECREATE]: ���� ���� �÷���, �ʿ��ϸ� �߰��ϱ�
void CGroup::creating(IN Graphics* lpGraphics, void* param1, ...)
{

}

// �̵� �׸���
// �̵� �߿� ������ �׸���
// - IN �Ű�����
//		Graphics* lpGraphics: �׸��� ��� Graphics
//		PointF originPoint: �̵��� ���� ��ǥ
//		PointF targetPoint: �̵� ���� ��ǥ
//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
void CGroup::moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	for (POSITION pos = m_FiguresList.GetTailPosition(); pos; m_FiguresList.GetPrev(pos)) {
		m_FiguresList.GetAt(pos)->moving(lpGraphics, originPoint, targetPoint, moveFlag);
	}
}

// ũ�� ���� �׸���
// ũ�� ���� �߿� ������ �׸���
// - IN �Ű�����
//		Graphics* lpGraphics: �׸��� ��� Graphics
//		Position selectedHandle: ��ü�� ���õ� �ڵ�
//		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
void CGroup::resizing(IN Graphics* lpGraphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	PointF handlePoint;
	getHandlePoint(getOppositeHandle(selectedHandle), &handlePoint);

	for (POSITION pos = m_FiguresList.GetTailPosition(); pos; m_FiguresList.GetPrev(pos)) {
		m_FiguresList.GetAt(pos)->resizing(lpGraphics, selectedHandle, targetPoint, resizeFlag, &handlePoint);
	}
}


/** �Ӽ� ���� **/
// ������ �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setOutlineColor(IN const Color& outlineColor)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setOutlineColor(outlineColor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// ������ �β� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setOutlineWidth(IN const REAL outlineWidth)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setOutlineWidth(outlineWidth)) {
			return TRUE;
		}
	}

	return FALSE;
}

// ������ ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setOutlinePattern(IN const DashStyle outlinePattern)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setOutlinePattern(outlinePattern)) {
			return TRUE;
		}
	}

	return FALSE;
}

// �� ä��� �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setFillColor(IN const Color& fillColor)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setFillColor(fillColor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// ���� ä��� �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setFillSubcolor(IN const Color& fillSubcolor)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setFillSubcolor(fillSubcolor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// ä��� ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setFillPattern(IN const HatchStyle fillPattern)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setFillPattern(fillPattern)) {
			return TRUE;
		}
	}

	return FALSE;
}