// Strap.cpp : CStrap 클래스의 구현
// CStrap : 선 개체를 정의하는 클래스
//

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Strap.h"
#include "Global.h"


// CStrap

IMPLEMENT_SERIAL(CStrap, CFigure, 1)

CStrap::CStrap()
	: CFigure()
	, m_OutlinePen(NULL)
{
}

CStrap::CStrap(IN Pen* pen)
	: CFigure()
	, m_OutlinePen(pen->Clone())
{
}

CStrap::~CStrap()
{
	if (m_OutlinePen) {
		m_OutlinePen->~Pen();
	}
}


// CStrap 멤버 함수


void CStrap::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code

	}
	else
	{	// loading code

	}
}

// 개별 좌표 이동
void CStrap::pointMove(IN PointF originPoint, IN PointF targetPoint)
{

}

// 개별 좌표 이동 그리기
RectF CStrap::pointMoving(Graphics& graphics, IN PointF originPoint, IN PointF targetPoint)
{
	RectF drawnArea;



	return drawnArea;
}

// 펜 획득
Pen* CStrap::getPen()
{
	return this->m_OutlinePen;
}

// 윤곽선 색 획득
Color CStrap::getOutlineColor()
{
	Color result;
	m_OutlinePen->GetColor(&result);

	return result;
}

// 윤곽선 두께 획득
REAL CStrap::getOutlineWidth()
{
	return m_OutlinePen->GetWidth();
}

// 윤곽선 패턴 획득
DashStyle CStrap::getOutlinePattern()
{
	return m_OutlinePen->GetDashStyle();
}

// 펜 설정
void CStrap::setPen(IN const Pen* pen)
{
	// 기존 펜 제거
	if (m_OutlinePen) {
		m_OutlinePen->~Pen();
	}

	// 전달받은 펜 복사
	m_OutlinePen = pen->Clone();
}

// 윤곽선 색 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CStrap::setOutlineColor(IN const Color& outlineColor)
{
	return m_OutlinePen->SetColor(outlineColor) ? TRUE : FALSE;
}

// 윤곽선 두께 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CStrap::setOutlineWidth(IN const REAL outlineWidth)
{
	return m_OutlinePen->SetWidth(outlineWidth) ? TRUE : FALSE;
}

// 윤곽선 패턴 설정
// - 반환 값 (BOOL)
//		TRUE: 설정 실패
//		FALSE: 설정 성공
BOOL CStrap::setOutlinePattern(IN const DashStyle outlinePattern)
{
	return m_OutlinePen->SetDashStyle(outlinePattern) ? TRUE : FALSE;
}


// 점 추가 (순수 가상): 순수 가상으로 바꾸기 전 임시 구현
//void CStrap::addPoint(PointF point){}