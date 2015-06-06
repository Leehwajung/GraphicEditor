// Group.h : CGroup 클래스의 인터페이스
// CGroup : 그룹화된 도형 개체들을 저장하는 클래스
// @Author Lee Hwajung

#pragma once
#include "Figure.h"

// CGroup 명령 대상입니다.

class CGroup : public CFigure
{
// 생성 및 소멸
public:
	CGroup();
	DECLARE_SERIAL(CGroup)
	virtual ~CGroup();

// 작업
public:
	/** 직렬화 **/
	// 직렬화 (순수가상함수로 바꿀지 검토)
	virtual void Serialize(CArchive& ar);

	/** 연산 **/
	// 생성
	// 매개변수의 값을 기준으로 새로운 개체를 정의
	// - IN 매개변수
	//		void* param1, ...: 각 파생 클래스에서 필요한대로 정의
	// - 반환 값 (BOOL)
	//		TRUE: 생성 실패
	//		FALSE: 생성 성공
	BOOL create(CFigurePtrList& figurePtrList);

	// 생성
	// 매개변수의 값을 기준으로 새로운 개체를 정의
	// - IN 매개변수
	//		int count: 가변길이로 넣을 개체 포인터의 개수
	//		CFigure* figure1, ...: 개체 포인터의 가변 길이 리스트
	// - 반환 값 (BOOL)
	//		TRUE: 생성 실패
	//		FALSE: 생성 성공
	BOOL create(int count, CFigure* figure1, ...);

private:
	// 생성
	// 매개변수의 값을 기준으로 새로운 개체를 정의
	// - IN 매개변수
	//		void* param1, ...: int*(count), CFigure*(figure1), CFigure*(...) 순으로 입력
	// - 반환 값 (BOOL)
	//		TRUE: 생성 실패
	//		FALSE: 생성 성공
	virtual BOOL create(void* param1, ...);

public:
	// 이동
	// 시작 좌표부터 끝 좌표까지의 Offset을 기준으로 개체를 이동
	// - IN 매개변수
	//		PointF originPoint: 이동의 시작 좌표
	//		PointF targetPoint: 이동의 끝 좌표
	//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// 크기 변경
	// 선택한 핸들의 좌표를 변경하여 크기 변경 (기준 좌표를 설정하면 이를 기준으로 각 좌표를 변경하여 크기 변경)
	// - IN 매개변수
	//		Position selectedHandle: 개체의 선택된 핸들
	//		PointF targetPoint: 선택된 핸들의 변경할 좌표
	//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
	//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
	virtual void resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);

	// 삭제
	// 개체를 삭제하고 메모리를 해제
	virtual void destroy();

	// 좌표 위치 확인
	// 점이 개체 안에 있는지 확인하고 그 위치를 반환함
	// - IN 매개변수
	//		PointF point: 확인할 좌표
	// - 반환 값 (Position)
	//		Position: 개체 상의 점의 위치
	virtual Position pointInFigure(IN PointF point);

/** 개체 영역 관리 **/
protected:
	// 개체 영역 갱신
	virtual void resetArea();

/** 그리기 **/
public:
	// 개체 그리기
	virtual void draw(IN Graphics* lpGraphics);

	// 생성 그리기
	// 생성 시에 보여줄 그리기
	// - IN 매개변수
	//		Graphics* lpGraphics: 그리기 대상 Graphics
	//		void* param1, ...: 각 파생 클래스에서 필요한대로 정의
	//		[CreateFlag createFlag = FREECREATE]: 생성 설정 플래그, 필요하면 추가하기
	virtual void creating(IN Graphics* lpGraphics, void* param1, ...);

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


/** 속성 설정 **/
public:
	// 윤곽선 색 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setOutlineColor(IN const Color& outlineColor);

	// 윤곽선 두께 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setOutlineWidth(IN const REAL outlineWidth);

	// 윤곽선 패턴 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setOutlinePattern(IN const DashStyle outlinePattern);

	// 주 채우기 색 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setFillColor(IN const Color& fillColor);

	// 보조 채우기 색 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setFillSubcolor(IN const Color& fillSubcolor);

	// 채우기 패턴 설정
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	virtual BOOL setFillPattern(IN const HatchStyle fillPattern);


// 특성
private:
	CFigurePtrList m_FiguresList;
};


