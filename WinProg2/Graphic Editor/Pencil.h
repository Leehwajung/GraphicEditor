// Pencil.h : CPencil Ŭ������ �������̽�
// CPencil : ���� �(����) ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "PolyLine.h"

// CPencil ��� ����Դϴ�.

class CPencil : public CPolyLine
{
public:
	CPencil();
	CPencil(IN Pen* pen);
	DECLARE_SERIAL(CPencil)
	~CPencil();

	/* LButtonDown */
	// ��ǥ ��ġ Ȯ��
	// ���� ���� �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
	// - IN �Ű�����
	//		PointF point: Ȯ���� ��ǥ
	// - ��ȯ �� (Position)
	//		Position: ���� ���� ���� ��ġ
	virtual Position pointInFigure(IN PointF point);
public:
	/* Menu Item */
	// ����
	// ��� �����ϰ� �޸𸮸� ����
	virtual void destroy();
};