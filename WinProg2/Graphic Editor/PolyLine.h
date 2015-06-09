// PolyLine.h : CPolyLine 클래스의 인터페이스
// CPolyLine : 폴리라인 개체를 정의하는 클래스
//

#pragma once
#include "Strap.h"

// CPolyLine 명령 대상입니다.

class CPolyLine : public CStrap
{
public:

	CPolyLine();
	CPolyLine(IN Pen* pen);
	CPolyLine(IN Pen* pen, CList <PointF, PointF&>& list);
	DECLARE_SERIAL(CPolyLine)
	~CPolyLine();
	CFigure* clone();
	virtual void Serialize(CArchive& ar);

	/** 연산 **/
	/* LButtonUp */
	void addPoint(IN PointF addingPoint, IN CreateFlag createFlag = FREECREATE);

	/* LButtonDlk */
	// 생성
	// 시작 좌표와 끝 좌표를 기준으로 직선을 생성함
	// - IN 매개변수
	//		CreateFlag createFlag = FREECREATE: 생성 설정 플래그
	// - 반환 값 (BOOL)
	//		TRUE: 생성 실패
	//		FALSE: 생성 성공
	// ok!!
	BOOL create(IN CreateFlag createFlag = FREECREATE);

private:
	// 생성
	// 시작 좌표와 끝 좌표를 기준으로 직선을 생성함
	// - IN 매개변수
	//		void* param1, ...: CreateFlag 순으로 입력
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
	// 곡선을 삭제하고 메모리를 해제
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
	//		Graphics& graphics: 그리기 대상 Graphics
	virtual void draw(IN Graphics& graphics);

	/* OnMouseMove */
	// 생성 그리기
	// 생성 시에 보여줄 그리기
	// - IN 매개변수
	//		PointF addingPoint
	//		Graphics& graphics: 그리기 대상 Graphics
	//		CreateFlag createFlag = FREECREATE: 생성 설정 플래그
	// ok!!
	RectF creating(IN Graphics& graphics, IN PointF addingPoint, IN CreateFlag createFlag = FREECREATE);

protected:
	// 생성 그리기
	// 생성 시에 보여줄 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	//		void* param1, ...:PointF addingPoint, CreateFlag 순으로 입력
	// ok!!
	virtual RectF creating(IN Graphics& graphics, void* param1, ...);

public:
	// 이동 그리기
	// 이동 중에 보여줄 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	//		PointF originPoint: 이동의 시작 좌표
	//		PointF targetPoint: 이동 중인 좌표
	//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
	virtual RectF moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// 크기 변경 그리기
	// 크기 변경 중에 보여줄 그리기
	// - IN 매개변수
	//		Graphics& graphics: 그리기 대상 Graphics
	//		Position selectedHandle: 개체의 선택된 핸들
	//		PointF targetPoint: 선택된 핸들을 이동하고 있는 좌표
	//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
	//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
	virtual RectF resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);

	// 개별 좌표 이동
	virtual void pointMove(IN PointF originPoint, IN PointF targetPoint);

	// 개별 좌표 이동 그리기
	virtual RectF pointMoving(Graphics& graphics, IN PointF originPoint, IN PointF targetPoint);

	// 개별 좌표 삭제 
	void RemovePoint(IN PointF originPoint);

	// 개별 좌표 삽입
	void InsertPoint(IN PointF originPoint);

	virtual void drawLineHandle(IN Graphics& graphics);

protected:
	/** 개체 영역 관리 **/
	// 개체 영역 갱신
	virtual RectF resetArea();

public:
	// Getter
	CList <PointF, PointF&>& GetPointsList();
	//BOOL GetCreatedFlag();

protected:

	CList <PointF, PointF&> m_PointsList;

	//BOOL m_CreatedFlag;
};


