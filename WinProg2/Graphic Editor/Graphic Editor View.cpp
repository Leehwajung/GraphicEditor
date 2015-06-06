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

// Graphic Editor View.cpp : CGraphicEditorView Ŭ������ ���� (�۾�, ������, (��� �޽��� �̿���) �޽��� ó����)
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
//#include "Text.h"

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
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSCHAR()
	ON_WM_SYSKEYUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CONTEXTMENU()

	/* ��� �޽��� ó���� */
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


/*** CGraphicEditorView ����/�Ҹ� ***/

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	//m_CurrentFigure = NULL;
	m_MouseVKFlags = 0;
	m_MouseButtonFlag = NBUTTON;
	m_InsertFlag = NONE;
	//// m_OperationModeFlag = SELECTABLE;
}

CGraphicEditorView::~CGraphicEditorView()
{
}


/*** CGraphicEditorView ���� �Լ� ***/

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

	// ������� ������ ��� ��ü�� �׸�
	if (!pDoc->m_FiguresList.IsEmpty()) {
		pDoc->m_FiguresList.draw(&graphics);
	}


	if (!m_MouseButtonFlag) {		// ��Ŭ�� ���� ���콺 ������

	}

	else if (m_MouseButtonFlag == LBUTTON) {		// ���콺 ���� ��ư �巡��
		if (m_MouseVKFlags & MK_CONTROL) {		// Ctrl ������ �巡��

		}
		else if (m_MouseVKFlags & MK_SHIFT) {	// Shift ������ �巡��

		}
		else {							// ����Ű ������ �ʰ� �巡��
			if (m_InsertFlag == LINE){
				if (getOperationModeFlag() == CREATE)
					/*m_DrawnArea = CGlobal::RectFToCRect(*/m_CurrentFigures.GetHead()->creating(&graphics, &m_LButtonPoint, &m_CurrPoint);

			}
			else if (m_CurrentFigures.GetHead()->IsKindOf(RUNTIME_CLASS(CLine))){
				if (getOperationModeFlag() == MOVE){
					m_CurrentFigures.moving(&graphics, m_LButtonPoint, m_CurrPoint);
				}

				else if (getOperationModeFlag() == RESIZE){
					((CLine*)m_CurrentFigures.GetHead())->pointMoving(&graphics, m_LButtonPoint, m_CurrPoint);
				}
			}
			else if (m_CurrentFigures.GetHead()->IsKindOf(RUNTIME_CLASS(CPolyLine))){
				if (getOperationModeFlag() == MOVE){
					m_CurrentFigure->moving(&graphics, m_LButtonPoint, m_CurrPoint);
				}

				else if (getOperationModeFlag() == RESIZE){
					((CPolyLine*)m_CurrentFigure)->pointMoving(&graphics, m_LButtonPoint, m_CurrPoint);
				}
			}
		}
	}

	else if (m_MouseButtonFlag == RBUTTON){	// ���콺 ������ ��ư �巡��
		if (m_MouseVKFlags & MK_CONTROL) {		// Ctrl ������ �巡��

		}
		else if (m_MouseVKFlags & MK_SHIFT) {	// Shift ������ �巡��

		}
		else {							// ����Ű ������ �ʰ� �巡��

		}
	}
	

	//////////////////////////////////////////////////////////////////////////
	///*int */m_mode = 0;// �ϴ� ����� �س�����. // �ϴ� ������ ������ ���� �� �����ص�.
	//switch(m_mode){
	//	case 1: // ��������
	//		break;
	//	case 2: // ����
	//		break;
	//	case 3 :// �ؽ�Ʈ
	//	
	//		break;
	// view ��ü �Ѱܼ�? �޾Ƽ� ���� �Լ����� �� ó���ϴ� ������� ���ڴ� ����??
	// Graphics �����͸� ��� ����(m_lpGraphics)�� �ּ� �� ��ü Ŭ�������� �׸��⸦ �����ϰ�, �� �Լ��� ȣ���ϴ� ������� �Ұž�
	//
	//}
	//////////////////////////////////////////////// ���⼭���� ���� �ڵ� ///////////////////////////////////////////////////////
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

	// ���ڿ� ��� �׽�Ʈ
	// Create a string.
	WCHAR string[] = L"Sample Text";

	// Initialize arguments.
	FontFamily fontfamily(L"Arial");
	Gdiplus::Font myFont(&fontfamily, 16, FontStyleRegular, UnitPixel);
	RectF layoutRect(100.0f, 0.0f, 200.0f, 50.0f);
	StringFormat format;
	SolidBrush blackBrush(Color(255, 255, 0, 0));

	// Draw string.
	graphics.DrawString(
		string,
		11,
		&myFont,
		layoutRect,
		&format,
		&blackBrush);

	// Draw layoutRect.
	graphics.DrawRectangle(&Pen(Color::Blue, 3), layoutRect);
	///////////////////////////////// ������� ���� �ڵ� ///////////////////////////////////////////////////////////////
}


/*** CGraphicEditorView �޽��� ó���� ***/

void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

		
		Pen dd(Color(255, 0, 0));			// �׽�Ʈ�� ��
		SolidBrush ff(Color::DarkGreen);	// �׽�Ʈ�� �귯��


		switch (m_InsertFlag)
		{
		// �� ���� ����
		case CGraphicEditorView::NONE: {

			if (getOperationModeFlag() == SELECTED) {	// ��ü�� ���õ� ���
				m_selectedPosition = m_CurrentFigure->pointInFigure(m_CurrPoint);
				if (m_selectedPosition == CFigure::OUTSIDE) {
					m_CurrentFigure = NULL;
				}
				else if (m_selectedPosition == CFigure::START || m_selectedPosition == CFigure::END || m_selectedPosition == CFigure::ONHANDLE){
					// m_OperationModeFlag = RESIZE;
			}
				else if (m_selectedPosition == CFigure::INSIDE){
					// m_OperationModeFlag = MOVE;
				}

			}
			else {					// ��ü�� ���õ��� ���� ���
				// m_OperationModeFlag = SELECTABLE;
				// ��ü ��ü ����Ʈ(�׷�)�� ������ ��ȸ
				// ���� ���� ���� (OUTSIDE/INSIDE �� ���� �����θ� m_selectedPosition ����)
				// Invalidate ȣ�� (���� ������ �׸��� ����)
			}
			break;
		}
		case CGraphicEditorView::LINE:
			m_CurrentFigure = new CLine(&dd);
			//// m_OperationModeFlag = CREATE;
			break;
		case CGraphicEditorView::POLYLINE:
			if (!m_CurrentFigure || ((CPolyLine*)m_CurrentFigure)->GetCreatedFlag()) {
				m_CurrentFigure = new CPolyLine(&dd);
				//// m_OperationModeFlag = CREATE;
			}
			break;
		case CGraphicEditorView::PENCIL:
			break;
		case CGraphicEditorView::CURVE:
			break;
		case CGraphicEditorView::ELLIPSE:
			m_CurrentFigure = new CEllipse(&dd, &ff);
			//// m_OperationModeFlag = CREATE;
			break;
		case CGraphicEditorView::RECTANGLE:
			m_CurrentFigure = new CRectangle(&dd, &ff);
			//// m_OperationModeFlag = CREATE;
			break;
		case CGraphicEditorView::STRING:
			m_CurrentFigure = new CText(this, &dd, &ff);
			
			break;
		case CGraphicEditorView::POLYGON:
			break;
		case CGraphicEditorView::CLOSEDCURVE:
			break;
		default:
			break;
		}

		

		//if (m_InsertFlag != NONE)
		//{
		//	m_CurrentFigure->create(&m_LButtonPoint);
		//}



		
		/*********** �� �κ��� �������� ���ÿ�. ***********/
		m_LButtonPoint = m_CurrPoint;		// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = LBUTTON;	// ��Ŭ�� �巡�� ��
		/**************************************************/

		CView::OnLButtonDown(nFlags, point);

		//CGraphicEditorDoc* pDoc = GetDocument();
	}
}

void CGraphicEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_MouseButtonFlag == LBUTTON/* && !(nFlags & MK_RBUTTON)*/) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

		switch (m_InsertFlag)
		{
		case CGraphicEditorView::NONE: {
			if (m_CurrentFigure) {
				if (m_selectedPosition == CFigure::INSIDE) {
					CFigure::MoveFlag moveFlag = CFigure::FREEMOVE;
					//if (nFlags & MK_SHIFT) {
					//	moveFlag = CFigure::;
					//}

					m_CurrentFigure->move(m_LButtonPoint, m_CurrPoint, moveFlag);

				}
				else if (m_selectedPosition & CFigure::ONHANDLE) {
					CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE;
					if (nFlags & MK_SHIFT) {
						resizeFlag = CFigure::PROPORTIONAL;
					}

					if (m_CurrentFigure->IsKindOf(RUNTIME_CLASS(CStrap))) {
						((CStrap*)m_CurrentFigure)->pointMove(m_LButtonPoint, m_CurrPoint);
					}
					else {
					m_CurrentFigure->resize(m_selectedPosition, m_CurrPoint, resizeFlag);
				}
			}
				// m_OperationModeFlag = SELECTABLE;
			}
		} break;
			
		/* ���� ���� */
		case CGraphicEditorView::LINE:
			m_CurrentFigure->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
			// m_OperationModeFlag = SELECTABLE;
			break;
		case CGraphicEditorView::POLYLINE:
			((CPolyLine*)m_CurrentFigure)->addPoint(m_CurrPoint, CFigure::FREECREATE);
			break;
		case CGraphicEditorView::PENCIL:
			break;
		case CGraphicEditorView::CURVE:
			break;
		case CGraphicEditorView::ELLIPSE:
			m_CurrentFigure->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
			// m_OperationModeFlag = SELECTABLE;
			break;
		case CGraphicEditorView::RECTANGLE:
			m_CurrentFigure->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
			// m_OperationModeFlag = SELECTABLE;
			break;
		case CGraphicEditorView::STRING:
			m_CurrentFigure->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
			break;
		case CGraphicEditorView::POLYGON:
			break;
		case CGraphicEditorView::CLOSEDCURVE:
			break;
		default:
			break;
		}


		//if (m_InsertFlag != NONE){
		//	m_CurrentFigure->create(&m_LButtonPoint);
		//	//m_InsertFlag = NONE;
			Invalidate();
		//	m_CurrentFigure->draw();
		//}

		/*********** �� �κ��� �������� ���ÿ�. ***********/
		m_LButtonPoint = m_CurrPoint;		// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = NBUTTON;	// ��Ŭ�� ����
		/**************************************************/

		CView::OnLButtonUp(nFlags, point);
	}
}

void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

		// ����Ŭ���ϸ� �������� ���� �Ϸ�
		if (m_InsertFlag == CGraphicEditorView::POLYLINE && m_CurrentFigures.hasOneFigure()) {
			((CPolyLine*)m_CurrentFigures.GetHead())->create(CFigure::FREECREATE);
			clearInsertFlag();
			// m_OperationModeFlag = SELECTABLE;
		}

		/*********** �� �κ��� �������� ���ÿ�. ***********/
		m_LButtonPoint = m_CurrPoint;		// �̺�Ʈ �߻� ��ǥ
		//m_MouseButtonFlag = NBUTTON;	// ��Ŭ��
		/**************************************************/

		CView::OnLButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.



		/*********** �� �κ��� �������� ���ÿ�. ***********/
		m_RButtonPoint = m_CurrPoint;		// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = RBUTTON;	// ��Ŭ�� �巡�� ��
		/**************************************************/

		CView::OnRButtonDown(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_MouseButtonFlag == RBUTTON/* && !(nFlags & MK_LBUTTON)*/) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		ClientToScreen(&point);
		OnContextMenu(this, point);



		/*********** �� �κ��� �������� ���ÿ�. ***********/
		m_RButtonPoint = m_CurrPoint;		// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = NBUTTON;	// ��Ŭ�� ����
		/**************************************************/
	}
}

void CGraphicEditorView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.



		/*********** �� �κ��� �������� ���ÿ�. ***********/
		m_RButtonPoint = m_CurrPoint;		// �̺�Ʈ �߻� ��ǥ
		m_MouseButtonFlag = NBUTTON;	// ��Ŭ��
		/**************************************************/

		CView::OnRButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//CView::OnMouseMove(nFlags, point);

	m_CurrPoint = CGlobal::CPointToPointF(point);
	m_MouseVKFlags = nFlags;

	if (getOperationModeFlag() == CREATE || getOperationModeFlag() == MOVE || getOperationModeFlag() == RESIZE) {
		Invalidate/*Rect*/(/*m_DrawnArea*/);
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

void CGraphicEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	if (m_CurrentFigures.hasOneFigure() && m_CurrentFigures.GetHead()->IsKindOf((RUNTIME_CLASS(CText)))) {
		switch (nChar) {
			// �齺���̽� �Է½�
		case VK_BACK:
			((CText*)m_CurrentFigures.GetHead())->delChar(); // ���ڻ���
			break;
			// ���� �Է��̹Ƿ� ����Ű�� �迭�� ���� �ʾƵ���
		case VK_RETURN:
		case VK_CONTROL:
			break;
			// ���� ���̽��� ������ ��������
		default:
			((CText*)m_CurrentFigures.GetHead())->addChar(nChar);
		}
	CView::OnChar(nChar, nRepCnt, nFlags);
	}

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

void CGraphicEditorView::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnSysChar(nChar, nRepCnt, nFlags);
}


void CGraphicEditorView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


/*** CGraphicEditorView �۾� ***/

CGraphicEditorView::OperationModeFlag CGraphicEditorView::getOperationModeFlag()
{
	/*
		### Comments about OperationModeFlag ###
		
	 $	m_InsertFlag, m_CurrentFigures, m_selectedPosition�� �������̴�.

	 $	SELECTABLE:	CREATE ���°� �ƴϸ鼭 ���õ� ��ü�� ���� �����̴�.
		SELECTED:	��ü�� ���õ� ���·� ������ ���� �ʰ� �ִ� �����̴�.
		CREATE:		���� ��ư�� �����ִ� �����̴�.
		MOVE:		������ ��ü�� �����鼭 ��ü ������ ���� ������ �����̴�. 
		RESIZE:		������ ��ü�� �����鼭 ��ü�� �ڵ��� ������ �����̴�.
		//WRITE:		CText ��ü�� ���ڿ��� �Է��ϴ� �����̴�.

	 $	������ ��ü�� ���� ��� m_selectedPosition�� "�ڵ� ��"�� �������� �ʾ�,
		���� ��ü�� ù ��° Ŭ������ ũ�� ������ ���´�.

	 $	ButtonDown���� m_selectedPosition�� "�ڵ� ��(������ ��ü�� ���� ��츸)"
		�Ǵ� "CFigure::INSIDE"�� �����ϰ�,
		ButtonUp���� m_selectedPosition�� "CFigure::OUTSIDE"�� �����Ͽ�,
		SELECTED ���¸� ���� �� �ֵ��� �Ѵ�.
	 */

	// ���� ��ư�� ����������,
	if (m_InsertFlag != NONE) {
		return CREATE;	// CREATE ����
	}

	// ���õ� ��ü�� ���� ��,
	if (!m_CurrentFigures.IsEmpty()) {
		if (m_selectedPosition & CFigure::ONHANDLE) {		// ���� ��ġ�� �ڵ��̸�,
			return RESIZE;									// RESIZE ����
		}

		else if (m_selectedPosition == CFigure::INSIDE) {	// ���� ��ġ�� ���θ�,
			return MOVE;									// MOVE ����
		}

		//else if (m_selectedPosition == CFigure::OUTSIDE) {
		//	return SELECTED;
		//}
		//
		//else if (m_CurrentFigures.hasOneFigure() && m_CurrentFigures.GetHead()->IsKindOf((RUNTIME_CLASS(CText)))) {
		//
		//}

		return SELECTED;									// �̿��� ���, SELECTED ����
	}

	// ���� ��ư�� �������� �����鼭, ���õ� ��ü�� ������,
	return SELECTABLE;	// 	SELECTABLE ����
}

void CGraphicEditorView::clearInsertFlag()
{
	// m_OperationModeFlag = SELECTABLE;
	m_InsertFlag = NONE;
}


/*** CGraphicEditorView �μ� ***/

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


/*** CGraphicEditorView ���� ***/

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


/*** CGraphicEditorView �߰��� ������ ���, �޽��� ó���� �� ������ ***/

