// Shape.cpp : CShape 클래스의 구현
// CShape : 2차원 도형 개체를 정의하는 클래스
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Shape.h"
#include "Global.h"


// CShape

CShape::CShape()
	: m_Pen(new defaultPen)
	, m_Brush(new defaultBrush)
{

}

CShape::CShape(Pen* pen, Brush* brush)
{
	m_Pen = pen->Clone();
	m_Brush = brush->Clone();
}

CShape::~CShape()
{
	if (m_Pen) {
		m_Pen->~Pen();
	}
	if (m_Brush) {
		m_Brush->~Brush();
	}
}


// CShape 멤버 함수

// 작업
Pen* CShape::getPen() {
	return m_Pen;
}

void CShape::setPen(const Pen* pen) {
	if (m_Pen) {
		m_Pen->~Pen();
	}
	m_Pen = pen->Clone();
}

Brush* CShape::getBrush() {
	return m_Brush;
}

void CShape::setBrush(const Brush* brush) {
	if (m_Brush) {
		m_Brush->~Brush();
	}
	m_Brush = brush->Clone();
}

// 재정의
/* 윤곽선 색 설정 */
void CShape::setLineColor(const Color& LineColor) {
	m_Pen->SetColor(LineColor);
}

/* 윤곽선 두께 설정 */
void CShape::setLineWidth(const REAL& LineWidth) {
	m_Pen->SetWidth(LineWidth);
}

/* 윤곽선 패턴 설정 */
void CShape::setLinePattern(const DashStyle& LinePattern) {
	m_Pen->SetDashStyle(LinePattern);
}

/* 칠하기 색 설정 */
void CShape::setFillColor(const Color& FillColor) {
	
}

/* 칠하기 패턴 설정 */
void CShape::setFillPattern(const int FillPattern) {

	m_lpGraphics->GetHDC();
}