// FigureProperties.h : CFigureProperties Ŭ������ �������̽�
// CFigureProperties : ���� ������ ���� �⺻ �Ӽ� ������ �����ϴ� Ŭ����
// @Author Lee Hwajung

#pragma once

#include "afx.h"
//#include <gdiplus.h>

using namespace Gdiplus;

// CFigureProperties ��� ����Դϴ�.

class CFigureProperties : public CObject
{
	
public:
	CFigureProperties();
	virtual ~CFigureProperties();
	DECLARE_SERIAL(CFigureProperties)

public:
	// ����ȭ
	virtual void Serialize(CArchive& ar);

	// ������
	Color getLineColor();
	void setLineColor(Color LineColor);
	int getLinePattern();
	void setLinePattern(int LinePattern);
	int getLineWidth();
	void setLineWidth(int LineWidth);

	// ä���
	Color getFillColor();
	void setFillColor(Color FillColor);
	int getFillPattern();
	void setFillPattern(int FillPattern);

	// �۲�
	Color getFontColor();
	void setFontColor(Color FontColor);
	LOGFONT getFontLog();
	void setFontLog(LOGFONT FontLog);

	CString getFontName();
	void setFontName(CString FontName);
	int getFontSize();
	void setFontSize(int FontSize);
	BOOL getFontBold();
	void setFontBold(BOOL FontBold);
	BOOL getFontItalic();
	void setFontItalic(BOOL FontItalic);
	BOOL getFontUnderline();
	void setFontUnderline(BOOL FontUnderline);
	BOOL getFontStrikeOut();
	void setFontStrikeOut(BOOL FontStrikeOut);

private:
	// ������
	Color m_LineColor;		// ������ ����
	int m_LinePattern;		// ������ ����
	int m_LineWidth;		// ������ ����

	// ä���
	Color m_FillColor;		// ä��� ����
	int m_FillPattern;		// ä��� ����

	// �۲�
	Color m_FontColor;		// �۲� ����
	LOGFONT m_FontLog;		// �۲� �̸�, ũ��, ����, ���Ÿ�, ����, ��Ҽ� �� https://msdn.microsoft.com/en-us/library/windows/desktop/dd145037(v=vs.85).aspx
}; 


/* Logical Font
https://msdn.microsoft.com/en-us/library/windows/desktop/dd145037(v=vs.85).aspx

#define LF_FACESIZE         32
...
typedef struct tagLOGFONTW
{
	LONG	lfHeight;					// �۲��ǳ���(�ȼ�����), ���밪�̹Ƿ� ��������
	LONG	lfWidth;					// ����
	LONG	lfEscapement;				// ���ڿ��� ����
	LONG	lfOrientation;				// ������ ������ 0.1 �����θ��
	LONG	lfWeight;					// �۲��� ���� ( = FW_BOLD)
	BYTE	lfItalic;					// ���ڸ�(�ణ ������ ������ ����) ���� ���(true, false)
	BYTE	lfUnderline;				// ����
	BYTE	lfStrikeOut;				// ���ڰ����
	BYTE	lfCharSet;					// ���������� ���.(�������� ������ ���ݾ� �ٸ� �� �ִ�)
	BYTE	lfOutPrecision;				// �������� �������Ȯ����, ��¹��� ���������� �����ϴ°Ͱ� �۲� �׷��� ����ϴ°Ͱ� �������ִ�. (MSDN ����)

	BYTE	lfClipPrecision;
	BYTE	lfQuality;
	BYTE	lfPitchAndFamily;
	WCHAR	lfFaceName[LF_FACESIZE];	// ��Ʈ

} LOGFONTW, *PLOGFONTW, NEAR *NPLOGFONTW, FAR *LPLOGFONTW;
#ifdef UNICODE
typedef LOGFONTW LOGFONT;
typedef PLOGFONTW PLOGFONT;
typedef NPLOGFONTW NPLOGFONT;
typedef LPLOGFONTW LPLOGFONT;
#else
...
#endif // UNICODE

��쿡���� �ý��ۿ� � �۲��� ��ġ�Ǿ��ִ��� Ȯ���ϰ� �۲��̸��� ������ �ʿ䰡�ִµ�
�̶��� ::EnumFonts() api��, ::EnumFontFamiliesEx() APi �� ����ϸ�ȴ�.

[��ó] LOGFONT ����ü|�ۼ��� gunny http://blog.naver.com/reverse_ing/60137355395
*/

