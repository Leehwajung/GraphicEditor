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

// Graphic Editor View.cpp : CGraphicEditorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Graphic Editor.h"
#endif

#include "Graphic Editor Doc.h"
#include "Graphic Editor View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Text.h"

// CGraphicEditorView

IMPLEMENT_DYNCREATE(CGraphicEditorView, CView)

BEGIN_MESSAGE_MAP(CGraphicEditorView, CView)
	/* �޽��� ó���� */
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSKEYUP()
	ON_WM_CONTEXTMENU()

	/* ��� ó���� */
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicEditorView::OnFilePrintPreview)

	//ON_COMMAND(ID_EDIT_COPY, &CGraphicEditorView::OnEditClear)
	//ON_COMMAND(ID_EDIT_COPY, &CGraphicEditorView::OnEditClearAll)
	ON_COMMAND(ID_EDIT_COPY, &CGraphicEditorView::OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, &CGraphicEditorView::OnEditCut)
	//ON_COMMAND(ID_EDIT_PASTE, &CGraphicEditorView::OnEditFind)
	ON_COMMAND(ID_EDIT_PASTE, &CGraphicEditorView::OnEditPaste)
	ON_COMMAND(ID_EDIT_DELETE, &CGraphicEditorView::OnEditDelete)
	//ON_COMMAND(ID_EDIT_DELETE, &CGraphicEditorView::OnEditRepeat)
	//ON_COMMAND(ID_EDIT_DELETE, &CGraphicEditorView::OnEditReplace)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CGraphicEditorView::OnEditSelectAll)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CGraphicEditorView::OnEditUndo)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CGraphicEditorView::OnEditRedo)
	ON_COMMAND(ID_IMAGE_CANVAS_SIZE, &CGraphicEditorView::OnImageCanvasSize)
	ON_COMMAND(ID_INSERT_LINE, &CGraphicEditorView::OnInsertLine)
	ON_UPDATE_COMMAND_UI(ID_INSERT_LINE, &CGraphicEditorView::OnUpdateInsertLine)
	ON_COMMAND(ID_INSERT_POLYLINE, &CGraphicEditorView::OnInsertPolyline)
	ON_UPDATE_COMMAND_UI(ID_INSERT_POLYLINE, &CGraphicEditorView::OnUpdateInsertPolyline)
	ON_COMMAND(ID_INSERT_PENCIL, &CGraphicEditorView::OnInsertPencil)
	ON_UPDATE_COMMAND_UI(ID_INSERT_PENCIL, &CGraphicEditorView::OnUpdateInsertPencil)
	ON_COMMAND(ID_INSERT_CURVE, &CGraphicEditorView::OnInsertCurve)
	ON_UPDATE_COMMAND_UI(ID_INSERT_CURVE, &CGraphicEditorView::OnUpdateInsertCurve)
	ON_COMMAND(ID_INSERT_ELLIPSE, &CGraphicEditorView::OnInsertEllipse)
	ON_UPDATE_COMMAND_UI(ID_INSERT_ELLIPSE, &CGraphicEditorView::OnUpdateInsertEllipse)
	ON_COMMAND(ID_INSERT_RECTANGLE, &CGraphicEditorView::OnInsertRectangle)
	ON_UPDATE_COMMAND_UI(ID_INSERT_RECTANGLE, &CGraphicEditorView::OnUpdateInsertRectangle)
	ON_COMMAND(ID_INSERT_STRING, &CGraphicEditorView::OnInsertString)
	ON_UPDATE_COMMAND_UI(ID_INSERT_STRING, &CGraphicEditorView::OnUpdateInsertString)
	ON_COMMAND(ID_INSERT_POLYGON, &CGraphicEditorView::OnInsertPolygon)
	ON_UPDATE_COMMAND_UI(ID_INSERT_POLYGON, &CGraphicEditorView::OnUpdateInsertPolygon)
	ON_COMMAND(ID_INSERT_CLOSEDCURVE, &CGraphicEditorView::OnInsertClosedcurve)
	ON_UPDATE_COMMAND_UI(ID_INSERT_CLOSEDCURVE, &CGraphicEditorView::OnUpdateInsertClosedcurve)
	ON_COMMAND(ID_ARRANGE_ORDER, &CGraphicEditorView::OnArrangeOrder)
	ON_COMMAND(ID_ARRANGE_BRING_FRONT, &CGraphicEditorView::OnArrangeBringFront)
	ON_COMMAND(ID_ARRANGE_SEND_BACK, &CGraphicEditorView::OnArrangeSendBack)
	ON_COMMAND(ID_ARRANGE_BRING_FORWARD, &CGraphicEditorView::OnArrangeBringForward)
	ON_COMMAND(ID_ARRANGE_SEND_BACKWARD, &CGraphicEditorView::OnArrangeSendBackward)
	ON_COMMAND(ID_ARRANGE_GROUPING, &CGraphicEditorView::OnArrangeGrouping)
	ON_COMMAND(ID_ARRANGE_GROUP, &CGraphicEditorView::OnArrangeGroup)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_GROUP, &CGraphicEditorView::OnUpdateArrangeGroup)
	ON_COMMAND(ID_ARRANGE_UNGROUP, &CGraphicEditorView::OnArrangeUngroup)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_UNGROUP, &CGraphicEditorView::OnUpdateArrangeUngroup)
	ON_COMMAND(ID_ZOOM_IN, &CGraphicEditorView::OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, &CGraphicEditorView::OnZoomOut)
	ON_COMMAND(ID_ZOOM_100, &CGraphicEditorView::OnZoom100)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_100, &CGraphicEditorView::OnUpdateZoom100)
END_MESSAGE_MAP()


// CGraphicEditorView ����/�Ҹ�

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_MouseButtonFlag = NULL;
	m_InsertFlag = NONE;
}

CGraphicEditorView::~CGraphicEditorView()
{
}

BOOL CGraphicEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}


// CGraphicEditorView �׸���

void CGraphicEditorView::OnDraw(CDC* pDC)
{
	// GDI+			https://msdn.microsoft.com/en-us/library/windows/desktop/ms533798(v=vs.85).aspx
	// GDI+ Ref.	https://msdn.microsoft.com/en-us/library/windows/desktop/ms533799(v=vs.85).aspx
	// GDI+ Classes	https://msdn.microsoft.com/en-us/library/windows/desktop/ms533958(v=vs.85).aspx

	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	Graphics graphics(*pDC);	// gdi+ �׸��⸦ ���� ��ü https://msdn.microsoft.com/en-us/library/windows/desktop/ms534453(v=vs.85).aspx

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	if (m_InsertFlag == LINE)
		currentFigure->draw();

	/*int */m_mode = 0;// �ϴ� ����� �س�����. // �ϴ� ������ ������ ���� �� �����ص�.
	switch(m_mode){
		case 1: // ��������
			break;
		case 2: // ����
			break;
		case 3 :// �ؽ�Ʈ
		
			break;
	// view ��ü �Ѱܼ�? �޾Ƽ� ���� �Լ����� �� ó���ϴ� ������� ���ڴ� ����??
	// Graphics �����͸� ��� ����(m_lpGraphics)�� �ּ� �� ��ü Ŭ�������� �׸��⸦ �����ϰ�, �� �Լ��� ȣ���ϴ� ������� �Ұž�

	}
	
	// GDI+ ���� �ڵ� (�簢�� �׸���)
	SolidBrush sb(Color(255,255,0,0));
	graphics.FillRectangle(&sb, Rect(33, 44, 55, 66));

	// Set up the arc.
	Pen redPen(Color(255, 255, 0, 0), 3);
	RectF ellipseRect(0, 0, 200, 100);
	REAL startAngle = 0.0f;
	REAL sweepAngle = 90.0f;

	// Draw the arc.
	graphics.DrawArc(&redPen, ellipseRect, startAngle, sweepAngle);

}


// CGraphicEditorView �޽��� ó����

void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {
		/***** �� �κ��� �������� ���ÿ�. *****/
		m_LButtonPoint = point;			// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = MK_LBUTTON;	// ��Ŭ�� �巡�� ��
		/**************************************/

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		if (m_InsertFlag == LINE){
			currentFigure->create(CGlobal::getPointF(m_LButtonPoint));
		}

		CView::OnLButtonDown(nFlags, point);

		CGraphicEditorDoc* pDoc = GetDocument();
	}
}

void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_MouseButtonFlag == MK_LBUTTON/* && !(nFlags & MK_RBUTTON)*/) {
		/***** �� �κ��� �������� ���ÿ�. *****/
		m_LButtonPoint = point;		// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = NULL;	// ��Ŭ�� ����
		/**************************************/

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
		if (m_InsertFlag == LINE){
			currentFigure->endCreate(CGlobal::getPointF(m_LButtonPoint));
			m_InsertFlag = NONE;
			Invalidate();
		}


		CView::OnLButtonUp(nFlags, point);
	}
}

void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {
		/***** �� �κ��� �������� ���ÿ�. *****/
		m_LButtonPoint = point;			// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = MK_LBUTTON;	// ��Ŭ��
		/**************************************/

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

		CView::OnLButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {
		/***** �� �κ��� �������� ���ÿ�. *****/
		m_RButtonPoint = point;			// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = MK_RBUTTON;	// ��Ŭ�� �巡�� ��
		/**************************************/

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

		CView::OnRButtonDown(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_MouseButtonFlag == MK_RBUTTON/* && !(nFlags & MK_LBUTTON)*/) {
		/***** �� �κ��� �������� ���ÿ�. *****/
		m_RButtonPoint = point;		// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = NULL;	// ��Ŭ�� ����
		/**************************************/

		ClientToScreen(&point);
		OnContextMenu(this, point);
	}
}

void CGraphicEditorView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {
		/***** �� �κ��� �������� ���ÿ�. *****/
		m_RButtonPoint = point;			// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = MK_RBUTTON;	// ��Ŭ��
		/**************************************/

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

		CView::OnRButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//CView::OnMouseMove(nFlags, point);

	if (!m_MouseButtonFlag) {		// ��Ŭ�� ���� ���콺 ������
	
	}

	else if (m_MouseButtonFlag == MK_LBUTTON) {		// ���콺 ���� ��ư �巡��
		if (nFlags & MK_CONTROL) {		// Ctrl ������ �巡��

		}
		else if (nFlags & MK_SHIFT) {	// Shift ������ �巡��

		}
		else {							// ����Ű ������ �ʰ� �帮��
			if (m_InsertFlag == LINE){
			currentFigure->creating(nFlags, CGlobal::getPointF(point));
			Invalidate();
			}
		}
	}

	else if (m_MouseButtonFlag == MK_RBUTTON){	// ���콺 ������ ��ư �巡��
		if (nFlags & MK_CONTROL) {		// Ctrl ������ �巡��

		}
		else if (nFlags & MK_SHIFT) {	// Shift ������ �巡��

		}
		else {							// ����Ű ������ �ʰ� �帮��

		}
	}
}

BOOL CGraphicEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CView::OnMouseWheel(nFlags, zDelta, point);
}

void CGraphicEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (nChar)
	{
	case VK_ESCAPE:
	case VK_CANCEL:
	case VK_BACK:
		clearInsertFlag();
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphicEditorView ����

#ifdef _DEBUG
void CGraphicEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicEditorDoc* CGraphicEditorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicEditorView �μ�

void CGraphicEditorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CGraphicEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CGraphicEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CGraphicEditorView ��� ó����

//void CGraphicEditorView::OnEditClear()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

//void CGraphicEditorView::OnEditClearAll()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

void CGraphicEditorView::OnEditCopy()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnEditCut()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

//void CGraphicEditorView::OnEditFind()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

void CGraphicEditorView::OnEditPaste()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnEditDelete()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

//void CGraphicEditorView::OnEditRepeat()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

//void CGraphicEditorView::OnEditReplace()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

void CGraphicEditorView::OnEditSelectAll()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnEditUndo()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnEditRedo()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnImageCanvasSize()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertLine()
{
	m_InsertFlag = LINE;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	// �׽�Ʈ�Դϴ�!!
}

void CGraphicEditorView::OnUpdateInsertLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == LINE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPolyline()
{
	m_InsertFlag = POLYLINE;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPolyline(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == POLYLINE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPencil()
{
	m_InsertFlag = PENCIL;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPencil(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == PENCIL);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertCurve()
{
	m_InsertFlag = CURVE;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertCurve(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == CURVE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertEllipse()
{
	m_InsertFlag = ELLIPSE;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertEllipse(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == ELLIPSE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertRectangle()
{
	m_InsertFlag = RECTANGLE;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == RECTANGLE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertString()
{
	m_InsertFlag = STRING;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertString(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == STRING);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPolygon()	// �ﰢ�� ��ư
{
	m_InsertFlag = POLYGON;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPolygon(CCmdUI *pCmdUI)	// �ﰢ�� ��ư
{
	pCmdUI->SetCheck(m_InsertFlag == POLYGON);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertClosedcurve()	// ���� ��ư
{
	m_InsertFlag = CLOSEDCURVE;	// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertClosedcurve(CCmdUI *pCmdUI)	// ���� ��ư
{
	pCmdUI->SetCheck(m_InsertFlag == CLOSEDCURVE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeOrder()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeBringFront()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeSendBack()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeBringForward()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeSendBackward()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeGrouping()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeGroup()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateArrangeGroup(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeUngroup()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateArrangeUngroup(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnZoomIn()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnZoomOut()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnZoom100()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateZoom100(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


// CGraphicEditorView �۾�

void CGraphicEditorView::clearInsertFlag()
{
	m_InsertFlag = NONE;
}



// CGraphicEditorView �߰��� ������ ���, �޽��� ó���� �� ������


