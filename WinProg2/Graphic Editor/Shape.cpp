// Shape.cpp : CShape Å¬·¡½ºÀÇ ±¸Çö
// CShape : 2Â÷¿ø µµÇü °³Ã¼¸¦ Á¤ÀÇÇÏ´Â Å¬·¡½º
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


// CShape ¸â¹ö ÇÔ¼ö

// Ææ È¹µæ
Pen* CShape::getPen()
{

}

// ºê·¯½Ã È¹µæ
Brush* CShape::getBrush()
{

}

// ºê·¯½Ã Å¸ÀÔ È¹µæ
BrushType CShape::getBrushType()
{

}

// À±°û¼± »ö È¹µæ
Color CShape::getOutlineColor()
{

}

// À±°û¼± µÎ²² È¹µæ
REAL CShape::getOutlineWidth()
{

}

// À±°û¼± ÆÐÅÏ È¹µæ
DashStyle CShape::getOutlinePattern()
{

}

// Ã¤¿ì±â »ö È¹µæ
Color CShape::getFillColor()
{

}

// Ã¤¿ì±â ÆÐÅÏ È¹µæ
HatchStyle CShape::getFillPattern()
{

}

// Ææ ¼³Á¤
void CShape::setPen(IN const Pen* pen)
{

}

// ºê·¯½Ã ¼³Á¤
void CShape::setBrush(IN const Brush* brush)
{

}

// À±°û¼± »ö ¼³Á¤
void CShape::setOutlineColor(IN const Color& outlineColor)
{

}

// À±°û¼± µÎ²² ¼³Á¤
void CShape::setOutlineWidth(IN const REAL outlineWidth)
{

}

// À±°û¼± ÆÐÅÏ ¼³Á¤
void CShape::setOutlinePattern(IN const DashStyle outlinePattern)
{

}

// Ä¥ÇÏ±â »ö ¼³Á¤
void CShape::setFillColor(IN const Color& fillColor)
{

}

// Ä¥ÇÏ±â ÆÐÅÏ ¼³Á¤
void CShape::setFillPattern(IN const HatchStyle fillPattern)
{

}