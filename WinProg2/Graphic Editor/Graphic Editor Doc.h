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

// Graphic Editor Doc.h : CGraphicEditorDoc Ŭ������ �������̽�
//

#pragma once
#include "Figure.h"
#include "FigureSettings.h"

class CGraphicEditorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CGraphicEditorDoc();
	DECLARE_DYNCREATE(CGraphicEditorDoc)

// Ư���Դϴ�.
public:
	CFigurePtrList m_FiguresList;		// ��� ��ü ����Ʈ
	
	CFigureSettings m_FigureSettings;	// ����ڰ� �޴��� ���� ������ �Ӽ� ������ ���� (�������� ������ ������ ���� �� ���࿡�� �״�� �ݿ��ϱ� ���Ͽ� Doc�� ����)
	Color m_OutlineColor;
	REAL m_OutlineWidth;
	DashStyle m_OutlinePattern;
	Color m_FillColor;
	Color m_FillSubcolor;
	HatchStyle m_FillPattern;
	Color m_FontColor;
	Color m_FontSubcolor;
	HatchStyle m_FontPattern;
	LOGFONT m_FontLog;
	StringFormat* m_StringFormat;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CGraphicEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
