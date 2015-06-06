// Group.cpp : CGroup 클래스의 구현
// CGroup : 그룹화된 도형 개체들을 저장하는 클래스
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Group.h"


// CGroup

IMPLEMENT_SERIAL(CGroup, CFigure, 1)


CGroup::CGroup()
{
}

CGroup::~CGroup()
{
}


// CGroup 멤버 함수


/** 직렬화 **/
// 직렬화 (순수가상함수로 바꿀지 검토)
void CGroup::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


/** 연산 **/
// 생성
// 매개변수의 값을 기준으로 새로운 개체를 정의
// - IN 매개변수
//		void* param1, ...: 각 파생 클래스에서 필요한대로 정의
// - 반환 값 (BOOL)
//		TRUE: 생성 실패
//		FALSE: 생성 성공
BOOL CGroup::create(IN CFigurePtrList& figurePtrList)
{
	m_FiguresList = figurePtrList;

	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		m_Area.Intersect(m_FiguresList.GetAt(pos)->getArea());
	}

	return FALSE;
}

// 생성
// 매개변수의 값을 기준으로 새로운 개체를 정의
// - IN 매개변수
//		int count: 가변길이로 넣을 개체 포인터의 개수
//		CFigure* figure1, ...: 개체 포인터의 가변 길이 리스트
// - 반환 값 (BOOL)
//		TRUE: 생성 실패
//		FALSE: 생성 성공
BOOL CGroup::create(IN const int count, IN CFigure* figure1, ...)
{
	m_Area = NULLRectF;
	m_FiguresList.RemoveAll();

	va_list vaList;
	va_start(vaList, figure1);
	if (!figure1) {
		return TRUE;
	}
	m_FiguresList.AddTail(figure1);

	CFigure* figure;
	
	for (int i = 1; i < count; i++) {
		figure = va_arg(vaList, CFigure*);
		if (!figure) {
			return TRUE;
		}
		m_FiguresList.AddTail(figure);
		m_Area.Intersect(figure->getArea());
	}

	va_end(vaList);

	return FALSE;
}

// 생성
// 매개변수의 값을 기준으로 새로운 개체를 정의
// - IN 매개변수
//		void* param1, ...: int*(count), CFigure*(figure1), CFigure*(...) 순으로 입력
// - 반환 값 (BOOL)
//		TRUE: 생성 실패
//		FALSE: 생성 성공
BOOL CGroup::create(void* param1, ...)
{
	m_Area = NULLRectF;
	va_list vaList;
	va_start(vaList, param1);
	int count = *(int*)param1;
	CFigure* figure;

	m_FiguresList.RemoveAll();
	for (int i = 0; i < count; i++) {
		figure = va_arg(vaList, CFigure*);
		if (!figure) {
			return TRUE;
		}
		m_FiguresList.AddTail(figure);
		m_Area.Intersect(figure->getArea());
	}

	va_end(vaList);

	return FALSE;
}

// 이동
// 시작 좌표부터 끝 좌표까지의 Offset을 기준으로 개체를 이동
// - IN 매개변수
//		PointF originPoint: 이동의 시작 좌표
//		PointF targetPoint: 이동의 끝 좌표
//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
void CGroup::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	m_Area = NULLRectF;
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		m_FiguresList.GetAt(pos)->move(originPoint, targetPoint, moveFlag);
		m_Area.Intersect(m_FiguresList.GetAt(pos)->getArea());
	}
}

// 크기 변경
// 선택한 핸들의 좌표를 변경하여 크기 변경 (기준 좌표를 설정하면 이를 기준으로 각 좌표를 변경하여 크기 변경)
// - IN 매개변수
//		Position selectedHandle: 개체의 선택된 핸들
//		PointF targetPoint: 선택된 핸들의 변경할 좌표
//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
void CGroup::resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	m_Area = NULLRectF;
	PointF handlePoint;
	getHandlePoint(getOppositeHandle(selectedHandle), &handlePoint);

	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		m_FiguresList.GetAt(pos)->resize(selectedHandle, targetPoint, resizeFlag, &handlePoint);
		m_Area.Intersect(m_FiguresList.GetAt(pos)->getArea());
	}
}

// 삭제
// 개체를 삭제하고 메모리를 해제
void CGroup::destroy()
{

}

// 좌표 위치 확인
// 점이 개체 안에 있는지 확인하고 그 위치를 반환함
// - IN 매개변수
//		PointF point: 확인할 좌표
// - 반환 값 (Position)
//		Position: 개체 상의 점의 위치
CFigure::Position CGroup::pointInFigure(IN PointF point)
{
	RectF handleRect;

	for (int handleIndex = TOPLEFT; handleIndex <= LEFT; handleIndex++) {

		getHandleRect((Position)handleIndex, &handleRect);
		if (handleRect.Contains(point)) {
			return (Position)handleIndex;
		}
	}

	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->pointInFigure(point) == INSIDE)
			return INSIDE;
	}

	return OUTSIDE;	// 임시 반환값
}

/** 개체 영역 관리 **/
// 개체 영역 갱신
RectF CGroup::resetArea()
{
	m_Area = NULLRectF;

	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		m_Area.Intersect(m_FiguresList.GetAt(pos)->resetArea());
	}

	return m_Area;
}

/** 그리기 **/
// 개체 그리기
void CGroup::draw(IN Graphics* lpGraphics)
{
	m_FiguresList.draw(lpGraphics);
}

// 생성 그리기
// 생성 시에 보여줄 그리기
// - IN 매개변수
//		Graphics* lpGraphics: 그리기 대상 Graphics
//		void* param1, ...: 각 파생 클래스에서 필요한대로 정의
//		[CreateFlag createFlag = FREECREATE]: 생성 설정 플래그, 필요하면 추가하기
RectF CGroup::creating(IN Graphics* lpGraphics, void* param1, ...)
{
	return NULLRectF;
}

// 이동 그리기
// 이동 중에 보여줄 그리기
// - IN 매개변수
//		Graphics* lpGraphics: 그리기 대상 Graphics
//		PointF originPoint: 이동의 시작 좌표
//		PointF targetPoint: 이동 중인 좌표
//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
RectF CGroup::moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	RectF drawnArea;

	for (POSITION pos = m_FiguresList.GetTailPosition(); pos; m_FiguresList.GetPrev(pos)) {
		m_FiguresList.GetAt(pos)->moving(lpGraphics, originPoint, targetPoint, moveFlag);
		drawnArea.Intersect(m_FiguresList.GetAt(pos)->getArea());
	}

	return drawnArea;
}

// 크기 변경 그리기
// 크기 변경 중에 보여줄 그리기
// - IN 매개변수
//		Graphics* lpGraphics: 그리기 대상 Graphics
//		Position selectedHandle: 개체의 선택된 핸들
//		PointF targetPoint: 선택된 핸들을 이동하고 있는 좌표
//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
RectF CGroup::resizing(IN Graphics* lpGraphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	RectF drawnArea;
	PointF handlePoint;
	getHandlePoint(getOppositeHandle(selectedHandle), &handlePoint);

	for (POSITION pos = m_FiguresList.GetTailPosition(); pos; m_FiguresList.GetPrev(pos)) {
		m_FiguresList.GetAt(pos)->resizing(lpGraphics, selectedHandle, targetPoint, resizeFlag, &handlePoint);
		drawnArea.Intersect(m_FiguresList.GetAt(pos)->getArea());
	}

	return drawnArea;
}


/** 속성 설정 **/
// 윤곽선 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setOutlineColor(IN const Color& outlineColor)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setOutlineColor(outlineColor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 윤곽선 두께 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setOutlineWidth(IN const REAL outlineWidth)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setOutlineWidth(outlineWidth)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 윤곽선 패턴 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setOutlinePattern(IN const DashStyle outlinePattern)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setOutlinePattern(outlinePattern)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 주 채우기 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setFillColor(IN const Color& fillColor)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setFillColor(fillColor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 보조 채우기 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setFillSubcolor(IN const Color& fillSubcolor)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setFillSubcolor(fillSubcolor)) {
			return TRUE;
		}
	}

	return FALSE;
}

// 채우기 패턴 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setFillPattern(IN const HatchStyle fillPattern)
{
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		if (m_FiguresList.GetAt(pos)->setFillPattern(fillPattern)) {
			return TRUE;
		}
	}

	return FALSE;
}