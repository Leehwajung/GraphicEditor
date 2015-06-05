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
	CPolyLine(IN Pen* pen);
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
	virtual BOOL create(void* param1, ...);

public:
	// �̵�
	// ���� ��ǥ���� �� ��ǥ������ Offset�� �������� ������ �̵�
	// - IN �Ű�����
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵��� �� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// ũ�� ����
	// ������ �ڵ��� ��ǥ�� �����Ͽ� ũ�� ���� (���� ��ǥ�� �����ϸ� �̸� �������� �� ��ǥ�� �����Ͽ� ũ�� ����)
	// - IN �Ű�����
	//		Position selectedHandle: ������ ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
	virtual void resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);


	/* Menu Item */
	// ����
	// ��� �����ϰ� �޸𸮸� ����
	virtual void destroy();

	/* LButtonDown */
	// ��ǥ ��ġ Ȯ��
	// ���� ���� �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
	// - IN �Ű�����
	//		PointF point: Ȯ���� ��ǥ
	// - ��ȯ �� (Position)
	//		Position: ���� ���� ���� ��ġ
	virtual Position pointInFigure(IN PointF point);


	/** �׸��� **/
	/* OnDraw */
	// ���� �׸���
	// - IN �Ű�����
	//		Graphics* lpGraphics: �׸��� ��� Graphics
	virtual void draw(IN Graphics* lpGraphics);

	/* OnMouseMove */
	// ���� �׸���
	// ���� �ÿ� ������ �׸���
	// - IN �Ű�����
	//		PointF addingPoint
	//		Graphics* lpGraphics: �׸��� ��� Graphics
	//		CreateFlag createFlag = FREECREATE: ���� ���� �÷���
	// ok!!
	void creating(IN Graphics* lpGraphics, IN PointF addingPoint, IN CreateFlag createFlag = FREECREATE);

private:
	// ���� �׸���
	// ���� �ÿ� ������ �׸���
	// - IN �Ű�����
	//		Graphics* lpGraphics: �׸��� ��� Graphics
	//		void* param1, ...:PointF addingPoint, CreateFlag ������ �Է�
	// ok!!
	virtual void creating(IN Graphics* lpGraphics, void* param1, ...);

public:
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

	// ���� ��ǥ �̵�
	virtual void pointMove(IN PointF originPoint, IN PointF targetPoint);

	// ���� ��ǥ �̵� �׸���
	virtual void pointMoving(IN PointF originPoint, IN PointF targetPoint);


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


