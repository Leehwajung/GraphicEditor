// Group.h : CGroup Ŭ������ �������̽�
// CGroup : �׷�ȭ�� ���� ��ü���� �����ϴ� Ŭ����
// @Author Lee Hwajung

#pragma once
#include "Figure.h"

// CGroup ��� ����Դϴ�.

class CGroup : public CFigure
{
// ���� �� �Ҹ�
public:
	CGroup();
	DECLARE_SERIAL(CGroup)
	virtual ~CGroup();

// �۾�
public:
	/** ����ȭ **/
	// ����ȭ (���������Լ��� �ٲ��� ����)
	virtual void Serialize(CArchive& ar);

	/** ���� **/
	// ����
	// �Ű������� ���� �������� ���ο� ��ü�� ����
	// - IN �Ű�����
	//		void* param1, ...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL create(void* param1, ...);

	// �̵�
	// ���� ��ǥ���� �� ��ǥ������ Offset�� �������� ��ü�� �̵�
	// - IN �Ű�����
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵��� �� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// ũ�� ����
	// ������ �ڵ��� ��ǥ�� �����Ͽ� ũ�� ���� (���� ��ǥ�� �����ϸ� �̸� �������� �� ��ǥ�� �����Ͽ� ũ�� ����)
	// - IN �Ű�����
	//		Position selectedHandle: ��ü�� ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
	virtual void resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);

	// ����
	// ��ü�� �����ϰ� �޸𸮸� ����
	virtual void destroy();

	// ��ǥ ��ġ Ȯ��
	// ���� ��ü �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
	// - IN �Ű�����
	//		PointF point: Ȯ���� ��ǥ
	// - ��ȯ �� (Position)
	//		Position: ��ü ���� ���� ��ġ
	virtual Position pointInFigure(IN PointF point);

/** ��ü ���� ���� **/
protected:
	// ��ü ���� ����
	virtual void resetArea();

/** �׸��� **/
public:
	// ��ü �׸���
	virtual void draw(IN Graphics* lpGraphics);

	// ���� �׸���
	// ���� �ÿ� ������ �׸���
	// - IN �Ű�����
	//		Graphics* lpGraphics: �׸��� ��� Graphics
	//		void* param1, ...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
	//		[CreateFlag createFlag = FREECREATE]: ���� ���� �÷���, �ʿ��ϸ� �߰��ϱ�
	virtual void creating(IN Graphics* lpGraphics, void* param1, ...);

	// �̵� �׸���
	// �̵� �߿� ������ �׸���
	// - IN �Ű�����
	//		Graphics* lpGraphics: �׸��� ��� Graphics
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵� ���� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	virtual void moving(IN Graphics* lpGraphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// ũ�� ���� �׸���
	// ũ�� ���� �߿� ������ �׸���
	// - IN �Ű�����
	//		Graphics* lpGraphics: �׸��� ��� Graphics
	//		Position selectedHandle: ��ü�� ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
	virtual void resizing(IN Graphics* lpGraphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);


/** �Ӽ� ���� **/
public:
	// ������ �� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setOutlineColor(IN const Color& outlineColor);

	// ������ �β� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setOutlineWidth(IN const REAL outlineWidth);

	// ������ ���� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setOutlinePattern(IN const DashStyle outlinePattern);

	// �� ä��� �� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setFillColor(IN const Color& fillColor);

	// ���� ä��� �� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setFillSubcolor(IN const Color& fillSubcolor);

	// ä��� ���� ����
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setFillPattern(IN const HatchStyle fillPattern);


// Ư��
private:
	CFigurePtrList m_FiguresList;
};


