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

#include "MainFrm.h"
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
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SETCURSOR()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSCHAR()
	ON_WM_SYSKEYUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CONTEXTMENU()

	/* ���� �޽��� ó���� */
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicEditorView::OnFilePrintPreview)

	//ON_COMMAND(ID_EDIT_COPY, &CGraphicEditorView::OnEditClear)
	//ON_COMMAND(ID_EDIT_COPY, &CGraphicEditorView::OnEditClearAll)
	ON_COMMAND(ID_EDIT_COPY, &CGraphicEditorView::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CGraphicEditorView::OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, &CGraphicEditorView::OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CGraphicEditorView::OnUpdateEditCut)
	//ON_COMMAND(ID_EDIT_PASTE, &CGraphicEditorView::OnEditFind)
	ON_COMMAND(ID_EDIT_PASTE, &CGraphicEditorView::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CGraphicEditorView::OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_DELETE, &CGraphicEditorView::OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, &CGraphicEditorView::OnUpdateEditDelete)
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
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_GROUPING, &CGraphicEditorView::OnUpdateArrangeGrouping)
	ON_COMMAND(ID_ARRANGE_GROUP, &CGraphicEditorView::OnArrangeGroup)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_GROUP, &CGraphicEditorView::OnUpdateArrangeGroup)
	ON_COMMAND(ID_ARRANGE_UNGROUP, &CGraphicEditorView::OnArrangeUngroup)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_UNGROUP, &CGraphicEditorView::OnUpdateArrangeUngroup)
	ON_COMMAND(ID_ZOOM_IN, &CGraphicEditorView::OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, &CGraphicEditorView::OnZoomOut)
	ON_COMMAND(ID_ZOOM_100, &CGraphicEditorView::OnZoom100)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_100, &CGraphicEditorView::OnUpdateZoom100)
	ON_COMMAND(ID_POINTMOVE, &CGraphicEditorView::OnPointmove)
	ON_UPDATE_COMMAND_UI(ID_POINTMOVE, &CGraphicEditorView::OnUpdatePointmove)
	ON_COMMAND(ID_POLYLINE_INDIVIDUAL_DELETE, &CGraphicEditorView::OnPolylineIndividualDelete)
	ON_UPDATE_COMMAND_UI(ID_POLYLINE_INDIVIDUAL_DELETE, &CGraphicEditorView::OnUpdatePolylineIndividualDelete)
	ON_COMMAND(ID_POLYLINE_INDIVIDUAL_INSERT, &CGraphicEditorView::OnPolylineIndividualInsert)
	ON_UPDATE_COMMAND_UI(ID_POLYLINE_INDIVIDUAL_INSERT, &CGraphicEditorView::OnUpdatePolylineIndividualInsert)
END_MESSAGE_MAP()


/*** CGraphicEditorView ����/�Ҹ� ***/

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	//m_CurrentFigure = NULL;
	m_MouseVKFlags = 0;
	m_MouseButtonFlag = NBUTTON;
	m_InsertFlag = NONE;
	m_PolyCreatableFlag = FALSE;
	m_CreateBuffer = NULL;
	m_EditPointFlag = FALSE;
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

void CGraphicEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_SelectedFigures.setFigurePtrList(&GetDocument()->m_FiguresList);
}

// CGraphicEditorView �׸���
void CGraphicEditorView::OnDraw(CDC* pDC)
{
	/* CGraphicEditorDoc */
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	/* ��� ��� */
	Graphics graphicsDC(*pDC);	// gdi+ �׸��⸦ ���� ��ü https://msdn.microsoft.com/en-us/library/windows/desktop/ms534453(v=vs.85).aspx
	
	/****************************** ���� ���۸� ******************************/
	CRect rect;
	GetClientRect(rect);
	Bitmap bmpCanvas(rect.right, rect.bottom);		// ĵ���� ��Ʈ�� ����
	Graphics graphicsCanvas(&bmpCanvas);			// ĵ���� �׷��Ƚ� ����
	graphicsCanvas.Clear(Color::White);				// ĵ���� ���� ����
	/*************************************************************************/
	
	graphicsCanvas.SetSmoothingMode(SmoothingModeHighQuality);	// Antialising
	
	
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	// GDI+			https://msdn.microsoft.com/en-us/library/windows/desktop/ms533798(v=vs.85).aspx
	// GDI+ Ref.	https://msdn.microsoft.com/en-us/library/windows/desktop/ms533799(v=vs.85).aspx
	// GDI+ Classes	https://msdn.microsoft.com/en-us/library/windows/desktop/ms533958(v=vs.85).aspx

	// ������� ������ ��� ��ü �׸���
	if (!pDoc->m_FiguresList.IsEmpty()) {
		pDoc->m_FiguresList.draw(graphicsCanvas);
	}

	// ���õ� ��ü�� ���� ���� �� �ڵ� �׸���
	if (!m_SelectedFigures.isEmpty()) {
		m_SelectedFigures.drawArea(graphicsCanvas, m_EditPointFlag);
	}

	// �巡�� ���� �׸���
	if (m_selectedPosition == CFigure::OUTSIDE) {
		SolidBrush brush(Color(30, 30, 30, 30));
		Pen pen(Color(50, 50, 50, 50));
		
		graphicsCanvas.FillRectangle(&brush, m_SelectArea);
		graphicsCanvas.DrawRectangle(&pen, m_SelectArea);
	}

	// ȯ�濡 ���� �׸���
	switch (m_MouseButtonFlag)	// ���콺 Ŭ��/�巡�� ���¿� ���� �׸���
	{
		/*** NO BUTTON ***/
		case CGraphicEditorView::NBUTTON: {
			if (m_CreateBuffer && getOperationModeFlag() == CREATE
				&& m_InsertFlag == POLYLINE && m_PolyCreatableFlag == FALSE) {
				((CPolyLine*)m_CreateBuffer)->draw(graphicsCanvas);
				/*m_drawnArea = CGlobal::RectFToCRect(*/((CPolyLine*)m_CreateBuffer)->creating(graphicsCanvas, m_CurrPoint);
			}
			else if (m_CreateBuffer && getOperationModeFlag() == CREATE
				&& m_InsertFlag == POLYGON && m_PolyCreatableFlag == FALSE) {
				((CPolygon*)m_CreateBuffer)->draw(graphicsCanvas);
				((CPolygon*)m_CreateBuffer)->creating(graphicsCanvas, m_CurrPoint);
			}
		} break;


		/*** LBUTTON ***/
		case CGraphicEditorView::LBUTTON: {
			switch (getOperationModeFlag())
			{
				/** LBUTTON SELECTABLE **/
				//case CGraphicEditorView::SELECTABLE: {
				//} break;

				/** LBUTTON SELECTED **/
				//case CGraphicEditorView::SELECTED: {
				//} break;

				/** LBUTTON CREATE **/
				case CGraphicEditorView::CREATE: {
					if (m_CreateBuffer) {
						switch (m_InsertFlag)
						{
						/* LBUTTON CREATE LINE */
						case CGraphicEditorView::LINE:
							m_CreateBuffer->creating(graphicsCanvas, &m_LButtonPoint, &m_CurrPoint);
							break;

							/* LBUTTON CREATE POLYLINE */
							//case CGraphicEditorView::POLYLINE:
							// �ƹ� ������ ���� ����
							//break;

						/* LBUTTON CREATE PENCIL */
						case CGraphicEditorView::PENCIL:
							if (m_PolyCreatableFlag == FALSE) {
								((CPencil*)m_CreateBuffer)->addPoint(m_CurrPoint, CFigure::FREECREATE);	// �� �߰�
								((CPencil*)m_CreateBuffer)->draw(graphicsCanvas);
							}
							break;

						/* LBUTTON CREATE CURVE */
						case CGraphicEditorView::CURVE:
							/*m_DrawnArea = CGlobal::RectFToCRect(*/m_CreateBuffer->creating(graphicsCanvas, &m_LButtonPoint, &m_CurrPoint);
							break;

						/* LBUTTON CREATE ELLIPSE/RECTANGLE/STRING */
						case CGraphicEditorView::ELLIPSE:
							((CRectangle*)m_CreateBuffer)->creating(graphicsCanvas, &m_LButtonPoint, &m_CurrPoint);
							break;

						case CGraphicEditorView::RECTANGLE:
							((CEllipse*)m_CreateBuffer)->creating(graphicsCanvas, &m_LButtonPoint, &m_CurrPoint);
							break;

						case CGraphicEditorView::STRING:

							break;

						/* LBUTTON CREATE POLYGON/CLOSEDCURVE */
						case CGraphicEditorView::POLYGON:
							// do nothing
							break;;
						case CGraphicEditorView::CLOSEDCURVE:

							break;
						}
					}
				} break;

				/** LBUTTON MOVE **/
				case CGraphicEditorView::MOVE: {			// ��ü �̵�
					m_SelectedFigures.moving(graphicsCanvas, m_LButtonPoint, m_CurrPoint);
				} break;

				/** LBUTTON RESIZE **/
				case CGraphicEditorView::RESIZE: {
					if (m_SelectedFigures.hasOne()) {	// ���� ���� ��ü �ϳ�
						CFigure* figure = m_SelectedFigures.getOneFigure();

						if (figure->IsKindOf(RUNTIME_CLASS(CLine))){			// CLine �� �̵� (�� �̵��� ũ�� ���� ���� �� �ϳ��� ����)
							if (m_EditPointFlag == TRUE)
								((CLine*)figure)->pointMoving(graphicsCanvas, m_LButtonPoint, m_CurrPoint);
						}
						else if (figure->IsKindOf(RUNTIME_CLASS(CPolyLine))){	// CPolyLine �� �̵� (�� �̵��� ũ�� ���� ���� �� �ϳ��� ����)
							if (m_EditPointFlag== TRUE)
								((CPolyLine*)figure)->pointMoving(graphicsCanvas, m_LButtonPoint, m_CurrPoint);
						}
						else if (figure->IsKindOf(RUNTIME_CLASS(CPolygon))){	// CPolyLine �� �̵� (�� �̵��� ũ�� ���� ���� �� �ϳ��� ����)
							if (m_EditPointFlag == TRUE)
								((CPolygon*)figure)->pointMoving(graphicsCanvas, m_LButtonPoint, m_CurrPoint);
						}

						else {								// ��ü �� �� ũ�� ����
							figure->resizing(graphicsCanvas, m_selectedPosition, m_CurrPoint);
						}
					}
					else {									// ���� ���� ��ü ���� �� ũ�� ����
						m_SelectedFigures.resizing(graphicsCanvas, m_selectedPosition, m_CurrPoint);
					}
				} break;
			}
		} break;


		/*** RBUTTON ***/
		case CGraphicEditorView::RBUTTON: {
			if (m_MouseVKFlags & MK_CONTROL) {		// Ctrl ������ �巡��

			}
			else if (m_MouseVKFlags & MK_SHIFT) {	// Shift ������ �巡��

			}
			else {							// ����Ű ������ �ʰ� �巡��

			}
		} break;

		case CGraphicEditorView::MBUTTON: {

		} break;
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
	// graphicsCanvas �����͸� ��� ����(m_graphicsCanvas)�� �ּ� �� ��ü Ŭ�������� �׸��⸦ �����ϰ�, �� �Լ��� ȣ���ϴ� ������� �Ұž�
	//
	//}
	//////////////////////////////////////////////// ���⼭���� ���� �ڵ� ///////////////////////////////////////////////////////
	// GDI+ ���� �ڵ� (�簢�� �׸���)
	SolidBrush sb(Color(255,255,0,0));
	graphicsCanvas.FillRectangle(&sb, Rect(33, 44, 55, 66));

	// Set up the arc.
	Pen redPen(Color(255, 255, 0, 0), 3);
	RectF ellipseRect(0, 0, 200, 100);
	REAL startAngle = 0.0f;
	REAL sweepAngle = 90.0f;

	// Draw the arc.
	graphicsCanvas.DrawArc(&redPen, ellipseRect, startAngle, sweepAngle);

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
	graphicsCanvas.DrawString(
		string,
		11,
		&myFont,
		layoutRect,
		&format,
		&blackBrush);

	// Draw layoutRect.
	graphicsCanvas.DrawRectangle(&Pen(Color::Blue, 3), layoutRect);
	///////////////////////////////// ������� ���� �ڵ� ///////////////////////////////////////////////////////////////
	
	//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), m_psMemDC, 0, 0, SRCCOPY);


	/**************************************** ���� ���۸� ****************************************/
	graphicsDC.DrawImage(&bmpCanvas, rect.left, rect.top, rect.right, rect.bottom);	// ĵ���� �׸���
	/*********************************************************************************************/
}


/*** CGraphicEditorView �޽��� ó���� ***/

BOOL CGraphicEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//return CView::OnEraseBkgnd(pDC);
	return FALSE;	// ���� ���۸��� ���Ͽ� ����� ������� ����
}


void CGraphicEditorView::OnDestroy()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	CView::OnDestroy();
}

void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

		
		Pen dd(Color(255, 0, 0));			// �׽�Ʈ�� ��
		SolidBrush ff(Color::DarkGreen);	// �׽�Ʈ�� �귯��


		switch (getOperationModeFlag())
		{
			case CGraphicEditorView::SELECTABLE: {
				m_selectedPosition = m_SelectedFigures.select(m_CurrPoint);		// ��ü ��ü ����Ʈ(�׷�)�� ������ ��ȸ
				// ���� ���� ���� (OUTSIDE/INSIDE �� ���� �����θ� m_selectedPosition ����)
				// Invalidate ȣ�� (���� ������ �׸��� ����)
				CFigure* figure;
				m_EditPointFlag = FALSE;
			} break;

			case CGraphicEditorView::SELECTED: {
				m_selectedPosition = m_SelectedFigures.contains(m_CurrPoint);	// ��ü �� ���� ��ġ�� ������

				if (m_selectedPosition == CFigure::OUTSIDE) {
					m_EditPointFlag = FALSE;
					if ((nFlags & MK_SHIFT) || (nFlags & MK_CONTROL)) {				// shift�� control�� ������ �巡���ϸ�
						// ���� ����Ʈ�� �������� �ʰ� �߰�
					}
					else{
						if (m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CText)))
							HideCaret();
						m_SelectedFigures.deselectAll();		// SELECTABLE ���·� ��ȯ
					}
					m_selectedPosition = m_SelectedFigures.select(m_CurrPoint);
				}
			} break;

			case CGraphicEditorView::CREATE: {
				switch (m_InsertFlag)
				{
					/* CREATE ���� */
				case CGraphicEditorView::LINE:
					preInsert();								// ���� ���� ��ü ����
					m_CreateBuffer = new CLine(&dd);	// ���ο� ���� ��ü ����
					break;

				case CGraphicEditorView::POLYLINE:
					if (m_PolyCreatableFlag) {							// CPolyLine ��ü ���� ���� ����
						preInsert();									// ���� ���� ��ü ����
						m_CreateBuffer = new CPolyLine(&dd);	// ��ü ����
						m_PolyCreatableFlag = FALSE;					// CPolyLine ��ü ���� �Ұ��� ���·� ����
					}
					((CPolyLine*)m_CreateBuffer)->addPoint(m_CurrPoint, CFigure::FREECREATE);	// �� �߰�
					break;

				case CGraphicEditorView::PENCIL:
					if (m_PolyCreatableFlag) {							// CPolyLine ��ü ���� ���� ����
						preInsert();									// ���� ���� ��ü ����
						m_CreateBuffer = new CPencil(&dd);	// ��ü ����
						m_PolyCreatableFlag = FALSE;					// CPolyLine ��ü ���� �Ұ��� ���·� ����
					}
					break;

				case CGraphicEditorView::CURVE:
					break;

				case CGraphicEditorView::ELLIPSE:
					preInsert();								// ���� ���� ��ü ����
					m_CreateBuffer = new CEllipse(&dd, &ff);
					break;

				case CGraphicEditorView::RECTANGLE:
					preInsert();								// ���� ���� ��ü ����
					m_CreateBuffer = new CRectangle(&dd, &ff);
					break;

				case CGraphicEditorView::STRING:
					preInsert();								// ���� ���� ��ü ����
					m_CreateBuffer = new CText(this, &dd, &ff);
					break;

				case CGraphicEditorView::POLYGON:
					if (m_PolyCreatableFlag) {							// CPolygon��ü ���� ���� ����
						preInsert();									// ���� ���� ��ü ����
						m_CreateBuffer = new CPolygon(&dd, &ff);		// ��ü ����
						m_PolyCreatableFlag = FALSE;					// CPolygon ��ü ���� �Ұ��� ���·� ����
					}
					((CPolygon*)m_CreateBuffer)->addPoint(m_CurrPoint, CFigure::FREECREATE);	// �� �߰�

					break;

				case CGraphicEditorView::CLOSEDCURVE:
					break;
				}
			} break;

			//case CGraphicEditorView::MOVE: {

			//} break;

			//case CGraphicEditorView::RESIZE: {

			//} break;
		}

		// �� Ŭ���̾�Ʈ ���� ���콺 ĸ��
		SetCapture();

		/*********** �� �κ��� �������� ���ÿ�. ***********/
		m_LButtonPoint = m_CurrPoint;	// �̺�Ʈ �߻� ��ǥ
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

		switch (getOperationModeFlag())
		{
			case CGraphicEditorView::SELECTABLE: {
				m_SelectedFigures.select(m_SelectArea);		// ��ü ��ü ����Ʈ(�׷�)�� ������ ��ȸ
				m_selectedPosition = CFigure::OUTSIDE;
				m_SelectArea = NULLRectF;
			} break;

			//case CGraphicEditorView::SELECTED: {
			//	if (m_SelectedFigures.hasOne()) {
			//		m_selectedPosition = m_SelectedFigures.getOneFigure()->pointInFigure(m_CurrPoint);
			//	}
			//	else if (!m_SelectedFigures.isEmpty()) {
			//		m_selectedPosition = m_SelectedFigures.contains(m_CurrPoint);
			//	}
			//} break;

			/* CREATE ���� */
			case CGraphicEditorView::CREATE: {
				switch (m_InsertFlag)
				{
				case CGraphicEditorView::LINE:
					m_CreateBuffer->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
					postInsert();
					break;

				case CGraphicEditorView::POLYLINE:
					// �ƹ� ���۵� ���� ���� //((CPolyLine*)m_CurrentFigure)->addPoint(m_CurrPoint, CFigure::FREECREATE);
					break;

				case CGraphicEditorView::PENCIL:
					((CPencil*)m_CreateBuffer)->create(CFigure::FREECREATE);
					m_PolyCreatableFlag = TRUE;
					postInsert();
					break;

				case CGraphicEditorView::CURVE:
					break;

				case CGraphicEditorView::ELLIPSE:
					m_CreateBuffer->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
					postInsert();
					break;

				case CGraphicEditorView::RECTANGLE:
					m_CreateBuffer->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
					postInsert();
					break;

				case CGraphicEditorView::STRING:
					m_CreateBuffer->create(&m_LButtonPoint, &m_CurrPoint, CFigure::FREECREATE);
					postInsert();
					break;

				case CGraphicEditorView::POLYGON:
					// �ƹ� ���۵� ���� ���� //((CPolyLine*)m_CurrentFigure)->addPoint(m_CurrPoint, CFigure::FREECREATE);
					break;

				case CGraphicEditorView::CLOSEDCURVE:
					break;
				}
			} break;

			case CGraphicEditorView::MOVE: {
				CFigure::MoveFlag moveFlag = CFigure::FREEMOVE;
				//if (nFlags & MK_SHIFT) {
				//	moveFlag = CFigure::;
				//}
				m_SelectedFigures.move(m_LButtonPoint, m_CurrPoint, moveFlag);
				m_selectedPosition = CFigure::OUTSIDE;
			} break;

			case CGraphicEditorView::RESIZE: {
				CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE;
				if (nFlags & MK_SHIFT) {
					resizeFlag = CFigure::PROPORTIONAL;
				}

				if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CStrap))) {
					if (m_EditPointFlag == TRUE)
					((CStrap*)m_SelectedFigures.getOneFigure())->pointMove(m_LButtonPoint, m_CurrPoint);
				}
				else if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolygon))){
					if (m_EditPointFlag == TRUE)
						((CPolygon*)m_SelectedFigures.getOneFigure())->pointMove(m_LButtonPoint, m_CurrPoint);
				}
				else {
					m_SelectedFigures.resize(m_selectedPosition, m_LButtonPoint, m_CurrPoint, resizeFlag);
				}
				m_selectedPosition = CFigure::OUTSIDE;
			} break;
		}

		// �����Ͱ� �����Ǿ����� ��ť��Ʈ ��ü�� �˸�
		GetDocument()->SetModifiedFlag();

		Invalidate();

		// ���콺 ĸ�ĸ� ������
		::ReleaseCapture();

		/*********** �� �κ��� �������� ���ÿ�. ***********/
		m_LButtonPoint = m_CurrPoint;	// �̺�Ʈ �߻� ��ǥ
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
		if (m_InsertFlag == CGraphicEditorView::POLYLINE /* && m_SelectedFigures.hasOne()*/) {
			((CPolyLine*)m_CreateBuffer)->create(CFigure::FREECREATE);
			
			m_PolyCreatableFlag = TRUE;
			postInsert();
			//clearInsertFlag();
		}

		else if (m_InsertFlag == CGraphicEditorView::POLYGON/* && m_SelectedFigures.hasOne()*/) {
			((CPolygon*)m_CreateBuffer)->create(CFigure::FREECREATE);
			m_PolyCreatableFlag = TRUE;
			postInsert();
			//clearInsertFlag();
		}


		/*********** �� �κ��� �������� ���ÿ�. ***********/
		m_LButtonPoint = m_CurrPoint;	// �̺�Ʈ �߻� ��ǥ
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
		m_RButtonPoint = m_CurrPoint;	// �̺�Ʈ �߻� ��ǥ
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
		m_RButtonPoint = m_CurrPoint;	// �̺�Ʈ �߻� ��ǥ
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
		m_RButtonPoint = m_CurrPoint;	// �̺�Ʈ �߻� ��ǥ
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

	switch (getOperationModeFlag())
	{
	case CGraphicEditorView::SELECTABLE:
		if (m_MouseButtonFlag == LBUTTON) {

			PointF startingPoint = m_LButtonPoint;
			SizeF rectSize;
			rectSize.Width = abs(m_LButtonPoint.X - m_CurrPoint.X);
			rectSize.Height = abs(m_LButtonPoint.Y - m_CurrPoint.Y);

			if (m_LButtonPoint.X > m_CurrPoint.X) {
				startingPoint.X = m_CurrPoint.X;
			}

			if (m_LButtonPoint.Y > m_CurrPoint.Y) {
				startingPoint.Y = m_CurrPoint.Y;
			}

			m_SelectArea = RectF(startingPoint, rectSize);
		}
		//break;

	//case CGraphicEditorView::SELECTED:
	//	break;

	case CGraphicEditorView::CREATE:
	case CGraphicEditorView::MOVE:
	case CGraphicEditorView::RESIZE:
		Invalidate/*Rect*/(/*m_DrawnArea*/);
		break;

	default:
		break;
	}
}

BOOL CGraphicEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CView::OnMouseWheel(nFlags, zDelta, point);
}

BOOL CGraphicEditorView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (nHitTest == HTCLIENT) {
		CPoint point;
		::GetCursorPos(&point);		// ��ũ����ǥ
		ScreenToClient(&point);		// Ŭ���̾�Ʈ��ǥ�κ�ȯ

		//if (m_SelectedFigures.GetSize() == 1){
		//	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HELP));
		//	return true;
		//}

		switch (getOperationModeFlag())
		{
		case CGraphicEditorView::SELECTABLE:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			break;
		case CGraphicEditorView::SELECTED:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
			break;
		case CGraphicEditorView::CREATE:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
			break;
		case CGraphicEditorView::MOVE:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
			break;
		case CGraphicEditorView::RESIZE:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
			break;
		}
		//CRgn rgn;
		//rgn.CreateEllipticRgn(50, 50, 500, 200);
		//if (rgn.PtInRegion(point))
		//	::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1);
		//else
		//	::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS);
		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CGraphicEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (nChar)
	{
	case VK_ESCAPE:
	case VK_CANCEL:
	case VK_BACK:
		cancelInsert();
		break;
	case VK_DELETE:
		OnEditDelete();
		break;
	case 'A':
	case 'a':
		if (nFlags & 13) {
			m_SelectedFigures.selectAll();
			Invalidate();
		}
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf((RUNTIME_CLASS(CText)))) {
		switch (nChar) {
			// �齺���̽� �Է½�
		case VK_BACK:
			((CText*)m_SelectedFigures.getOneFigure())->delChar(); // ���ڻ���
			break;
			// ���� �Է��̹Ƿ� ����Ű�� �迭�� ���� �ʾƵ���
		case VK_RETURN:
		case VK_CONTROL:
			break;
			// ���� ���̽��� ������ ��������
		default:
			((CText*)m_SelectedFigures.getOneFigure())->addChar(nChar);
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

void CGraphicEditorView::preInsert()	// ����(����) �۾� ���� �ؾ� �� �۾�
{
	m_SelectedFigures.deselectAll();	// ���� ��ü ����
}

void CGraphicEditorView::postInsert()	// ����(����) �۾� �Ŀ� �ؾ� �� �۾�
{
	GetDocument()->m_FiguresList.AddHead(m_CreateBuffer);	// ��ü ��ü ����Ʈ�� �߰�
	//m_selectedPosition = CFigure::OUTSIDE;
	m_CreateBuffer = NULL;
}

void CGraphicEditorView::cancelInsert()	// ����(����) �۾� ��� �ÿ� �ؾ� �� �۾�
{
	setOperationModeFlag(SELECTABLE);
	Invalidate();
}

void CGraphicEditorView::clearInsertFlag()
{
	// m_OperationModeFlag = SELECTABLE;
	m_InsertFlag = NONE;
}

CGraphicEditorView::OperationModeFlag CGraphicEditorView::getOperationModeFlag()
{
	/*
		### Comments about OperationModeFlag ###
		
	 $	m_InsertFlag, m_SelectedFigures, m_selectedPosition�� �������̴�.

	 $	SELECTABLE:	CREATE ���°� �ƴϸ鼭 ���õ� ��ü�� ���� �����̴�.
		SELECTED:	��ü�� ���õ� ���·� ������ ���� �ʰ� �ִ� �����̴�.
		CREATE:		���� ��ư�� �����ִ� �����̴�.
		MOVE:		������ ��ü�� �����鼭 ��ü ������ ���� ������ �����̴�. 
		RESIZE:		������ ��ü�� �����鼭 ��ü�� �ڵ��� ������ �����̴�.
		//WRITE:		CText ��ü�� ���ڿ��� �Է��ϴ� �����̴�.

	 $	������ ��ü�� ���� ��� m_selectedPosition�� "�ڵ� ��"�� �������� �ʵ��� �Ͽ�,
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
	if (!m_SelectedFigures.isEmpty()) {
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
		//else if (m_SelectedFigures.hasOneFigure() && m_SelectedFigures.GetHead()->IsKindOf((RUNTIME_CLASS(CText)))) {
		//
		//}

		return SELECTED;									// �̿��� ���, SELECTED ����
	}

	// ���� ��ư�� �������� �����鼭, ���õ� ��ü�� ������,
	return SELECTABLE;	// SELECTABLE ����
}

void CGraphicEditorView::setOperationModeFlag(OperationModeFlag operationModeFlag/* = SELECTABLE*/)
{
	switch (operationModeFlag)
	{
	case CGraphicEditorView::SELECTABLE:
	m_InsertFlag = NONE;
		m_selectedPosition = CFigure::OUTSIDE;
		m_SelectedFigures.deselectAll();
		break;

	case CGraphicEditorView::SELECTED:
		break;

	case CGraphicEditorView::CREATE:
		break;

	case CGraphicEditorView::MOVE:
		break;

	case CGraphicEditorView::RESIZE:
		break;
	}
}

BOOL CGraphicEditorView::getCopyableFlag()
{
	return !m_SelectedFigures.isEmpty();
}

BOOL CGraphicEditorView::getPastableFlag()
{
	return !m_BufferList.IsEmpty();
}

BOOL CGraphicEditorView::getDeletableFlag()
{
	return !m_SelectedFigures.isEmpty();
}

BOOL CGraphicEditorView::getGroupableFlag()
{
	return m_SelectedFigures.getSize() > 1;
}

BOOL CGraphicEditorView::getUngroupableFlag()
{
	CFigurePtrList* figurePtrList = m_SelectedFigures.getFigurePtrList();
	CFigure* figure;
	const POSITION* positions = m_SelectedFigures.getData();

	for (int i = 0; i < m_SelectedFigures.getSize(); i++) {
		figure = figurePtrList->GetAt(positions[i]);

		if (figure->IsKindOf(RUNTIME_CLASS(CGroup))) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CGraphicEditorView::getLineSelectedFlag()
{
	if (m_SelectedFigures.hasOne()) {
		if (m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CLine))) {
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CGraphicEditorView::getPolySelectedFlag()
{
	if (m_SelectedFigures.hasOne()) {
		if (m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolyLine))
			|| m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolygon))) {
			return TRUE;
		}
	}

	return FALSE;
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
