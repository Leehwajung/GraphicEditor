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
// �׷� ��ü�� �׷��� ���� ��ü���� �����ϰ� �޸𸮸� ����
void CGroup::destroy()
{
	for (POSITION pos = m_FiguresList.GetTailPosition(); pos; m_FiguresList.GetPrev(pos)) {
		m_FiguresList.GetAt(pos)->~CFigure();
	}

	this->~CGroup();
}

// ����
// �׷��� �����ϰ� �׷� ��ü�� ����
// - OUT �Ű�����
//		CFigurePtrList& figurePtrList: ���� �׷��� ��ü ����Ʈ
void CGroup::unGroup(OUT CFigurePtrList& figurePtrList)
{
	figurePtrList = m_FiguresList;

	this->~CGroup();
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
	Position selectedPosition;

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
RectF CGroup::creating(IN Graphics* lpGraphics, void* param1, ...)
{
	return NULLRectF;
}

// �̵� �׸���
// �̵� �߿� ������ �׸���
// - IN �Ű�����
//		Graphics* lpGraphics: �׸��� ��� Graphics
//		PointF originPoint: �̵��� ���� ��ǥ
//		PointF targetPoint: �̵� ���� ��ǥ
//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
RectF CGroup::moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	return m_FiguresList.moving(lpGraphics, originPoint, targetPoint, moveFlag);
}

// ũ�� ���� �׸���
// ũ�� ���� �߿� ������ �׸���
// - IN �Ű�����
//		Graphics* lpGraphics: �׸��� ��� Graphics
//		Position selectedHandle: ��ü�� ���õ� �ڵ�
//		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
RectF CGroup::resizing(IN Graphics* lpGraphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	PointF handlePoint;
	getHandlePoint(getOppositeHandle(selectedHandle), &handlePoint);

	return m_FiguresList.resizing(lpGraphics, selectedHandle, targetPoint, resizeFlag, &handlePoint);
}


/** �Ӽ� ���� **/
// ������ �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setOutlineColor(IN const Color& outlineColor)
{
	return m_FiguresList.setOutlineColor(outlineColor);
}

// ������ �β� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setOutlineWidth(IN const REAL outlineWidth)
{
	return m_FiguresList.setOutlineWidth(outlineWidth);
}

// ������ ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setOutlinePattern(IN const DashStyle outlinePattern)
{
	return m_FiguresList.setOutlinePattern(outlinePattern);
}

// �� ä��� �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setFillColor(IN const Color& fillColor)
{
	return m_FiguresList.setFillColor(fillColor);
}

// ���� ä��� �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setFillSubcolor(IN const Color& fillSubcolor)
{
	return m_FiguresList.setFillSubcolor(fillSubcolor);
}

// ä��� ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setFillPattern(IN const HatchStyle fillPattern)
{
	return m_FiguresList.setFillPattern(fillPattern);
}