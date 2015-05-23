// Figure.h : CFigure Ŭ������ �������̽�
// @Author Lee Hwajung

#pragma once

//#include "afx.h"
//#include <gdiplus.h>
#include "FigureProperties.h"

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
	virtual void setProperties(CFigureProperties properties);	// ������ ������ ��ü �Ӽ� ����

	// OnDraw / OnPaint
	virtual void draw();										// ��ü �׸���
	virtual void drawSelect();

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

// Ư��
protected:
	CDC* m_lpdc;
	CPoint m_StartingPoint;
	operationModeFlags m_OperationMode;
	CRgn m_Region;			// ���� ���� https://msdn.microsoft.com/en-us/library/6y4t32t5(v=vs.120).aspx

	Color m_LineColor;		// ������ ��
	int m_LinePattern;	// ������ ����
	int m_LineWidth;		// ������ �β�
};


