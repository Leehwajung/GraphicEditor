// Figure.h : CFigure 클래스의 인터페이스
// CFigure : 클라이언트 영역에서 볼 수 있는 개체를 정의하는 클래스 (모든 개체의 조상 클래스)
// @Author Lee Hwajung

#pragma once

#include "afx.h"
#include <gdiplus.h>
//#include <afxcoll.h>
#include "FigureProperties.h"

using Gdiplus::Color;

// CFigure 명령 대상입니다.

class CFigure : public CObject
{
public:
	enum operationModeFlags {
		None			= (int) 0x00000,
		Create			= (int) 0x00001,
		Move			= (int) 0x00002,
		Resize			= (int) 0x00004
	};

	enum resizeFlags {
		Free			= (int) 0x00000,
		Proportional	= (int) 0x00004
	};

public:
	CFigure();
	CFigure(CDC* dc);
	virtual ~CFigure();

public:
	// LButtonDown
	virtual void create(CPoint startingPoint);					// 개체 생성
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
	virtual void resize(CPoint point, CPoint* anchorPoint = NULL, int resizeFlags = Free);			// 개체 크기 변경
	virtual void setProperties(CFigureProperties properties);	// 설정된 값으로 개체 속성 설정

	// OnDraw / OnPaint
	virtual void draw();										// 개체 그리기
	virtual void drawSelect();

	// Menu Item
	virtual void destroy();										// 개체 삭제

	virtual void setLineColor(Color lineColor);					// 윤곽선 색 설정
	virtual void setLineWidth(int lineWidth);					// 윤곽선 두께 설정
	virtual void setLinePattern(int linePattern);				// 윤곽선 패턴 설정
	virtual void setFillColor(Color FillColor);					// 칠하기 색 설정
	virtual void setFillPattern(int fillPattern);				// 칠하기 패턴 설정

	// Getter / Setter
	CDC* getDC();
	void setDC(CDC* dc);

	CPoint& getStartingPoint();
	void setStartingPoint(CPoint StartingPoint);

	operationModeFlags getOperationMode();
	void setOperationMode(operationModeFlags OperationMode);

// 특성
protected:
	CDC* m_lpdc;
	CPoint m_StartingPoint;
	operationModeFlags m_OperationMode;
	CRgn m_Region;			// 도형 영역 https://msdn.microsoft.com/en-us/library/6y4t32t5(v=vs.120).aspx

	Color m_LineColor;		// 윤곽선 색
	int m_LinePattern;		// 윤곽선 패턴
	int m_LineWidth;		// 윤곽선 두께
};


