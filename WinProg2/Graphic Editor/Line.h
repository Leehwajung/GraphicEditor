#pragma once
#include "Figure.h"


// Make and Edit by Byun Jun
class CLine : public CFigure
{
public:
	CLine();
	~CLine();

	// LButtonDown
	virtual void Create(CPoint startingPoint);					// 선 생성
	virtual operationModeFlags cursorPosition(CPoint point);	// 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지)
	virtual operationModeFlags cursorPosition(CRect rect);		// 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지)

	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, CPoint point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
	virtual void creating(UINT nFlags, CPoint point);			// 생성 그리기
	virtual void moving(UINT nFlags, CPoint point);				// 이동 그리기
	virtual void resizing(UINT nFlags, CPoint point);			// 크기 변경 그리기

	// LButtonUp / LButtonDlk
	virtual void addPoint(CPoint point);						// 점 추가
	virtual void move(CPoint target);							// 개체 이동
	virtual void resize(CPoint point, int resizeFlags);			// 개체 크기 변경

	// OnDraw / OnPaint
	virtual void draw();										// 개체 그리기

	// Menu Item
	virtual void destroy();										// 개체 삭제

	virtual void setLineColor(Color lineColor);					// 선 색 설정
	virtual void setLineWidth(int lineWidth);					// 선 두께 설정
	virtual void setLinePattern(int linePattern);				// 선 패턴 설정
	virtual void setProperties(CFigureProperties properties);	// 설정된 값으로 개체 속성 설정

	// Getter
	CList<CPoint, CPoint&>& GetPointsList();

private:

	/* 두 개의 좌표 */
	CList <CPoint, CPoint&> m_PointsList;

	/* 그리기 위한 펜 */
	CPen m_LinePen;

	/* 선 두께 */
	int m_LineWidth;

	/* 선 패턴 */
	int m_LinePattern;




};

   