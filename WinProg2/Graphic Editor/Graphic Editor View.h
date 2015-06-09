// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Graphic Editor View.h : CGraphicEditorView Ŭ������ �������̽�
//

#pragma once
#include "Group.h"
#include "Line.h"
#include "Global.h"
#include "SelectedFigureArray.h"

class CGraphicEditorView : public CView
{
protected: // serialization������ ��������ϴ�.
	CGraphicEditorView();
	DECLARE_DYNCREATE(CGraphicEditorView)

// Ư���Դϴ�.
public:
	CGraphicEditorDoc* GetDocument() const;
	//CGroup m_SelectedFiguresList;				// ����ڰ� ������ ��ü���� ���
	//CFigurePtrList m_CurrentFigures;			// ���� ������ ��ü ����Ʈ
	CSelectedFigureArray m_SelectedFigures;		// ���� ������ ��ü �迭
	CFigurePtrList m_BufferList; //������ ��ü�� ������ ���۸���Ʈ
	CFigure* m_CreateBuffer;
	//CFigure* m_CurrentFigure;					// ���� ������ ��ü

	PointF m_CurrPoint;							// ���� ���콺�� ��ǥ
	PointF m_LButtonPoint;						// ���콺 ���� ��ư �̺�Ʈ�� ���������� �߻��� ��ǥ (Down, UP, DblClk �ÿ� ����)
	PointF m_RButtonPoint;						// ���콺 ������ ��ư �̺�Ʈ�� ���������� �߻��� ��ǥ (Down, UP, DblClk �ÿ� ����)
	
	UINT m_MouseVKFlags;						// ���콺 ����Ű ���� �÷��� (MK_CONTROL / MK_LBUTTON / MK_MBUTTON / MK_RBUTTON / MK_SHIFT) (Indicates whether various virtual keys are down.)

	enum MouseButtonFlag {
		NBUTTON = NULL,							// ���콺 ��ư�� ������ ���� ����
		LBUTTON = MK_LBUTTON,					// ��Ŭ�� ����
		RBUTTON = MK_RBUTTON,					// ��Ŭ�� ����
		MBUTTON = MK_MBUTTON					// ��� Ŭ�� ����
	};
	MouseButtonFlag m_MouseButtonFlag;			// ���콺 ��ư�� Ŭ���Ǿ��ִ� ���� �÷���
	
	enum InsertFlag {
		NONE			= NULL,					// ���� �г� ��ư�� ������ ���� ����
		LINE			= ID_INSERT_LINE,		// ���� ��ư
		POLYLINE		= ID_INSERT_POLYLINE,	// ���� �� ��ư
		PENCIL			= ID_INSERT_PENCIL,		// �� ��ư
		CURVE			= ID_INSERT_CURVE,		// � ��ư
		ELLIPSE			= ID_INSERT_ELLIPSE,	// Ÿ�� ��ư
		RECTANGLE		= ID_INSERT_RECTANGLE,	// �簢�� ��ư
		STRING			= ID_INSERT_STRING,		// ���ڿ� ��ư
		POLYGON			= ID_INSERT_POLYGON,	// �ﰢ�� ��ư
		CLOSEDCURVE		= ID_INSERT_CLOSEDCURVE	// ���� ��ư
	};
	InsertFlag m_InsertFlag;

	enum OperationModeFlag {
		SELECTABLE		= (int) 0x00000,
		SELECTED		= (int) 0x00001,
		CREATE			= (int) 0x00002,
		MOVE			= (int) 0x00003,
		RESIZE			= (int) 0x00004,
		//WRITE			= (int) 0x00005
	};
	//OperationModeFlag m_OperationModeFlag;

	CFigure::Position m_selectedPosition;

	BOOL m_PolyCreatableFlag;	// CPolyLine �� CPolygon ��ü ���� ���� ���� �÷���
	BOOL m_EditPointFlag;

	//int m_mode;
	
	//CClientDC* m_pDC;
	//Graphics& m_pGraphics;

	// ���� ���۸��� ���� ������
	//CDC* m_psMemDC;
	//CBitmap* m_psBitmap;
	//CBitmap* m_psOldBitmap;

// �۾��Դϴ�.
public:
	void preInsert();		// ����(����) �۾� ���� �ؾ� �� �۾�
	void postInsert();		// ����(����) �۾� �Ŀ� �ؾ� �� �۾�
	void cancelInsert();	// ����(����) �۾� ��� �ÿ� �ؾ� �� �۾�
	void clearInsertFlag();
	OperationModeFlag getOperationModeFlag();
	void setOperationModeFlag(OperationModeFlag operationModeFlag = SELECTABLE);
	
// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);		// �� �並 �׸��� ���� �����ǵǾ����ϴ�.
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CGraphicEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	// �޽��� ó����
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	// ��� ó����
	afx_msg void OnFilePrintPreview();
	//afx_msg void OnEditClear();
	//afx_msg void OnEditClearAll();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	//afx_msg void OnEditFind();
	afx_msg void OnEditPaste();
	afx_msg void OnEditDelete();
	//afx_msg void OnEditRepeat();
	//afx_msg void OnEditReplace();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnImageCanvasSize();
	afx_msg void OnInsertLine();
	afx_msg void OnUpdateInsertLine(CCmdUI *pCmdUI);
	afx_msg void OnInsertPolyline();
	afx_msg void OnUpdateInsertPolyline(CCmdUI *pCmdUI);
	afx_msg void OnInsertPencil();
	afx_msg void OnUpdateInsertPencil(CCmdUI *pCmdUI);
	afx_msg void OnInsertCurve();
	afx_msg void OnUpdateInsertCurve(CCmdUI *pCmdUI);
	afx_msg void OnInsertEllipse();
	afx_msg void OnUpdateInsertEllipse(CCmdUI *pCmdUI);
	afx_msg void OnInsertRectangle();
	afx_msg void OnUpdateInsertRectangle(CCmdUI *pCmdUI);
	afx_msg void OnInsertString();
	afx_msg void OnUpdateInsertString(CCmdUI *pCmdUI);
	afx_msg void OnInsertPolygon();
	afx_msg void OnUpdateInsertPolygon(CCmdUI *pCmdUI);
	afx_msg void OnInsertClosedcurve();
	afx_msg void OnUpdateInsertClosedcurve(CCmdUI *pCmdUI);
	afx_msg void OnArrangeOrder();
	afx_msg void OnArrangeBringFront();
	afx_msg void OnArrangeSendBack();
	afx_msg void OnArrangeBringForward();
	afx_msg void OnArrangeSendBackward();
	afx_msg void OnArrangeGrouping();
	afx_msg void OnArrangeGroup();
	afx_msg void OnUpdateArrangeGroup(CCmdUI *pCmdUI);
	afx_msg void OnArrangeUngroup();
	afx_msg void OnUpdateArrangeUngroup(CCmdUI *pCmdUI);
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnZoom100();
	afx_msg void OnUpdateZoom100(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPolylineIndividualDelete();
	afx_msg void OnPolylineIndividualInsert();
	afx_msg void OnPointmove();
};

#ifndef _DEBUG  // Graphic Editor View.cpp�� ����� ����
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

