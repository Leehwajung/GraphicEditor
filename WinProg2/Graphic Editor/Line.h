#pragma once
#include "Figure.h"


// Make and Edit by Byun Jun
class CLine : public CFigure
{
public:
	CLine();
	~CLine();

	// LButtonDown
	virtual void Create(CPoint startingPoint);               // �� ����
	virtual operationModeFlags cursorPosition(CPoint point); // Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���)
	virtual operationModeFlags cursorPosition(CRect rect);		// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���)

	// OnMouseMove
	void mouseMoveOperation(UINT nFlags, CPoint point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
	virtual void creating(UINT nFlags, CPoint point);			// ���� �׸���
	virtual void moving(UINT nFlags, CPoint point);				// �̵� �׸���
	virtual void resizing(UINT nFlags, CPoint point);			// ũ�� ���� �׸���

	// LButtonUp / LButtonDlk
	virtual void addPoint(CPoint point);						// �� �߰�
	virtual void move(CPoint target);							// ��ü �̵�
	virtual void resize(CPoint point, int resizeFlags);			// ��ü ũ�� ����

	// OnDraw / OnPaint
	virtual void draw();										// ��ü �׸���

	// Menu Item
	virtual void destroy();										// ��ü ����

	virtual void setLineColor(Color lineColor);					// �� �� ����
	virtual void setLineWidth(int lineWidth);					// �� �β� ����
	virtual void setLinePattern(int linePattern);				// �� ���� ����

	// Getter
	CList<CPoint, CPoint&>& GetPointsList();

private:

	/* �� ���� ��ǥ */
	CList <CPoint, CPoint&> m_PointsList;

	/* �׸��� ���� �� */
	CPen m_LinePen;

	/* �� �β� */
	int m_lineWidth;

	/* �� ���� */
	int m_linePattern;




};

   