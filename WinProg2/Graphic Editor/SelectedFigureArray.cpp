// SelectedFigureArray.cpp : CSelectedFigureArray Ŭ������ ����
// CSelectedFigureArray : CFigurePtrList ��ü�� �����ϴ� Ŭ����
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "SelectedFigureArray.h"


// CSelectedFigureArray

CSelectedFigureArray::CSelectedFigureArray()
{
}

CSelectedFigureArray::CSelectedFigureArray(CFigurePtrList* lpFigurePtrList)
	: m_FigurePtrList(lpFigurePtrList)
{
}

CSelectedFigureArray::~CSelectedFigureArray()
{
}


// CSelectedFigureArray ��� �Լ�

// ������ ��ü�� �ִ��� �˻�
BOOL CSelectedFigureArray::isEmpty()
{
	return m_FigurePosArray.IsEmpty();
}

// ������ ��ü�� �� ������ �˻�
BOOL CSelectedFigureArray::hasOne()								// hasOneFigure
{
	return m_FigurePosArray.GetSize() == 1;
}

// ������ ��ü �� �� ���� ��ü ȹ��
CFigure* CSelectedFigureArray::getOneFigure()
{
	if (hasOne()) {
		return m_FigurePtrList->GetAt(m_FigurePosArray[0]);
	}

	return m_FigurePtrList->GetAt(getForwardPos());
}

// ���� ������ ��ü�� ��� �ִ��� Ȯ��
CFigure::Position CSelectedFigureArray::contains(PointF point)	// pointInFigure
{
	if (hasOne()) {
		CFigure* figure = getOneFigure();

		if (figure->IsKindOf(RUNTIME_CLASS(CLine))) {
			return ((CLine*)figure)->pointInFigure(point);
		}
		else if (getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolyLine))) {
			return ((CPolyLine*)figure)->pointInFigure(point);
		}
		else {
			return figure->pointInFigure(point);
		}
	}

	CFigure::Position figPosition;
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		figPosition = m_FigurePtrList->GetAt(m_FigurePosArray[i])->pointInFigure(point);
		if (figPosition != CFigure::OUTSIDE) {
			return figPosition;
		}
	}

	return CFigure::OUTSIDE;
}

// �ֻ��� ��ü ����
void CSelectedFigureArray::select()
{
	deselectAll();
	m_FigurePosArray.Add(m_FigurePtrList->GetHeadPosition());
}

// �������� ��ü ����
void CSelectedFigureArray::select(POSITION position)
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		if (m_FigurePosArray[i] == position) {
			return;		// ������ �������� �����ϸ� ����
		}
	}

	m_FigurePosArray.Add(position);
}

// point�� ��ġ�� �ִ� ��ü ����
CFigure::Position CSelectedFigureArray::select(PointF point)	// getFigure
{
	for (POSITION pos = m_FigurePtrList->GetHeadPosition(); pos; m_FigurePtrList->GetNext(pos)) {
		if (m_FigurePtrList->GetAt(pos)->pointInFigure(point) == CFigure::INSIDE) {
			for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
				if (m_FigurePosArray[i] == pos) {
					return CFigure::INSIDE;;		// ������ �������� �����ϸ� ����
				}
			}

			m_FigurePosArray.Add(pos);

			return CFigure::INSIDE;
		}
	}

	return  CFigure::OUTSIDE;
}

// rect �ȿ� �ִ� ��ü ����
void CSelectedFigureArray::select(RectF rect)					// getFigures
{
	for (POSITION pos = m_FigurePtrList->GetHeadPosition(); pos; m_FigurePtrList->GetNext(pos)) {
		if (m_FigurePtrList->GetAt(pos)->figureInRect(rect)) {
			for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
				if (m_FigurePosArray[i] == pos) {
					break;		// ������ �������� �����ϸ� ����
				}
			}

			m_FigurePosArray.Add(pos);
		}
	}
}

// ��ü ��ü ����
void CSelectedFigureArray::selectAll()
{
	m_FigurePosArray.RemoveAll();

	for (POSITION pos = m_FigurePtrList->GetHeadPosition(); pos; m_FigurePtrList->GetNext(pos)) {

		m_FigurePosArray.Add(pos);
	}
}

// �ֻ��� ��ü ���� ����
void CSelectedFigureArray::deselect()
{
	m_FigurePosArray.RemoveAt(0);
}

// �������� ��ü ���� ����
BOOL CSelectedFigureArray::deselect(POSITION position)
{
	BOOL NOTfindFlag = TRUE;

	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		if (m_FigurePosArray[i] == position) {
			m_FigurePosArray.RemoveAt(i);
			NOTfindFlag = FALSE;
		}
	}

	return NOTfindFlag;
}

// point�� ��ġ�� �ִ� ��ü ���� ����
void CSelectedFigureArray::deselect(PointF point)
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->pointInFigure(point) == CFigure::INSIDE) {
			m_FigurePosArray.RemoveAt(i);
			break;
		}
	}
}

// rect �ȿ� �ִ� ��ü ���� ����
void CSelectedFigureArray::deselect(RectF rect)
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->figureInRect(rect)) {
			m_FigurePosArray.RemoveAt(i);
		}
	}
}

// ��ü ��ü ���� ����
void CSelectedFigureArray::deselectAll()
{
	m_FigurePosArray.RemoveAll();
}

// ������ ��ü ����
void CSelectedFigureArray::Delete()
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->destroy();
	}
}

// ��ü ��ü ����
void CSelectedFigureArray::DeleteAll()
{
	for (POSITION pos = m_FigurePtrList->GetHeadPosition(); pos; m_FigurePtrList->GetNext(pos)) {
		m_FigurePtrList->GetAt(pos)->destroy();
	}
}

// ���� ��ü �̵�
void CSelectedFigureArray::move(IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag/* = CFigure::FREEMOVE*/)
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->move(originPoint, targetPoint, moveFlag);
	}
}

// ���� ��ü ũ�� ����
void CSelectedFigureArray::resize(IN CFigure::Position selectedHandle, IN PointF originPoint, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag/* = CFigure::FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->resize(selectedHandle, targetPoint, resizeFlag, anchorPoint);
	}
}

// ���� ��ü �� �׷� ����
void CSelectedFigureArray::unGroup()
{
	CFigure* figure;

	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		figure = m_FigurePtrList->GetAt(m_FigurePosArray[i]);

		if (figure->IsKindOf(RUNTIME_CLASS(CGroup))) {
			((CGroup*)figure)->unGroup(m_FigurePosArray[i] , *this);
		}
	}
}

// ���� ��ü �׸���
void CSelectedFigureArray::draw(IN Graphics& graphics)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->draw(graphics);
	}
}

// ���� ��ü���� ���� ���� �׸���
void CSelectedFigureArray::drawArea(IN Graphics& graphics, IN BOOL editPointFlag)
{
	if (hasOne()) {
		CFigure* figure = getOneFigure();

		if (editPointFlag){
			if (figure->IsKindOf(RUNTIME_CLASS(CStrap)) && !figure->IsKindOf(RUNTIME_CLASS(CPencil))){
				((CStrap*)figure)->drawLineHandle(graphics);
			}
			else if (figure->IsKindOf(RUNTIME_CLASS(CPolygon))){
				((CPolygon*)figure)->drawLineHandle(graphics);
			}
		}
		//else if (figure->IsKindOf(RUNTIME_CLASS(CLine))) {
		//	((CLine*)figure)->drawArea(graphics);
		//}
		//else if (figure->IsKindOf(RUNTIME_CLASS(CPolyLine))) {
		//	((CPolyLine*)figure)->drawArea(graphics);
		//}
		else {
			figure->drawArea(graphics);
		}
		return;
	}

	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->drawArea(graphics);
	}
}

// ���� ��ü �̵� �׸���
RectF CSelectedFigureArray::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag/* = CFigure::FREEMOVE*/)
{
	RectF drawnArea = m_FigurePtrList->GetAt(m_FigurePosArray[0])->getArea();
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->moving(graphics, originPoint, targetPoint, moveFlag);
		RectF::Union(drawnArea, drawnArea, m_FigurePtrList->GetAt(m_FigurePosArray[i])->getArea());		// �׷��� ������ ��ü�� ������ ��ħ
	}
	return drawnArea;
}

// ���� ��ü ũ�� ���� �׸���
RectF CSelectedFigureArray::resizing(IN Graphics& graphics, IN CFigure::Position selectedHandle, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag/* = CFigure::FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	RectF drawnArea = m_FigurePtrList->GetAt(m_FigurePosArray[0])->getArea();
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->resizing(graphics, selectedHandle, targetPoint, resizeFlag, anchorPoint);
		RectF::Union(drawnArea, drawnArea, m_FigurePtrList->GetAt(m_FigurePosArray[i])->getArea());		// �׷��� ������ ��ü�� ������ ��ħ
	}
	return drawnArea;
}

// ���� ��ü ������ �� ����
BOOL CSelectedFigureArray::setOutlineColor(IN const Color& outlineColor)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setOutlineColor(outlineColor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// ���� ��ü ������ �β� ����
BOOL CSelectedFigureArray::setOutlineWidth(IN const REAL outlineWidth)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setOutlineWidth(outlineWidth)) {
			return TRUE;
		}
	}

	return FALSE;
}

// ���� ��ü ������ ���� ����
BOOL CSelectedFigureArray::setOutlinePattern(IN const DashStyle outlinePattern)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setOutlinePattern(outlinePattern)) {
			return TRUE;
		}
	}

	return FALSE;
}

// ���� ��ü ä��� �� ����
BOOL CSelectedFigureArray::setFillColor(IN const Color& fillColor)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setFillColor(fillColor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// ���� ��ü ä��� ������ ����
BOOL CSelectedFigureArray::setFillSubcolor(IN const Color& fillSubcolor)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setFillSubcolor(fillSubcolor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// ���� ��ü ä��� ���� ����
BOOL CSelectedFigureArray::setFillPattern(IN const HatchStyle fillPattern)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setFillPattern(fillPattern)) {
			return TRUE;
		}
	}

	return FALSE;
}

// FigurePtrList ȹ��
CFigurePtrList* CSelectedFigureArray::getFigurePtrList()
{
	return m_FigurePtrList;
}

// FigurePtrList ����
void CSelectedFigureArray::setFigurePtrList(CFigurePtrList* lpFigurePtrList)
{
	m_FigurePosArray.RemoveAll();
	m_FigurePtrList = lpFigurePtrList;
}

// �������� ���� �迭�� ����
const POSITION* CSelectedFigureArray::getData()
{
	return m_FigurePosArray.GetData();
}

// �������� ���� �迭�� ���� ������ ����
int CSelectedFigureArray::getSize()
{
	return m_FigurePosArray.GetSize();
}

// �� ���� ������ ȹ��
POSITION CSelectedFigureArray::getForwardPos()
{
	POSITION result = m_FigurePosArray[0];

	for (int i = 1; i < m_FigurePosArray.GetSize(); i++) {
		if (result > m_FigurePosArray[i]) {
			result = m_FigurePosArray[i];
		}
	}

	return result;
}