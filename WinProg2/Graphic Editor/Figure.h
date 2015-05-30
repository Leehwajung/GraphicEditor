// Figure.h : CFigure Ŭ������ �������̽�
// CFigure : Ŭ���̾�Ʈ �������� �� �� �ִ� ��ü�� �����ϴ� Ŭ���� (��� ��ü�� ���� Ŭ����)
// @Author Lee Hwajung

#pragma once

#include "afx.h"
//#include <gdiplus.h>
//#include <afxcoll.h>
#include "FigureProperties.h"
#include "Global.h"

using namespace Gdiplus;

// CFigure ��� ����Դϴ�.

class CFigure : public CObject
{
// �ڷ���
public:
	enum Position {
		OUTSIDE			= (int) 0x00000,	// ��ü ��
		INSIDE			= (int) 0x00001,	// ��ü ��
		ONPOINT			= (int) 0x00008,	// �ڵ� �� (�ڵ� ���� �������� ONPOINT���� &�������� �˾Ƴ� �� ����)
		TOPLEFT			= (int) 0x00008,	// �»� �ڵ�
		TOP				= (int) 0x00009,	// ���� �ڵ�
		TOPRIGHT		= (int) 0x0000A,	// ��� �ڵ�
		RIGHT			= (int) 0x0000B,	// ���� �ڵ�
		BUTTOMRIGHT		= (int) 0x0000C,	// ���� �ڵ�
		BUTTOM			= (int) 0x0000D,	// ���� �ڵ�
		BUTTOMLEFT		= (int) 0x0000E,	// ���� �ڵ�
		LEFT			= (int) 0x0000F		// ���� �ڵ�
	};

	enum CreateFlag {
		FREECREATE		= NULL,				// ���� ����
		REAULAR			= MK_SHIFT			// ���ٸ�ü �Ǵ� �����⼱ ����
	};

	enum MoveFlag {
		FREEMOVE		= NULL,				// ���� �̵�
	};

	enum ResizeFlag {
		FREERESIZE		= NULL,				// ���� ũ�� ����
		PROPORTIONAL	= MK_SHIFT			// ���� ũ�� ����
	};



// ���� �� �Ҹ�
public:
	CFigure();
	CFigure(IN CClientDC* lpClientDC);
	CFigure(IN Graphics* lpGraphics);
	DECLARE_DYNAMIC(CFigure)
	virtual ~CFigure();



// �۾�
public:
	/* ���� */
	// ���� (����)
	// �Ű������� ���� �������� ���ο� ��ü�� ����
	// - IN �Ű�����
	//		...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
	//		[CreateFlag createFlag = FREECREATE]: ���� ���� �÷���, �ʿ��ϸ� �߰��ϱ�
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL create(...);
	
	// �̵� (����)
	// ���� ��ǥ���� �� ��ǥ������ Offset�� �������� ��ü�� �̵�
	// - IN �Ű�����
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵��� �� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	
	// ũ�� ���� (����)
	// ������ �ڵ��� ��ǥ�� �����Ͽ� ũ�� ���� (���� ��ǥ�� �����ϸ� �̸� �������� �� ��ǥ�� �����Ͽ� ũ�� ����)
	// - IN �Ű�����
	//		Position selcetedHandle: ��ü�� ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selcetedHandle�� ���� ���� Default ���� ��ǥ )
	virtual void resize(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);
	
	// ���� (���� ����)
	// ��ü�� �����ϰ� �޸𸮸� ����
	virtual void destroy();
	
	// ��ǥ ��ġ Ȯ�� (���� ����)
	// ���� ��ü �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
	// - IN �Ű�����
	//		PointF point: Ȯ���� ��ǥ
	// - ��ȯ �� (Position)
	//		Position: ��ü ���� ���� ��ġ
	virtual Position pointInFigure(IN PointF point);

	// �ڵ��� ��ǥ
	// �ڵ��� �߾� ��ǥ�� ����
	// - IN �Ű�����
	//		Position handle: ��ǥ�� ������ϴ� �ڵ�
	// - OUT �Ű�����
	//		PointF* handlePoint:
	//			�ּ� ��: �Ű������� Position�� �ڵ��� ��� �ڵ��� ��ǥ
	//			NULL: �Ű������� Position�� �ڵ��� �ƴ� ���
	// - ��ȯ �� (BOOL)
	//		TRUE: �Ű������� Position�� �ڵ��� ���
	//		FALSE: �Ű������� Position�� �ڵ��� �ƴ� ���
	BOOL getHandlePoint(IN Position handle, OUT PointF* handlePoint);


	/* �׸��� */
	// ���� �׸��� (���� ����)
	virtual void draw();

	// ���� �׸��� (���� ����)
	// ���� �ÿ� ������ �׸���
	// - IN �Ű�����
	//		...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
	//		[CreateFlag createFlag = FREECREATE]: ���� ���� �÷���, �ʿ��ϸ� �߰��ϱ�
	virtual void creating(...);

	// �̵� �׸��� (���� ����)
	// �̵� �߿� ������ �׸���
	// - IN �Ű�����
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵� ���� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	virtual void moving(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	
	// ũ�� ���� �׸��� (���� ����)
	// ũ�� ���� �߿� ������ �׸���
	// - IN �Ű�����
	//		Position selcetedHandle: ��ü�� ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selcetedHandle�� ���� ���� Default ���� ��ǥ )
	virtual void resizing(IN Position selcetedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);

	
	/* Graphics ���� */
	// ClientDC ȹ��
	CClientDC* getClientDC();

	// Graphics ȹ��
	Graphics* getGraphics();

	// ClientDC ����
	void setClientDC(CClientDC* lpClientDC);

	// Graphics ����
	void setGraphics(Graphics* lpGraphics);


	/* �Ӽ� ���� */
	// ������ �� ���� (���� ����)
	virtual void setOutlineColor(IN const Color& outlineColor);

	// ������ �β� ���� (���� ����)
	virtual void setOutlineWidth(IN const REAL outlineWidth);

	// ������ ���� ���� (���� ����)
	virtual void setOutlinePattern(IN const DashStyle outlinePattern);

	// ä��� �� ���� (���� ����)
	virtual void setFillColor(IN const Color& fillColor);

	// ä��� ���� ���� (���� ����)
	virtual void setFillPattern(IN const HatchStyle fillPattern);


protected:
	/* ��ü ���� ���� */
	// ��ü ���� ���� (���� ����)
	virtual void resetArea();

	// ��ü ���� �׸���
	void drawArea();

private:
	/* �ڵ� ���� */
	// �ڵ��� ����
	// �ڵ��� ������ ����
	// - IN �Ű�����
	//		Position handle: ������ ������ϴ� �ڵ�
	// - OUT �Ű�����
	//		PointF* handlePoint:
	//			�ּ� ��: �Ű������� Position�� �ڵ��� ��� �ڵ��� ����
	//			NULL: �Ű������� Position�� �ڵ��� �ƴ� ���
	// - ��ȯ �� (BOOL)
	//		TRUE: �Ű������� Position�� �ڵ��� ���
	//		FALSE: �Ű������� Position�� �ڵ��� �ƴ� ���
	BOOL getHandleRect(IN Position handle, OUT RectF* handleRect);

	// ��ü �ڵ� �׸���
	// - IN �Ű�����
	//		Position handle: �׸������ϴ� �ڵ�
	// - ��ȯ �� (BOOL)
	//		TRUE: �Ű������� Position�� �ڵ��� ���
	//		FALSE: �Ű������� Position�� �ڵ��� �ƴ� ���
	BOOL drawHandle(IN Position handle);
	
	

// Ư��
protected:
	Graphics* m_lpGraphics;					// ��� ��� Graphics
	RectF m_Area;							// ��ü ���� (�簢��) https://msdn.microsoft.com/en-us/library/6y4t32t5(v=vs.120).aspx
private:
	BOOL m_GraphicsDynamicAllocationFlag;	// m_lpGraphics��, ��ü ���ο��� �������� �Ҵ��ߴ��� ���θ� �����ϴ� �÷���
	const REAL HANDLESIZE = 10;				// �ڵ� ũ��
};



//	// LButtonDown
//	virtual void create(...);					// ��ü ����
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
//	virtual void move(PointF originPoint, PointF targetPoint);	// ��ü �̵�
//	virtual void resize(PointF point, PointF* anchorPoint = NULL, int resizeFlags = Free);	// ��ü ũ�� ����
//	
//	virtual operationModeFlags cursorPosition(RectF rect);		// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� ���� �ȿ� ������ ��� �ִ���)
//
//	// OnDraw / OnPaint
//	virtual void draw();										// ��ü �׸���
//	virtual void drawSelect();
//
//	// Menu Item
//	virtual void destroy();										// ��ü ����
//
//	virtual void setLineColor(const Color& lineColor);			// ������ �� ����
//	virtual void setLineWidth(const REAL& LineWidth);			// ������ �β� ����
//	virtual void setLinePattern(const DashStyle& LinePattern);	// ������ ���� ����
//	virtual void setFillColor(const Color& FillColor);			// ĥ�ϱ� �� ����
//	virtual void setFillPattern(const int fillPattern);			// ĥ�ϱ� ���� ����
//	// ���� �����Լ��� �����ϱ�
//
//	// Getter / Setter
//	Graphics* getGraphics();
//	void setGraphics(Graphics* lpGraphics);
//
//	PointF& getStartingPoint();
//	void setStartingPoint(PointF& StartingPoint);
//
//	operationModeFlags getOperationMode();
//	void setOperationMode(operationModeFlags OperationMode);
//
//protected:
//	virtual void resetArea();		// ��ü ���� ���� �缳�� (���� �� ȣ�������), �ܺο��� ȣ�� �Ұ�


// PointF m_StartingPoint;