// Line.h : CLine Ŭ������ �������̽�
// CLine : ���� ��ü�� �����ϴ� Ŭ����
// 

#pragma once
#include "Strap.h"


// Make and Edit by Byun Jun
class CLine : public CStrap
{
public:
	CLine();
	~CLine();

	// LButtonDown
	virtual void Create(PointF startingPoint);					// �� ����
	virtual operationModeFlags cursorPosition(PointF point);	// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���)
	virtual operationModeFlags cursorPosition(CRect rect);		// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���)

	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
	virtual void creating(UINT nFlags, PointF point);			// ���� �׸���
	virtual void moving(UINT nFlags, PointF point);				// �̵� �׸���
	virtual void resizing(UINT nFlags, PointF point);			// ũ�� ���� �׸���

	// LButtonUp / LButtonDlk
	virtual void addPoint(PointF point);						// �� �߰�
	virtual void move(PointF target);							// ��ü �̵�
	virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);			// ��ü ũ�� ����

	// OnDraw / OnPaint
	virtual void draw();										// ��ü �׸���

	// Menu Item
	virtual void destroy();										// ��ü ����

	virtual void setLineColor(Color lineColor);					// �� �� ����
	virtual void setLineWidth(int lineWidth);					// �� �β� ����
	virtual void setLinePattern(int linePattern);				// �� ���� ����
	virtual void setProperties(CFigureProperties properties);	// ������ ������ ��ü �Ӽ� ����

	// Getter
	CList <PointF, PointF&>& GetPointsList();

private:

	/* �� ���� ��ǥ */
	CList <PointF, PointF&> m_PointsList;

	/* �׸��� ���� �� */
	//Pen m_LinePen;

	///* �� �β� */
	//int m_LineWidth;

	///* �� ���� */
	//int m_LinePattern;


	PointF m_EndPoint;
	Color m_LineColor;	// ������ ��
	int m_LinePattern;	// ������ ����
	int m_LineWidth;	// ������ �β�
};

   