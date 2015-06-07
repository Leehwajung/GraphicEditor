// Pencil.cpp : CPencil Ŭ������ ����
// CPencil : ���� �(����) ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Pencil.h"


IMPLEMENT_SERIAL(CPencil, CPolyLine, 1)

// CPencil

CPencil::CPencil()
:CPolyLine()//, m_CreatedFlag(FALSE)
{
}

CPencil::CPencil(IN Pen* pen)
: CPolyLine(pen)//, m_CreatedFlag(FALSE)
{

}

CPencil::~CPencil()
{
}


// CPencil ��� �Լ�
CFigure::Position CPencil::pointInFigure(IN PointF point){

	// 1. ���� ��ǥ�� ONHANDLE �� ��
	POSITION pos = m_PointsList.GetHeadPosition();
	while (pos != NULL){
		PointF  tmp_point = m_PointsList.GetNext(pos);

		RectF handleRect;
		handleRect = getHandleRect(tmp_point);

		if (handleRect.Contains(point))
			return INSIDE;
	}

	// 2. ���� ��ǥ�� ���� �ִ� ������ ���� �� INSIDE�̴�.
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

	// �ٱ� ����
	return OUTSIDE;
}
// Menu Item
/* �� ���� */
void CPencil::destroy() {

	if (this) {
		this->~CPencil();
	}
	//invalidate �ٸ� �͵��� �ϴ� ����
}

void CPencil::drawArea(IN Graphics& graphics) {

	CFigure::drawArea(graphics);
}