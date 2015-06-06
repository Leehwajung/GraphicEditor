// Line.h : CLine 클래스의 인터페이스
// CLine : 직선 개체를 정의하는 클래스
// 

#pragma once
#include "Strap.h"

// CLine 명령 대상입니다.
// Make and Edit by Byun Jun
class CLine : public CStrap
{
public:
	CLine();
	CLine(IN Pen* pen);
	CLine(IN Pen* pen, PointF startingPoint, PointF endingPoint);
	DECLARE_SERIAL(CLine)
	~CLine();

	virtual void Serialize(CArchive& ar);

	/** 연산 **/
	/* LButtonUp / LButtonDlk */
	// 생성
	// 시작 좌표와 끝 좌표를 기준으로 직선을 생성함
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
	// 시작 좌표와 끝 좌표를 기준으로 직선을 생성함
	// - IN 매개변수
	//		void* param1, ...: PointF*(startingPoint), PointF*(endingPoint), CreateFlag 순으로 입력
	// - 반환 값 (BOOL)
	//		TRUE: 생성 실패
	//		FALSE: 생성 성공
	virtual BOOL create(void* param1, ...);

public:
	// 이동
	// 시작 좌표부터 끝 좌표까지의 Offset을 기준으로 직선을 이동
	// - IN 매개변수
	//		PointF originPoint: 이동의 시작 좌표
	//		PointF targetPoint: 이동의 끝 좌표
	//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// 크기 변경
	// 선택한 핸들의 좌표를 변경하여 크기 변경 (기준 좌표를 설정하면 이를 기준으로 각 좌표를 변경하여 크기 변경)
	// - IN 매개변수
	//		Position selectedHandle: 직선의 선택된 핸들
	//		PointF targetPoint: 선택된 핸들의 변경할 좌표
	//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
	//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
	virtual void resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);


	/* Menu Item */
	// 삭제
	// 직선을 삭제하고 메모리를 해제
	virtual void destroy();


	/* LButtonDown */
	// 좌표 위치 확인
	// 점이 직선 안에 있는지 확인하고 그 위치를 반환함
	// - IN 매개변수
	//		PointF point: 확인할 좌표
	// - 반환 값 (Position)
	//		Position: 직선 상의 점의 위치
	virtual Position pointInFigure(IN PointF point);

	
	/** 그리기 **/
	/* OnDraw */
	// 도형 그리기
	// - IN 매개변수
	//		Graphics* lpGraphics: 그리기 대상 Graphics
	virtual void draw(IN Graphics* lpGraphics);

	/* OnMouseMove */
	// 생성 그리기
	// 생성 시에 보여줄 그리기
	// - IN 매개변수
	//		Graphics* lpGraphics: 그리기 대상 Graphics
	//		PointF startingPoint: 생성 시작 좌표
	//		PointF targetPoint: 생성 시 선택 중인 좌표
	//		CreateFlag createFlag = FREECREATE: 생성 설정 플래그
	void creating(IN Graphics* lpGraphics, IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag = FREECREATE);

private:
	// 생성 그리기
	// 생성 시에 보여줄 그리기
	// - IN 매개변수
	//		Graphics* lpGraphics: 그리기 대상 Graphics
	//		void* param1, ...: PointF*(startingPoint), PointF*(endingPoint), CreateFlag 순으로 입력
	virtual void creating(IN Graphics* lpGraphics, void* param1, ...);

public:
	// 이동 그리기
	// 이동 중에 보여줄 그리기
	// - IN 매개변수
	//		Graphics* lpGraphics: 그리기 대상 Graphics
	//		PointF originPoint: 이동의 시작 좌표
	//		PointF targetPoint: 이동 중인 좌표
	//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
	virtual void moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// 크기 변경 그리기
	// 크기 변경 중에 보여줄 그리기
	// - IN 매개변수
	//		Graphics* lpGraphics: 그리기 대상 Graphics
	//		Position selectedHandle: 개체의 선택된 핸들
	//		PointF targetPoint: 선택된 핸들을 이동하고 있는 좌표
	//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
	//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
	virtual void resizing(IN Graphics* lpGraphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);

	// 개별 좌표 이동
	virtual void pointMove(IN PointF originPoint, IN PointF targetPoint);

	// 개별 좌표 이동 그리기
	virtual void pointMoving(Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint);

	virtual BOOL getHandleRect(IN Position handle, OUT RectF* handleRect);


protected:
	/** 개체 영역 관리 **/
	// 개체 영역 갱신
	virtual RectF resetArea();

public:
	//// LButtonDown
	//virtual void create(PointF startingPoint);					// 선 생성
	//virtual operationModeFlags cursorPosition(PointF point);	// 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지)
	//virtual operationModeFlags cursorPosition(RectF rect);		// 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지)
	//
	//// OnMouseMove
	//void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
	//virtual void creating(UINT nFlags, PointF point);			// 생성 그리기
	//virtual void moving(UINT nFlags, PointF point);				// 이동 그리기
	//virtual void resizing(UINT nFlags, PointF point);			// 크기 변경 그리기
	//
	//// LButtonUp / LButtonDlk
	//virtual void endCreate(PointF point);						// 생성 완료
	//virtual void move(PointF originPoint, PointF targetPoint);							// 개체 이동
	//virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// 개체 크기 변경
	//
	//// OnDraw / OnPaint
	//virtual void draw();										// 개체 그리기
	//
	//// Menu Item
	//virtual void destroy();										// 개체 삭제
	//
	//virtual BOOL setLineColor(const Color& LineColor);			// 선 색 설정
	//virtual BOOL setLineWidth(const REAL& LineWidth);			// 선 두께 설정
	//virtual BOOL setLinePattern(const DashStyle& LinePattern);	// 선 패턴 설정

private:

	/* 그리기 위한 펜 */
	//Pen m_LinePen;

	///* 선 두께 */
	//int m_LineWidth;

	///* 선 패턴 */
	//int m_LinePattern;
	//Pen* m_OutlinePen;

	PointF m_StartingPoint;
	PointF m_EndPoint;

	REAL m_Gradient;


	//Color m_LineColor;	// 선 색
	//int m_LinePattern;	// 선 패턴
	//int m_LineWidth;	// 선 두께
};