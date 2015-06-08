// SelectedFigureArray.cpp : CSelectedFigureArray Ŭ������ ����
// CSelectedFigureArray : CFigurePtrList ��ü�� �����ϴ� Ŭ����
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "SelectedFigureArray.h"


// CSelectedFigureArray

//CSelectedFigureArray::CSelectedFigureArray()
//{
//}

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

	for (int i = 1; i < m_FigurePosArray.GetSize(); i++) {
		if (result > m_FigurePosArray[i]) {
			result = m_FigurePosArray[i];
		}
	}



	CFigure::Position figPosition;
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		figPosition = this->GetAt(pos)->pointInFigure(point);
		if (figPosition != CFigure::OUTSIDE) {
			return figPosition;
		}
	}

	return CFigure::OUTSIDE;
}

// �ֻ��� ��ü ����
void CSelectedFigureArray::select()
{

}

// point�� ��ġ�� �ִ� ��ü ����
CFigure::Position CSelectedFigureArray::select(PointF point)	// getFigure
{

}

// rect �ȿ� �ִ� ��ü ����
void CSelectedFigureArray::select(RectF rect)					// getFigures
{

}

// ��ü ��ü ����
void CSelectedFigureArray::selectAll()
{

}

// �ֻ��� ��ü ���� ����
void CSelectedFigureArray::deselect()
{

}

// point�� ��ġ�� �ִ� ��ü ���� ����
void CSelectedFigureArray::deselect(PointF point)
{

}

// rect �ȿ� �ִ� ��ü ���� ����
void CSelectedFigureArray::deselect(RectF rect)
{

}

// ��ü ��ü ���� ����
void CSelectedFigureArray::deselectAll(RectF rect)
{

}

// ������ ��ü ����
void CSelectedFigureArray::Delete()
{

}

// ��ü ��ü ����
void CSelectedFigureArray::DeleteAll()
{

}

// ���� ��ü �̵�
void CSelectedFigureArray::move(IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag = CFigure::FREEMOVE)
{

}

// ���� ��ü ũ�� ����
void CSelectedFigureArray::resize(IN CFigure::Position selectedHandle, IN PointF originPoint, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE, IN PointF* anchorPoint = NULL)
{

}

// ���� ��ü �׸���
void CSelectedFigureArray::draw(IN Graphics& graphics)
{

}

// ���� ��ü���� ���� ���� �׸���
void CSelectedFigureArray::drawArea(IN Graphics& graphics)
{

}

// ���� ��ü �̵� �׸���
RectF CSelectedFigureArray::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag = CFigure::FREEMOVE)
{

}

// ���� ��ü ũ�� ���� �׸���
RectF CSelectedFigureArray::resizing(IN Graphics& graphics, IN CFigure::Position selectedHandle, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE, IN PointF* anchorPoint = NULL)
{

}

// ���� ��ü ������ �� ����
BOOL CSelectedFigureArray::setOutlineColor(IN const Color& outlineColor)
{

}

// ���� ��ü ������ �β� ����
BOOL CSelectedFigureArray::setOutlineWidth(IN const REAL outlineWidth)
{

}

// ���� ��ü ������ ���� ����
BOOL CSelectedFigureArray::setOutlinePattern(IN const DashStyle outlinePattern)
{

}

// ���� ��ü ä��� �� ����
BOOL CSelectedFigureArray::setFillColor(IN const Color& fillColor)
{

}

// ���� ��ü ä��� ������ ����
BOOL CSelectedFigureArray::setFillSubcolor(IN const Color& fillSubcolor)
{
	
}

// ���� ��ü ä��� ���� ����
BOOL CSelectedFigureArray::setFillPattern(IN const HatchStyle fillPattern)
{

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