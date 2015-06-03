// Line.h : CLine Ŭ������ �������̽�
// CLine : ���� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Strap.h"

// CLine ��� ����Դϴ�.
// Make and Edit by Byun Jun
class CLine : public CStrap
{
public:
	CLine();
	CLine(IN CClientDC* lpClientDC);
	CLine(IN Graphics* lpGraphics);
	CLine(IN CClientDC* lpClientDC, IN Pen* pen);
	CLine(IN Graphics* lpGraphics, IN Pen* pen);
	DECLARE_SERIAL(CLine)
	~CLine();

	virtual void Serialize(CArchive& ar);

	/** ���� **/
	/* LButtonUp / LButtonDlk */
	// ����
	// ���� ��ǥ�� �� ��ǥ�� �������� ������ ������
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
	// ���� ��ǥ�� �� ��ǥ�� �������� ������ ������
	// - IN �Ű�����
	//		void* param1, ...: PointF*(startingPoint), PointF*(endingPoint), CreateFlag ������ �Է�
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
	//		Position selcetedHandle: ������ ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selcetedHandle�� ���� ���� Default ���� ��ǥ )
	virtual void resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);


	/* Menu Item */
	// ����
	// ������ �����ϰ� �޸𸮸� ����
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
	virtual void draw();

	/* OnMouseMove */
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
	//		void* param1, ...: PointF*(startingPoint), PointF*(endingPoint), CreateFlag ������ �Է�
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
	/** ��ü ���� ���� **/
	// ��ü ���� ����
	virtual void resetArea();

public:
	//// LButtonDown
	//virtual void create(PointF startingPoint);					// �� ����
	//virtual operationModeFlags cursorPosition(PointF point);	// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���)
	//virtual operationModeFlags cursorPosition(RectF rect);		// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���)
	//
	//// OnMouseMove
	//void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
	//virtual void creating(UINT nFlags, PointF point);			// ���� �׸���
	//virtual void moving(UINT nFlags, PointF point);				// �̵� �׸���
	//virtual void resizing(UINT nFlags, PointF point);			// ũ�� ���� �׸���
	//
	//// LButtonUp / LButtonDlk
	//virtual void endCreate(PointF point);						// ���� �Ϸ�
	//virtual void move(PointF originPoint, PointF targetPoint);							// ��ü �̵�
	//virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// ��ü ũ�� ����
	//
	//// OnDraw / OnPaint
	//virtual void draw();										// ��ü �׸���
	//
	//// Menu Item
	//virtual void destroy();										// ��ü ����
	//
	//virtual BOOL setLineColor(const Color& LineColor);			// �� �� ����
	//virtual BOOL setLineWidth(const REAL& LineWidth);			// �� �β� ����
	//virtual BOOL setLinePattern(const DashStyle& LinePattern);	// �� ���� ����

private:

	/* �׸��� ���� �� */
	//Pen m_LinePen;

	///* �� �β� */
	//int m_LineWidth;

	///* �� ���� */
	//int m_LinePattern;
	//Pen* m_OutlinePen;

	PointF m_StartingPoint;
	PointF m_EndPoint;

	int m_Gradient;

	//Color m_LineColor;	// �� ��
	//int m_LinePattern;	// �� ����
	//int m_LineWidth;	// �� �β�
};