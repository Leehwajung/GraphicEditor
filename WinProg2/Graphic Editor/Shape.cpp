// Shape.cpp : CShape Ŭ������ ����
// CShape : 2���� ���� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Shape.h"
#include "Global.h"


// CShape

CShape::CShape()
{
}

CShape::CShape(CClientDC* lpClientDC)
	: CFigure(lpClientDC)
	, m_Pen(new defaultPen)
	, m_Brush(new defaultBrush)
{
}

CShape::CShape(Graphics* lpGraphics)
	: CFigure(lpGraphics)
	, m_Pen(new defaultPen)
	, m_Brush(new defaultBrush)
{

}

CShape::CShape(CClientDC* lpClientDC, Pen* pen, SolidBrush* brush)
	: CFigure(lpClientDC)
{
	m_Pen = pen->Clone();
	m_Brush = (SolidBrush*)brush->Clone();
}

CShape::~CShape()
{
	if (!m_Pen) {
		m_Pen->~Pen();
	}
	if (!m_Brush) {
		m_Brush->~SolidBrush();
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

SolidBrush* CShape::getBrush() {
	return m_Brush;
}

void CShape::setBrush(const SolidBrush* brush) {
	if (m_Brush) {
		m_Brush->~SolidBrush();
	}
	m_Brush = (SolidBrush*) brush->Clone();
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
	m_Brush->SetColor(FillColor);
}

/* ĥ�ϱ� ���� ���� */
void CShape::setFillPattern(const int FillPattern) {
	// ���� ���� ����
}