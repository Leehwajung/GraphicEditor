// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Graphic Editor View.h : CGraphicEditorView 클래스의 인터페이스
//

#pragma once
#include "Group.h"
#include "Line.h"
#include "Global.h"

class CGraphicEditorView : public CView
{
protected: // serialization에서만 만들어집니다.
	CGraphicEditorView();
	DECLARE_DYNCREATE(CGraphicEditorView)

// 특성입니다.
public:
	CGraphicEditorDoc* GetDocument() const;
	CGroup m_SelectedFiguresList;				// 사용자가 선택한 개체들의 목록
	CFigurePtrList m_CurrentFigures;			// 현재 선택한 개체 리스트
	//CFigure* m_CurrentFigure;					// 현재 선택학 개체
	//CRect m_DrawnArea;

	PointF m_CurrPoint;							// 현재 마우스의 좌표
	PointF m_LButtonPoint;						// 마우스 왼쪽 버튼 이벤트가 마지막으로 발생한 좌표 (Down, UP, DblClk 시에 저장)
	PointF m_RButtonPoint;						// 마우스 오른쪽 버튼 이벤트가 마지막으로 발생한 좌표 (Down, UP, DblClk 시에 저장)
	
	UINT m_MouseVKFlags;						// 마우스 가상키 조합 플래그 (MK_CONTROL / MK_LBUTTON / MK_MBUTTON / MK_RBUTTON / MK_SHIFT) (Indicates whether various virtual keys are down.)

	enum MouseButtonFlag {
		NBUTTON = NULL,							// 마우스 버튼이 눌리지 않은 상태
		LBUTTON = MK_LBUTTON,					// 좌클릭 상태
		RBUTTON = MK_RBUTTON,					// 우클릭 상태
		MBUTTON = MK_MBUTTON					// 가운데 클릭 상태
	};
	MouseButtonFlag m_MouseButtonFlag;			// 마우스 버튼이 클릭되어있는 상태 플래그
	
	enum InsertFlag {
		NONE			= NULL,					// 삽입 패널 버튼이 눌리지 않은 상태
		LINE			= ID_INSERT_LINE,		// 직선 버튼
		POLYLINE		= ID_INSERT_POLYLINE,	// 꺽인 선 버튼
		PENCIL			= ID_INSERT_PENCIL,		// 펜 버튼
		CURVE			= ID_INSERT_CURVE,		// 곡선 버튼
		ELLIPSE			= ID_INSERT_ELLIPSE,	// 타원 버튼
		RECTANGLE		= ID_INSERT_RECTANGLE,	// 사각형 버튼
		STRING			= ID_INSERT_STRING,		// 문자열 버튼
		POLYGON			= ID_INSERT_POLYGON,	// 삼각형 버튼
		CLOSEDCURVE		= ID_INSERT_CLOSEDCURVE	// 도형 버튼
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

	BOOL m_PolyCreatableFlag;	// CPolyLine 및 CPolygon 객체 생성 가능 상태 플래그

	//int m_mode;
	
	//CClientDC* m_pDC;
	//Graphics& m_pGraphics;

	// 더블 버퍼링을 위한 변수들
	//CDC* m_psMemDC;
	//CBitmap* m_psBitmap;
	//CBitmap* m_psOldBitmap;

// 작업입니다.
public:
	void preInsert();		// 삽입(생성) 작업 전에 해야 할 작업
	void postInsert();		// 삽입(생성) 작업 후에 해야 할 작업
	void cancelInsert();	// 삽입(생성) 작업 취소 시에 해야 할 작업
	void clearInsertFlag();
	OperationModeFlag getOperationModeFlag();
	void setOperationModeFlag(OperationModeFlag operationModeFlag = SELECTABLE);
	
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);		// 이 뷰를 그리기 위해 재정의되었습니다.
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CGraphicEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	// 메시지 처리기
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

	// 명령 처리기
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
};

#ifndef _DEBUG  // Graphic Editor View.cpp의 디버그 버전
inline CGraphicEditorDoc* CGraphicEditorView::GetDocument() const
   { return reinterpret_cast<CGraphicEditorDoc*>(m_pDocument); }
#endif

