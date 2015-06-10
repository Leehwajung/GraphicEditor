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
	Color m_FontColor;
	Color m_FontSubcolor;
	HatchStyle m_FontPattern;
	LOGFONT m_FontLog;
	CString m_FontName;
	REAL m_FontSize;
	StringFormat* m_StringFormat;
};


