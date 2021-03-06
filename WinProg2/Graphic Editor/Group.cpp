// Group.cpp : CGroup 클래스의 구현
// CGroup : 그룹화된 도형 개체들을 저장하는 클래스
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Group.h"


// CGroup

IMPLEMENT_SERIAL(CGroup, CFigure, 1)


CGroup::CGroup()
	: CFigure()
{
}

CGroup::CGroup(IN CFigurePtrList& figurePtrList)
	: CFigure()
{
	create(figurePtrList);
}

CGroup::CGroup(IN CSelectedFigureArray& selectedFigureArray)
	: CFigure()
{
	const POSITION* positionArray = selectedFigureArray.getData();
	CFigurePtrList* figurePtrList = selectedFigureArray.getFigurePtrList();
	int size = selectedFigureArray.getSize();
	CFigure* figure;

	m_Area = figurePtrList->GetAt(positionArray[0])->getArea();
	for (int i = 0; i < size; i++) {
		figure = figurePtrList->GetAt(positionArray[i]);		// 전체 리스트에서 개체를 가져옴
		m_FiguresList.AddTail(figure);						// 그룹의 리스트에 개체를 저장

		RectF::Union(m_Area, m_Area, figure->getArea());		// 그룹의 영역에 개체의 영역을 합침
		figurePtrList->RemoveAt(positionArray[i]);			// 전체 리스트에서 원소를 삭제
	}

	selectedFigureArray.deselectAll();		// 선택 전체 해제
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
//		CFigurePtrList& figurePtrList: 개체 포인터 목록
// - 반환 값 (BOOL)
//		TRUE: 생성 실패
//		FALSE: 생성 성공
BOOL CGroup::create(IN CFigurePtrList& figurePtrList)
{
	m_FiguresList = figurePtrList;

	m_Area = m_FiguresList.GetHead()->getArea();
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		RectF::Union(m_Area, m_Area, m_FiguresList.GetAt(pos)->getArea());		// 그룹의 영역에 개체의 영역을 합침
	}

	return FALSE;
}

// 생성
// 매개변수의 값을 기준으로 새로운 개체를 정의
// - IN 매개변수
//		CSelectedFigureArray& figurePtrList: 개체 포지션 배열
// - 반환 값 (BOOL)
//		TRUE: 생성 실패
//		FALSE: 생성 성공
BOOL CGroup::create(IN CSelectedFigureArray& selectedFigureArray)
{
	const POSITION* positionArray = selectedFigureArray.getData();
	CFigurePtrList* figurePtrList = selectedFigureArray.getFigurePtrList();
	int size = selectedFigureArray.getSize();
	CFigure* figure;

	m_Area = figurePtrList->GetAt(positionArray[0])->getArea();
	for (int i = 0; i < size; i++) {
		figure = figurePtrList->GetAt(positionArray[i]);		// 전체 리스트에서 개체를 가져옴
		m_FiguresList.AddTail(figure);						// 그룹의 리스트에 개체를 저장
		RectF::Union(m_Area, m_Area, figure->getArea());		// 그룹의 영역에 개체의 영역을 합침
		figurePtrList->RemoveAt(positionArray[i]);			// 전체 리스트에서 원소를 삭제
	}

	figurePtrList->AddHead(this);			// 그룹을 전체 리스트에 등록
	selectedFigureArray.deselectAll();		// 선택 전체 해제
	selectedFigureArray.select(/*figurePtrList->GetHeadPosition()*/);			// 그룹 선택

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
	
	m_Area = figure1->getArea();
	for (int i = 1; i < count; i++) {
		figure = va_arg(vaList, CFigure*);
		if (!figure) {
			return TRUE;
		}
		m_FiguresList.AddTail(figure);
		RectF::Union(m_Area, m_Area, figure->getArea());		// 그룹의 영역에 개체의 영역을 합침
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

	figure = va_arg(vaList, CFigure*);
	m_Area = figure->getArea();
	if (!figure) {
		return TRUE;
	}
	m_FiguresList.AddTail(figure);
	RectF::Union(m_Area, m_Area, figure->getArea());		// 그룹의 영역에 개체의 영역을 합침

	for (int i = 1; i < count; i++) {
		figure = va_arg(vaList, CFigure*);
		if (!figure) {
			return TRUE;
		}
		m_FiguresList.AddTail(figure);
		RectF::Union(m_Area, m_Area, figure->getArea());		// 그룹의 영역에 개체의 영역을 합침
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
	m_Area = m_FiguresList.GetHead()->getArea();
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		m_FiguresList.GetAt(pos)->move(originPoint, targetPoint, moveFlag);
		RectF::Union(m_Area, m_Area, m_FiguresList.GetAt(pos)->getArea());		// 그룹의 영역에 개체의 영역을 합침
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
	PointF handlePoint;
	getHandlePoint(getOppositeHandle(selectedHandle), &handlePoint);

	m_Area = m_FiguresList.GetHead()->getArea();
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		m_FiguresList.GetAt(pos)->resize(selectedHandle, targetPoint, resizeFlag, &handlePoint);
		RectF::Union(m_Area, m_Area, m_FiguresList.GetAt(pos)->getArea());		// 그룹의 영역에 개체의 영역을 합침
	}
}

// 삭제
// 그룹 개체와 그룹의 원소 개체들을 삭제하고 메모리를 해제
void CGroup::destroy()
{
	for (POSITION pos = m_FiguresList.GetTailPosition(); pos; m_FiguresList.GetPrev(pos)) {
		m_FiguresList.GetAt(pos)->~CFigure();
	}

	this->~CGroup();
}

// 해제
// 그룹을 해제하고 그룹 개체를 삭제
// - OUT 매개변수
//		CFigurePtrList& figurePtrList: 원래 그룹의 개체 리스트
void CGroup::unGroup(OUT CFigurePtrList& figurePtrList)
{
	figurePtrList = m_FiguresList;

	this->~CGroup();
}

// 해제
// 그룹을 해제
// - OUT 매개변수
//		POSITION position: 해제될 그룹이 존재하는 포지션
//		CSelectedFigureArray& selectedFigureArray: 그룹에 해당하는 선택 개체 배열
void CGroup::unGroup(IN POSITION position, OUT CSelectedFigureArray& selectedFigureArray)
{
	const POSITION* positionArray = selectedFigureArray.getData();
	CFigurePtrList* figurePtrList = selectedFigureArray.getFigurePtrList();

	for (POSITION pos = m_FiguresList.GetTailPosition(); pos; m_FiguresList.GetPrev(pos)) {
		figurePtrList->InsertAfter(position, m_FiguresList.GetAt(pos));		// 그룹의 개체를 전체 리스트에 등록
	}

	selectedFigureArray.deselect(position);



	POSITION pos = position;
	m_FiguresList.GetNext(pos);
	for (int i = 0; i < m_FiguresList.GetSize(); i++) {
		selectedFigureArray.select(pos);		// 선택 리스트에 그룹에서 해제된 개체 등록
		m_FiguresList.GetNext(pos);
	}

	figurePtrList->deleteAt(position);
	m_FiguresList.RemoveAll();
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
	Position selectedPosition;

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

	return OUTSIDE;
}

/** 개체 영역 관리 **/
// 개체 영역 갱신
RectF CGroup::resetArea()
{
	m_Area = m_FiguresList.GetHead()->getArea();

	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		RectF::Union(m_Area, m_Area, m_FiguresList.GetAt(pos)->getArea());		// 그룹의 영역에 개체의 영역을 합침
	}

	return m_Area;
}

/** 그리기 **/
// 개체 그리기
void CGroup::draw(IN Graphics& graphics)
{
	m_FiguresList.draw(graphics);
}

// 생성 그리기
// 생성 시에 보여줄 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
//		void* param1, ...: 각 파생 클래스에서 필요한대로 정의
//		[CreateFlag createFlag = FREECREATE]: 생성 설정 플래그, 필요하면 추가하기
RectF CGroup::creating(IN Graphics& graphics, void* param1, ...)
{
	return NULLRectF;
}

// 이동 그리기
// 이동 중에 보여줄 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
//		PointF originPoint: 이동의 시작 좌표
//		PointF targetPoint: 이동 중인 좌표
//		MoveFlag moveFlag = FREEMOVE: 이동 설정 플래그
RectF CGroup::moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{
	return m_FiguresList.moving(graphics, originPoint, targetPoint, moveFlag);
}

// 크기 변경 그리기
// 크기 변경 중에 보여줄 그리기
// - IN 매개변수
//		Graphics& graphics: 그리기 대상 Graphics
//		Position selectedHandle: 개체의 선택된 핸들
//		PointF targetPoint: 선택된 핸들을 이동하고 있는 좌표
//		ResizeFlag resizeFlag = FREERESIZE: 크기 변경 설정 플래그
//		PointF* anchorPoint = NULL: 크기 변경의 기준(고정) 좌표 (NULL일 경우, selectedHandle을 통해 얻은 Default 기준 좌표 )
RectF CGroup::resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{
	PointF handlePoint;
	getHandlePoint(getOppositeHandle(selectedHandle), &handlePoint);

	return m_FiguresList.resizing(graphics, selectedHandle, targetPoint, resizeFlag, &handlePoint);
}


/** 속성 설정 **/
// 채우기 브러시 설정
void CGroup::setFillBrush(IN const Brush* brush, IN BOOL PropertyMaintenanceFlag/* = FALSE*/)
{
	m_FiguresList.setFillBrush(brush, PropertyMaintenanceFlag);
}

// 윤곽선 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setOutlineColor(IN const Color& outlineColor)
{
	return m_FiguresList.setOutlineColor(outlineColor);
}

// 윤곽선 두께 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setOutlineWidth(IN const REAL outlineWidth)
{
	return m_FiguresList.setOutlineWidth(outlineWidth);
}

// 윤곽선 패턴 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setOutlinePattern(IN const DashStyle outlinePattern)
{
	return m_FiguresList.setOutlinePattern(outlinePattern);
}

// 주 채우기 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setFillColor(IN const Color& fillColor)
{
	return m_FiguresList.setFillColor(fillColor);
}

// 보조 채우기 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setFillSubcolor(IN const Color& fillSubcolor)
{
	return m_FiguresList.setFillSubcolor(fillSubcolor);
}

// 채우기 패턴 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CGroup::setFillPattern(IN const HatchStyle fillPattern)
{
	return m_FiguresList.setFillPattern(fillPattern);
}

// FiguresList를 얻음
CFigurePtrList& CGroup::getFiguresList()
{
	return m_FiguresList;
}

// FiguresList를 갱신함
void CGroup::setFiguresList(IN CFigurePtrList& figurePtrList)
{
	m_FiguresList = figurePtrList;

	m_Area = m_FiguresList.GetHead()->getArea();
	for (POSITION pos = m_FiguresList.GetHeadPosition(); pos; m_FiguresList.GetNext(pos)) {
		RectF::Union(m_Area, m_Area, m_FiguresList.GetAt(pos)->getArea());		// 그룹의 영역에 개체의 영역을 합침
	}
}