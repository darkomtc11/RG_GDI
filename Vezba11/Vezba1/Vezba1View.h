
// Vezba1View.h : interface of the CVezba1View class
//

#pragma once

enum eCustomShape { CSCircle = 0, CSDiamond = 4, CSHexagon = 6, CSOctagon = 8, CSHalf32 = 2048 };
enum eShapeSize { SSS = 45, SSH = 70, SSM = 100, SSL = 150, SSXL = 200 };

class CVezba1View : public CView
{
protected: // create from serialization only
	CVezba1View() noexcept;
	DECLARE_DYNCREATE(CVezba1View)
	int baseLength;
	CDC* pdc;

	CPen *pen = new CPen(0, 5, RGB(0, 255, 255));
	CPen *tirq = new CPen(0, 5, RGB(0, 255, 255));
	CPen *bluep = new CPen(0, 6, RGB(0, 0, 255));
	CPen *redp = new CPen(0, 7, RGB(255, 0, 0));
	CPen *yellow =new  CPen(0, 5, RGB(255, 255, 0));

	CBrush *brush =new  CBrush(RGB(255, 0, 255));
	CBrush *purple =new CBrush(RGB(255, 0, 255));
	CBrush *red = new CBrush(RGB(255, 0, 0));
	CBrush *blue =new  CBrush(RGB(0, 0, 255));

	CBrush pattern1;
	CBrush pattern2;

	float bigArmAngle = 0;
	float smallArmAngle = 0;
	float handAngle = 0;

	HENHMETAFILE Meta;

	// Attributes
public:
	CVezba1Doc* GetDocument() const;

	// Operations
public:
	void DrawGrid();
	void DrawShape(eCustomShape, eShapeSize, CPoint, int, bool, CPen*, CBrush*);
	void DrawPolygon(int, int, CPoint, int);
	void DrawHalf(int, int, CPoint, int);
	void DrawTrapezoid(CPoint, CPoint, int, int, CPen*, CBrush*);
	void SetRotation(float, bool);
	void SetTranlation(float, float, bool);
	CPoint DrawBase(CPoint, float);
	CPoint DrawSmallArm(CPoint, float);
	CPoint DrawBigArm(CPoint, float);
	void DrawHand(CPoint, bool, float);
	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CVezba1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Vezba1View.cpp
inline CVezba1Doc* CVezba1View::GetDocument() const
{
	return reinterpret_cast<CVezba1Doc*>(m_pDocument);
}
#endif

