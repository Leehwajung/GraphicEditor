// Shape.cpp : CShape Ŭ������ ����
// CShape : 2���� ���� ��ü�� �����ϴ� Ŭ����
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


// CShape ��� �Լ�

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