// SelectedFigureArray.cpp : CSelectedFigureArray 클래스의 구현
// CSelectedFigureArray : CFigurePtrList 객체를 관리하는 클래스
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

// 최상위 개체 선택
void CSelectedFigureArray::select()
{

}

// point의 위치에 있는 개체 선택
CFigure::Position CSelectedFigureArray::select(PointF point)	// getFigure
{

}

// rect 안에 있는 개체 선택
void CSelectedFigureArray::select(RectF rect)					// getFigures
{

}

// 전체 개체 선택
void CSelectedFigureArray::selectAll()
{

}

// 최상위 개체 선택 해제
void CSelectedFigureArray::deselect()
{

}

// point의 위치이 있는 개체 선택 해제
void CSelectedFigureArray::deselect(PointF point)
{

}

// rect 안에 있는 개체 선택 해제
void CSelectedFigureArray::deselect(RectF rect)
{

}

// 전체 개체 선택 해제
void CSelectedFigureArray::deselectAll(RectF rect)
{

}

// 선택한 개체 삭제
void CSelectedFigureArray::Delete()
{

}

// 전체 개체 삭제
void CSelectedFigureArray::DeleteAll()
{

}

// 선택 개체 이동
void CSelectedFigureArray::move(IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag = CFigure::FREEMOVE)
{

}

// 선택 개체 크기 변경
void CSelectedFigureArray::resize(IN CFigure::Position selectedHandle, IN PointF originPoint, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE, IN PointF* anchorPoint = NULL)
{

}

// 선택 개체 그리기
void CSelectedFigureArray::draw(IN Graphics& graphics)
{

}

// 선택 개체들의 선택 영역 그리기
void CSelectedFigureArray::drawArea(IN Graphics& graphics)
{

}

// 선택 개체 이동 그리기
RectF CSelectedFigureArray::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag = CFigure::FREEMOVE)
{

}

// 선택 개체 크기 변경 그리기
RectF CSelectedFigureArray::resizing(IN Graphics& graphics, IN CFigure::Position selectedHandle, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE, IN PointF* anchorPoint = NULL)
{

}

// 선택 개체 윤곽선 색 설정
BOOL CSelectedFigureArray::setOutlineColor(IN const Color& outlineColor)
{

}

// 선택 개체 윤곽선 두께 설정
BOOL CSelectedFigureArray::setOutlineWidth(IN const REAL outlineWidth)
{

}

// 선택 개체 윤곽선 패턴 설정
BOOL CSelectedFigureArray::setOutlinePattern(IN const DashStyle outlinePattern)
{

}

// 선택 개체 채우기 색 설정
BOOL CSelectedFigureArray::setFillColor(IN const Color& fillColor)
{

}

// 선택 개체 채우기 보조색 설정
BOOL CSelectedFigureArray::setFillSubcolor(IN const Color& fillSubcolor)
{
	
}

// 선택 개체 채우기 패턴 설정
BOOL CSelectedFigureArray::setFillPattern(IN const HatchStyle fillPattern)
{

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