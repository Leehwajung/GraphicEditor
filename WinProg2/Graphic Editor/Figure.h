// Figure.h : CFigure Ŭ������ �������̽�
// CFigure : Ŭ���̾�Ʈ �������� �� �� �ִ� ��ü�� �����ϴ� Ŭ���� (��� ��ü�� ���� Ŭ����)
// @Author Lee Hwajung

#pragma once

#include "afx.h"
#include <cstdarg>
//#include <gdiplus.h>
//#include <afxcoll.h>
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
		ONHANDLE		= (int) 0x00008,	// �ڵ� �� (�ڵ� ���� �������� ONHANDLE���� &�������� �˾Ƴ� �� ����)
		TOPLEFT			= (int) 0x00008,	// �»� �ڵ�
		TOP				= (int) 0x00009,	// ���� �ڵ�
		TOPRIGHT		= (int) 0x0000A,	// ��� �ڵ�
		RIGHT			= (int) 0x0000B,	// ���� �ڵ�
		BOTTOMRIGHT		= (int) 0x0000C,	// ���� �ڵ�
		BOTTOM			= (int) 0x0000D,	// ���� �ڵ�
		BOTTOMLEFT		= (int) 0x0000E,	// ���� �ڵ�
		LEFT			= (int) 0x0000F,	// ���� �ڵ�
		START			= (int) 0x00018,	// ���� �ڵ�
		END				= (int) 0x00019		// �� �ڵ�
	};

	enum CreateFlag {
		FREECREATE		= NULL,				// ���� ����
		REGULAR			= MK_SHIFT			// ���ٸ�ü �Ǵ� �����⼱ ����
	};

	enum MoveFlag {
		FREEMOVE		= NULL,				// ���� �̵�
		FOURWAY			= MK_SHIFT			// 4���� �̵� (�����¿�)
	};

	enum ResizeFlag {
		FREERESIZE		= NULL,				// ���� ũ�� ����
		PROPORTIONAL	= MK_SHIFT			// ���� ũ�� ����
	};



// ���� �� �Ҹ�
public:
	CFigure();
	//CFigure(IN CClientDC* lpClientDC);
	//CFigure(IN Graphics& graphics);
	DECLARE_SERIAL(CFigure)
	virtual ~CFigure();


// �۾�
public:
/** ����ȭ **/
	// ����ȭ (���������Լ��� �ٲ��� ����)
	virtual void Serialize(CArchive& ar);

/** ���� **/
	// ���� (�ڵ� ���� �Լ�)
	// �Ű������� ���� �������� ���ο� ��ü�� ����
	// - IN �Ű�����
	//		void* param1, ...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
	//		[CreateFlag createFlag = FREECREATE]: ���� ���� �÷���, �ʿ��ϸ� �߰��ϱ�
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL create(void* param1, ...);
	
	// �̵� (�ڵ� ���� �Լ�)
	// ���� ��ǥ���� �� ��ǥ������ Offset�� �������� ��ü�� �̵�
	// - IN �Ű�����
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵��� �� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	virtual void move(IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	
	// ũ�� ���� (�ڵ� ���� �Լ�)
	// ������ �ڵ��� ��ǥ�� �����Ͽ� ũ�� ���� (���� ��ǥ�� �����ϸ� �̸� �������� �� ��ǥ�� �����Ͽ� ũ�� ����)
	// - IN �Ű�����
	//		Position selectedHandle: ��ü�� ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� ������ ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
	virtual void resize(IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);
	
	// ��/��/���� ���� �Լ�
	virtual CFigure* clone();

	// ���� (�ڵ� ���� �Լ�)
	// ��ü�� �����ϰ� �޸𸮸� ����
	virtual void destroy();
	
	// ��ǥ ��ġ Ȯ�� (�ڵ� ���� �Լ�)
	// ���� ��ü �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
	// - IN �Ű�����
	//		PointF point: Ȯ���� ��ǥ
	// - ��ȯ �� (Position)
	//		Position: ��ü ���� ���� ��ġ
	virtual Position pointInFigure(IN PointF point);

	// ��ü ��ġ Ȯ��
	// ��ü�� �簢�� �ȿ� �ִ��� Ȯ���ϰ� �� ��ġ�� ��ȯ��
	// - IN �Ű�����
	//		RectF rect: Ȯ���� ��ǥ
	// - ��ȯ �� (BOOL)
	//		TRUE: ��ü�� �簢�� ���ο� ������ �� (������ ��� ���� �簢�� ���ο� ����)
	//		FALSE: ��ü�� �簢�� ���ο� �������� ���� ��
	BOOL figureInRect(IN RectF rect);


	/* ��ü ���� ���� */
	// ��ü ���� ���� (�ڵ� ���� �Լ�)
	virtual RectF resetArea();

	// ��ü ����
	// ��ü ������ ����
	RectF getArea();


	/* �ڵ� ���� */
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

protected:
	// �ڵ��� ����
	// �ڵ��� ������ ����
	// - IN �Ű�����
	//		PointF handlePoint: ������ ������ϴ� �ڵ��� ��ǥ
	// - ��ȯ �� (RectF)
	//		�ڵ��� ����
	RectF getHandleRect(IN PointF handlePoint);

	// �ڵ��� ����
	// �ڵ��� ������ ����
	// - IN �Ű�����
	//		Position handle: ������ ������ϴ� �ڵ�
	// - OUT �Ű�����
	//		PointF* handlePoint:
	//			�ּ� ��: �Ű������� Position�� �ڵ��� ��� �ڵ��� ����
	//			NULL: �Ű������� Position�� �ڵ��� �ƴ� ���
	// - ��ȯ �� (BOOL)
	//		TRUE: �Ű������� Position�� �ڵ��� �ƴ� ���
	//		FALSE: �Ű������� Position�� �ڵ��� ���
	/*virtual */BOOL getHandleRect(IN Position handle, OUT RectF* handleRect);

	// ���ݴ��� �ڵ�
	// ���ݴ��� �ڵ��� ����
	// - IN �Ű�����
	//		Position handle: ���ݴ��� �ڵ��� ������ϴ� �ڵ�
	// - ��ȯ �� (Position)
	//		���ݴ��� �ڵ�
	Position getOppositeHandle(IN Position handle);


/** �׸��� **/
public:
	// ��ü �׸��� (�ڵ� ���� �Լ�)
	virtual void draw(IN Graphics& graphics);

	// ���� �׸��� (�ڵ� ���� �Լ�)
	// ���� �ÿ� ������ �׸���
	// - IN �Ű�����
	//		Graphics& graphics: �׸��� ��� Graphics
	//		void* param1, ...: �� �Ļ� Ŭ�������� �ʿ��Ѵ�� ����
	//		[CreateFlag createFlag = FREECREATE]: ���� ���� �÷���, �ʿ��ϸ� �߰��ϱ�
	virtual RectF creating(IN Graphics& graphics, void* param1, ...);

	// �̵� �׸��� (�ڵ� ���� �Լ�)
	// �̵� �߿� ������ �׸���
	// - IN �Ű�����
	//		Graphics& graphics: �׸��� ��� Graphics
	//		PointF originPoint: �̵��� ���� ��ǥ
	//		PointF targetPoint: �̵� ���� ��ǥ
	//		MoveFlag moveFlag = FREEMOVE: �̵� ���� �÷���
	virtual RectF moving(IN Graphics& graphics, IN PointF originPoint, IN PointF targetPoint, IN MoveFlag moveFlag = FREEMOVE);
	
	// ũ�� ���� �׸��� (�ڵ� ���� �Լ�)
	// ũ�� ���� �߿� ������ �׸���
	// - IN �Ű�����
	//		Graphics& graphics: �׸��� ��� Graphics
	//		Position selectedHandle: ��ü�� ���õ� �ڵ�
	//		PointF targetPoint: ���õ� �ڵ��� �̵��ϰ� �ִ� ��ǥ
	//		ResizeFlag resizeFlag = FREERESIZE: ũ�� ���� ���� �÷���
	//		PointF* anchorPoint = NULL: ũ�� ������ ����(����) ��ǥ (NULL�� ���, selectedHandle�� ���� ���� Default ���� ��ǥ )
	virtual RectF resizing(IN Graphics& graphics, IN Position selectedHandle, IN PointF targetPoint, IN ResizeFlag resizeFlag = FREERESIZE, IN PointF* anchorPoint = NULL);

	// ��ü ���� �׸���
	// - IN �Ű�����
	//		Graphics& graphics: �׸��� ��� Graphics
	void drawArea(IN Graphics& graphics);

protected:
	// ��ü �ڵ� �׸���
	// - IN �Ű�����
	//		Graphics& graphics: �׸��� ��� Graphics
	//		PointF handlePoint: �׸������ϴ� �ڵ� ��ǥ
	// - ��ȯ �� (BOOL)
	//		TRUE: �Ű������� Position�� �ڵ��� �ƴ� ���
	//		FALSE: �Ű������� Position�� �ڵ��� ���
	BOOL drawHandle(IN Graphics& graphics, IN PointF handlePoint);

	// ��ü �ڵ� �׸���
	// - IN �Ű�����
	//		Graphics& graphics: �׸��� ��� Graphics
	//		Position handle: �׸������ϴ� �ڵ�
	// - ��ȯ �� (BOOL)
	//		TRUE: �Ű������� Position�� �ڵ��� �ƴ� ���
	//		FALSE: �Ű������� Position�� �ڵ��� ���
	BOOL drawHandle(IN Graphics& graphics, IN Position handle);

	// ��ü �ڵ� ��ü �׸���
	// - IN �Ű�����
	//		Graphics& graphics: �׸��� ��� Graphics
	//		PointF* handlePoints: �ڵ��� ��ǥ �迭
	//		count: �迭�� ũ��
	void drawHandles(IN Graphics& graphics, IN PointF* handlePoints, IN INT count);

	// ��ü �ڵ� ��ü �׸���
	// - IN �Ű�����
	//		Graphics& graphics: �׸��� ��� Graphics
	void drawHandles(IN Graphics& graphics);


/** �Ӽ� ���� **/
public:
	// ä��� �귯�� ����
	virtual void setFillBrush(IN const Brush* brush, IN BOOL PropertyMaintenanceFlag = FALSE);

	// ������ �� ���� (�ڵ� ���� �Լ�)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setOutlineColor(IN const Color& outlineColor);

	// ������ �β� ���� (�ڵ� ���� �Լ�)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setOutlineWidth(IN const REAL outlineWidth);

	// ������ ���� ���� (�ڵ� ���� �Լ�)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setOutlinePattern(IN const DashStyle outlinePattern);

	// �� ä��� �� ���� (�ڵ� ���� �Լ�)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setFillColor(IN const Color& fillColor);

	// ���� ä��� �� ���� (�ڵ� ���� �Լ�)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setFillSubcolor(IN const Color& fillSubcolor);

	// ä��� ���� ���� (�ڵ� ���� �Լ�)
	// - ��ȯ �� (BOOL)
	//		TRUE: ���� ����
	//		FALSE: ���� ����
	virtual BOOL setFillPattern(IN const HatchStyle fillPattern);

	UINT getID() { return ID; }

// Ư��
protected:
	RectF m_Area;							// ��ü ���� (�簢��)
	const REAL HANDLESIZE = 10;				// �ڵ� ũ��
private:
	UINT ID;				// ��ü ���� ID
	static UINT IDcount;	// ID �Ҵ��� ���� ���� ����

};

typedef Pen*		PenPtr;
typedef Brush*		BrushPtr;
typedef CFigure*	CFigurePtr;

//	// LButtonDown
//	virtual void create(void* param1, ...);					// ��ü ����
//	virtual operationModeFlags cursorPosition(PointF point);	// Ŀ�� ��ġ ã�� (Ŀ���� ���� ���� �ִ���, ������ �� ���� �ִ���)
//
//
//	// OnMouseMove
//	void mouseMoveOperation(UINT nFlags, PointF point);			// OnMouseMove���� ����� �Լ� (���� / �̵� / ũ�� ���� �Ǵ�)
//	virtual RectF creating(UINT nFlags, PointF point);			// ���� �׸���
//	virtual RectF moving(UINT nFlags, PointF point);				// �̵� �׸���
//	virtual RectF resizing(UINT nFlags, PointF point);			// ũ�� ���� �׸���
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
//	virtual BOOL setLineColor(const Color& lineColor);			// ������ �� ����
//	virtual BOOL setLineWidth(const REAL& LineWidth);			// ������ �β� ����
//	virtual BOOL setLinePattern(const DashStyle& LinePattern);	// ������ ���� ����
//	virtual BOOL setFillColor(const Color& FillColor);			// �� ä��� �� ����
//	virtual BOOL setFillPattern(const int fillPattern);			// ä��� ���� ����
//	// ���� �����Լ��� �����ϱ�
//
//	// Getter / Setter
//	Graphics& getGraphics();
//	void setGraphics(Graphics& graphics);
//
//	PointF& getStartingPoint();
//	void setStartingPoint(PointF& StartingPoint);
//
//	operationModeFlags getOperationMode();
//	void setOperationMode(operationModeFlags OperationMode);
//
//protected:
//	virtual RectF resetArea();		// ��ü ���� ���� �缳�� (���� �� ȣ�������), �ܺο��� ȣ�� �Ұ�


// PointF m_StartingPoint;