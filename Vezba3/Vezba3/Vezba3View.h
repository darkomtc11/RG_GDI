
// Vezba3View.h : interface of the CVezba3View class
//

#pragma once

typedef struct hatch {
	char r;
	char g;
	char b;
	char type;
} Hatch;

class CVezba3View : public CView
{
protected: // create from serialization only
	CVezba3View() noexcept;
	DECLARE_DYNCREATE(CVezba3View)

	int baseLength;
	CDC* pdc;

	float bigArmAngle = 0.0;
	float smallArmAngle = 0.0;
	float handAngle = 0.0;

// Attributes
public:
	CVezba3Doc* GetDocument() const;

// Operations
public:
	void SetRotation(float, bool);
	void SetTranlation(float, float, bool);
	void MirrorVertical(bool);
	void DrawGrid();
	void DrawImage(int, int, int, Hatch);

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
	virtual ~CVezba3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Vezba3View.cpp
inline CVezba3Doc* CVezba3View::GetDocument() const
   { return reinterpret_cast<CVezba3Doc*>(m_pDocument); }
#endif

