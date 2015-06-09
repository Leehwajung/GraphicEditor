// Curve.cpp : CCurve Ŭ������ ����
// CCurve : � ��ü�� �����ϴ� Ŭ����
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


// CCurve ��� �Լ�
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
	// 1. ���� ��ǥ�� ONHANDLE �� ��
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

	// �ٱ� ����
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

	// ������ �׸��� �κ� 

	graphics.DrawCurve(CGlobal::crateIngPen(m_OutlinePen), pointsArray.GetData(), pointsArray.GetSize());

	return drawnArea;
}
RectF CCurve::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/){
	RectF drawnArea;

	/* ���� �̵� �� �� �̵��� ��� ���� ���ϱ� ���� */
	PointF RelativePoint = targetPoint - originPoint;

	// Curve�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
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

	// Curve�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
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

	// Curve�� �׷��ֱ� ���� CList�� CArray�� �ٲ��ִ� ����� ����ϱ�� �Ѵ�.
	CArray<PointF, PointF&> pointsArray;

	for (POSITION pos = m_PointsList.GetHeadPosition(); pos; m_PointsList.GetNext(pos)) {
		pointsArray.Add(m_PointsList.GetAt(pos));
	}

	// Draw the Curve.
	graphics.DrawCurve(m_OutlinePen, pointsArray.GetData(), pointsArray.GetSize());
}
