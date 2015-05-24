// Figure.h : CFigure Ŭ������ �������̽�
// CFigure : Ŭ���̾�Ʈ �������� �� �� �ִ� ��ü�� �����ϴ� Ŭ���� (��� ��ü�� ���� Ŭ����)
// @Author Lee Hwajung

#pragma once

#include "afx.h"
#include <gdiplus.h>
//#include <afxcoll.h>
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
		Proportional	= (int) 0x00004
	};

public:
	CFigure();
	CFigure(Graphics* lpGraphics);
	virtual ~CFigure();

public:
	// LButtonDown
	virtual void create(PointF startingPoint);					// ��ü ����
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
	Graphics* getGraphics();
	void setGraphics(Graphics* lpGraphics);

	PointF& getStartingPoint();
	void setStartingPoint(PointF StartingPoint);

	operationModeFlags getOperationMode();
	void setOperationMode(operationModeFlags OperationMode);

// Ư��
protected:
	Graphics* m_lpGraphics;
	PointF m_StartingPoint;
	operationModeFlags m_OperationMode;
	Region m_Region;			// ��ü ���� ���� (�簢��) https://msdn.microsoft.com/en-us/library/6y4t32t5(v=vs.120).aspx
};


