// Group.cpp : CGroup Ŭ������ ����
// CGroup : �׷�ȭ�� ���� ��ü���� �����ϴ� Ŭ����
// @Author Lee Hwajung

#include "stdafx.h"
#include "Graphic Editor.h"
#include "Group.h"


// CGroup

IMPLEMENT_SERIAL(CGroup, CFigure, 1)


CGroup::CGroup()
{
}

CGroup::~CGroup()
{
}


// CGroup ��� �Լ�


/** ����ȭ **/
// ����ȭ (���������Լ��� �ٲ��� ����)
void CGroup::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}


/** ���� **/
// ����
// �Ű������� ���� �������� ���ο� ��ü�� ����
// - IN �Ű�����
//		void* param1, ...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::create(void* param1, ...)
{
	return FALSE;	// �ӽ� ��ȯ��
}

// �̵�
// ���� ��ǥ���� �� ��ǥ������ Offset�� �������� ��ü�� �̵�
// - IN �Ű�����
//		PointF originPoint: �̵��� ���� ��ǥ
//		PointF targetPoint: �̵��� �� ��ǥ
//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
void CGroup::move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{

}

// ũ�� ����
// ������ �ڵ��� ��ǥ�� �����Ͽ� ũ�� ���� (���� ��ǥ�� �����ϸ� �̸� �������� �� ��ǥ�� �����Ͽ� ũ�� ����)
// - IN �Ű�����
//		Position selectedHandle: ��ü�� ���õ� �ڵ�
//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
void CGroup::resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{

}

// ����
// ��ü�� �����ϰ� �޸𸮸� ����
void CGroup::destroy()
{

}

// ��ǥ ��ġ Ȯ��
// ���� ��ü �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
// - IN �Ű�����
//		PointF point: Ȯ���� ��ǥ
// - ��ȯ �� (Position)
//		Position: ��ü ���� ���� ��ġ
CFigure::Position CGroup::pointInFigure(IN PointF point)
{
	return OUTSIDE;	// �ӽ� ��ȯ��
}

/** ��ü ���� ���� **/
// ��ü ���� ����
void CGroup::resetArea()
{

}

/** �׸��� **/
// ��ü �׸���
void CGroup::draw(IN Graphics* lpGraphics)
{

}

// ���� �׸���
// ���� �ÿ� ������ �׸���
// - IN �Ű�����
//		Graphics* lpGraphics: �׸��� ��� Graphics
//		void* param1, ...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
//		[CreateFlag createFlag = FREECREATE]: ���� ���� �÷���, �ʿ��ϸ� �߰��ϱ�
void CGroup::creating(IN Graphics* lpGraphics, void* param1, ...)
{

}

// �̵� �׸���
// �̵� �߿� ������ �׸���
// - IN �Ű�����
//		Graphics* lpGraphics: �׸��� ��� Graphics
//		PointF originPoint: �̵��� ���� ��ǥ
//		PointF targetPoint: �̵� ���� ��ǥ
//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
void CGroup::moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag/* = FREEMOVE*/)
{

}

// ũ�� ���� �׸���
// ũ�� ���� �߿� ������ �׸���
// - IN �Ű�����
//		Graphics* lpGraphics: �׸��� ��� Graphics
//		Position selectedHandle: ��ü�� ���õ� �ڵ�
//		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
void CGroup::resizing(IN Graphics* lpGraphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag/* = FREERESIZE*/, IN PointF* anchorPoint/* = NULL*/)
{

}


/** �Ӽ� ���� **/
// ������ �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setOutlineColor(IN const Color& outlineColor)
{
	return FALSE;	// �ӽ� ��ȯ��
}

// ������ �β� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setOutlineWidth(IN const REAL outlineWidth)
{
	return FALSE;	// �ӽ� ��ȯ��
}

// ������ ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setOutlinePattern(IN const DashStyle outlinePattern)
{
	return FALSE;	// �ӽ� ��ȯ��
}

// �� ä��� �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setFillColor(IN const Color& fillColor)
{
	return FALSE;	// �ӽ� ��ȯ��
}

// ���� ä��� �� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setFillSubcolor(IN const Color& fillSubcolor)
{
	return FALSE;	// �ӽ� ��ȯ��
}

// ä��� ���� ����
// - ��ȯ �� (BOOL)
//		TRUE: ���� ����
//		FALSE: ���� ����
BOOL CGroup::setFillPattern(IN const HatchStyle fillPattern)
{
	return FALSE;	// �ӽ� ��ȯ��
}