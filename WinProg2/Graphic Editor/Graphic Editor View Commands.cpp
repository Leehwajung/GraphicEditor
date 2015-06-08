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
	//https://msdn.microsoft.com/ko-kr/library/cc451491(v=vs.71).aspx
	//https://msdn.microsoft.com/ko-kr/library/cc451492(v=vs.71).aspx

	
	CSharedFile file;
	//CShareFile ��ü�� �����ϴ� ��ī�̺� ����
	CArchive ar(&file, CArchive::store);
	

	CGraphicEditorDoc* pDoc = GetDocument();
	pDoc->m_FiguresList.Serialize(ar);
	ar.Close();

	if (!OpenClipboard())//Ŭ������ ���½��н�
	{
		AfxMessageBox(_T("Cannot open the Clipboard"));
		return;
	}
	//Create an OLE data source on the heap
	COleDataSource* pDataSource = new COleDataSource;
	
	//��ϵ� ��������
	TRY
	{
		pDataSource->CacheGlobalData(m_cfsDraw, file.Detach());
		OleInitialize(NULL);
		pDataSource->SetClipboard(); 
	}
		CATCH_ALL(e)
	{
		delete pDataSource;
		THROW_LAST();
	}
	END_CATCH_ALL
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
	COleDataObject dataObject;

	//Ŭ������ ������ ������
	dataObject.AttachClipboard();
	if (m_CurrentFigures.hasOneFigure()){//�ϳ��� ��ü
	//Ŭ������ ������ �� ���α׷��� �´� ������ ��츸 ����
		if (dataObject.IsDataAvailable(m_cfsDraw))
		{
			CFile* pFile = dataObject.GetFileData(m_cfsDraw);
			if (pFile == NULL)
				return;

			CArchive ar(pFile, CArchive::load); //pFile�� ������ �ε��ϴ� ��ī�̺� ����
			TRY
			{
				//���� ����Ʈ�� ����ȭ�� �����Ͽ� Ŭ�������� ������ ���ø���Ʈ�� ����
				//ar.m_pDocument = GetDocument();
				//	pDoc->m_sSelectedList.Serialize(ar);
			}
			CATCH_ALL(e)
			{
				ar.Close();
				delete pFile;
				THROW_LAST();
			}
			END_CATCH_ALL

				ar.Close();
			delete pFile;
		}
		Invalidate();
	}
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
	//m_CurrentFigures.RemoveAll();	// ���� ���� (���� ��ü ����)
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
	//m_CurrentFigures.RemoveAll();	// ���� ���� (���� ��ü ����)
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
	//m_CurrentFigures.RemoveAll();	// ���� ���� (���� ��ü ����)
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
	//m_CurrentFigures.RemoveAll();	// ���� ���� (���� ��ü ����)
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
	//m_CurrentFigures.RemoveAll();	// ���� ���� (���� ��ü ����)
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
	//m_CurrentFigures.RemoveAll();	// ���� ���� (���� ��ü ����)
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
	//m_CurrentFigures.RemoveAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = STRING;			// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertString(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_InsertFlag == STRING);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertPolygon()	// �ﰢ�� ��ư
{
	//m_CurrentFigures.RemoveAll();	// ���� ���� (���� ��ü ����)
	m_InsertFlag = POLYGON;			// ���� ����
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnUpdateInsertPolygon(CCmdUI *pCmdUI)	// �ﰢ�� ��ư
{
	pCmdUI->SetCheck(m_InsertFlag == POLYGON);	// ���� ����
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnInsertClosedcurve()	// ���� ��ư
{
	//m_CurrentFigures.RemoveAll();	// ���� ���� (���� ��ü ����)
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
}

void CGraphicEditorView::OnArrangeGroup()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	//GetDocument()->m_FiguresList.AddHead(new CGroup(m_CurrentFigures));

	//for (POSITION pos = figurelist->GetTailPosition(); pos; figurelist->GetPrev(pos)) {
	//	m_CurrentFigures.InsertAfter(pos, figurelist->GetAt(subpos));
	//}

	//m_CurrentFigures.RemoveAll();
	//m_CurrentFigures.AddTail(GetDocument()->m_FiguresList.GetHead());
}

void CGraphicEditorView::OnUpdateArrangeGroup(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
}

void CGraphicEditorView::OnArrangeUngroup()
{
	clearInsertFlag();
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	for (POSITION pos = m_CurrentFigures.GetHeadPosition(); pos; m_CurrentFigures.GetNext(pos)) {
		if (m_CurrentFigures.GetAt(pos)->IsKindOf(RUNTIME_CLASS(CGroup))) {
			CFigurePtrList* figurelist = &((CGroup*)m_CurrentFigures.GetAt(pos))->getFiguresList();

			for (POSITION subpos = figurelist->GetTailPosition(); subpos; figurelist->GetPrev(subpos)) {
				m_CurrentFigures.InsertAfter(pos, figurelist->GetAt(subpos));
			}
			
		}
	}
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