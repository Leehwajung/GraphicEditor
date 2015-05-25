// Figure.h : CFigure 클래스의 인터페이스
// CFigure : 클라이언트 영역에서 볼 수 있는 개체를 정의하는 클래스 (모든 개체의 조상 클래스)
// @Author Lee Hwajung

#pragma once

#include "afx.h"
#include <gdiplus.h>
//#include <afxcoll.h>
#include "FigureProperties.h"
#include "Global.h"

using namespace Gdiplus;

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
	CFigure(Graphics* lpGraphics);
	virtual ~CFigure();

public:
	// LButtonDown
	virtual void create(PointF startingPoint);					// 개체 생성
	virtual operationModeFlags cursorPosition(PointF point);	// 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지)


	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
	virtual void creating(UINT nFlags, PointF point);			// 생성 그리기
	virtual void moving(UINT nFlags, PointF point);				// 이동 그리기
	virtual void resizing(UINT nFlags, PointF point);			// 크기 변경 그리기

	// LButtonUp
	virtual void addPoint(PointF point);						// 점 추가
	virtual void move(PointF target);							// 개체 이동
	virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// 개체 크기 변경
	virtual void setProperties(CFigureProperties properties);	// 설정된 값으로 개체 속성 설정
	virtual operationModeFlags cursorPosition(RectF rect);		// 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지)

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
	// 순수 가상함수로 변경하기

	// Getter / Setter
	Graphics* getGraphics();
	void setGraphics(Graphics* lpGraphics);

	PointF& getStartingPoint();
	void setStartingPoint(PointF StartingPoint);

	operationModeFlags getOperationMode();
	void setOperationMode(operationModeFlags OperationMode);

// 특성
protected:
	Graphics* m_lpGraphics;
	PointF m_StartingPoint;
	operationModeFlags m_OperationMode;
	RectF m_Rect;			// 개체 선택 영역 (사각형) https://msdn.microsoft.com/en-us/library/6y4t32t5(v=vs.120).aspx
};


