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


// CShape ��� �Լ�

// �۾�
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

// ������
/* ������ �� ���� */
void CShape::setLineColor(const Color& LineColor) {
	m_Pen->SetColor(LineColor);
}

/* ������ �β� ���� */
void CShape::setLineWidth(const REAL& LineWidth) {
	m_Pen->SetWidth(LineWidth);
}

/* ������ ���� ���� */
void CShape::setLinePattern(const DashStyle& LinePattern) {
	m_Pen->SetDashStyle(LinePattern);
}

/* ĥ�ϱ� �� ���� */
void CShape::setFillColor(const Color& FillColor) {
	
}

/* ĥ�ϱ� ���� ���� */
void CShape::setFillPattern(const int FillPattern) {

	m_lpGraphics->GetHDC();
}