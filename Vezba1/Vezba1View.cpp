
// Vezba1View.cpp : implementation of the CVezba1View class
//

#include "pch.h"
#include "framework.h"
#include<iostream>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Vezba1.h"
#endif

#include "Vezba1Doc.h"
#include "Vezba1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

# define M_PI 3.141592653589793238462643383279502884

using namespace std;
// CVezba1View

IMPLEMENT_DYNCREATE(CVezba1View, CView)

BEGIN_MESSAGE_MAP(CVezba1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	//	ON_WM_KEYDOWN()
//	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CVezba1View construction/destruction

CVezba1View::CVezba1View() noexcept
{
	// TODO: add construction code here
	baseLength = 50;
}

CVezba1View::~CVezba1View()
{
}

BOOL CVezba1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVezba1View drawing

void CVezba1View::DrawGrid()
{
	CPen pen(0, 2, RGB(150, 150, 150));
	CPen* oldPen = (CPen*)pdc->SelectObject(&pen);

	int maxSize = 1200;
	for (int i = 0; i <= maxSize / baseLength; i++)
	{
		pdc->MoveTo(0, i * baseLength);
		pdc->LineTo(maxSize, i * baseLength);

		pdc->MoveTo(i * baseLength, 0);
		pdc->LineTo(i * baseLength, maxSize);
	}

	pdc->SelectObject(oldPen);
}

void CVezba1View::DrawShape(eCustomShape shape, eShapeSize size, CPoint point, int angle, bool half, CPen* pen, CBrush* brush)
{
	//CPen pen(0, 2, RGB(0, 120, 0));
	CPen* oldPen = (CPen*)pdc->SelectObject(pen);
	//CBrush brush(RGB(255, 0, 0));
	CBrush* oldBrush = (CBrush*)pdc->SelectObject(brush);

	if (shape == CSCircle)
	{
		pdc->Ellipse(point.x - size / 2, point.y - size / 2, point.x + size / 2, point.y + size / 2);
	}
	else
	{
		if (half)
		{
			DrawHalf((int)shape, (int)size, point, angle);
		}
		else
		{
			DrawPolygon((int)shape, (int)size, point, angle);
		}
	}

	pdc->SelectObject(oldPen);
	pdc->SelectObject(oldBrush);
}

void CVezba1View::DrawPolygon(int sides, int r, CPoint point, int angle)
{
	float phai = M_PI / (sides);
	float theta = M_PI / 2 - phai;

	float Ox = point.x;
	float Oy = point.y;

	float Px = 0;
	float Py = 0;

	Px = Ox - r / 2 * sin(M_PI / 180 * angle);
	Py = Oy - r / 2 * cos(M_PI / 180 * angle);

	float hyp = sqrt((Px - Ox) * (Px - Ox) +
		(Py - Oy) * (Py - Oy));

	CPoint* points = new CPoint[sides];
	for (int i = 0; i < sides; i++)
	{
		float x1 = hyp * cos(theta);
		float mu = atan2(Py - Oy, Px - Ox);
		float x2 = x1 * cos((mu - theta));
		float y2 = x1 * sin((mu - theta));
		points[i] = CPoint(int(Px), int(Py));
		Px = float(Px - 2 * x2);
		Py = float(Py - 2 * y2);
	}

	pdc->Polygon(points, sides);
}

void CVezba1View::DrawHalf(int sides, int r, CPoint point, int angle)
{
	float phai = M_PI / (sides);
	float theta = M_PI / 2 - phai;

	float Ox = point.x;
	float Oy = point.y;

	float Px1 = Ox - r / 2 * sin(M_PI / 180 * angle);
	float Py1 = Oy - r / 2 * cos(M_PI / 180 * angle);

	float Px2 = Ox - (r + 34) / 2 * sin(M_PI / 180 * angle);
	float Py2 = Oy - (r + 34) / 2 * cos(M_PI / 180 * angle);

	float hyp1 = sqrt((Px1 - Ox) * (Px1 - Ox) +
		(Py1 - Oy) * (Py1 - Oy));

	float hyp2 = sqrt((Px2 - Ox) * (Px2 - Ox) +
		(Py2 - Oy) * (Py2 - Oy));

	CPoint* points = new CPoint[sides + 2];
	for (int i = 0; i < (sides + 2) / 2; i++)
	{
		float x11 = hyp1 * cos(theta);
		float mu1 = atan2(Py1 - Oy, Px1 - Ox);
		float x21 = x11 * cos((mu1 - theta));
		float y21 = x11 * sin((mu1 - theta));
		points[i] = CPoint(int(Px1), int(Py1));
		Px1 = float(Px1 - 2 * x21);
		Py1 = float(Py1 - 2 * y21);

		float x12 = hyp2 * cos(theta);
		float mu2 = atan2(Py2 - Oy, Px2 - Ox);
		float x22 = x12 * cos((mu2 - theta));
		float y22 = x12 * sin((mu2 - theta));
		points[sides + 1 - i] = CPoint(int(Px2), int(Py2));
		Px2 = float(Px2 - 2 * x22);
		Py2 = float(Py2 - 2 * y22);
	}

	//CPen* oldPen;
	//CBrush* oldBrush;
	//CPen* pen = new CPen(0, 10, RGB(255, 0, 0));
	//oldPen = pdc->SelectObject(pen);

	//CBrush* brush = new CBrush(RGB(0, 0, 255));
	//oldBrush = pdc->SelectObject(brush);

	pdc->Polygon(points, sides + 2);

	//pdc->SelectObject(oldPen);
	//pdc->SelectObject(oldBrush);
}

void CVezba1View::DrawTrapezoid(CPoint topP, CPoint bottomP, int top, int bottom, CPen* pen, CBrush* brush)
{
	CPoint* points = new CPoint[4];

	points[0].x = topP.x - top / 2;
	points[0].y = topP.y;

	points[1].x = topP.x + top / 2;
	points[1].y = topP.y;

	points[2].x = bottomP.x + bottom / 2;
	points[2].y = bottomP.y;

	points[3].x = bottomP.x - bottom / 2;
	points[3].y = bottomP.y;

	//CPen pen(0, 4, RGB(0, 120, 0));
	CPen* oldPen = (CPen*)pdc->SelectObject(pen);
	//CBrush brush(RGB(255, 255, 0));
	CBrush* oldBrush = (CBrush*)pdc->SelectObject(brush);

	pdc->Polygon(points, 4);

	pdc->SelectObject(oldPen);
	pdc->SelectObject(oldBrush);
}

void CVezba1View::SetRotation(float r)
{
	XFORM Xform;
	r = r * (M_PI / 180);

	Xform.eM11 = (FLOAT)cos(r);
	Xform.eM12 = (FLOAT)sin(r);
	Xform.eM21 = (FLOAT)-sin(r);
	Xform.eM22 = (FLOAT)cos(r);
	Xform.eDx = (FLOAT)1.0;
	Xform.eDy = (FLOAT)1.0;

	ModifyWorldTransform(pdc->m_hDC, &Xform, MWT_LEFTMULTIPLY);
}

void CVezba1View::SetTranlate(float x, float y)
{
	XFORM Xform;

	Xform.eM11 = (FLOAT)1.0;
	Xform.eM12 = (FLOAT)0.0;
	Xform.eM21 = (FLOAT)0.0;
	Xform.eM22 = (FLOAT)1.0;
	Xform.eDx = x;
	Xform.eDy = y;

	ModifyWorldTransform(pdc->m_hDC, &Xform, MWT_LEFTMULTIPLY);
}

void CVezba1View::OnDraw(CDC* pDC)
{
	SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	CVezba1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;

	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(2000, 2000);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(-500, -500);

	pdc = pDC;

	DrawGrid();
	//SetRotation(5);
	SetTranlate(566, 50);
	CPen pen(0, 5, RGB(0, 255, 255));
	CPen tirq(0, 5, RGB(0, 255, 255));
	CPen bluep(0, 6, RGB(0, 0, 255));
	CPen redp(0, 7, RGB(255, 0, 0));
	CPen yellow(0, 5, RGB(255, 255, 0));

	CBrush brush(RGB(255, 0, 255));
	CBrush purple(RGB(255, 0, 255));
	CBrush red(RGB(255, 0, 0));
	CBrush blue(RGB(0, 0, 255));


	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_HATCHED;
	logBrush.lbColor = RGB(0, 255, 255);
	logBrush.lbHatch = HS_VERTICAL;

	CBrush pattern1;
	pattern1.CreateBrushIndirect(&logBrush);

	logBrush.lbHatch = HS_HORIZONTAL;

	CBrush pattern2;
	pattern2.CreateBrushIndirect(&logBrush);


	CPoint arm1Top(150, 900);
	CPoint arm1Bottom(150, 400);

	CPoint arm2Top(500, 775);
	CPoint arm2Bottom(500, 400);



	DrawTrapezoid(arm1Top, arm1Bottom, 50, 150, &tirq, &red);
	DrawTrapezoid(arm2Top, arm2Bottom, 50, 100, &bluep, &pattern1);

	DrawShape(CSHexagon, SSM, arm1Top, 30, false, &tirq, &purple);
	DrawShape(CSHexagon, SSS, arm1Top, 30, false, &tirq, &purple);
	DrawShape(CSHexagon, SSXL, arm1Bottom, 30, false, &tirq, &purple);
	DrawShape(CSHexagon, SSS, arm1Bottom, 30, false, &tirq, &purple);

	DrawShape(CSDiamond, SSM, arm2Top, 90, false, &bluep, &blue);
	DrawShape(CSDiamond, SSS, arm2Top, 90, false, &bluep, &blue);
	DrawShape(CSDiamond, SSL, arm2Bottom, 90, false, &bluep, &blue);
	DrawShape(CSDiamond, SSS, arm2Bottom, 90, false, &bluep, &blue);

	CPoint half(800, 550);
	CPoint left(800, 500 - 5);

	DrawShape(CSDiamond, SSM, half, 180, true, &yellow, &pattern2);
	DrawShape(CSCircle, SSS, left, 0, false, &yellow, &pattern2);

	CPoint baseTop(800, 800);
	CPoint baseMid(800, 850);
	CPoint baseBottom1(800, 900);
	CPoint baseBottom2(800, 950);

	DrawShape(CSOctagon, SSM, baseTop, 0, false, &bluep, &red);
	DrawTrapezoid(baseTop, baseMid, 100, 100, &bluep, &red);
	DrawTrapezoid(baseMid, baseBottom1, 100, 200, &bluep, &red);
	DrawTrapezoid(baseBottom1, baseBottom2, 300, 300, &bluep, &purple);

	CPoint cover1(800, 800);
	CPoint cover2(800, 850);

	DrawTrapezoid(cover1, cover1, 88, 88, &redp, &red);
	DrawTrapezoid(cover2, cover2, 88, 88, &redp, &red);

}


// CVezba1View printing

BOOL CVezba1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVezba1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVezba1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CVezba1View diagnostics

#ifdef _DEBUG
void CVezba1View::AssertValid() const
{
	CView::AssertValid();
}

void CVezba1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVezba1Doc* CVezba1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVezba1Doc)));
	return (CVezba1Doc*)m_pDocument;
}
#endif //_DEBUG


// CVezba1View message handlers

