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

// Graphic Editor View.cpp : CGraphicEditorView 클래스의 구현 (작업, 재정의, (명령 메시지 이외의) 메시지 처리기)
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.

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
	/* 메시지 처리기 */
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

	/* 통지 메시지 처리기 */
	// 표준 인쇄 명령입니다.
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
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_ORDER, &CGraphicEditorView::OnUpdateArrangeOrder)
	ON_COMMAND(ID_ARRANGE_BRING_FRONT, &CGraphicEditorView::OnArrangeBringFront)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_BRING_FRONT, &CGraphicEditorView::OnUpdateArrangeBringFront)
	ON_COMMAND(ID_ARRANGE_SEND_BACK, &CGraphicEditorView::OnArrangeSendBack)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_SEND_BACK, &CGraphicEditorView::OnUpdateArrangeSendBack)
	ON_COMMAND(ID_ARRANGE_BRING_FORWARD, &CGraphicEditorView::OnArrangeBringForward)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_BRING_FORWARD, &CGraphicEditorView::OnUpdateArrangeBringForward)
	ON_COMMAND(ID_ARRANGE_SEND_BACKWARD, &CGraphicEditorView::OnArrangeSendBackward)
	ON_UPDATE_COMMAND_UI(ID_ARRANGE_SEND_BACKWARD, &CGraphicEditorView::OnUpdateArrangeSendBackward)
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
	ON_COMMAND(ID_OUTLINE_COLOR, &CGraphicEditorView::OnOutlineColor)
	ON_UPDATE_COMMAND_UI(ID_OUTLINE_COLOR, &CGraphicEditorView::OnUpdateOutlineColor)
	ON_COMMAND(ID_OUTLINE_WIDTH, &CGraphicEditorView::OnOutlineWidth)
	ON_UPDATE_COMMAND_UI(ID_OUTLINE_WIDTH, &CGraphicEditorView::OnUpdateOutlineWidth)
	ON_COMMAND(ID_OUTLINE_PATTERN, &CGraphicEditorView::OnOutlinePattern)
	ON_UPDATE_COMMAND_UI(ID_OUTLINE_PATTERN, &CGraphicEditorView::OnUpdateOutlinePattern)
	ON_COMMAND(ID_FILL_COLOR, &CGraphicEditorView::OnFillColor)
	ON_UPDATE_COMMAND_UI(ID_FILL_COLOR, &CGraphicEditorView::OnUpdateFillColor)
	ON_COMMAND(ID_FILL_SUBCOLOR, &CGraphicEditorView::OnFillSubcolor)
	ON_UPDATE_COMMAND_UI(ID_FILL_SUBCOLOR, &CGraphicEditorView::OnUpdateFillSubcolor)
	ON_COMMAND(ID_FILL_PATTERN, &CGraphicEditorView::OnFillPattern)
	ON_UPDATE_COMMAND_UI(ID_FILL_PATTERN, &CGraphicEditorView::OnUpdateFillPattern)
	ON_COMMAND(ID_POSITION_VERTICAL, &CGraphicEditorView::OnPositionVertical)
	ON_UPDATE_COMMAND_UI(ID_POSITION_VERTICAL, &CGraphicEditorView::OnUpdatePositionVertical)
	ON_COMMAND(ID_POSITION_HORIZONTAL, &CGraphicEditorView::OnPositionHorizontal)
	ON_UPDATE_COMMAND_UI(ID_POSITION_HORIZONTAL, &CGraphicEditorView::OnUpdatePositionHorizontal)
	ON_COMMAND(ID_SIZE_HEIGHT, &CGraphicEditorView::OnSizeHeight)
	ON_UPDATE_COMMAND_UI(ID_SIZE_HEIGHT, &CGraphicEditorView::OnUpdateSizeHeight)
	ON_COMMAND(ID_SIZE_WIDTH, &CGraphicEditorView::OnSizeWidth)
	ON_UPDATE_COMMAND_UI(ID_SIZE_WIDTH, &CGraphicEditorView::OnUpdateSizeWidth)
	ON_COMMAND(ID_FONT_CHARSET, &CGraphicEditorView::OnFontCharset)
	ON_UPDATE_COMMAND_UI(ID_FONT_CHARSET, &CGraphicEditorView::OnUpdateFontCharset)
	ON_COMMAND(ID_FONT_SIZE, &CGraphicEditorView::OnFontSize)
	ON_UPDATE_COMMAND_UI(ID_FONT_SIZE, &CGraphicEditorView::OnUpdateFontSize)
	ON_COMMAND(ID_FONT_BOLD, &CGraphicEditorView::OnFontBold)
	ON_UPDATE_COMMAND_UI(ID_FONT_BOLD, &CGraphicEditorView::OnUpdateFontBold)
	ON_COMMAND(ID_FONT_ITALIC, &CGraphicEditorView::OnFontItalic)
	ON_UPDATE_COMMAND_UI(ID_FONT_ITALIC, &CGraphicEditorView::OnUpdateFontItalic)
	ON_COMMAND(ID_FONT_UNDERLINE, &CGraphicEditorView::OnFontUnderline)
	ON_UPDATE_COMMAND_UI(ID_FONT_UNDERLINE, &CGraphicEditorView::OnUpdateFontUnderline)
	ON_COMMAND(ID_FONT_COLOR, &CGraphicEditorView::OnFontColor)
	ON_UPDATE_COMMAND_UI(ID_FONT_COLOR, &CGraphicEditorView::OnUpdateFontColor)
	ON_COMMAND(ID_POINTMOVE, &CGraphicEditorView::OnPointmove)
	ON_UPDATE_COMMAND_UI(ID_POINTMOVE, &CGraphicEditorView::OnUpdatePointmove)
	ON_COMMAND(ID_POLY_INDIVIDUAL_INSERT, &CGraphicEditorView::OnPolyIndividualInsert)
	ON_UPDATE_COMMAND_UI(ID_POLY_INDIVIDUAL_INSERT, &CGraphicEditorView::OnUpdatePolyIndividualInsert)
	ON_COMMAND(ID_POLY_INDIVIDUAL_DELETE, &CGraphicEditorView::OnPolyIndividualDelete)
	ON_UPDATE_COMMAND_UI(ID_POLY_INDIVIDUAL_DELETE, &CGraphicEditorView::OnUpdatePolyIndividualDelete)
	END_MESSAGE_MAP()


/*** CGraphicEditorView 생성/소멸 ***/

CGraphicEditorView::CGraphicEditorView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

	//m_CurrentFigure = NULL;
	m_WndRibbonBar = ((CMDIFrameWndEx*)AfxGetMainWnd())->GetRibbonBar();
	m_CurrentBrushType = BrushTypeSolidColor;
	m_MouseVKFlags = 0;
	m_MouseButtonFlag = NBUTTON;
	m_InsertFlag = NONE;
	m_PolyCreatableFlag = FALSE;
	m_CreateBuffer = NULL;
	m_EditPointFlag = FALSE;
	//// m_OperationModeFlag = SELECTABLE;
}

REAL CGraphicEditorView::m_offset = 0;

CGraphicEditorView::~CGraphicEditorView()
{
}


/*** CGraphicEditorView 가상 함수 ***/

BOOL CGraphicEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

void CGraphicEditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_SelectedFigures.setFigurePtrList(&GetDocument()->m_FiguresList);

}

// CGraphicEditorView 그리기
void CGraphicEditorView::OnDraw(CDC* pDC)
{
	/* CGraphicEditorDoc */
	CGraphicEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	/* 출력 대상 */
	Graphics graphicsDC(*pDC);	// gdi+ 그리기를 위한 객체 https://msdn.microsoft.com/en-us/library/windows/desktop/ms534453(v=vs.85).aspx
	
	/****************************** 더블 버퍼링 ******************************/
	CRect rect;
	GetClientRect(rect);
	Bitmap bmpCanvas(rect.right, rect.bottom);		// 캔버스 비트맵 생성
	Graphics graphicsCanvas(&bmpCanvas);			// 캔버스 그래픽스 생성
	graphicsCanvas.Clear(Color::White);				// 캔버스 배경색 지정
	/*************************************************************************/
	
	graphicsCanvas.SetSmoothingMode(SmoothingModeHighQuality);	// Antialising
	
	
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	// GDI+			https://msdn.microsoft.com/en-us/library/windows/desktop/ms533798(v=vs.85).aspx
	// GDI+ Ref.	https://msdn.microsoft.com/en-us/library/windows/desktop/ms533799(v=vs.85).aspx
	// GDI+ Classes	https://msdn.microsoft.com/en-us/library/windows/desktop/ms533958(v=vs.85).aspx

	// 현재까지 생성된 모든 개체 그리기
	if (!pDoc->m_FiguresList.IsEmpty()) {
		pDoc->m_FiguresList.draw(graphicsCanvas);
	}

	// 선택된 개체의 선택 영역 및 핸들 그리기
	if (!m_SelectedFigures.isEmpty()) {
		m_SelectedFigures.drawArea(graphicsCanvas, m_EditPointFlag);
	}

	// 드래그 영역 그리기
	if (m_selectedPosition == CFigure::OUTSIDE) {
		SolidBrush brush(Color(30, 30, 30, 30));
		Pen pen(Color(50, 50, 50, 50));
		
		graphicsCanvas.FillRectangle(&brush, m_SelectArea);
		graphicsCanvas.DrawRectangle(&pen, m_SelectArea);
	}

	// 환경에 따른 그리기
	switch (m_MouseButtonFlag)	// 마우스 클릭/드래그 상태에 따른 그리기
	{
		/*** NO BUTTON ***/
		case CGraphicEditorView::NBUTTON: {
			if (m_CreateBuffer && getOperationModeFlag() == CREATE && m_PolyCreatableFlag == FALSE) {
				CFigure::CreateFlag createFlag = CFigure::FREECREATE;
				if (m_MouseVKFlags & MK_SHIFT) {
					createFlag = CFigure::REGULAR;
				}

				switch (m_InsertFlag)
				{
				case CGraphicEditorView::POLYLINE:
					((CPolyLine*)m_CreateBuffer)->draw(graphicsCanvas);		// 현재까지 생성된 것을 그림
					/*m_drawnArea = CGlobal::RectFToCRect(*/((CPolyLine*)m_CreateBuffer)->creating(graphicsCanvas, m_CurrPoint, createFlag);
					break;

				case CGraphicEditorView::CURVE:
					((CCurve*)m_CreateBuffer)->draw(graphicsCanvas);
					((CCurve*)m_CreateBuffer)->creating(graphicsCanvas, m_CurrPoint, createFlag);
					break;

				case CGraphicEditorView::POLYGON:
					((CPolygon*)m_CreateBuffer)->draw(graphicsCanvas);
					((CPolygon*)m_CreateBuffer)->creating(graphicsCanvas, m_CurrPoint, createFlag);
					break;

				//case CGraphicEditorView::CLOSEDCURVE:
				//	break;
				}
			}
		}
	

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
					CFigure::CreateFlag createFlag = CFigure::FREECREATE;
					if (m_MouseVKFlags & MK_SHIFT) {
						createFlag = CFigure::REGULAR;
					}

					if (m_CreateBuffer) {
						switch (m_InsertFlag)
						{
						/* LBUTTON CREATE LINE */
						case CGraphicEditorView::LINE:
							m_CreateBuffer->creating(graphicsCanvas, &m_LButtonPoint, &m_CurrPoint, createFlag);
							break;

						/* LBUTTON CREATE POLYLINE */
						//case CGraphicEditorView::POLYLINE:
						//	// 아무 동작을 하지 않음
						//break;

						/* LBUTTON CREATE PENCIL */
						case CGraphicEditorView::PENCIL:
							if (m_PolyCreatableFlag == FALSE) {
								((CPencil*)m_CreateBuffer)->addPoint(m_CurrPoint, createFlag);	// 점 추가
								((CPencil*)m_CreateBuffer)->draw(graphicsCanvas);				// 현재까지 생성된 것을 그림
							}
							break;

						///* LBUTTON CREATE CURVE */
						//case CGraphicEditorView::CURVE:
						//	// 아무 동작을 하지 않음
						//	break;

						/* LBUTTON CREATE ELLIPSE/RECTANGLE/STRING */
						case CGraphicEditorView::ELLIPSE:
							((CEllipse*)m_CreateBuffer)->creating(graphicsCanvas, &m_LButtonPoint, &m_CurrPoint, createFlag);
							break;

						case CGraphicEditorView::RECTANGLE:
							((CRectangle*)m_CreateBuffer)->creating(graphicsCanvas, &m_LButtonPoint, &m_CurrPoint, createFlag);
							break;

						case CGraphicEditorView::STRING:

							break;

						/* LBUTTON CREATE POLYGON/CLOSEDCURVE */
						//case CGraphicEditorView::POLYGON:
						//	// do nothing
						//	break;;

						//case CGraphicEditorView::CLOSEDCURVE:
						//	// do nothing
						//	break;
						}
					}
				} break;

				/** LBUTTON MOVE **/
				case CGraphicEditorView::MOVE: {			// 개체 이동
					CFigure::MoveFlag moveFlag = CFigure::FREEMOVE;
					if (m_MouseVKFlags & MK_SHIFT) {
						moveFlag = CFigure::FOURWAY;
					}

					m_SelectedFigures.moving(graphicsCanvas, m_LButtonPoint, m_CurrPoint, moveFlag);
				} break;

				/** LBUTTON RESIZE **/
				case CGraphicEditorView::RESIZE: {
					CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE;
					if (m_MouseVKFlags & MK_SHIFT) {		// 정비례 크기 변경 구현 후 주석 제거
						resizeFlag = CFigure::PROPORTIONAL;
					}
					
					if (m_SelectedFigures.hasOne()) {	// 현재 선택 개체 하나
						CFigure* figure = m_SelectedFigures.getOneFigure();

						if (m_EditPointFlag == TRUE) {	// 점 편집 상태 (RESIZE 상태에서 동작함)
							if (figure->IsKindOf(RUNTIME_CLASS(CLine))){			// CLine 점 이동
								((CLine*)figure)->pointMoving(graphicsCanvas, m_LButtonPoint, m_CurrPoint);
							}
							else if (figure->IsKindOf(RUNTIME_CLASS(CPolyLine))){	// CPolyLine 점 이동
								((CPolyLine*)figure)->pointMoving(graphicsCanvas, m_LButtonPoint, m_CurrPoint);
							}
							else if (figure->IsKindOf(RUNTIME_CLASS(CPolygon))){	// CPolygon 점 이동
								((CPolygon*)figure)->pointMoving(graphicsCanvas, m_LButtonPoint, m_CurrPoint);
							}
							else if (figure->IsKindOf(RUNTIME_CLASS(CCurve))){		// CCurve 점 이동
								((CCurve*)figure)->pointMoving(graphicsCanvas, m_LButtonPoint, m_CurrPoint);
							}
						}
						else {								// 개체 한 개 크기 변경
							figure->resizing(graphicsCanvas, m_selectedPosition, m_CurrPoint, resizeFlag);
						}
					}
					else {									// 현재 선택 개체 여러 개 크기 변경
						m_SelectedFigures.resizing(graphicsCanvas, m_selectedPosition, m_CurrPoint, resizeFlag);
					}
				} break;
			}
		} break;


		/*** RBUTTON ***/
		case CGraphicEditorView::RBUTTON: {
			if (m_MouseVKFlags & MK_CONTROL) {		// Ctrl 누르고 드래그

			}
			else if (m_MouseVKFlags & MK_SHIFT) {	// Shift 누르고 드래그

			}
			else {							// 보조키 누르지 않고 드래그

			}
		} break;

		case CGraphicEditorView::MBUTTON: {

		} break;
	}


	/**************************************** 더블 버퍼링 ****************************************/
	graphicsDC.DrawImage(&bmpCanvas, rect.left, rect.top, rect.right, rect.bottom);	// 캔버스 그리기
	/*********************************************************************************************/
}


/*** CGraphicEditorView 메시지 처리기 ***/

BOOL CGraphicEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CView::OnEraseBkgnd(pDC);
	return FALSE;	// 더블 버퍼링을 위하여 배경을 출력하지 않음
}


void CGraphicEditorView::OnDestroy()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CView::OnDestroy();
}

void CGraphicEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		/* CGraphicEditorDoc */
		CGraphicEditorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		
		Pen settedPen(pDoc->m_FigureSettings.m_OutlineColor, pDoc->m_FigureSettings.m_OutlineWidth);
		settedPen.SetDashStyle(pDoc->m_FigureSettings.m_OutlinePattern);
		
		SolidBrush solidBrush(pDoc->m_FigureSettings.m_FillColor);
		HatchBrush hatchBrush(pDoc->m_FigureSettings.m_FillPattern, pDoc->m_FigureSettings.m_FillSubcolor, pDoc->m_FigureSettings.m_FillColor);
		Brush* settedBrush = &solidBrush;

		switch (m_CurrentBrushType)
		{
		case Gdiplus::BrushTypeSolidColor:
			settedBrush = &solidBrush;
			break;

		case Gdiplus::BrushTypeHatchFill:
			settedBrush = &hatchBrush;
			break;

		//case Gdiplus::BrushTypeTextureFill:
		//
		//	break;

		//case Gdiplus::BrushTypePathGradient:
		//
		//	break;

		//case Gdiplus::BrushTypeLinearGradient:
		//
		//	break;
		}

		switch (getOperationModeFlag())
		{
			case CGraphicEditorView::SELECTABLE: {
				m_selectedPosition = m_SelectedFigures.select(m_CurrPoint);		// 전체 개체 리스트(그룹)을 순차로 순회
				// 선택 도형 갱신 (OUTSIDE/INSIDE 두 개의 값으로만 m_selectedPosition 갱신)
				// Invalidate 호출 (선택 영역을 그리기 위해)
				CFigure* figure;
				m_EditPointFlag = FALSE;
			} break;

			case CGraphicEditorView::SELECTED: {
				m_selectedPosition = m_SelectedFigures.contains(m_CurrPoint);	// 개체 내 선택 위치를 가져옴
				if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CText)))
					ShowCaret();
				if (m_selectedPosition == CFigure::OUTSIDE) {
					m_EditPointFlag = FALSE;
					if ((m_MouseVKFlags & MK_SHIFT) || (m_MouseVKFlags & MK_CONTROL)) {				// shift나 control을 누르고 드래그하면
						// 현재 리스트를 삭제하지 않고 추가
					}
					else{
							HideCaret();
						m_SelectedFigures.deselectAll();		// SELECTABLE 상태로 전환
					}
					m_selectedPosition = m_SelectedFigures.select(m_CurrPoint);
				}
			} break;

			case CGraphicEditorView::CREATE: {
				switch (m_InsertFlag)
				{
					/* CREATE 상태 */
				case CGraphicEditorView::LINE:
					preInsert();								// 이전 선택 개체 제거
					m_CreateBuffer = new CLine(&settedPen);	// 새로운 생성 개체 선택
					break;

				case CGraphicEditorView::POLYLINE:
					if (m_PolyCreatableFlag) {							// CPolyLine 객체 생성 가능 상태
						preInsert();									// 이전 선택 개체 제거
						m_CreateBuffer = new CPolyLine(&settedPen);	// 객체 생성
						m_PolyCreatableFlag = FALSE;					// CPolyLine 객체 생성 불가능 상태로 변경
					}
					((CPolyLine*)m_CreateBuffer)->addPoint(m_CurrPoint, CFigure::FREECREATE);	// 점 추가
					break;

				case CGraphicEditorView::PENCIL:
					if (m_PolyCreatableFlag) {							// CPolyLine 객체 생성 가능 상태
						preInsert();									// 이전 선택 개체 제거
						m_CreateBuffer = new CPencil(&settedPen);	// 객체 생성
						m_PolyCreatableFlag = FALSE;					// CPolyLine 객체 생성 불가능 상태로 변경
					}
					break;

				case CGraphicEditorView::CURVE:
					if (m_PolyCreatableFlag) {							// CCurve객체 생성 가능 상태
						preInsert();									// 이전 선택 개체 제거
						m_CreateBuffer = new CCurve(&settedPen);	            // 객체 생성
						m_PolyCreatableFlag = FALSE;					// CCurve 객체 생성 불가능 상태로 변경
					}
					((CCurve*)m_CreateBuffer)->addPoint(m_CurrPoint, CFigure::FREECREATE);	// 점 추가
					break;

				case CGraphicEditorView::ELLIPSE:
					preInsert();								// 이전 선택 개체 제거
					m_CreateBuffer = new CEllipse(&settedPen, settedBrush);
					break;

				case CGraphicEditorView::RECTANGLE:
					preInsert();								// 이전 선택 개체 제거
					m_CreateBuffer = new CRectangle(&settedPen, settedBrush);
					break;

				case CGraphicEditorView::STRING: {
					preInsert();// 이전 선택 개체 제거

					m_CreateBuffer = new CText(this, &settedPen, settedBrush);
					FontFamily fontfamily(pDoc->m_FigureSettings.m_FontName);
					Gdiplus::Font font(&fontfamily, pDoc->m_FigureSettings.m_FontSize, FontStyleRegular, UnitPixel);
					((CText*)m_CreateBuffer)->setFont(&font);
					((CText*)m_CreateBuffer)->setFontBrush(&SolidBrush(pDoc->m_FigureSettings.m_FontColor));
					} break;

				case CGraphicEditorView::POLYGON:
					if (m_PolyCreatableFlag) {							// CPolygon객체 생성 가능 상태
						preInsert();									// 이전 선택 개체 제거
						m_CreateBuffer = new CPolygon(&settedPen, settedBrush);		// 객체 생성
						m_PolyCreatableFlag = FALSE;					// CPolygon 객체 생성 불가능 상태로 변경
					}
					((CPolygon*)m_CreateBuffer)->addPoint(m_CurrPoint, CFigure::FREECREATE);	// 점 추가

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

		// 비 클라이언트 영역 마우스 캡쳐
		SetCapture();

		/*********** 이 부분은 변경하지 마시오. ***********/
		m_LButtonPoint = m_CurrPoint;	// 이벤트 발생 좌표
		m_MouseButtonFlag = LBUTTON;	// 좌클릭 드래그 중
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

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		switch (getOperationModeFlag())
		{
			case CGraphicEditorView::SELECTABLE: {
				m_SelectedFigures.select(m_SelectArea);		// 전체 개체 리스트(그룹)을 순차로 순회
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

			/* CREATE 상태 */
			case CGraphicEditorView::CREATE: {
				CFigure::CreateFlag createFlag = CFigure::FREECREATE;
				if (m_MouseVKFlags & MK_SHIFT) {
					createFlag = CFigure::REGULAR;
				}

				switch (m_InsertFlag)
				{
				case CGraphicEditorView::LINE:
					m_CreateBuffer->create(&m_LButtonPoint, &m_CurrPoint, createFlag);
					postInsert();
					break;

				case CGraphicEditorView::POLYLINE:
					// 아무 동작도 하지 않음 //((CPolyLine*)m_CurrentFigure)->addPoint(m_CurrPoint, CFigure::FREECREATE);
					break;

				case CGraphicEditorView::PENCIL:
					((CPencil*)m_CreateBuffer)->create(createFlag);
					m_PolyCreatableFlag = TRUE;
					postInsert();
					break;

				case CGraphicEditorView::CURVE:
					// 아무 동작도 하지 않음
					break;

				case CGraphicEditorView::ELLIPSE:
					m_CreateBuffer->create(&m_LButtonPoint, &m_CurrPoint, createFlag);
					postInsert();
					break;

				case CGraphicEditorView::RECTANGLE:
					m_CreateBuffer->create(&m_LButtonPoint, &m_CurrPoint, createFlag);
					postInsert();
					break;

				case CGraphicEditorView::STRING:
					m_CreateBuffer->create(&m_LButtonPoint, &m_CurrPoint, createFlag);
					clearInsertFlag();
					postInsert();
					m_SelectedFigures.select();
					break;

				case CGraphicEditorView::POLYGON:
					// 아무 동작도 하지 않음 //((CPolyLine*)m_CurrentFigure)->addPoint(m_CurrPoint, createFlag);
					break;

				case CGraphicEditorView::CLOSEDCURVE:
					break;
				}
			} break;

			case CGraphicEditorView::MOVE: {
				CFigure::MoveFlag moveFlag = CFigure::FREEMOVE;
				if (m_MouseVKFlags & MK_SHIFT) {
					moveFlag = CFigure::FOURWAY;
				}

				m_SelectedFigures.move(m_LButtonPoint, m_CurrPoint, moveFlag);
				m_selectedPosition = CFigure::OUTSIDE;
			} break;

			case CGraphicEditorView::RESIZE: {
				CFigure::ResizeFlag resizeFlag = CFigure::FREERESIZE;
				if (m_MouseVKFlags & MK_SHIFT) {		// 정비례 크기 변경 구현 후 주석 제거
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

		// 데이터가 수정되었음을 도큐먼트 객체에 알림
		GetDocument()->SetModifiedFlag();

		Invalidate();

		// 마우스 캡쳐를 종료함
		::ReleaseCapture();

		/*********** 이 부분은 변경하지 마시오. ***********/
		m_LButtonPoint = m_CurrPoint;	// 이벤트 발생 좌표
		m_MouseButtonFlag = NBUTTON;	// 비클릭 상태
		/**************************************************/

		CView::OnLButtonUp(nFlags, point);
	}
}

void CGraphicEditorView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_RBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

		// 더블클릭하면 폴리라인 생성 완료
		if (m_InsertFlag == CGraphicEditorView::POLYLINE /* && m_SelectedFigures.hasOne()*/) {
			((CPolyLine*)m_CreateBuffer)->create(CFigure::FREECREATE);
			
			m_PolyCreatableFlag = TRUE;
			postInsert();
			//clearInsertFlag();
		}
		else if (m_InsertFlag == CGraphicEditorView::CURVE/* && m_SelectedFigures.hasOne()*/) {
			((CCurve*)m_CreateBuffer)->create(CFigure::FREECREATE);
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


		/*********** 이 부분은 변경하지 마시오. ***********/
		m_LButtonPoint = m_CurrPoint;	// 이벤트 발생 좌표
		//m_MouseButtonFlag = NBUTTON;	// 좌클릭
		/**************************************************/

		CView::OnLButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


		/*********** 이 부분은 변경하지 마시오. ***********/
		m_RButtonPoint = m_CurrPoint;	// 이벤트 발생 좌표
		m_MouseButtonFlag = RBUTTON;	// 우클릭 드래그 중
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

		/*********** 이 부분은 변경하지 마시오. ***********/
		m_RButtonPoint = m_CurrPoint;	// 이벤트 발생 좌표
		m_MouseButtonFlag = NBUTTON;	// 비클릭 상태
		/**************************************************/
	}
}

void CGraphicEditorView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_MouseButtonFlag && !(nFlags & MK_LBUTTON)) {

		m_CurrPoint = CGlobal::CPointToPointF(point);
		m_MouseVKFlags = nFlags;

		// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.



		/*********** 이 부분은 변경하지 마시오. ***********/
		m_RButtonPoint = m_CurrPoint;	// 이벤트 발생 좌표
		m_MouseButtonFlag = NBUTTON;	// 우클릭
		/**************************************************/

		CView::OnRButtonDblClk(nFlags, point);
	}
}

void CGraphicEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//CView::OnMouseMove(nFlags, point);

	m_CurrPoint = CGlobal::CPointToPointF(point);
	m_MouseVKFlags = nFlags;

	switch (getOperationModeFlag())
	{
	case CGraphicEditorView::SELECTABLE:
		if (m_MouseButtonFlag == LBUTTON) {

			// 드래그 영역
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
			// 여기까지 드래그 영역
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CView::OnMouseWheel(nFlags, zDelta, point);
}

BOOL CGraphicEditorView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nHitTest == HTCLIENT) {
		CPoint point;
		::GetCursorPos(&point);		// 스크린좌표
		ScreenToClient(&point);		// 클라이언트좌표로변환

		CFigure::Position PosAtAll = GetDocument()->m_FiguresList.pointInFigure(m_CurrPoint);

		switch (getOperationModeFlag())
		{
		case CGraphicEditorView::SELECTED:
			switch (m_SelectedFigures.contains(m_CurrPoint))
			{
			case CFigure::OUTSIDE:
				if (PosAtAll == CFigure::INSIDE) {
					::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
				}
				else {
					::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
				}
				break;

			case CFigure::INSIDE:
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
				break;

				//case CFigure::ONHANDLE:
			case CFigure::START:
			case CFigure::END:
			case CFigure::TOPLEFT:
			case CFigure::BOTTOMRIGHT:
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
				break;

			case CFigure::TOP:
			case CFigure::BOTTOM:
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
				break;

			case CFigure::TOPRIGHT:
			case CFigure::BOTTOMLEFT:
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
				break;

			case CFigure::RIGHT:
			case CFigure::LEFT:
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
				break;
			}
			break;

		case CGraphicEditorView::SELECTABLE:
			if (PosAtAll == CFigure::INSIDE) {
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
			}
			else {
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			}
			break;

		case CGraphicEditorView::CREATE:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
			break;

		case CGraphicEditorView::MOVE:
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
			break;

		case CGraphicEditorView::RESIZE:
			switch (m_selectedPosition)
			{
			//case CFigure::ONHANDLE:
			case CFigure::START:
			case CFigure::END:
			case CFigure::TOPLEFT:
			case CFigure::BOTTOMRIGHT:
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
				break;

			case CFigure::TOP:
			case CFigure::BOTTOM:
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
				break;

			case CFigure::TOPRIGHT:
			case CFigure::BOTTOMLEFT:
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
				break;

			case CFigure::RIGHT:
			case CFigure::LEFT:
				::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
				break;
			}
			break;
		}
		return TRUE;
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CGraphicEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_ESCAPE:
	case VK_CANCEL:
		switch (getOperationModeFlag())
		{
		case CGraphicEditorView::SELECTABLE:
			break;
		case CGraphicEditorView::SELECTED:
			m_SelectedFigures.deselectAll();
			break;
		case CGraphicEditorView::CREATE:
		cancelInsert();
		break;
		case CGraphicEditorView::MOVE:
			m_SelectedFigures.deselectAll();
			break;
		case CGraphicEditorView::RESIZE:
			m_SelectedFigures.deselectAll();
			break;
		default:
			break;
		}
		break;
	case VK_DELETE:
		OnEditDelete();
		break;
	//case 'A':
	//case 'a':
	//	if (nFlags & 13) {
	//		m_SelectedFigures.selectAll();
	//		Invalidate();
	//	}
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CText* text = NULL;

	switch (getOperationModeFlag())
	{
	case CGraphicEditorView::SELECTABLE:
		break;

	case CGraphicEditorView::SELECTED:
	case CGraphicEditorView::RESIZE:
	if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf((RUNTIME_CLASS(CText)))) {
			text = (CText*)m_SelectedFigures.getOneFigure();
		}
		break;

	case CGraphicEditorView::CREATE:
		if (m_CreateBuffer && m_CreateBuffer->IsKindOf((RUNTIME_CLASS(CText)))) {
			text = (CText*)m_CreateBuffer;
		}
		break;

	case CGraphicEditorView::MOVE:
		break;

	
	}
	
	if (text) {
		switch (nChar) {
			// 백스페이스 입력시
		case VK_BACK:
			//((CText*)m_SelectedFigures.getOneFigure())->delChar(); // 문자삭제
			text->delChar();
			Invalidate();
			break;
			// 한줄 입력이므로 엔터키는 배열에 들어가지 않아도됨
		case VK_RETURN:
		case VK_CONTROL:
			break;
			// 위의 케이스를 제외한 문자저장
		default:
			text->addChar(nChar);
			Invalidate();
			break;
		}
	CView::OnChar(nChar, nRepCnt, nFlags);
	}
}

void CGraphicEditorView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnSysChar(nChar, nRepCnt, nFlags);
}


void CGraphicEditorView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGraphicEditorView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnContextMenu(CWnd* pWnd, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


/*** CGraphicEditorView 작업 ***/

void CGraphicEditorView::preInsert()	// 삽입(생성) 작업 전에 해야 할 작업
{
	m_SelectedFigures.deselectAll();	// 선택 개체 제거
}

void CGraphicEditorView::postInsert()	// 삽입(생성) 작업 후에 해야 할 작업
{
	GetDocument()->m_FiguresList.AddHead(m_CreateBuffer);	// 전체 개체 리스트에 추가
	//m_SelectedFigures.select();
	//m_selectedPosition = CFigure::OUTSIDE;
	m_CreateBuffer = NULL;
}

void CGraphicEditorView::cancelInsert()	// 삽입(생성) 작업 취소 시에 해야 할 작업
{
	setOperationModeFlag(SELECTABLE);
	if (m_CreateBuffer) {
		m_CreateBuffer->destroy();
	}
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
		
	 $	m_InsertFlag, m_SelectedFigures, m_selectedPosition에 종속적이다.

	 $	SELECTABLE:	CREATE 상태가 아니면서 선택된 개체가 없는 상태이다.
		SELECTED:	개체가 선택된 상태로 연산을 하지 않고 있는 상태이다.
		CREATE:		삽입 버튼이 눌려있는 상태이다.
		MOVE:		선택한 개체가 있으면서 개체 내부의 점을 선택한 상태이다. 
		RESIZE:		선택한 개체가 있으면서 개체의 핸들을 선택한 상태이다.
		//WRITE:		CText 객체에 문자열을 입력하는 상태이다.

	 $	선택한 개체가 없을 경우 m_selectedPosition을 "핸들 위"로 갱신하지 않도록 하여,
		임의 개체의 첫 번째 클릭에서 크기 변경을 막는다.

	 $	ButtonDown에서 m_selectedPosition을 "핸들 위(선택한 개체가 있을 경우만)"
		또는 "CFigure::INSIDE"로 갱신하고,
		ButtonUp에서 m_selectedPosition을 "CFigure::OUTSIDE"로 갱신하여,
		SELECTED 상태를 얻을 수 있도록 한다.
	 */

	// 삽입 버튼이 눌려있으면,
	if (m_InsertFlag != NONE) {
		return CREATE;	// CREATE 상태
	}

	// 선택된 개체가 있을 때,
	if (!m_SelectedFigures.isEmpty()) {
		if (m_selectedPosition & CFigure::ONHANDLE) {		// 선택 위치가 핸들이면,
			return RESIZE;									// RESIZE 상태
		}

		else if (m_selectedPosition == CFigure::INSIDE) {	// 선택 위치가 내부면,
			return MOVE;									// MOVE 상태
		}

		//else if (m_selectedPosition == CFigure::OUTSIDE) {
		//	return SELECTED;
		//}
		//
		//else if (m_SelectedFigures.hasOneFigure() && m_SelectedFigures.GetHead()->IsKindOf((RUNTIME_CLASS(CText)))) {
		//
		//}

		return SELECTED;									// 이외의 경우, SELECTED 상태
	}

	// 삽입 버튼이 눌려있지 않으면서, 선택된 개체가 없으면,
	return SELECTABLE;	// SELECTABLE 상태
}

void CGraphicEditorView::setOperationModeFlag(OperationModeFlag operationModeFlag/* = SELECTABLE*/)
{
	switch (operationModeFlag)
	{
	case CGraphicEditorView::SELECTABLE:
	m_InsertFlag = NONE;
		m_selectedPosition = CFigure::OUTSIDE;
		HideCaret();
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
		if (m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolyLine)) && !m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPencil))
			|| m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolygon))) {
			return TRUE;
		}
	}

	return FALSE;
}


/*** CGraphicEditorView 인쇄 ***/

void CGraphicEditorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CGraphicEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CGraphicEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


/*** CGraphicEditorView 진단 ***/

#ifdef _DEBUG
void CGraphicEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicEditorDoc* CGraphicEditorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicEditorDoc)));
	return (CGraphicEditorDoc*)m_pDocument;
}
#endif //_DEBUG


/*** CGraphicEditorView 추가로 생성된 명령, 메시지 처리기 및 재정의 ***/

