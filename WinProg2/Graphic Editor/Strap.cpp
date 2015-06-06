// Strap.cpp : CStrap Ŭ������ ����
// CStrap : �� ��ü�� �����ϴ� Ŭ����
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


// CStrap ��� �Լ�


void CStrap::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code

	}
	else
	{	// loading code

	}
}

// ���� ��ǥ �̵�
void CStrap::pointMove(IN PointF originPoint, IN PointF targetPoint)
{

}

// ���� ��ǥ �̵� �׸���
RectF CStrap::pointMoving(Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint)
{
	RectF drawnArea;



	return drawnArea;
}

// �� ȹ��
Pen* CStrap::getPen()
{
	return this->m_OutlinePen;
}

// ������ �� ȹ��
Color CStrap::getOutlineColor()
{
	Color result;
	m_OutlinePen->GetColor(&result);

	return result;
}

// ������ �β� ȹ��
REAL CStrap::getOutlineWidth()
{
	return m_OutlinePen->GetWidth();
}

// ������ ���� ȹ��
DashStyle CStrap::getOutlinePattern()
{
	return m_OutlinePen->GetDashStyle();
}

// �� ����
void CStrap::setPen(IN const Pen* pen)
{
	// ���� �� ����
	if (m_OutlinePen) {
		m_OutlinePen->~Pen();
	}

	// ���޹��� �� ����
	m_OutlinePen = pen->Clone();
}

// ������ �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CStrap::setOutlineColor(IN const Color& outlineColor)
{
	return m_OutlinePen->SetColor(outlineColor) ? TRUE : FALSE;
}

// ������ �β� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CStrap::setOutlineWidth(IN const REAL outlineWidth)
{
	return m_OutlinePen->SetWidth(outlineWidth) ? TRUE : FALSE;
}

// ������ ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CStrap::setOutlinePattern(IN const DashStyle outlinePattern)
{
	return m_OutlinePen->SetDashStyle(outlinePattern) ? TRUE : FALSE;
}


// �� �߰� (���� ����): ���� �������� �ٲٱ� �� �ӽ� ����
//void CStrap::addPoint(PointF point){}