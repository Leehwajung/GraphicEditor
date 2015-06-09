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
	
	pDoc->m_BufferList.RemoveAll();//복사가 일어남으로 그동안 저장되어있던 리스트를 비워줌.
	if (m_CurrentFigures.hasOneFigure()){//하나가 선택된 경우
		// 선택된 도형을 m_BufferList에 복사한다.
		//pDoc->m_BufferList.AddTail(); //단, m_FiguresList에는 계속 존재
}

	else // 다중 선택 case
	{
	}
	
	//
}

void CGraphicEditorView::OnEditCut()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CGraphicEditorDoc* pDoc = GetDocument();
	POSITION deletePos = pDoc->m_FiguresList.GetHeadPosition(); //삭제할위치를 얻기위해
	
	while (deletePos != NULL)
	{
		pDoc->m_FiguresList.GetNext(deletePos); // 삭제할 위치를 찾을 때까지
		//if ()// deletepos와 선택된 도형이 맞으면 break;
	}
	//pDoc->m_BufferList.AddTail();//원본리스트에서 버퍼리스트로 복사
	pDoc->m_FiguresList.deleteAt(deletePos);//원본 리스트에서 삭제

	Invalidate();//잘라내기를 했으므로, 뷰에서 지워짐
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
	POSITION headpos = pDoc->m_BufferList.GetHeadPosition();
	//m_BufferList에 있는 것들을 m_FigureList에 추가해서 그릴 것.\
	Invalidate();
}

void CGraphicEditorView::OnEditDelete()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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

void CGraphicEditorView::OnInsertPolygon()	// 삼각형 버튼
{
	//m_SelectedFigures.deselectAll();	// 수정 금지 (선택 개체 제거)
	m_InsertFlag = POLYGON;			// 수정 금지
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnUpdateInsertPolygon(CCmdUI *pCmdUI)	// 삼각형 버튼
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

void CGraphicEditorView::OnArrangeBringFront()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeSendBack()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeBringForward()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeSendBackward()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeGrouping()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CGraphicEditorView::OnArrangeGroup()
{
	clearInsertFlag();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	//GetDocument()->m_FiguresList.AddHead(new CGroup(m_CurrentFigures));

	//for (POSITION pos = figurelist->GetTailPosition(); pos; figurelist->GetPrev(pos)) {
	//	m_CurrentFigures.InsertAfter(pos, figurelist->GetAt(subpos));
	//}

	//m_SelectedFigures.deselectAll();
	//m_CurrentFigures.AddTail(GetDocument()->m_FiguresList.GetHead());
}

void CGraphicEditorView::OnUpdateArrangeGroup(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
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
}

void CGraphicEditorView::OnUpdateArrangeUngroup(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
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

void CGraphicEditorView::OnPolylineIndividualDelete()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolyLine))) {
		CPolyLine* polyLine = (CPolyLine*)m_SelectedFigures.getOneFigure();

		if (polyLine->GetPointsList().GetSize() == 1){
			polyLine->destroy();
		}
		else 
			(polyLine)->RemovePoint(m_RButtonPoint);
		Invalidate();
	}

}

void CGraphicEditorView::OnPolylineIndividualInsert()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_SelectedFigures.hasOne() && m_SelectedFigures.getOneFigure()->IsKindOf(RUNTIME_CLASS(CPolyLine))) {
		((CPolyLine*)m_SelectedFigures.getOneFigure())->InsertPoint(m_RButtonPoint);
		Invalidate();
	}
}