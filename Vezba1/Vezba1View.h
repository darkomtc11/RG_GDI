
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
	void SetRotation(float);
	void SetTranlate(float, float);
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
};

#ifndef _DEBUG  // debug version in Vezba1View.cpp
inline CVezba1Doc* CVezba1View::GetDocument() const
{
	return reinterpret_cast<CVezba1Doc*>(m_pDocument);
}
#endif

