// FigurePtrList.cpp : CFigurePtrList 클래스의 구현
// CFigurePtrList : 개체들의 포인터를 저장하는 리스트 클래스
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "FigurePtrList.h"


// CFigurePtrList

//CFigurePtrList::CFigurePtrList()
//{
//}
//
//CFigurePtrList::~CFigurePtrList()
//{
//}


// CFigurePtrList 멤버 함수

CFigurePtrList& CFigurePtrList::operator = (const CFigurePtrList& figurePtrList)
{
	this->RemoveAll();

	for (POSITION pos = figurePtrList.GetHeadPosition(); pos; figurePtrList.GetNext(pos)) {
		this->AddTail(figurePtrList.GetAt(pos));
	}

	return *this;
}

void CFigurePtrList::deleteAt(POSITION position)
{
	this->GetAt(position)->~CFigure();
	this->RemoveAt(position);
}

void CFigurePtrList::deleteAll()
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		this->GetAt(pos)->~CFigure();
	}
	this->RemoveAll();
}

void CFigurePtrList::deleteHead()
{
	this->RemoveHead()->~CFigure();
}

void CFigurePtrList::deleteTail()
{
	this->RemoveTail()->~CFigure();
}

BOOL CFigurePtrList::hasOneFigure()
{
	return this->GetSize() == 1;
}

void CFigurePtrList::move(IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag/* = CFigure::FREEMOVE*/)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		this->GetAt(pos)->move(originPoint, targetPoint, moveFlag);
	}
}

void CFigurePtrList::resize(IN CFigure::Position selectedHandle, IN PointF originPoint, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag/* = CFigure::FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	//CFigure::Position figPosition;
	//for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
	//	figPosition = this->GetAt(pos)->pointInFigure(point);
	//	if (figPosition != CFigure::OUTSIDE) {
	//		return figPosition;
	//	}
	//}

	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		this->GetAt(pos)->resize(selectedHandle, targetPoint, resizeFlag, anchorPoint);
	}
}

CFigure::Position CFigurePtrList::pointInFigure(IN PointF point)
{
	if (this->hasOneFigure()) {
		if (this->GetHead()->IsKindOf(RUNTIME_CLASS(CLine))) {
			return ((CLine*)this->GetHead())->pointInFigure(point);
		}
		else if (this->GetHead()->IsKindOf(RUNTIME_CLASS(CPolyLine))) {
			return ((CPolyLine*)this->GetHead())->pointInFigure(point);
		}
		else {
			return this->GetHead()->pointInFigure(point);
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

CFigure* CFigurePtrList::getFigure(IN PointF point)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		if (this->GetAt(pos)->pointInFigure(point) == CFigure::INSIDE) {
			return this->GetAt(pos);
		}
	}
}

CFigure::Position CFigurePtrList::getFigure(IN PointF point, OUT CFigurePtrList& figureList)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		if (this->GetAt(pos)->pointInFigure(point) == CFigure::INSIDE) {
			figureList.AddTail(this->GetAt(pos));

			return CFigure::INSIDE;
		}
	}

	return  CFigure::OUTSIDE;
}

CFigure::Position CFigurePtrList::getFigures(IN RectF rect, OUT CFigurePtrList& figureList)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		if (this->GetAt(pos)->figureInRect(rect)) {
			figureList.AddTail(this->GetAt(pos));
		}
	}

	return CFigure::OUTSIDE;
}

void CFigurePtrList::draw(IN Graphics& graphics)
{
	for (POSITION pos = this->GetTailPosition(); pos; this->GetPrev(pos)) {
		this->GetAt(pos)->draw(graphics);
	}
}

void CFigurePtrList::drawArea(IN Graphics& graphics)
{
	if (this->hasOneFigure()) {
		if (this->GetHead()->IsKindOf(RUNTIME_CLASS(CShape))) {
			return ((CShape*)this->GetHead())->drawArea(graphics);
		}
		//else if (this->GetHead()->IsKindOf(RUNTIME_CLASS(CLine))) {
		//	return ((CLine*)this->GetHead())->drawHandles(graphics);
		//}
		//else if (this->GetHead()->IsKindOf(RUNTIME_CLASS(CPolyLine))) {
		//	return ((CPolyLine*)this->GetHead())->drawHandles(graphics);
		//}
		else {
			return this->GetHead()->drawArea(graphics);
		}
	}

	for (POSITION pos = this->GetTailPosition(); pos; this->GetPrev(pos)) {
		this->GetAt(pos)->drawArea(graphics);
	}
}

RectF CFigurePtrList::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag/* = CFigure::FREEMOVE*/)
{
	RectF drawnArea = this->GetHead()->getArea();
	for (POSITION pos = this->GetTailPosition(); pos; this->GetPrev(pos)) {
		this->GetAt(pos)->moving(graphics, originPoint, targetPoint, moveFlag);
		RectF::Union(drawnArea, drawnArea, this->GetAt(pos)->getArea());		// 그룹의 영역에 개체의 영역을 합침
	}
	return drawnArea;
}

RectF CFigurePtrList::resizing(IN Graphics& graphics, IN CFigure::Position selectedHandle, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag/* = CFigure::FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	RectF drawnArea = this->GetHead()->getArea();
	for (POSITION pos = this->GetTailPosition(); pos; this->GetPrev(pos)) {
		this->GetAt(pos)->resizing(graphics, selectedHandle, targetPoint, resizeFlag, anchorPoint);
		RectF::Union(drawnArea, drawnArea, this->GetAt(pos)->getArea());		// 그룹의 영역에 개체의 영역을 합침
	}
	return drawnArea;
}

BOOL CFigurePtrList::setOutlineColor(IN const Color& outlineColor)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		if (this->GetAt(pos)->setOutlineColor(outlineColor)) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CFigurePtrList::setOutlineWidth(IN const REAL outlineWidth)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		if (this->GetAt(pos)->setOutlineWidth(outlineWidth)) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CFigurePtrList::setOutlinePattern(IN const DashStyle outlinePattern)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		if (this->GetAt(pos)->setOutlinePattern(outlinePattern)) {
			return TRUE;
		}
	}

	return FALSE;
}

void CFigurePtrList::setFillBrush(IN const Brush* brush, IN BOOL PropertyMaintenanceFlag/* = FALSE*/)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		this->GetAt(pos)->setFillBrush(brush, PropertyMaintenanceFlag);
	}
}

BOOL CFigurePtrList::setFillColor(IN const Color& fillColor)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		if (this->GetAt(pos)->setFillColor(fillColor)) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CFigurePtrList::setFillSubcolor(IN const Color& fillSubcolor)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		if (this->GetAt(pos)->setFillSubcolor(fillSubcolor)) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CFigurePtrList::setFillPattern(IN const HatchStyle fillPattern)
{
	for (POSITION pos = this->GetHeadPosition(); pos; this->GetNext(pos)) {
		if (this->GetAt(pos)->setFillPattern(fillPattern)) {
			return TRUE;
		}
	}

	return FALSE;
}
