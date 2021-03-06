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

// Graphic Editor Doc.h : CGraphicEditorDoc 클래스의 인터페이스
//

#pragma once
#include "Figure.h"
#include "FigureSettings.h"

class CGraphicEditorDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CGraphicEditorDoc();
	DECLARE_DYNCREATE(CGraphicEditorDoc)

// 특성입니다.
public:
	CFigurePtrList m_FiguresList;		// 모든 개체 리스트
	
	CFigureSettings m_FigureSettings;	// 사용자가 메뉴를 통해 선택한 속성 설정을 저장 (마지막에 선택한 내용을 다음 번 실행에서 그대로 반영하기 위하여 Doc에 선언)
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

// 작업입니다.
public:

// 재정의입니다.
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

// 구현입니다.
public:
	virtual ~CGraphicEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
