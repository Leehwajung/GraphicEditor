// Rectangle.h : CRectangle 클래스의 인터페이스
// CRectangle : 직사각형 개체를 정의하는 클래스
// 

#pragma once
#include "Shape.h"

// CRectangle 명령 대상입니다.

class CRectangle : public CShape
{
// 생성 및 소멸
public:
	CRectangle();
	CRectangle(IN CClientDC* lpClientDC);
	CRectangle(IN Graphics* lpGraphics);
	CRectangle(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush);
	CRectangle(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush);
	CRectangle(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush, IN RectF rect);
	CRectangle(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush, IN RectF rect);
	DECLARE_SERIAL(CRectangle)
	virtual ~CRectangle();



// 작업 및 재정의
public:
	/* 직렬화 */
	// 직렬화
	virtual void Serialize(CArchive& ar);


	/* 연산 */
	// 생성
	// 시작 좌표와 끝 좌표를 기준으로 사각형을 생성함
	// - IN 매개변수
	//		PointF startingPoint: 생성 시작 좌표
	//		PointF endingPoint: 생성 끝 좌표
	//		CreateFlag createFlag = FREECREATE: 생성 설정 플래그
	// - 반환 값 (BOOL)
	//		TRUE: 생성 실패
	//		FALSE: 생성 성공
	BOOL create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag = FREECREATE);

private:
	// 생성
	// 시작 좌표와 끝 좌표를 기준으로 사각형을 생성함
	// - IN 매개변수
	//		...: PointF(startingPoint), PointF(endingPoint), CreateFlag 순으로 입력
	// - 반환 값 (BOOL)
	//		TRUE: 생성 실패
	//		FALSE: 생성 성공
	virtual BOOL create(...);

public:
	// 이동
	// 시작 좌표부터 끝 좌표까지의 Offset을 기준으로 사각형을 이동
	// - IN 매개변수
	//		PointF originPoint: 이동의 시작 좌표
	//		PointF targetPoint: 이동의 끝 좌표
	//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// 크기 변경
	// 선택한 핸들의 좌표를 변경하여 크기 변경 (기준 좌표를 설정하면 이를 기준으로 각 좌표를 변경하여 크기 변경)
	// - IN 매개변수
	//		Position selcetedHandle: 사각형의 선택된 핸들
	//		PointF targetPoint: 선택된 핸들의 변경할 좌표
	//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
	//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selcetedHandle을 통해 얻은 Default 기준 좌표 )
	virtual void resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);

	// 삭제
	// 사각형을 삭제하고 메모리를 해제
	virtual void destroy();

	// 좌표 위치 확인
	// 점이 사각형 안에 있는지 확인하고 그 위치를 반환함
	// - IN 매개변수
	//		PointF point: 확인할 좌표
	// - 반환 값 (Position)
	//		Position: 사각형 상의 점의 위치
	virtual Position pointInFigure(IN PointF point);


	/* 그리기 */
	// 도형 그리기
	virtual void draw();

	// 생성 그리기
	// 생성 시에 보여줄 그리기
	// - IN 매개변수
	//		PointF startingPoint: 생성 시작 좌표
	//		PointF targetPoint: 생성 시 선택 중인 좌표
	//		CreateFlag createFlag = FREECREATE: 생성 설정 플래그
	void creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag = FREECREATE);

private:
	// 생성 그리기
	// 생성 시에 보여줄 그리기
	// - IN 매개변수
	//		...: PointF(startingPoint), PointF(endingPoint), CreateFlag 순으로 입력
	virtual void creating(...);

public:
	// 이동 그리기
	// 이동 중에 보여줄 그리기
	// - IN 매개변수
	//		PointF originPoint: 이동의 시작 좌표
	//		PointF targetPoint: 이동 중인 좌표
	//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
	virtual void moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// 크기 변경 그리기
	// 크기 변경 중에 보여줄 그리기
	// - IN 매개변수
	//		Position selcetedHandle: 개체의 선택된 핸들
	//		PointF targetPoint: 선택된 핸들을 이동하고 있는 좌표
	//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
	//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selcetedHandle을 통해 얻은 Default 기준 좌표 )
	virtual void resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);


protected:
	/* 개체 영역 관리 */
	// 개체 영역 갱신
	virtual void resetArea();



// 특성
protected:
	RectF m_Rect;	// 사각형
};



//// 생성 및 소멸
//public:
//	CRectangle();
//	CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/);
//	CRectangle(Graphics* lpGraphics/*, PointF startingPoint*/);
//	//CRectangle(CClientDC* lpClientDC, RectF& rect);
//	CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/, /*RectF& rect,*/ Pen* pen, SolidBrush* brush);
//	virtual ~CRectangle();
//
//public:
//	// LButtonDown
//	virtual void create(PointF startingPoint);					// 개체 생성
//	virtual operationModeFlags cursorPosition(PointF point);	// 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지)
//
//
//	// OnMouseMove
//	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
//	virtual void creating(UINT nFlags, PointF point);			// 생성 그리기
//	virtual void moving(UINT nFlags, PointF point);				// 이동 그리기
//	virtual void resizing(UINT nFlags, PointF point);			// 크기 변경 그리기
//
//	// LButtonUp
//	virtual void endCreate(PointF point);						// 생성 완료
//	virtual void move(PointF originPoint, PointF targetPoint);							// 개체 이동
//	virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// 개체 크기 변경
//	virtual operationModeFlags cursorPosition(RectF rect);		// 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지)
//	
//	// OnDraw / OnPaint
//	virtual void draw();										// 개체 그리기
//	virtual void drawSelect();
//
//	// Menu Item
//	virtual void destroy();										// 개체 삭제