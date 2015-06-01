// Rectangle.h : CRectangle Ŭ������ �������̽�
// CRectangle : ���簢�� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Shape.h"

// CRectangle ��� ����Դϴ�.

class CRectangle : public CShape
{
// ���� �� �Ҹ�
public:
	CRectangle();
	CRectangle(IN CClientDC* lpClientDC);
	CRectangle(IN Graphics* lpGraphics);
	CRectangle(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush);
	CRectangle(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush);
	CRectangle(IN CClientDC* lpClientDC, IN Pen* pen, IN BrushPtr brush, IN RectF rect);
	CRectangle(IN Graphics* lpGraphics, IN Pen* pen, IN BrushPtr brush, IN RectF rect);
	DECLARE_SERIAL(CRectangle)
	virtual ~CRectangle();



// �۾� �� ������
public:
	/* ����ȭ */
	// ����ȭ
	virtual void Serialize(CArchive& ar);


	/* ���� */
	// ����
	// ���� ��ǥ�� �� ��ǥ�� �������� �簢���� ������
	// - IN �Ű�����
	//		PointF startingPoint: ���� ���� ��ǥ
	//		PointF endingPoint: ���� �� ��ǥ
	//		CreateFlag createFlag = FREECREATE: ���� ���� �÷���
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	BOOL create(IN PointF startingPoint, IN PointF endingPoint, IN CreateFlag createFlag = FREECREATE);

private:
	// ����
	// ���� ��ǥ�� �� ��ǥ�� �������� �簢���� ������
	// - IN �Ű�����
	//		void* param1, ...: PointF*(startingPoint), PointF*(endingPoint), CreateFlag* ������ �Է�
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL create(void* param1, ...);

public:
	// �̵�
	// ���� ��ǥ���� �� ��ǥ������ Offset�� �������� �簢���� �̵�
	// - IN �Ű�����
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵��� �� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// ũ�� ����
	// ������ �ڵ��� ��ǥ�� �����Ͽ� ũ�� ���� (���� ��ǥ�� �����ϸ� �̸� �������� �� ��ǥ�� �����Ͽ� ũ�� ����)
	// - IN �Ű�����
	//		Position selcetedHandle: �簢���� ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selcetedHandle�� ���� ���� Default ���� ��ǥ )
	virtual void resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);

	// ����
	// �簢���� �����ϰ� �޸𸮸� ����
	virtual void destroy();

	// ��ǥ ��ġ Ȯ��
	// ���� �簢�� �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
	// - IN �Ű�����
	//		PointF point: Ȯ���� ��ǥ
	// - ��ȯ �� (Position)
	//		Position: �簢�� ���� ���� ��ġ
	virtual Position pointInFigure(IN PointF point);


	/* �׸��� */
	// ���� �׸���
	virtual void draw();

	// ���� �׸���
	// ���� �ÿ� ������ �׸���
	// - IN �Ű�����
	//		PointF startingPoint: ���� ���� ��ǥ
	//		PointF targetPoint: ���� �� ���� ���� ��ǥ
	//		CreateFlag createFlag = FREECREATE: ���� ���� �÷���
	void creating(IN PointF startingPoint, IN PointF targetPoint, IN CreateFlag createFlag = FREECREATE);

private:
	// ���� �׸���
	// ���� �ÿ� ������ �׸���
	// - IN �Ű�����
	//		...: PointF(startingPoint), PointF(endingPoint), CreateFlag ������ �Է�
	virtual void creating(void* param1, ...);

public:
	// �̵� �׸���
	// �̵� �߿� ������ �׸���
	// - IN �Ű�����
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵� ���� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	virtual void moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);

	// ũ�� ���� �׸���
	// ũ�� ���� �߿� ������ �׸���
	// - IN �Ű�����
	//		Position selcetedHandle: ��ü�� ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selcetedHandle�� ���� ���� Default ���� ��ǥ )
	virtual void resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);


protected:
	/* ��ü ���� ���� */
	// ��ü ���� ����
	virtual void resetArea();



// Ư��
protected:
	RectF m_Rect;	// �簢��
};



//// ���� �� �Ҹ�
//public:
//	CRectangle();
//	CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/);
//	CRectangle(Graphics* lpGraphics/*, PointF startingPoint*/);
//	//CRectangle(CClientDC* lpClientDC, RectF& rect);
//	CRectangle(CClientDC* lpClientDC/*, PointF startingPoint*/, /*RectF& rect,*/ Pen* pen, SolidBrush* brush);
//	virtual ~CRectangle();
//
//public:
//	// LButtonDown
//	virtual void create(PointF startingPoint);					// ��ü ����
//	virtual operationModeFlags cursorPosition(PointF point);	// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���)
//
//
//	// OnMouseMove
//	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
//	virtual void creating(UINT nFlags, PointF point);			// ���� �׸���
//	virtual void moving(UINT nFlags, PointF point);				// �̵� �׸���
//	virtual void resizing(UINT nFlags, PointF point);			// ũ�� ���� �׸���
//
//	// LButtonUp
//	virtual void endCreate(PointF point);						// ���� �Ϸ�
//	virtual void move(PointF originPoint, PointF targetPoint);							// ��ü �̵�
//	virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// ��ü ũ�� ����
//	virtual operationModeFlags cursorPosition(RectF rect);		// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���)
//	
//	// OnDraw / OnPaint
//	virtual void draw();										// ��ü �׸���
//	virtual void drawSelect();
//
//	// Menu Item
//	virtual void destroy();										// ��ü ����