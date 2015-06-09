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

// Graphic Editor View Commands.cpp : CGraphicEditorView Ŭ������ ���� (��� �޽��� ó����)
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


/*** CGraphicEditorView ��� �޽��� ó���� ***/

// void CGraphicEditorView::OnFilePrintPreview() {}
// �� ó����� "Graphic Editor View.cpp"���� ������. ("CGraphicEditorView �μ�" ����)

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
	CGraphicEditorDoc* pDoc = GetDocument();
	CFigure* figure;
	
	m_BufferList.RemoveAll();//���簡 �Ͼ���� �׵��� ����Ǿ��ִ� ����Ʈ�� �����.

	/* ��, m_FiguresList���� ��� �����ؾ��ϹǷ� �������� ����.*/
	if (m_SelectedFigures.hasOne()){//�ϳ��� ���õ� ���
		figure = m_SelectedFigures.getOneFigure();
		m_BufferList.AddTail(figure->clone());//figure�� �߰�����
	}

	else // ���� ���� case
	{
		//���� �迭�� ����
		const POSITION* positionArray = m_SelectedFigures.getData();
		for (int i = 0; i < m_SelectedFigures.getSize(); i++)// ����� ����ŭ
		{
			figure = pDoc->m_FiguresList.GetAt(positionArray[i]);
			m_BufferList.AddTail(figure->clone());
	}
}
}

void CGraphicEditorView::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	pCmdUI->Enable(getCopyableFlag());
}

void CGraphicEditorView::OnEditCut()//�߶󳻱�
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CGraphicEditorDoc* pDoc = GetDocument();
	CFigure* figure;
	m_BufferList.RemoveAll();//�߶󳻱� �߻�. �׵��� ����Ǿ��ִ� ����Ʈ�� �����.
	
	if (m_SelectedFigures.hasOne()){
		//��������ġ�� �������
		POSITION deletePos = m_SelectedFigures.getForwardPos();
		figure = m_SelectedFigures.getOneFigure();
		m_BufferList.AddTail(figure);//figure�� �߰�����
		m_SelectedFigures.deselect(deletePos);
		pDoc->m_FiguresList.RemoveAt(deletePos);//���� ����Ʈ���� ����
	}
	else{// ����
		//���� �迭�� ����
		const POSITION* positionArray = m_SelectedFigures.getData();
		for (int i = 0; i < m_SelectedFigures.getSize(); i++)// ����� ����ŭ
	{
			figure = pDoc->m_FiguresList.GetAt(positionArray[i]);
			m_BufferList.AddTail(figure->clone());
			pDoc->m_FiguresList.RemoveAt(positionArray[i]);//���� ����Ʈ���� ����
		}
		m_SelectedFigures.deselectAll();
	}
	Invalidate();//�߶󳻱⸦ �����Ƿ�, �信�� ������
}

void CGraphicEditorView::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	pCmdUI->Enable(getCopyableFlag());
}

//void CGraphicEditorView::OnEditFind()
//{
//	clearInsertFlag();
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

void CGraphicEditorView::OnEditPaste()//�ٿ��ֱ�
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CGraphicEditorDoc* pDoc = GetDocument();
	CFigure* figure;
	POSITION headpos = m_BufferList.GetHeadPosition();
	//m_BufferList�� �ִ� �͵��� ist�� �߰��ؼ� �׸� ��
	
	if (m_BufferList.hasOneFigure()){//�ϳ��� ����Ǿ��ִ� ���
		CFigure* figure = m_BufferList.GetHead();
		pDoc->m_FiguresList.AddHead(figure->clone());//figure�� �߰�����
		m_SelectedFigures.select();
	}

	else{//���� ����
		//CFigure* figure = m_BufferList.GetHead();
		for (int i = 0; i < m_BufferList.GetCount(); i++)// ����� ����ŭ
		{
			figure = m_BufferList.GetAt(headpos);
			m_BufferList.GetNext(headpos);
			pDoc->m_FiguresList.AddHead(figure->clone());//figure�� �߰���
			m_SelectedFigures.select();
		}
	}
	Invalidate();
}

void CGraphicEditorView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	pCmdUI->Enable(getPastableFlag());
}

void CGraphicEditorView::OnEditDelete()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 
	CGraphicEditorDoc* pDoc = GetDocument();

	if (m_SelectedFigures.hasOne()){
		//��������ġ�� �������
		POSITION deletePos = m_SelectedFigures.getForwardPos();
		m_SelectedFigures.deselect(deletePos);
		pDoc->m_FiguresList.RemoveAt(deletePos);//���� ����Ʈ���� ����
	}
	else{// ����
		//���� �迭�� ����
		const POSITION* positionArray = m_SelectedFigures.getData();
		for (int i = 0; i < m_SelectedFigures.getSize(); i++)// ����� ����ŭ
		{
			pDoc->m_FiguresList.RemoveAt(positionArray[i]);//���� ����Ʈ���� ����
		}
		m_SelectedFigures.deselectAll();
	}
	Invalidate();//�߶󳻱⸦ �����Ƿ�, �信�� ������
}

void CGraphicEditorView::OnUpdateEditDelete(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	pCmdUI->Enable(getDeletableFlag());
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

	m_SelectedFigures.selectAll();
	Invalidate();
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
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = LINE;			// ���� ����
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
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = POLYLINE;		// ���� ����
	m_PolyCreatableFlag = TRUE;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPolyline(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == POLYLINE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPencil()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = PENCIL;			// ���� ����
	m_PolyCreatableFlag = TRUE;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPencil(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == PENCIL);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertCurve()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = CURVE;			// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertCurve(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == CURVE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertEllipse()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = ELLIPSE;			// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertEllipse(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == ELLIPSE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertRectangle()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = RECTANGLE;		// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == RECTANGLE);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertString()
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = STRING;			// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertString(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == STRING);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPolygon()	// �ٰ��� ��ư
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = POLYGON;			// ���� ����
	m_PolyCreatableFlag = TRUE;
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPolygon(CCmdUI *pCmdUI)	// �ٰ��� ��ư
{
	pCmdUI->SetCheck(m_InsertFlag == POLYGON);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertClosedcurve()	// ���� ��ư
{
	//m_SelectedFigures.deselectAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = CLOSEDCURVE;		// ���� ����
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
	
	GetDocument()->m_FiguresList.AddHead(new CGroup(m_SelectedFigures));

	Invalidate();
}

void CGraphicEditorView::OnUpdateArrangeGrouping(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	pCmdUI->Enable(getGroupableFlag() || getUngroupableFlag());
}

void CGraphicEditorView::OnArrangeGroup()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	pCmdUI->Enable(getGroupableFlag());
}

void CGraphicEditorView::OnArrangeUngroup()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	pCmdUI->Enable(getUngroupableFlag());
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

void CGraphicEditorView::OnOutlineColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateOutlineColor(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnOutlineWidth()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateOutlineWidth(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnOutlinePattern()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateOutlinePattern(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnFillColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	ASSERT_VALID(m_WndRibbonBar);

	CMFCRibbonColorButton* pColor = DYNAMIC_DOWNCAST(
		CMFCRibbonColorButton, m_WndRibbonBar->FindByID(ID_FILL_COLOR));
	
	Color color;
	color.SetFromCOLORREF(pColor->GetColor());
	m_SelectedFigures.setFillColor(color);

	Invalidate();
}


void CGraphicEditorView::OnUpdateFillColor(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnFillGradation()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateFillGradation(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnFillPattern()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateFillPattern(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnPositionVertical()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdatePositionVertical(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnPositionHorizontal()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdatePositionHorizontal(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnSizeHeight()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateSizeHeight(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnSizeWidth()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateSizeWidth(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnFontCharset()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateFontCharset(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnFontSize()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateFontSize(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnFontBold()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateFontBold(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnFontItalic()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateFontItalic(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnFontUnderline()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateFontUnderline(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnFontColor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CGraphicEditorView::OnUpdateFontColor(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnPointmove()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	m_EditPointFlag = m_EditPointFlag ? FALSE : TRUE;
	
		Invalidate();
}

void CGraphicEditorView::OnUpdatePointmove(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	pCmdUI->Enable(getLineSelectedFlag() || getPolySelectedFlag());
	pCmdUI->SetText(m_EditPointFlag ? _T("�� ���� ����") : _T("�� ����"));
}

void CGraphicEditorView::OnPolyIndividualInsert()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	pCmdUI->Enable(m_EditPointFlag /*&& (m_selectedPosition == CFigure::INSIDE) */&& getPolySelectedFlag());
}

void CGraphicEditorView::OnPolyIndividualDelete()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.

	pCmdUI->Enable(m_EditPointFlag /*&& (m_selectedPosition & CFigure::ONHANDLE) */&& getPolySelectedFlag());
}

