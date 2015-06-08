// FigurePtrList.h : CFigurePtrList 클래스의 인터페이스
// CFigurePtrList : 개체들의 포인터를 저장하는 리스트 클래스
// @Author Lee Hwajung

#pragma once

// CFigurePtrList 명령 대상입니다.

class CFigurePtrList : public CTypedPtrList<CObList, CFigure*>/*CObList*/ /*CList < CFigurePtr, CFigurePtr >*/
{							// CTypedPtrList: https://msdn.microsoft.com/ko-kr/library/850101a7.aspx
public:
	CFigurePtrList& operator= (const CFigurePtrList& figurePtrList);

	void deleteAt(POSITION position);
	void deleteAll();
	void deleteHead();
	void deleteTail();

	BOOL hasOneFigure();

	void move(IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag = CFigure::FREEMOVE);
	void resize(IN CFigure::Position selectedHandle, IN PointF originPoint, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE, IN PointF* anchorPoint = NULL);

	CFigure::Position pointInFigure(IN PointF point);

	CFigure* getFigure(IN PointF point);
	CFigure::Position getFigure(IN PointF point, OUT CFigurePtrList& figureList);
	CFigure::Position getFigures(IN RectF rect, OUT CFigurePtrList& figureList);

	void draw(IN Graphics& graphics);
	void drawArea(IN Graphics& graphics);
	RectF moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag = CFigure::FREEMOVE);
	RectF resizing(IN Graphics& graphics, IN CFigure::Position selectedHandle, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE, IN PointF* anchorPoint = NULL);

	BOOL setOutlineColor(IN const Color& outlineColor);
	BOOL setOutlineWidth(IN const REAL outlineWidth);
	BOOL setOutlinePattern(IN const DashStyle outlinePattern);
	BOOL setFillColor(IN const Color& fillColor);
	BOOL setFillSubcolor(IN const Color& fillSubcolor);
	BOOL setFillPattern(IN const HatchStyle fillPattern);
};