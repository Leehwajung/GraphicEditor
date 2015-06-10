// SelectedFigureArray.cpp : CSelectedFigureArray 클래스의 구현
// CSelectedFigureArray : CFigurePtrList 객체를 관리하는 클래스
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


// CSelectedFigureArray 멤버 함수

// 선택한 개체가 있는지 검사
BOOL CSelectedFigureArray::isEmpty()
{
	return m_FigurePosArray.IsEmpty();
}

// 선택한 개체가 한 개인지 검사
BOOL CSelectedFigureArray::hasOne()								// hasOneFigure
{
	return m_FigurePosArray.GetSize() == 1;
}

// 선택한 개체 중 최 상위 개체 획득
CFigure* CSelectedFigureArray::getOneFigure()
{
	if (hasOne()) {
		return m_FigurePtrList->GetAt(m_FigurePosArray[0]);
	}

	return m_FigurePtrList->GetAt(getForwardPos());
}

// 점이 선택한 개체의 어디에 있는지 확인
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
		//else if (getOneFigure()->IsKindOf(RUNTIME_CLASS(CPencil))) {
		//	return ((CPolyLine*)figure)->pointInFigure(point);
		//}
		//else if (getOneFigure()->IsKindOf(RUNTIME_CLASS(CCurve))) {
		//	return ((CPolyLine*)figure)->pointInFigure(point);
		//}
		else if (getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolygon))) {
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

// 최상위 개체 선택
void CSelectedFigureArray::select()
{
	deselectAll();
	m_FigurePosArray.Add(m_FigurePtrList->GetHeadPosition());
}

// 포지션의 개체 선택
void CSelectedFigureArray::select(POSITION position)
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		if (m_FigurePosArray[i] == position) {
			return;		// 동일한 포지션이 존재하면 종료
		}
	}

	m_FigurePosArray.Add(position);
}

// point의 위치에 있는 개체 선택
CFigure::Position CSelectedFigureArray::select(PointF point)	// getFigure
{
	for (POSITION pos = m_FigurePtrList->GetHeadPosition(); pos; m_FigurePtrList->GetNext(pos)) {
		if (m_FigurePtrList->GetAt(pos)->pointInFigure(point) == CFigure::INSIDE) {
			for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
				if (m_FigurePosArray[i] == pos) {
					return CFigure::INSIDE;;		// 동일한 포지션이 존재하면 종료
				}
			}

			m_FigurePosArray.Add(pos);

			return CFigure::INSIDE;
		}
	}

	return  CFigure::OUTSIDE;
}

// rect 안에 있는 개체 선택
void CSelectedFigureArray::select(RectF rect)					// getFigures
{
	for (POSITION pos = m_FigurePtrList->GetHeadPosition(); pos; m_FigurePtrList->GetNext(pos)) {
		if (m_FigurePtrList->GetAt(pos)->figureInRect(rect)) {
			for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
				if (m_FigurePosArray[i] == pos) {
					break;		// 동일한 포지션이 존재하면 종료
				}
			}

			m_FigurePosArray.Add(pos);
		}
	}
}

// 전체 개체 선택
void CSelectedFigureArray::selectAll()
{
	m_FigurePosArray.RemoveAll();

	for (POSITION pos = m_FigurePtrList->GetHeadPosition(); pos; m_FigurePtrList->GetNext(pos)) {

		m_FigurePosArray.Add(pos);
	}
}

// 최상위 개체 선택 해제
void CSelectedFigureArray::deselect()
{
	m_FigurePosArray.RemoveAt(0);
}

// 포지션의 개체 선택 해제
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

// point의 위치이 있는 개체 선택 해제
void CSelectedFigureArray::deselect(PointF point)
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->pointInFigure(point) == CFigure::INSIDE) {
			m_FigurePosArray.RemoveAt(i);
			break;
		}
	}
}

// rect 안에 있는 개체 선택 해제
void CSelectedFigureArray::deselect(RectF rect)
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->figureInRect(rect)) {
			m_FigurePosArray.RemoveAt(i);
		}
	}
}

// 전체 개체 선택 해제
void CSelectedFigureArray::deselectAll()
{
	m_FigurePosArray.RemoveAll();
}

// 선택한 개체 삭제
void CSelectedFigureArray::Delete()
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->destroy();
	}
}

// 전체 개체 삭제
void CSelectedFigureArray::DeleteAll()
{
	for (POSITION pos = m_FigurePtrList->GetHeadPosition(); pos; m_FigurePtrList->GetNext(pos)) {
		m_FigurePtrList->GetAt(pos)->destroy();
	}
}

// 선택 개체 이동
void CSelectedFigureArray::move(IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag/* = CFigure::FREEMOVE*/)
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->move(originPoint, targetPoint, moveFlag);
	}
}

// 선택 개체 크기 변경
void CSelectedFigureArray::resize(IN CFigure::Position selectedHandle, IN PointF originPoint, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag/* = CFigure::FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->resize(selectedHandle, targetPoint, resizeFlag, anchorPoint);
	}
}

// 선택 개체 중 그룹 해제
void CSelectedFigureArray::unGroup()
{
	CFigure* figure;

	for (int i = 0; i < m_FigurePosArray.GetSize(); i++) {
		figure = m_FigurePtrList->GetAt(m_FigurePosArray[i]);

		if (figure->IsKindOf(RUNTIME_CLASS(CGroup))) {
			int groupsize = ((CGroup*)figure)->getFiguresList().GetSize();
			((CGroup*)figure)->unGroup(m_FigurePosArray[i] , *this);
			i += (groupsize - 1);
		}
	}
}

// 선택 개체 그리기
void CSelectedFigureArray::draw(IN Graphics& graphics)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->draw(graphics);
	}
}

// 선택 개체들의 선택 영역 그리기
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

// 선택 개체 이동 그리기
RectF CSelectedFigureArray::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag/* = CFigure::FREEMOVE*/)
{
	RectF drawnArea = m_FigurePtrList->GetAt(m_FigurePosArray[0])->getArea();
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->moving(graphics, originPoint, targetPoint, moveFlag);
		RectF::Union(drawnArea, drawnArea, m_FigurePtrList->GetAt(m_FigurePosArray[i])->getArea());		// 그룹의 영역에 개체의 영역을 합침
	}
	return drawnArea;
}

// 선택 개체 크기 변경 그리기
RectF CSelectedFigureArray::resizing(IN Graphics& graphics, IN CFigure::Position selectedHandle, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag/* = CFigure::FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	RectF drawnArea = m_FigurePtrList->GetAt(m_FigurePosArray[0])->getArea();
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->resizing(graphics, selectedHandle, targetPoint, resizeFlag, anchorPoint);
		RectF::Union(drawnArea, drawnArea, m_FigurePtrList->GetAt(m_FigurePosArray[i])->getArea());		// 그룹의 영역에 개체의 영역을 합침
	}
	return drawnArea;
}

// 선택 개체 윤곽선 색 설정
BOOL CSelectedFigureArray::setOutlineColor(IN const Color& outlineColor)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setOutlineColor(outlineColor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 선택 개체 윤곽선 두께 설정
BOOL CSelectedFigureArray::setOutlineWidth(IN const REAL outlineWidth)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setOutlineWidth(outlineWidth)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 선택 개체 윤곽선 패턴 설정
BOOL CSelectedFigureArray::setOutlinePattern(IN const DashStyle outlinePattern)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setOutlinePattern(outlinePattern)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 선택 개체 채우기 색 설정
BOOL CSelectedFigureArray::setFillColor(IN const Color& fillColor)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setFillColor(fillColor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 선택 개체 채우기 보조색 설정
BOOL CSelectedFigureArray::setFillSubcolor(IN const Color& fillSubcolor)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setFillSubcolor(fillSubcolor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 선택 개체 채우기 패턴 설정
BOOL CSelectedFigureArray::setFillPattern(IN const HatchStyle fillPattern)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		if (m_FigurePtrList->GetAt(m_FigurePosArray[i])->setFillPattern(fillPattern)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 선택 개체 채우기 브러시 설정
void CSelectedFigureArray::setFillBrush(IN const Brush* brush, IN BOOL PropertyMaintenanceFlag/* = FALSE*/)
{
	for (int i = m_FigurePosArray.GetSize() - 1; i >= 0; i--) {
		m_FigurePtrList->GetAt(m_FigurePosArray[i])->setFillBrush(brush, PropertyMaintenanceFlag);
	}
}

// FigurePtrList 획득
CFigurePtrList* CSelectedFigureArray::getFigurePtrList()
{
	return m_FigurePtrList;
}

// FigurePtrList 설정
void CSelectedFigureArray::setFigurePtrList(CFigurePtrList* lpFigurePtrList)
{
	m_FigurePosArray.RemoveAll();
	m_FigurePtrList = lpFigurePtrList;
}

// 포지션의 정적 배열을 얻음
const POSITION* CSelectedFigureArray::getData()
{
	return m_FigurePosArray.GetData();
}

// 포지션의 정적 배열의 원소 개수를 얻음
int CSelectedFigureArray::getSize()
{
	return m_FigurePosArray.GetSize();
}

// 맨 앞의 포지션 획득
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