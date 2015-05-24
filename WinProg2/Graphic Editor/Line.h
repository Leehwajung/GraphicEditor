// Line.h : CLine 클래스의 인터페이스
// CLine : 선 개체를 정의하는 클래스 (CPolyLine / CPencil의 기반 클래스)
// 

#pragma once
#include "Figure.h"


// Make and Edit by Byun Jun
class CLine : public CFigure
{
public:
	CLine();
	~CLine();

	// LButtonDown
	virtual void Create(PointF startingPoint);					// 선 생성
	virtual operationModeFlags cursorPosition(PointF point);	// 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지)
	virtual operationModeFlags cursorPosition(CRect rect);		// 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지)

	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
	virtual void creating(UINT nFlags, PointF point);			// 생성 그리기
	virtual void moving(UINT nFlags, PointF point);				// 이동 그리기
	virtual void resizing(UINT nFlags, PointF point);			// 크기 변경 그리기

	// LButtonUp / LButtonDlk
	virtual void addPoint(PointF point);						// 점 추가
	virtual void move(PointF target);							// 개체 이동
	virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// 개체 크기 변경

	// OnDraw / OnPaint
	virtual void draw();										// 개체 그리기

	// Menu Item
	virtual void destroy();										// 개체 삭제

	virtual void setLineColor(Color lineColor);					// 선 색 설정
	virtual void setLineWidth(int lineWidth);					// 선 두께 설정
	virtual void setLinePattern(int linePattern);				// 선 패턴 설정
	virtual void setProperties(CFigureProperties properties);	// 설정된 값으로 개체 속성 설정

	// Getter
	CList <PointF, PointF&>& GetPointsList();

private:

	/* 두 개의 좌표 */
	CList <PointF, PointF&> m_PointsList;

	/* 그리기 위한 펜 */
	//Pen m_LinePen;

	///* 선 두께 */
	//int m_LineWidth;

	///* 선 패턴 */
	//int m_LinePattern;

	Color m_LineColor;	// 윤곽선 색
	int m_LinePattern;	// 윤곽선 패턴
	int m_LineWidth;	// 윤곽선 두께
};

   