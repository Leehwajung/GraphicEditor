// FigureProperties.h : CFigureProperties 클래스의 인터페이스
// CFigureProperties : 도형 생성을 위한 기본 속성 설정을 저장하는 클래스
// @Author Lee Hwajung

#pragma once

#include "afx.h"
//#include <gdiplus.h>

using namespace Gdiplus;

// CFigureProperties 명령 대상입니다.

class CFigureProperties : public CObject
{
	
public:
	CFigureProperties();
	virtual ~CFigureProperties();
	DECLARE_SERIAL(CFigureProperties)

public:
	// 직렬화
	virtual void Serialize(CArchive& ar);

	// 윤곽선
	Color getLineColor();
	void setLineColor(Color LineColor);
	int getLinePattern();
	void setLinePattern(int LinePattern);
	int getLineWidth();
	void setLineWidth(int LineWidth);

	// 채우기
	Color getFillColor();
	void setFillColor(Color FillColor);
	int getFillPattern();
	void setFillPattern(int FillPattern);

	// 글꼴
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
	// 윤곽선
	Color m_LineColor;		// 윤곽선 색상
	int m_LinePattern;		// 윤곽선 패턴
	int m_LineWidth;		// 윤곽선 굵기

	// 채우기
	Color m_FillColor;		// 채우기 색상
	int m_FillPattern;		// 채우기 패턴

	// 글꼴
	Color m_FontColor;		// 글꼴 색상
	LOGFONT m_FontLog;		// 글꼴 이름, 크기, 굵게, 이탤릭, 밑줄, 취소선 등 https://msdn.microsoft.com/en-us/library/windows/desktop/dd145037(v=vs.85).aspx
}; 


/* Logical Font
https://msdn.microsoft.com/en-us/library/windows/desktop/dd145037(v=vs.85).aspx

#define LF_FACESIZE         32
...
typedef struct tagLOGFONTW
{
	LONG	lfHeight;					// 글꼴의높이(픽셀단위), 절대값이므로 음수가능
	LONG	lfWidth;					// 장평
	LONG	lfEscapement;				// 문자열의 기울기
	LONG	lfOrientation;				// 글자의 각도를 0.1 단위로명시
	LONG	lfWeight;					// 글꼴의 굵기 ( = FW_BOLD)
	BYTE	lfItalic;					// 이텔릭(약간 옆으로 기울어진 문자) 할지 명시(true, false)
	BYTE	lfUnderline;				// 밑줄
	BYTE	lfStrikeOut;				// 문자가운데줄
	BYTE	lfCharSet;					// 문자집합을 명시.(국가별로 설정이 조금씩 다를 수 있다)
	BYTE	lfOutPrecision;				// 나머지는 출력의정확도나, 출력물의 질적수준을 변경하는것과 글꼴 그룹을 명시하는것과 관련이있다. (MSDN 참조)

	BYTE	lfClipPrecision;
	BYTE	lfQuality;
	BYTE	lfPitchAndFamily;
	WCHAR	lfFaceName[LF_FACESIZE];	// 폰트

} LOGFONTW, *PLOGFONTW, NEAR *NPLOGFONTW, FAR *LPLOGFONTW;
#ifdef UNICODE
typedef LOGFONTW LOGFONT;
typedef PLOGFONTW PLOGFONT;
typedef NPLOGFONTW NPLOGFONT;
typedef LPLOGFONTW LPLOGFONT;
#else
...
#endif // UNICODE

경우에따라 시스템에 어떤 글꼴이 설치되어있는지 확인하고 글꼴이름을 열거할 필요가있는데
이때는 ::EnumFonts() api나, ::EnumFontFamiliesEx() APi 를 사용하면된다.

[출처] LOGFONT 구조체|작성자 gunny http://blog.naver.com/reverse_ing/60137355395
*/

