// Figure.h : CFigure Ŭ������ �������̽�
//

#pragma once

//#include "afx.h"
//#include <gdiplus.h>

using namespace Gdiplus;

// CFigure ��� ����Դϴ�.

class CFigure : public CObject
{
public:
	enum operationModeFlags {
		None			= (int) 0x00000,
		Create			= (int) 0x00001,
		Move			= (int) 0x00002,
		Resize			= (int) 0x00004
	};

	enum resizeFlags {
		Free			= (int) 0x00000,
		Proportional	= (int) 0x00100
	};

public:
	CFigure();
	CFigure(CDC* dc);
	virtual ~CFigure();

public:
	// LButtonDown
	virtual void create(CPoint startingPoint);					// ��ü ����
	virtual operationModeFlags cursorPosition(CPoint point);	// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���)
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

	virtual void setLineColor(Color lineColor);					// ������ �� ����
	virtual void setLineWidth(int lineWidth);					// ������ �β� ����
	virtual void setLinePattern(int linePattern);				// ������ ���� ����
	virtual void setFillColor(Color FillColor);					// ĥ�ϱ� �� ����
	virtual void setFillPattern(int fillPattern);				// ĥ�ϱ� ���� ����

	// Getter / Setter
	CDC* getDC();
	void setDC(CDC* dc);

	CPoint& getStartingPoint();
	void setStartingPoint(CPoint StartingPoint);

	operationModeFlags getOperationMode();
	void setOperationMode(operationModeFlags OperationMode);

protected:
	CDC* m_lpdc;
	CPoint m_startingPoint;
	operationModeFlags m_OperationMode;
	Color m_lineColor;
};


