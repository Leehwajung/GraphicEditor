// Shape.cpp : CShape Ŭ������ ����
// CShape : 2���� ���� ��ü�� �����ϴ� Ŭ����
// 

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Shape.h"
#include "Global.h"


// CShape

IMPLEMENT_DYNAMIC(CShape, CFigure)

CShape::CShape()
	: CFigure()
	, m_Pen(NULL)
	, m_Brush(NULL)
{
}

CShape::CShape(IN CClientDC* lpClientDC)
	: CFigure(lpClientDC)
	, m_Pen(NULL)
	, m_Brush(NULL)
{
}

CShape::CShape(IN Graphics* lpGraphics)
	: CFigure(lpGraphics)
	, m_Pen(NULL)
	, m_Brush(NULL)
{
}

CShape::CShape(IN CClientDC* lpClientDC, IN Pen* pen, IN Brush* brush)
	: CFigure(lpClientDC)
	, m_Pen(pen->Clone())
	, m_Brush(brush->Clone())
{
}

CShape::CShape(IN Graphics* lpGraphics, IN Pen* pen, IN Brush* brush)
	: CFigure(lpGraphics)
	, m_Pen(pen->Clone())
	, m_Brush(brush->Clone())
{

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

// �� ȹ��
Pen* CShape::getPen()
{

}

// �귯�� ȹ��
Brush* CShape::getBrush()
{

}

// �귯�� Ÿ�� ȹ��
BrushType CShape::getBrushType()
{

}

// ������ �� ȹ��
Color CShape::getOutlineColor()
{

}

// ������ �β� ȹ��
REAL CShape::getOutlineWidth()
{

}

// ������ ���� ȹ��
DashStyle CShape::getOutlinePattern()
{

}

// ä��� �� ȹ��
Color CShape::getFillColor()
{

}

// ä��� ���� ȹ��
HatchStyle CShape::getFillPattern()
{

}

// �� ����
void CShape::setPen(IN const Pen* pen)
{

}

// �귯�� ����
void CShape::setBrush(IN const Brush* brush)
{

}

// ������ �� ����
void CShape::setOutlineColor(IN const Color& outlineColor)
{

}

// ������ �β� ����
void CShape::setOutlineWidth(IN const REAL outlineWidth)
{

}

// ������ ���� ����
void CShape::setOutlinePattern(IN const DashStyle outlinePattern)
{

}

// ĥ�ϱ� �� ����
void CShape::setFillColor(IN const Color& fillColor)
{

}

// ĥ�ϱ� ���� ����
void CShape::setFillPattern(IN const HatchStyle fillPattern)
{

}