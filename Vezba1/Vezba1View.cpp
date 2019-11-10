
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
ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CVezba1View construction/destruction

CVezba1View::CVezba1View() noexcept
{
	// TODO: add construction code here
	baseLength = 50;


	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_HATCHED;
	logBrush.lbColor = RGB(0, 255, 255);
	logBrush.lbHatch = HS_VERTICAL;

	pattern1.CreateBrushIndirect(&logBrush);

	logBrush.lbHatch = HS_HORIZONTAL;

	pattern2.CreateBrushIndirect(&logBrush);

	LPCSTR WMFname = LPCSTR("D:\\Faculty\\RG\\RG_GDI\\Vezba1\\LAB II - GDI - opruga.emf");
	Meta = GetEnhMetaFileA(WMFname);
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
	CPen* pen = new CPen(0, 2, RGB(150, 150, 150));
	CPen* oldPen = (CPen*)pdc->SelectObject(&pen);

	int maxSize = 1000;
	for (int i = 0; i <= maxSize / baseLength; i++)
	{
		if (i % 5 == 0 && false) {
			pen = new CPen(0, 2, RGB(255, 0, 0));
			oldPen = (CPen*)pdc->SelectObject(pen);
		}
		pdc->MoveTo(0, i * baseLength);
		pdc->LineTo(maxSize, i * baseLength);

		pdc->MoveTo(i * baseLength, 0);
		pdc->LineTo(i * baseLength, maxSize);

		pdc->SelectObject(oldPen);
	}
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

	pdc->Polygon(points, sides + 2);
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

	CPen* oldPen = (CPen*)pdc->SelectObject(pen);
	CBrush* oldBrush = (CBrush*)pdc->SelectObject(brush);

	pdc->Polygon(points, 4);

	pdc->SelectObject(oldPen);
	pdc->SelectObject(oldBrush);
}

void CVezba1View::SetRotation(float r, bool modify = true)
{
	XFORM Xform;
	r = r * (M_PI / 180);

	Xform.eM11 = (FLOAT)cos(r);
	Xform.eM12 = (FLOAT)sin(r);
	Xform.eM21 = (FLOAT)-sin(r);
	Xform.eM22 = (FLOAT)cos(r);
	Xform.eDx = (FLOAT)1.0;
	Xform.eDy = (FLOAT)1.0;

	if (modify)
	{
		ModifyWorldTransform(pdc->m_hDC, &Xform, MWT_LEFTMULTIPLY);
	}
	else
	{
		SetWorldTransform(pdc->m_hDC, &Xform);
	}
}

void CVezba1View::SetTranlation(float x, float y, bool modify = true)
{
	XFORM Xform;

	Xform.eM11 = (FLOAT)1.0;
	Xform.eM12 = (FLOAT)0.0;
	Xform.eM21 = (FLOAT)0.0;
	Xform.eM22 = (FLOAT)1.0;
	Xform.eDx = x;
	Xform.eDy = y;

	if (modify)
	{
		ModifyWorldTransform(pdc->m_hDC, &Xform, MWT_LEFTMULTIPLY);
	}
	else
	{
		SetWorldTransform(pdc->m_hDC, &Xform);
	}
}

CPoint CVezba1View::DrawBase(CPoint t, float angle)
{
	SetTranlation(t.x, t.y);
	SetRotation(angle);
	CPoint point(0, 0);
	CPoint point2(point.x, point.y + 50);
	CPoint point3(point.x, point.y + 100);
	CPoint point4(point.x, point.y + 150);

	DrawShape(CSOctagon, SSM, point, 0, false, bluep, red);
	DrawTrapezoid(point, point2, 100, 100, bluep, red);
	DrawTrapezoid(point2, point3, 100, 200, bluep, red);
	DrawTrapezoid(point3, point4, 300, 300, bluep, purple);

	DrawTrapezoid(point, point, 88, 88, redp, red);
	DrawTrapezoid(point2, point2, 88, 88, redp, red);

	return point;
}

CPoint CVezba1View::DrawSmallArm(CPoint t, float angle)
{
	SetTranlation(t.x, t.y);
	SetRotation(angle);
	CPoint point(0, 0);
	CPoint point2(point.x, point.y - 375);
	DrawTrapezoid(point2, point, 50, 100, bluep, &pattern1);

	DrawShape(CSDiamond, SSM, point2, 90, false, bluep, blue);
	DrawShape(CSDiamond, SSS, point2, 90, false, bluep, blue);
	DrawShape(CSDiamond, SSL, point, 90, false, bluep, blue);
	DrawShape(CSDiamond, SSS, point, 90, false, bluep, blue);

	PlayEnhMetaFile(pdc->m_hDC, Meta, CRect(point.x - 75, point.y + 15, point2.x + 75, point2.y - 15));

	return point2;
}

CPoint CVezba1View::DrawBigArm(CPoint t, float angle)
{
	SetTranlation(t.x, t.y);
	SetRotation(angle);
	CPoint point(0, 0);
	CPoint point2(point.x, point.y - 500);
	DrawTrapezoid(point2, point, 50, 150, tirq, red);

	DrawShape(CSHexagon, SSM, point2, 30, false, tirq, purple);
	DrawShape(CSHexagon, SSS, point2, 30, false, tirq, purple);
	DrawShape(CSHexagon, SSXL, point, 30, false, tirq, purple);
	DrawShape(CSHexagon, SSS, point, 30, false, tirq, purple);

	PlayEnhMetaFile(pdc->m_hDC, Meta, CRect(point.x - 100, point.y + 15, point2.x + 100, point2.y + 15));

	return point2;
}

void CVezba1View::DrawHand(CPoint t, bool first, float angle)
{
	SetTranlation(t.x, t.y);
	SetRotation(angle);
	CPoint point(0, 0);
	CPoint point2(point.x, point.y + 55);

	DrawShape(CSDiamond, SSM, point2, first ? 180 : 0, true, yellow, &pattern2);
	DrawShape(CSCircle, SSS, point, 0, false, yellow, &pattern2);
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
	pDC->SetWindowExt(1000, 1000);
	pDC->SetViewportExt(min(rect.right, rect.bottom), min(rect.right, rect.bottom));
	pDC->SetWindowOrg(-(rect.right - min(rect.right, rect.bottom) )/2, -(rect.bottom - min(rect.right, rect.bottom))/2);

	pdc = pDC;

	DrawGrid();

	CPoint point(850, 150);

	CPoint hand = DrawSmallArm(DrawBigArm(DrawBase(point, 180), 0 + bigArmAngle), 90 + smallArmAngle);
	DrawHand(hand, true, 180 + handAngle);
	DrawHand(CPoint(0, 0), false, 0 - 2 * handAngle);

	/*SetTranlation(0, 0, false);
	SetRotation(0, false);

	pdc->MoveTo(CPoint(300, 300));
	pdc->LineTo(CPoint(500, 500));*/

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



void CVezba1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar) {
	case 'q':case 'Q': bigArmAngle = (int)(bigArmAngle - 5) % 360; break;
	case 'w':case 'W': bigArmAngle = (int)(bigArmAngle + 5) % 360; break;
	case 'e':case 'E': smallArmAngle = (int)(smallArmAngle - 5) % 360; break;
	case 'r':case 'R': smallArmAngle = (int)(smallArmAngle + 5) % 360; break;
	case 't':case 'T': handAngle = (int)(handAngle - 5) % 360; break;
	case 'y':case 'Y': handAngle = (int)(handAngle + 5) % 360; break;
	}

	Invalidate();
	//CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
