// SelectedFigureArray.h : CSelectedFigureArray 클래스의 인터페이스
// CSelectedFigureArray : CFigurePtrList 객체를 관리하는 클래스
// @Author Lee Hwajung

#pragma once

// CSelectedFigureArray 명령 대상입니다.

typedef CArray<POSITION, POSITION&> CPositionArray;

class CSelectedFigureArray : public CObject
{
public:
	//CSelectedFigureArray();
	// 생성자
	CSelectedFigureArray(CFigurePtrList* lpFigurePtrList);

	// 소멸자
	virtual ~CSelectedFigureArray();

	// 선택한 개체가 있는지 검사
	BOOL isEmpty();

	// 선택한 개체가 한 개인지 검사
	BOOL hasOne();								// hasOneFigure

	// 선택한 개체 중 최 상위 개체 획득
	CFigure* getOneFigure();

	// 점이 선택한 개체의 어디에 있는지 확인
	CFigure::Position contains(PointF point);	// pointInFigure

	// 최상위 개체 선택
	void select();

	// point의 위치에 있는 개체 선택
	CFigure::Position select(PointF point);		// getFigure

	// rect 안에 있는 개체 선택
	void select(RectF rect);					// getFigures

	// 전체 개체 선택
	void selectAll();

	// 최상위 개체 선택 해제
	void deselect();

	// point의 위치이 있는 개체 선택 해제
	void deselect(PointF point);

	// rect 안에 있는 개체 선택 해제
	void deselect(RectF rect);

	// 전체 개체 선택 해제
	void deselectAll(RectF rect);

	// 선택한 개체 삭제
	void Delete();

	// 전체 개체 삭제
	void DeleteAll ();

	// 선택 개체 이동
	void move(IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag = CFigure::FREEMOVE);
	
	// 선택 개체 크기 변경
	void resize(IN CFigure::Position selectedHandle, IN PointF originPoint, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE, IN PointF* anchorPoint = NULL);

	// 선택 개체 그리기
	void draw(IN Graphics& graphics);

	// 선택 개체들의 선택 영역 그리기
	void drawArea(IN Graphics& graphics);

	// 선택 개체 이동 그리기
	RectF moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN CFigure::MoveFlag moveFlag = CFigure::FREEMOVE);
	
	// 선택 개체 크기 변경 그리기
	RectF resizing(IN Graphics& graphics, IN CFigure::Position selectedHandle, IN PointF targetPoint, IN CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE, IN PointF* anchorPoint = NULL);

	// 선택 개체 윤곽선 색 설정
	BOOL setOutlineColor(IN const Color& outlineColor);

	// 선택 개체 윤곽선 두께 설정
	BOOL setOutlineWidth(IN const REAL outlineWidth);

	// 선택 개체 윤곽선 패턴 설정
	BOOL setOutlinePattern(IN const DashStyle outlinePattern);

	// 선택 개체 채우기 색 설정
	BOOL setFillColor(IN const Color& fillColor);

	// 선택 개체 채우기 보조색 설정
	BOOL setFillSubcolor(IN const Color& fillSubcolor);

	// 선택 개체 채우기 패턴 설정
	BOOL setFillPattern(IN const HatchStyle fillPattern);

	// FigurePtrList 획득
	CFigurePtrList* getFigurePtrList();

	// FigurePtrList 설정
	void setFigurePtrList(CFigurePtrList* lpFigurePtrList);

private:
	// 맨 앞의 포지션 획득
	POSITION getForwardPos();

private:
	CPositionArray m_FigurePosArray;
	CFigurePtrList* m_FigurePtrList;
};


