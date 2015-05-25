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

CShape::~CShape()
{
	m_Pen->~Pen();
	m_Brush->~Brush();
}


// CShape 멤버 함수

Pen* CShape::getPen() {
	return m_Pen;
}

void CShape::setPen(const Pen* pen) {
	m_Pen = pen->Clone();
}


Brush* CShape::getBrush() {
	return m_Brush;
}


void CShape::setBrush(const Brush* brush) {
	m_Brush = brush->Clone();
}