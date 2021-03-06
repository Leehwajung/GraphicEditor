// Figure.h : CFigure 클래스의 인터페이스
// CFigure : 클라이언트 영역에서 볼 수 있는 개체를 정의하는 클래스 (모든 개체의 조상 클래스)
// @Author Lee Hwajung

#pragma once

#include "afx.h"
#include <cstdarg>
//#include <gdiplus.h>
//#include <afxcoll.h>
#include "Global.h"

using namespace Gdiplus;

// CFigure 명령 대상입니다.

class CFigure : public CObject
{
// 자료형
public:
	enum Position {
		OUTSIDE			= (int) 0x00000,	// 개체 밖
		INSIDE			= (int) 0x00001,	// 개체 위
		ONHANDLE		= (int) 0x00008,	// 핸들 위 (핸들 위의 점인지는 ONHANDLE와의 &연산으로 알아낼 수 있음)
		TOPLEFT			= (int) 0x00008,	// 좌상 핸들
		TOP				= (int) 0x00009,	// 상측 핸들
		TOPRIGHT		= (int) 0x0000A,	// 우상 핸들
		RIGHT			= (int) 0x0000B,	// 우측 핸들
		BOTTOMRIGHT		= (int) 0x0000C,	// 우하 핸들
		BOTTOM			= (int) 0x0000D,	// 하측 핸들
		BOTTOMLEFT		= (int) 0x0000E,	// 좌하 핸들
		LEFT			= (int) 0x0000F,	// 좌측 핸들
		START			= (int) 0x00018,	// 시작 핸들
		END				= (int) 0x00019		// 끝 핸들
	};

	enum CreateFlag {
		FREECREATE		= NULL,				// 자유 생성
		REGULAR			= MK_SHIFT			// 정다면체 또는 정방향선 생성
	};

	enum MoveFlag {
		FREEMOVE		= NULL,				// 자유 이동
		FOURWAY			= MK_SHIFT			// 4방향 이동 (상하좌우)
	};

	enum ResizeFlag {
		FREERESIZE		= NULL,				// 자유 크기 변경
		PROPORTIONAL	= MK_SHIFT			// 비율 크기 변경
	};



// 생성 및 소멸
public:
	CFigure();
	//CFigure(IN CClientDC* lpClientDC);
	//CFigure(IN Graphics& graphics);
	DECLARE_SERIAL(CFigure)
	virtual ~CFigure();


// 작업
public:
/** 직렬화 **/
	// 직렬화 (순수가상함수로 바꿀지 검토)
	virtual void Serialize(CArchive& ar);

/** 연산 **/
	// 생성 (코드 없는 함수)
	// 매개변수의 값을 기준으로 새로운 개체를 정의
	// - IN 매개변수
	//		void* param1, ...: 각 파생 클래스에서 필요한대로 정의
	//		[CreateFlag createFlag = FREECREATE]: 생성 설정 플래그, 필요하면 추가하기
	// - 반환 값 (BOOL)
	//		TRUE: 생성 실패
	//		FALSE: 생성 성공
	virtual BOOL create(void* param1, ...);
	
	// 이동 (코드 없는 함수)
	// 시작 좌표부터 끝 좌표까지의 Offset을 기준으로 개체를 이동
	// - IN 매개변수
	//		PointF originPoint: 이동의 시작 좌표
	//		PointF targetPoint: 이동의 끝 좌표
	//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	
	// 크기 변경 (코드 없는 함수)
	// 선택한 핸들의 좌표를 변경하여 크기 변경 (기준 좌표를 설정하면 이를 기준으로 각 좌표를 변경하여 크기 변경)
	// - IN 매개변수
	//		Position selectedHandle: 개체의 선택된 핸들
	//		PointF targetPoint: 선택된 핸들의 변경할 좌표
	//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
	//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
	virtual void resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);
	
	// 복/붙/잘을 위한 함수
	virtual CFigure* clone();

	// 삭제 (코드 없는 함수)
	// 개체를 삭제하고 메모리를 해제
	virtual void destroy();
	
	// 좌표 위치 확인 (코드 없는 함수)
	// 점이 개체 안에 있는지 확인하고 그 위치를 반환함
	// - IN 매개변수
	//		PointF point: 확인할 좌표
	// - 반환 값 (Position)
	//		Position: 개체 상의 점의 위치
	virtual Position pointInFigure(IN PointF point);

	// 개체 위치 확인
	// 개체가 사각형 안에 있는지 확인하고 그 위치를 반환함
	// - IN 매개변수
	//		RectF rect: 확인할 좌표
	// - 반환 값 (BOOL)
	//		TRUE: 개체가 사각형 내부에 존재할 때 (도형의 모든 점이 사각형 내부에 존재)
	//		FALSE: 개체가 사각형 내부에 존재하지 않을 때
	BOOL figureInRect(IN RectF rect);


	/* 개체 영역 관리 */
	// 개체 영역 갱신 (코드 없는 함수)
	virtual RectF resetArea();

	// 개체 영역
	// 개체 영역을 얻음
	RectF getArea();


	/* 핸들 관리 */
	// 핸들의 좌표
	// 핸들의 중앙 좌표를 얻음
	// - IN 매개변수
	//		Position handle: 좌표를 얻고자하는 핸들
	// - OUT 매개변수
	//		PointF* handlePoint:
	//			주소 값: 매개변수의 Position이 핸들인 경우 핸들의 좌표
	//			NULL: 매개변수의 Position이 핸들이 아닐 경우
	// - 반환 값 (BOOL)
	//		TRUE: 매개변수의 Position이 핸들인 경우
	//		FALSE: 매개변수의 Position이 핸들이 아닐 경우
	BOOL getHandlePoint(IN Position handle, OUT PointF* handlePoint);

protected:
	// 핸들의 영역
	// 핸들의 영역을 얻음
	// - IN 매개변수
	//		PointF handlePoint: 영역을 얻고자하는 핸들의 좌표
	// - 반환 값 (RectF)
	//		핸들의 영역
	RectF getHandleRect(IN PointF handlePoint);

	// 핸들의 영역
	// 핸들의 영역을 얻음
	// - IN 매개변수
	//		Position handle: 영역을 얻고자하는 핸들
	// - OUT 매개변수
	//		PointF* handlePoint:
	//			주소 값: 매개변수의 Position이 핸들인 경우 핸들의 영역
	//			NULL: 매개변수의 Position이 핸들이 아닐 경우
	// - 반환 값 (BOOL)
	//		TRUE: 매개변수의 Position이 핸들이 아닐 경우
	//		FALSE: 매개변수의 Position이 핸들인 경우
	/*virtual */BOOL getHandleRect(IN Position handle, OUT RectF* handleRect);

	// 정반대편 핸들
	// 정반대편 핸들을 얻음
	// - IN 매개변수
	//		Position handle: 정반대편 핸들을 얻고자하는 핸들
	// - 반환 값 (Position)
	//		정반대편 핸들
	Position getOppositeHandle(IN Position handle);


/** 그리기 **/
public:
	// 개체 그리기 (코드 없는 함수)
	virtual void draw(IN Graphics& graphics);

	// 생성 그리기 (코드 없는 함수)
	// 생성 시에 보여줄 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	//		void* param1, ...: 각 파생 클래스에서 필요한대로 정의
	//		[CreateFlag createFlag = FREECREATE]: 생성 설정 플래그, 필요하면 추가하기
	virtual RectF creating(IN Graphics& graphics, void* param1, ...);

	// 이동 그리기 (코드 없는 함수)
	// 이동 중에 보여줄 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	//		PointF originPoint: 이동의 시작 좌표
	//		PointF targetPoint: 이동 중인 좌표
	//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
	virtual RectF moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	
	// 크기 변경 그리기 (코드 없는 함수)
	// 크기 변경 중에 보여줄 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	//		Position selectedHandle: 개체의 선택된 핸들
	//		PointF targetPoint: 선택된 핸들을 이동하고 있는 좌표
	//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
	//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
	virtual RectF resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);

	// 개체 영역 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	void drawArea(IN Graphics& graphics);

protected:
	// 개체 핸들 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	//		PointF handlePoint: 그리고자하는 핸들 좌표
	// - 반환 값 (BOOL)
	//		TRUE: 매개변수의 Position이 핸들이 아닐 경우
	//		FALSE: 매개변수의 Position이 핸들인 경우
	BOOL drawHandle(IN Graphics& graphics, IN PointF handlePoint);

	// 개체 핸들 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	//		Position handle: 그리고자하는 핸들
	// - 반환 값 (BOOL)
	//		TRUE: 매개변수의 Position이 핸들이 아닐 경우
	//		FALSE: 매개변수의 Position이 핸들인 경우
	BOOL drawHandle(IN Graphics& graphics, IN Position handle);

	// 개체 핸들 전체 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	//		PointF* handlePoints: 핸들의 좌표 배열
	//		count: 배열의 크기
	void drawHandles(IN Graphics& graphics, IN PointF* handlePoints, IN INT count);

	// 개체 핸들 전체 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	void drawHandles(IN Graphics& graphics);


/** 속성 설정 **/
public:
	// 채우기 브러시 설정
	virtual void setFillBrush(IN const Brush* brush, IN BOOL PropertyMaintenanceFlag = FALSE);

	// 윤곽선 색 설정 (코드 없는 함수)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setOutlineColor(IN const Color& outlineColor);

	// 윤곽선 두께 설정 (코드 없는 함수)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setOutlineWidth(IN const REAL outlineWidth);

	// 윤곽선 패턴 설정 (코드 없는 함수)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setOutlinePattern(IN const DashStyle outlinePattern);

	// 주 채우기 색 설정 (코드 없는 함수)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setFillColor(IN const Color& fillColor);

	// 보조 채우기 색 설정 (코드 없는 함수)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setFillSubcolor(IN const Color& fillSubcolor);

	// 채우기 패턴 설정 (코드 없는 함수)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setFillPattern(IN const HatchStyle fillPattern);

	UINT getID() { return ID; }

// 특성
protected:
	RectF m_Area;							// 개체 영역 (사각형)
	const REAL HANDLESIZE = 10;				// 핸들 크기
private:
	UINT ID;				// 개체 고유 ID
	static UINT IDcount;	// ID 할당을 위한 정적 변수

};

typedef Pen*		PenPtr;
typedef Brush*		BrushPtr;
typedef CFigure*	CFigurePtr;

//	// LButtonDown
//	virtual void create(void* param1, ...);					// 개체 생성
//	virtual operationModeFlags cursorPosition(PointF point);	// 커서 위치 찾기 (커서가 도형 위에 있는지, 도형의 점 위에 있는지)
//
//
//	// OnMouseMove
//	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove에서 사용할 함수 (생성 / 이동 / 크기 변경 판단)
//	virtual RectF creating(UINT nFlags, PointF point);			// 생성 그리기
//	virtual RectF moving(UINT nFlags, PointF point);				// 이동 그리기
//	virtual RectF resizing(UINT nFlags, PointF point);			// 크기 변경 그리기
//
//	// LButtonUp
//	virtual void endCreate(PointF point);						// 생성 완료
//	virtual void move(PointF originPoint, PointF targetPoint);	// 개체 이동
//	virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);	// 개체 크기 변경
//	
//	virtual operationModeFlags cursorPosition(RectF rect);		// 커서 위치 찾기 (커서로 만든 선택 영역 안에 도형이 들어 있는지)
//
//	// OnDraw / OnPaint
//	virtual void draw();										// 개체 그리기
//	virtual void drawSelect();
//
//	// Menu Item
//	virtual void destroy();										// 개체 삭제
//
//	virtual BOOL setLineColor(const Color& lineColor);			// 윤곽선 색 설정
//	virtual BOOL setLineWidth(const REAL& LineWidth);			// 윤곽선 두께 설정
//	virtual BOOL setLinePattern(const DashStyle& LinePattern);	// 윤곽선 패턴 설정
//	virtual BOOL setFillColor(const Color& FillColor);			// 주 채우기 색 설정
//	virtual BOOL setFillPattern(const int fillPattern);			// 채우기 패턴 설정
//	// 순수 가상함수로 변경하기
//
//	// Getter / Setter
//	Graphics& getGraphics();
//	void setGraphics(Graphics& graphics);
//
//	PointF& getStartingPoint();
//	void setStartingPoint(PointF& StartingPoint);
//
//	operationModeFlags getOperationMode();
//	void setOperationMode(operationModeFlags OperationMode);
//
//protected:
//	virtual RectF resetArea();		// 개체 선택 영역 재설정 (연산 후 호출시켜줌), 외부에서 호출 불가


// PointF m_StartingPoint;