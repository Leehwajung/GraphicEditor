// FigureSettings.h : CFigureSettings 클래스의 인터페이스
// CFigureSettings : 도형 생성 및 속성 변경을 위한 기본 설정을 저장하는 클래스
// @Author Lee Hwajung

#pragma once

// CFigureSettings 명령 대상입니다.

class CFigureSettings : public CObject
{
public:
	CFigureSettings();
	~CFigureSettings();

	/** 속성 설정 **/
public:
	// 윤곽선 색 설정 (순수 가상)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	BOOL setOutlineColor(IN const Color& outlineColor);

	// 윤곽선 두께 설정 (순수 가상)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	BOOL setOutlineWidth(IN const REAL outlineWidth);

	// 윤곽선 패턴 설정 (순수 가상)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	BOOL setOutlinePattern(IN const DashStyle outlinePattern);

	// 주 채우기 색 설정 (순수 가상)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	BOOL setFillColor(IN const Color& fillColor);

	// 보조 채우기 색 설정 (순수 가상)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	BOOL setFillSubcolor(IN const Color& fillSubcolor);

	// 채우기 패턴 설정 (순수 가상)
	// - 반환 값 (BOOL)
	//		TRUE: 설정 실패
	//		FALSE: 설정 성공
	BOOL setFillPattern(IN const HatchStyle fillPattern);

	Pen* getOutlinePen() { return m_OutlinePen; }
	Brush* getFillBrush() { return m_FillBrush; }
	Brush* getFontBrush() { return m_FontBrush; }

private:
	Pen* m_OutlinePen;
	SolidBrush* m_FillSolidBrush;

	Brush* m_FontBrush;
};


