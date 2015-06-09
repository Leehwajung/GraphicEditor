// Pencil.cpp : CPencil 클래스의 구현
// CPencil : 자유 곡선(연필) 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Pencil.h"


// CPencil

IMPLEMENT_SERIAL(CPencil, CPolyLine, 1)

CPencil::CPencil()
	:CPolyLine()//, m_CreatedFlag(FALSE)
{
}

CPencil::CPencil(IN Pen* pen)
: CPolyLine(pen)//, m_CreatedFlag(FALSE)
{

}

CPencil::CPencil(IN Pen* pen, CList <PointF, PointF&>& list)
: CPolyLine(pen,list)
{

}
CPencil::~CPencil()
{

}

CFigure* CPencil::clone(){
	return new CPencil(m_OutlinePen,m_PointsList);
}

// CPencil 멤버 함수
CFigure::Position CPencil::pointInFigure(IN PointF point){

	// 1. 현재 좌표가 ONHANDLE 일 때
	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = m_PointsList.GetNext(pos);

		RectF handleRect;
		handleRect = getHandleRect(tmp_point);

		if (handleRect.Contains(point))
			return INSIDE;
	}

	// 2. 현재 좌표가 선이 있는 영역에 있을 때 INSIDE이다.
	pos = m_PointsList.GetHeadPosition();
	PointF first_point = m_PointsList.GetNext(pos);
	while (pos != NULL){
		PointF second_point = m_PointsList.GetNext(pos);

		REAL Gradient = (first_point.Y - second_point.Y) / (first_point.X - second_point.X);

		const int count = 4;

		REAL tmp_seta = atan(-1 / Gradient);
		REAL seta = 90 - tmp_seta;

		PointF points[count];
		GraphicsPath path;
		int width = (m_OutlinePen->GetWidth() > HANDLESIZE) ? m_OutlinePen->GetWidth() : HANDLESIZE;
		if (Gradient >= 0){
			points[0] = PointF(first_point.X + width / 2 * cos(seta), first_point.Y + width / 2 * sin(seta));
			points[1] = PointF(first_point.X - width / 2 * cos(seta), first_point.Y - width / 2 * sin(seta));
			points[2] = PointF(second_point.X - width / 2 * cos(seta), second_point.Y - width / 2 * sin(seta));
			points[3] = PointF(second_point.X + width / 2 * cos(seta), second_point.Y + width / 2 * sin(seta));
		}
		else if (Gradient < 0){
			points[0] = PointF(first_point.X - width / 2 * cos(seta), first_point.Y + width / 2 * sin(seta));
			points[1] = PointF(first_point.X + width / 2 * cos(seta), first_point.Y - width / 2 * sin(seta));
			points[2] = PointF(second_point.X + width / 2 * cos(seta), second_point.Y - width / 2 * sin(seta));
			points[3] = PointF(second_point.X - width / 2 * cos(seta), second_point.Y + width / 2 * sin(seta));
		}
		path.AddPolygon(points, count);

		Region rgn(&path);
		if (rgn.IsVisible(point)) {
			return INSIDE;
		}
		first_point = second_point;
	}

	// 바깥 영역
	return OUTSIDE;
}
// Menu Item
/* 선 삭제 */
void CPencil::destroy() {

	if (this) {
		this->~CPencil();
	}
	//invalidate 다른 것들은 일단 보류
}
