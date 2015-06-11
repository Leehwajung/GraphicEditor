// FigureSettings.h : CFigureSettings 클래스의 인터페이스
// CFigureSettings : 도형 생성 및 속성 변경을 위한 기본 설정을 저장하는 클래스
// 

#pragma once

// CFigureSettings 명령 대상입니다.

class CFigureSettings : public CObject
{
public:
	CFigureSettings();
	~CFigureSettings();

	/** 속성 설정 **/
public:
	// 윤곽선 색 설정
	void setOutlineColor(IN const Color& outlineColor);

	// 윤곽선 두께 설정
	void setOutlineWidth(IN const REAL outlineWidth);

	// 윤곽선 패턴 설정
	void setOutlinePattern(IN const DashStyle outlinePattern);

	// 주 채우기 색 설정
	void setFillColor(IN const Color& fillColor);

	// 보조 채우기 색 설정
	void setFillSubcolor(IN const Color& fillSubcolor);

	// 채우기 패턴 설정
	void setFillPattern(IN const HatchStyle fillPattern);

	// 주 글꼴색 설정
	void setFontColor(IN const Color& fontColor);

	// 보조 글꼴색 설정
	void setFontSubcolor(IN const Color& fontSubcolor);

	// 글꼴색 패턴 설정
	void setFontPattern(IN const HatchStyle fontPattern);

	// 글꼴 속성 설정
	void setFontLog(IN const LOGFONT fontLog);

	// 문자열 포맷 설정
	void setStringFormat(IN const StringFormat& StringFormat);

	Pen* getOutlinePen(Pen* outlinepen);
	Brush* getFillBrush(Brush* fillBrush);
	Brush* getFontBrush(Brush* fontBrush);
	LOGFONT* getFontLog();
	StringFormat* getStringFormat();

public:
	Color m_OutlineColor;
	REAL m_OutlineWidth;
	DashStyle m_OutlinePattern;
	Color m_FillColor;
	Color m_FillSubcolor;
	HatchStyle m_FillPattern;
	REAL m_FillGradientAngle;
	Color m_FontColor;
	Color m_FontSubcolor;
	HatchStyle m_FontPattern;
	LOGFONT m_FontLog;
	CString m_FontName;
	REAL m_FontSize;
	StringFormat* m_StringFormat;
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