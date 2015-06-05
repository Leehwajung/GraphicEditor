// PolyLine.h : CPolyLine Ŭ������ �������̽�
// CPolyLine : �������� ��ü�� �����ϴ� Ŭ����
//

#pragma once
#include "Strap.h"

// CPolyLine ��� ����Դϴ�.

class CPolyLine : public CStrap
{
public:

	CPolyLine();
	CPolyLine(IN CClientDC* lpClientDC);
	CPolyLine(IN Graphics* lpGraphics);
	CPolyLine(IN CClientDC* lpClientDC, IN Pen* pen);
	CPolyLine(IN Graphics* lpGraphics, IN Pen* pen);
	DECLARE_SERIAL(CPolyLine)
	~CPolyLine();

	virtual void Serialize(CArchive& ar);

	/** ���� **/
	/* LButtonUp */
	void addPoint(PointF addingPoint);

	/* LButtonDlk */
	// ����
	// ���� ��ǥ�� �� ��ǥ�� �������� ������ ������
	// - IN �Ű�����
	//		CreateFlag createFlag = FREECREATE: ���� ���� �÷���
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	// ok!!
	BOOL create(IN CreateFlag createFlag = FREECREATE);

private:
	// ����
	// ���� ��ǥ�� �� ��ǥ�� �������� ������ ������
	// - IN �Ű�����
	//		void* param1, ...: CreateFlag ������ �Է�
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	// ok!!
	virtual BOOL create(void* param1, ...);

public:
	// �̵�
	// ���� ��ǥ���� �� ��ǥ������ Offset�� �������� ������ �̵�
	// - IN �Ű�����
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵��� �� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	// ok!!
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// ũ�� ����
	// ������ �ڵ��� ��ǥ�� �����Ͽ� ũ�� ���� (���� ��ǥ�� �����ϸ� �̸� �������� �� ��ǥ�� �����Ͽ� ũ�� ����)
	// - IN �Ű�����
	//		Position selcetedHandle: ������ ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selcetedHandle�� ���� ���� Default ���� ��ǥ )
	// ok!!
	virtual void resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);


	/* Menu Item */
	// ����
	// ��� �����ϰ� �޸𸮸� ����
	// ok!!
	virtual void destroy();

	/* LButtonDown */
	// ��ǥ ��ġ Ȯ��
	// ���� ���� �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
	// - IN �Ű�����
	//		PointF point: Ȯ���� ��ǥ
	// - ��ȯ �� (Position)
	//		Position: ���� ���� ���� ��ġ
	// ok!!
	virtual Position pointInFigure(IN PointF point);


	/** �׸��� **/
	/* OnDraw */
	// ���� �׸���
	virtual void draw();

	/* OnMouseMove */
	// ���� �׸���
	// ���� �ÿ� ������ �׸���
	// - IN �Ű�����
	//		PointF addingPoint
	//		CreateFlag createFlag = FREECREATE: ���� ���� �÷���
	// ok!!
	void creating(IN PointF addingPoint, IN CreateFlag createFlag = FREECREATE);

private:
	// ���� �׸���
	// ���� �ÿ� ������ �׸���
	// - IN �Ű�����
	//		void* param1, ...:PointF addingPoint, CreateFlag ������ �Է�
	// ok!!
	virtual void creating(void* param1, ...);

public:
	// �̵� �׸���
	// �̵� �߿� ������ �׸���
	// - IN �Ű�����
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵� ���� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	// ok!!
	virtual void moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// ũ�� ���� �׸���
	// ũ�� ���� �߿� ������ �׸���
	// - IN �Ű�����
	//		Position selcetedHandle: ��ü�� ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selcetedHandle�� ���� ���� Default ���� ��ǥ )
	// ok!!
	virtual void resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);


protected:
	/** ��ü ���� ���� **/
	// ��ü ���� ����
	virtual void resetArea();

public:
	// Getter
	CList <PointF, PointF&>& GetPointsList();

private:

	CList <PointF, PointF&> m_PointsList;

	RectF m_SubArea;
};
