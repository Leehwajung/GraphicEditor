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

// Graphic Editor View Commands.cpp : CGraphicEditorView 클래스의 구현 (명령 메시지 처리기)
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Graphic Editor.h"
#endif

#include "Graphic Editor Doc.h"
#include "Graphic Editor View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Text.h"


/*** CGraphicEditorView 명령 메시지 처리기 ***/

// void CGraphicEditorView::OnFilePrintPreview() {}
// 이 처리기는 "Graphic Editor View.cpp"에서 구현됨. ("CGraphicEditorView 인쇄" 참고)

//void CGraphicEditorView::OnEditClear()
//{
//	clearInsertFlag();
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}

//void CGraphicEditorView::OnEditClearAll()
//{
//	clearInsertFlag();
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}


void CGraphicEditorView::OnEditCopy()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGraphicEditorDoc* pDoc = GetDocument();
	CFigure* figure;
	
	m_BufferList.RemoveAll();//복사가 일어남으로 그동안 저장되어있던 리스트를 비워줌.

	/* 단, m_FiguresList에는 계속 존재해야하므로 삭제하지 않음.*/
	if (m_SelectedFigures.hasOne()){//하나가 선택된 경우
		figure = m_SelectedFigures.getOneFigure();
		m_BufferList.AddTail(figure->clone());//figure를 추가해줌
	}

	else // 다중 선택 case
	{
		//정적 배열을 얻어옴
		const POSITION* positionArray = m_SelectedFigures.getData();
		for (int i = 0; i < m_SelectedFigures.getSize(); i++)// 저장된 수만큼
		{
			figure = pDoc->m_FiguresList.GetAt(positionArray[i]);
			m_BufferList.AddTail(figure->clone());
	}
}
}

void CGraphicEditorView::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(getCopyableFlag());
}

void CGraphicEditorView::OnEditCut()//잘라내기
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGraphicEditorDoc* pDoc = GetDocument();
	CFigure* figure;
	m_BufferList.RemoveAll();//잘라내기 발생. 그동안 저장되어있던 리스트를 비워줌.
	
	if (m_SelectedFigures.hasOne()){
		//삭제할위치를 얻기위해
		POSITION deletePos = m_SelectedFigures.getForwardPos();
		figure = m_SelectedFigures.getOneFigure();
		m_BufferList.AddTail(figure);//figure를 추가해줌
		m_SelectedFigures.deselect(deletePos);
		pDoc->m_FiguresList.RemoveAt(deletePos);//원본 리스트에서 삭제
	}
	else{// 다중
		//정적 배열을 얻어옴
		const POSITION* positionArray = m_SelectedFigures.getData();
		for (int i = 0; i < m_SelectedFigures.getSize(); i++)// 저장된 수만큼
	{
			figure = pDoc->m_FiguresList.GetAt(positionArray[i]);
			m_BufferList.AddTail(figure->clone());
			pDoc->m_FiguresList.RemoveAt(positionArray[i]);//원본 리스트에서 삭제
		}
		m_SelectedFigures.deselectAll();
	}
	Invalidate();//잘라내기를 했으므로, 뷰에서 지워짐
}

void CGraphicEditorView::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(getCopyableFlag());
}

//void CGraphicEditorView::OnEditFind()
//{
//	clearInsertFlag();
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}

void CGraphicEditorView::OnEditPaste()//붙여넣기
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CGraphicEditorDoc* pDoc = GetDocument();
	CFigure* figure;
	POSITION headpos = m_BufferList.GetHeadPosition();
	//m_BufferList에 있는 것들을 ist에 추가해서 그릴 것
	
	if (m_BufferList.hasOneFigure()){//하나가 저장되어있는 경우
		CFigure* figure = m_BufferList.GetHead();
		pDoc->m_FiguresList.AddHead(figure->clone());//figure를 추가해줌
		m_SelectedFigures.select();
	}

	else{//다중 저장
		//CFigure* figure = m_BufferList.GetHead();
		for (int i = 0; i < m_BufferList.GetCount(); i++)// 저장된 수만큼
		{
			figure = m_BufferList.GetAt(headpos);
			m_BufferList.GetNext(headpos);
			pDoc->m_FiguresList.AddHead(figure->clone());//figure를 추가해
			m_SelectedFigures.select();
		}
	}
	Invalidate();
}

void CGraphicEditorView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(getPastableFlag());
}

void CGraphicEditorView::OnEditDelete()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 
	CGraphicEditorDoc* pDoc = GetDocument();

	if (m_SelectedFigures.hasOne()){
		//삭제할위치를 얻기위해
		POSITION deletePos = m_SelectedFigures.getForwardPos();
		m_SelectedFigures.deselect(deletePos);
		pDoc->m_FiguresList.RemoveAt(deletePos);//원본 리스트에서 삭제
	}
	else{// 다중
		//정적 배열을 얻어옴
		const POSITION* positionArray = m_SelectedFigures.getData();
		for (int i = 0; i < m_SelectedFigures.getSize(); i++)// 저장된 수만큼
		{
			pDoc->m_FiguresList.RemoveAt(positionArray[i]);//원본 리스트에서 삭제
		}
		m_SelectedFigures.deselectAll();
	}
	HideCaret();//
	Invalidate();//잘라내기를 했으므로, 뷰에서 지워짐
}

void CGraphicEditorView::OnUpdateEditDelete(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(getDeletableFlag());
}

//void CGraphicEditorView::OnEditRepeat()
//{
//	clearInsertFlag();
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}

//void CGraphicEditorView::OnEditReplace()
//{
//	clearInsertFlag();
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}

void CGraphicEditorView::OnEditSelectAll()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	m_SelectedFigures.selectAll();
	Invalidate();
}

void CGraphicEditorView::OnEditUndo()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnEditRedo()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnImageCanvasSize()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertLine()
{
	//m_SelectedFigures.deselectAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = LINE;			// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	// 테스트입니다!!
}

void CGraphicEditorView::OnUpdateInsertLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == LINE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertPolyline()
{
	//m_SelectedFigures.deselectAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = POLYLINE;		// 수정 금지
	m_PolyCreatableFlag = TRUE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertPolyline(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == POLYLINE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertPencil()
{
	//m_SelectedFigures.deselectAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = PENCIL;			// 수정 금지
	m_PolyCreatableFlag = TRUE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertPencil(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == PENCIL);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertCurve()
{
	//m_SelectedFigures.deselectAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = CURVE;			// 수정 금지
	m_PolyCreatableFlag = TRUE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertCurve(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == CURVE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertEllipse()
{
	//m_SelectedFigures.deselectAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = ELLIPSE;			// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertEllipse(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == ELLIPSE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertRectangle()
{
	//m_SelectedFigures.deselectAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = RECTANGLE;		// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == RECTANGLE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertString()
{
	//m_SelectedFigures.deselectAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = STRING;			// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertString(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == STRING);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertPolygon()	// 다각형 버튼
{
	//m_SelectedFigures.deselectAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = POLYGON;			// 수정 금지
	m_PolyCreatableFlag = TRUE;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertPolygon(CCmdUI *pCmdUI)	// 다각형 버튼
{
	pCmdUI->SetCheck(m_InsertFlag == POLYGON);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnInsertClosedcurve()	// 도형 버튼
{
	//m_SelectedFigures.deselectAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = CLOSEDCURVE;		// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertClosedcurve(CCmdUI *pCmdUI)	// 도형 버튼
{
	pCmdUI->SetCheck(m_InsertFlag == CLOSEDCURVE);	// 수정 금지
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeOrder()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateArrangeOrder(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->Enable(FALSE);
}

void CGraphicEditorView::OnArrangeBringFront()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateArrangeBringFront(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeSendBack()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateArrangeSendBack(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeBringForward()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateArrangeBringForward(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeSendBackward()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateArrangeSendBackward(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeGrouping()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	GetDocument()->m_FiguresList.AddHead(new CGroup(m_SelectedFigures));

	Invalidate();
}

void CGraphicEditorView::OnUpdateArrangeGrouping(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(getGroupableFlag() || getUngroupableFlag());
}

void CGraphicEditorView::OnArrangeGroup()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	GetDocument()->m_FiguresList.AddHead(new CGroup(m_SelectedFigures));

	Invalidate();
	//for (POSITION pos = figurelist->GetTailPosition(); pos; figurelist->GetPrev(pos)) {
	//	m_CurrentFigures.InsertAfter(pos, figurelist->GetAt(subpos));
	//}

	//m_SelectedFigures.deselectAll();
	//m_CurrentFigures.AddTail(GetDocument()->m_FiguresList.GetHead());
}

void CGraphicEditorView::OnUpdateArrangeGroup(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(getGroupableFlag());
}

void CGraphicEditorView::OnArrangeUngroup()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//for (POSITION pos = m_CurrentFigures.GetHeadPosition(); pos; m_CurrentFigures.GetNext(pos)) {
	//	if (m_CurrentFigures.GetAt(pos)->IsKindOf(RUNTIME_CLASS(CGroup))) {
	//		CFigurePtrList* figurelist = &((CGroup*)m_CurrentFigures.GetAt(pos))->getFiguresList();

	//		for (POSITION subpos = figurelist->GetTailPosition(); subpos; figurelist->GetPrev(subpos)) {
	//			m_CurrentFigures.InsertAfter(pos, figurelist->GetAt(subpos));
	//		}
	//		
	//	}
	//}

	m_SelectedFigures.unGroup();
	Invalidate();
}

void CGraphicEditorView::OnUpdateArrangeUngroup(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(getUngroupableFlag());
}

void CGraphicEditorView::OnZoomIn()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnZoomOut()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnZoom100()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateZoom100(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnOutlineColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	ASSERT_VALID(m_WndRibbonBar);

	CMFCRibbonColorButton* pColor = DYNAMIC_DOWNCAST(
		CMFCRibbonColorButton, m_WndRibbonBar->FindByID(ID_OUTLINE_COLOR));

	Color color;
	color.SetFromCOLORREF(pColor->GetColor());
	GetDocument()->m_FigureSettings.m_OutlineColor = color;
	m_SelectedFigures.setOutlineColor(color);

	Invalidate();
}

void CGraphicEditorView::OnUpdateOutlineColor(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	//if (!m_SelectedFigures.isEmpty()) {
	//	CMFCRibbonColorButton* pColor = DYNAMIC_DOWNCAST(
	//		CMFCRibbonColorButton, m_WndRibbonBar->FindByID(ID_OUTLINE_COLOR));
	//	pColor->SetColor(m_SelectedFigures.getOneFigure()->get)
	//}
}

void CGraphicEditorView::OnOutlineWidth()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	ASSERT_VALID(m_WndRibbonBar);

	CMFCRibbonEdit* pSpin = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_WndRibbonBar->FindByID(ID_OUTLINE_WIDTH));
	REAL OutlineWidth = _wtof(pSpin->GetEditText());

	GetDocument()->m_FigureSettings.m_OutlineWidth = OutlineWidth;

	if (!m_SelectedFigures.isEmpty()) {
		m_SelectedFigures.getOneFigure()->setOutlineWidth(OutlineWidth);
	}

	Invalidate();
}


void CGraphicEditorView::OnUpdateOutlineWidth(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnOutlinePattern()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	ASSERT_VALID(m_WndRibbonBar);

	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(
		CMFCRibbonComboBox, m_WndRibbonBar->FindByID(ID_OUTLINE_PATTERN));
	// Get the selected index
	int nCurSel = pComboBox->GetCurSel();
	if (nCurSel >= 0)
	{
		CString item = pComboBox->GetItem(nCurSel);
		DashStyle dashStyle;

		//if (item.Compare(_T("Solid"))) {
		//	dashStyle = DashStyleSolid;
		//}
		//else if (item.Compare(_T("Dash"))) {
		//	dashStyle = DashStyleDash;
		//}
		//else if (item.Compare(_T("Dot"))) {
		//	dashStyle = DashStyleDot;
		//}
		//else if (item.Compare(_T("Dash-Dot"))) {
		//	dashStyle = DashStyleDashDot;
		//}
		//else if (item.Compare(_T("Dash-Dot-Dot"))) {
		//	dashStyle = DashStyleDashDotDot;
		//}
		dashStyle = (DashStyle)nCurSel;

		GetDocument()->m_FigureSettings.m_OutlinePattern = dashStyle;

		if (!m_SelectedFigures.isEmpty()) {
			m_SelectedFigures.setOutlinePattern(dashStyle);
		}
	}

	Invalidate();
}


void CGraphicEditorView::OnUpdateOutlinePattern(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnFillColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	ASSERT_VALID(m_WndRibbonBar);

	CMFCRibbonColorButton* pColor = DYNAMIC_DOWNCAST(
		CMFCRibbonColorButton, m_WndRibbonBar->FindByID(ID_FILL_COLOR));
	
	Color color;
	color.SetFromCOLORREF(pColor->GetColor());
	GetDocument()->m_FigureSettings.m_FillColor = color;
	if (!m_SelectedFigures.isEmpty()) {
		m_SelectedFigures.setFillColor(color);
	}

	Invalidate();
}


void CGraphicEditorView::OnUpdateFillColor(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnFillSubcolor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	ASSERT_VALID(m_WndRibbonBar);

	CMFCRibbonColorButton* pColor = DYNAMIC_DOWNCAST(
		CMFCRibbonColorButton, m_WndRibbonBar->FindByID(ID_FILL_SUBCOLOR));

	Color color;
	color.SetFromCOLORREF(pColor->GetColor());
	GetDocument()->m_FigureSettings.m_FillSubcolor = color;
	if (!m_SelectedFigures.isEmpty()) {
		m_SelectedFigures.setFillSubcolor(color);
	}

	Invalidate();
}


void CGraphicEditorView::OnUpdateFillSubcolor(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnFillPattern()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	ASSERT_VALID(m_WndRibbonBar);

	CMFCRibbonComboBox* pComboBox = DYNAMIC_DOWNCAST(
		CMFCRibbonComboBox, m_WndRibbonBar->FindByID(ID_FILL_PATTERN));
	// Get the selected index
	int nCurSel = pComboBox->GetCurSel();
	if (nCurSel >= 0)
	{
		CString item = pComboBox->GetItem(nCurSel);

		switch (nCurSel)
		{
			case 0: {	// SolidBrush
				m_CurrentBrushType = BrushTypeSolidColor;
				if (!m_SelectedFigures.isEmpty()) {
					m_SelectedFigures.setFillBrush(&SolidBrush(GetDocument()->m_FigureSettings.m_FillColor), TRUE);
				}
			} break;

				//Linear - Gradient;
			//case 1: {	// LinearGradientBrush
			//	m_CurrentBrushType = BrushTypeLinearGradient;
			//	if (!m_SelectedFigures.isEmpty()) {
			//		m_SelectedFigures.setFillBrush(&LinearGradientBrush(RectF(100, 100, 100, 100), GetDocument()->m_FigureSettings.m_FillColor, GetDocument()->m_FigureSettings.m_FillSubcolor, LinearGradientModeHorizontal/*GetDocument()->m_FigureSettings.m_FillGradientAngle*/), TRUE);
			//	}
			//} break;

			default: {	// HatchBrush
				m_CurrentBrushType = BrushTypeHatchFill;
				HatchStyle hatchStyle = (HatchStyle)(nCurSel - 1);
				GetDocument()->m_FigureSettings.m_FillPattern = hatchStyle;

				if (!m_SelectedFigures.isEmpty()) {
					m_SelectedFigures.setFillBrush(&HatchBrush(hatchStyle, GetDocument()->m_FigureSettings.m_FillSubcolor, GetDocument()->m_FigureSettings.m_FillColor), TRUE);
					m_SelectedFigures.setFillPattern(hatchStyle);
				}
			} break;
		}
	}

	Invalidate();
}


void CGraphicEditorView::OnUpdateFillPattern(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnPositionVertical()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnUpdatePositionVertical(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnPositionHorizontal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnUpdatePositionHorizontal(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnSizeHeight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnUpdateSizeHeight(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnSizeWidth()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnUpdateSizeWidth(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnFontCharset()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	ASSERT_VALID(m_WndRibbonBar);

	CMFCRibbonFontComboBox* pFontComboBox = DYNAMIC_DOWNCAST(
		CMFCRibbonFontComboBox, m_WndRibbonBar->FindByID(ID_FONT_CHARSET));
	// Get the selected index
	int nCurSel = pFontComboBox->GetCurSel();
	if (nCurSel >= 0)
	{
		CString item = pFontComboBox->GetItem(nCurSel);

		GetDocument()->m_FigureSettings.m_FontName = item;
		if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CText))) {

			FontFamily fontfamily(GetDocument()->m_FigureSettings.m_FontName);
			Gdiplus::Font font(&fontfamily, GetDocument()->m_FigureSettings.m_FontSize, FontStyleRegular, UnitPixel);

			((CText*)m_SelectedFigures.getOneFigure())->setFont(&font);
		}
	}

	Invalidate();
}


void CGraphicEditorView::OnUpdateFontCharset(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnFontSize()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CMFCRibbonEdit* pSpin = DYNAMIC_DOWNCAST(CMFCRibbonEdit, m_WndRibbonBar->FindByID(ID_FONT_SIZE));
	REAL fontSize = _wtof(pSpin->GetEditText());
	
	GetDocument()->m_FigureSettings.m_FontSize = fontSize;

	if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CText))) {

		FontFamily fontfamily(GetDocument()->m_FigureSettings.m_FontName);
		Gdiplus::Font font(&fontfamily, fontSize, FontStyleRegular, UnitPixel);

		((CText*)m_SelectedFigures.getOneFigure())->setFont(&font);
	}

	Invalidate();
}


void CGraphicEditorView::OnUpdateFontSize(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnFontBold()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnUpdateFontBold(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnFontItalic()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnUpdateFontItalic(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnFontUnderline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnUpdateFontUnderline(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CGraphicEditorView::OnFontColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	ASSERT_VALID(m_WndRibbonBar);

	CMFCRibbonColorButton* pColor = DYNAMIC_DOWNCAST(
		CMFCRibbonColorButton, m_WndRibbonBar->FindByID(ID_FONT_COLOR));

	Color color;
	color.SetFromCOLORREF(pColor->GetColor());
	GetDocument()->m_FigureSettings.m_FontColor = color;

	if (/*m_SelectedFigures.hasOne() && */m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CText))) {

		//FontFamily fontfamily(GetDocument()->m_FigureSettings.m_FontName);
		//Gdiplus::Font font(&fontfamily, GetDocument()->m_FigureSettings.m_FontSize, FontStyleRegular, UnitPixel);

		((CText*)m_SelectedFigures.getOneFigure())->setFontBrush(&SolidBrush(color));
	}
	m_SelectedFigures.setFillSubcolor(color);

	Invalidate();
}


void CGraphicEditorView::OnUpdateFontColor(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnPointmove()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	m_EditPointFlag = m_EditPointFlag ? FALSE : TRUE;
	
		Invalidate();
	}

void CGraphicEditorView::OnUpdatePointmove(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(getLineSelectedFlag() || getPolySelectedFlag());
	pCmdUI->SetText(m_EditPointFlag ? _T("점 편집 해제") : _T("점 편집"));
}

void CGraphicEditorView::OnPolyIndividualInsert()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_SelectedFigures.hasOne()) {
		if (m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolyLine)))
		((CPolyLine*)m_SelectedFigures.getOneFigure())->InsertPoint(m_RButtonPoint);

		else if (m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolygon)))
			((CPolygon*)m_SelectedFigures.getOneFigure())->InsertPoint(m_RButtonPoint);
		Invalidate();
	}
}

void CGraphicEditorView::OnUpdatePolyIndividualInsert(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(m_EditPointFlag /*&& (m_selectedPosition == CFigure::INSIDE) */&& getPolySelectedFlag());
}

void CGraphicEditorView::OnPolyIndividualDelete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_SelectedFigures.hasOne()) {
		if (m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolyLine))){
		CPolyLine* polyLine = (CPolyLine*)m_SelectedFigures.getOneFigure();

		if (polyLine->GetPointsList().GetSize() == 1){
			polyLine->destroy();
		}
		else 
			(polyLine)->RemovePoint(m_RButtonPoint);
		}
		else if (m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolygon))){
			CPolygon* polygon = (CPolygon*)m_SelectedFigures.getOneFigure();

			if (polygon->GetPointsList().GetSize() == 1){
				polygon->destroy();
			}
			else
				(polygon)->RemovePoint(m_RButtonPoint);
		}
	Invalidate();
}
}

void CGraphicEditorView::OnUpdatePolyIndividualDelete(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	pCmdUI->Enable(m_EditPointFlag /*&& (m_selectedPosition & CFigure::ONHANDLE) */&& getPolySelectedFlag());
}

