// Curve.cpp : CCurve 클래스의 구현
// CCurve : 곡선 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Curve.h"


// CCurve

IMPLEMENT_SERIAL(CCurve, CPolyLine, 1)

CCurve::CCurve()
	: CPolyLine()
{
}

CCurve::CCurve(IN Pen* pen)
:CPolyLine(pen)
{

}
CCurve::CCurve(IN Pen* pen, CList <PointF, PointF&>& list)
:CPolyLine(pen,list)
{

}

CCurve::~CCurve()
{
}


// CCurve 멤버 함수
CFigure* CCurve::clone(){
	return new CCurve(m_OutlinePen, m_PointsList);
}

void CCurve::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

CFigure::Position CCurve::pointInFigure(IN PointF point) {
	// 1. 현재 좌표가 ONHANDLE 일 때
	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = m_PointsList.GetNext(pos);

		RectF handleRect;
		handleRect = getHandleRect(tmp_point);

		if (handleRect.Contains(point))
			return ONHANDLE;
	}

	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	GraphicsPath gp;
	gp.AddCurve(pointsArray.GetData(), pointsArray.GetSize());
	if (gp.IsVisible(point)) {
		return INSIDE;
	}

	// 바깥 영역
	return OUTSIDE;


}

RectF CCurve::creating(IN Graphics& graphics, IN PointF addingPoint, IN CreateFlag createFlag /*= FREECREATE*/){
	return creating(graphics, &addingPoint, &createFlag);
}
RectF CCurve::creating(IN Graphics& graphics, void* param1, ...){
	va_list vaList;
	va_start(vaList, param1);
	PointF* addingPoint = (PointF*)param1;
	CreateFlag createFlag = va_arg(vaList, CreateFlag);
	va_end(vaList);

	RectF drawnArea;

	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}
	pointsArray.Add(*addingPoint);

	// 실제로 그리는 부분 

	graphics.DrawCurve(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());

	return drawnArea;
}
RectF CCurve::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/){
	RectF drawnArea;

	/* 끌고 이동 할 때 이동한 상대 값을 구하기 위함 */
	PointF RelativePoint = targetPoint - originPoint;

	// Curve을 그려주기 전에 CList를 CArray로 바꿔주는 방법을 사용하기로 한다.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos) + RelativePoint);
	}

	// Draw the Curve.
	graphics.DrawCurve(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());
	return drawnArea;
}
RectF CCurve::resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/){
	RectF drawnArea;
	return drawnArea;
}
RectF CCurve::pointMoving(Graphics& graphics, IN PointF originPoint, IN PointF targetPoint){
	RectF drawnArea;

	PointF  point;

	BOOL SameHandle = FALSE;

	// Curve을 그려주기 전에 CList를 CArray로 바꿔주는 방법을 사용하기로 한다.
	CArray<PointF, PointF&> pointsArray;
	CArray<RectF, RectF&> HandleRectArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		point = m_PointsList.GetAt(pos);

		RectF handleRect;
		handleRect = getHandleRect(point);
		HandleRectArray.Add(handleRect);

		for (int i = 0; i < HandleRectArray.GetSize() - 1; i++){
			for (int j = i + 1; j < HandleRectArray.GetSize(); j++)
			if (HandleRectArray[i].Contains(originPoint) && HandleRectArray[j].Contains(originPoint))
				SameHandle = TRUE;
		}
		if (SameHandle == FALSE){
			if (handleRect.Contains(originPoint)){
				point = targetPoint;
				pointsArray.Add(point);
			}
			else pointsArray.Add(point);
		}
	}

	graphics.DrawCurve(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());

	return drawnArea;
}
void CCurve::draw(IN Graphics& graphics){

	// Curve를 그려주기 전에 CList를 CArray로 바꿔주는 방법을 사용하기로 한다.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	// Draw the Curve.
	graphics.DrawCurve(m_OutlinePen, pointsArray.GetData(), pointsArray.GetSize());
}
