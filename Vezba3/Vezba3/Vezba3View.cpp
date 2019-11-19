
// Vezba3View.cpp : implementation of the CVezba3View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Vezba3.h"
#endif

#include "Vezba3Doc.h"
#include "Vezba3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

# define M_PI 3.141592653589793238462643383279502884


// CVezba3View

IMPLEMENT_DYNCREATE(CVezba3View, CView)

BEGIN_MESSAGE_MAP(CVezba3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CVezba3View construction/destruction

CVezba3View::CVezba3View() noexcept
{
	baseLength = 25;
}

CVezba3View::~CVezba3View()
{
}

BOOL CVezba3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CVezba3View::SetRotation(float r, bool modify = true)
{
	XFORM Xform;
	r = r * (M_PI / 180.0);

	Xform.eM11 = (FLOAT)cos(r);
	Xform.eM12 = (FLOAT)sin(r);
	Xform.eM21 = (FLOAT)-sin(r);
	Xform.eM22 = (FLOAT)cos(r);
	Xform.eDx = (FLOAT)1.0;
	Xform.eDy = (FLOAT)1.0;

	if (modify)
		ModifyWorldTransform(pdc->m_hDC, &Xform, MWT_LEFTMULTIPLY);
	else
		SetWorldTransform(pdc->m_hDC, &Xform);
}

void CVezba3View::SetTranlation(float x, float y, bool modify = true)
{
	XFORM Xform;

	Xform.eM11 = (FLOAT)1.0;
	Xform.eM12 = (FLOAT)0.0;
	Xform.eM21 = (FLOAT)0.0;
	Xform.eM22 = (FLOAT)1.0;
	Xform.eDx = (FLOAT)x;
	Xform.eDy = (FLOAT)y;

	if (modify)
		ModifyWorldTransform(pdc->m_hDC, &Xform, MWT_LEFTMULTIPLY);
	else
		SetWorldTransform(pdc->m_hDC, &Xform);
}

void CVezba3View::MirrorVertical(bool modify = true)
{
	XFORM Xform;

	Xform.eM11 = (FLOAT)-1.0;
	Xform.eM12 = (FLOAT)0.0;
	Xform.eM21 = (FLOAT)0.0;
	Xform.eM22 = (FLOAT)1.0;
	Xform.eDx = (FLOAT)0.0;
	Xform.eDy = (FLOAT)0.0;

	if (modify)
		ModifyWorldTransform(pdc->m_hDC, &Xform, MWT_LEFTMULTIPLY);
	else
		SetWorldTransform(pdc->m_hDC, &Xform);
}

void CVezba3View::DrawGrid()
{
	CPen pen(0, 2, RGB(150, 150, 150));
	//CPen pen(0, 1, RGB(255, 0, 0));
	CPen* oldPen = (CPen*)pdc->SelectObject(&pen);

	int maxSize = 500;
	for (int i = 0; i <= maxSize / baseLength; i++)
	{
		pdc->MoveTo(0, i * baseLength);
		pdc->LineTo(maxSize, i * baseLength);

		pdc->MoveTo(i * baseLength, 0);
		pdc->LineTo(i * baseLength, maxSize);
	}

	pdc->SelectObject(oldPen);
}

CBitmap* CVezba3View::HatchImage(BITMAP bm, CBitmap *bmpImage, Hatch hatch)
{
	BYTE* bmpBuffer = (BYTE*)GlobalAlloc(GPTR, bm.bmWidthBytes * bm.bmHeight);
	bmpImage->GetBitmapBits(bm.bmWidthBytes * bm.bmHeight, bmpBuffer);

	for (int i = 0; i < bm.bmHeight; i++)
	{
		for (int j = 0; j < bm.bmWidth; j++)
		{
			BYTE* pixel = bmpBuffer + (i * 4 * bm.bmWidth + j * 4);
			switch (hatch.type)
			{
			case 0:
				pixel[0] &= hatch.b;
				pixel[1] &= hatch.g;
				pixel[2] &= hatch.r;
				break;
			case 1:
				if (25 > i % 50) {
					pixel[0] &= hatch.b;
					pixel[1] &= hatch.g;
					pixel[2] &= hatch.r;
				}
				break;
			case 2:
				if (25 > j % 50) {
					pixel[0] &= hatch.b;
					pixel[1] &= hatch.g;
					pixel[2] &= hatch.r;
				}
				break;
			case 3:
				if (25 > i % 50 && 25 > j % 50 ||
					25 < i % 50 && 25 < j % 50) {
					pixel[0] &= hatch.b;
					pixel[1] &= hatch.g;
					pixel[2] &= hatch.r;
				}
				break;
			case 4:
				if (25 < i % 50 && 25 > j % 50 ||
					25 > i % 50 && 25 < j % 50) {
					pixel[0] &= hatch.b;
					pixel[1] &= hatch.g;
					pixel[2] &= hatch.r;
				}
				break;
			case 5:
				if (25 < (i - j + bm.bmWidth) % 50) {
					pixel[0] &= hatch.b;
					pixel[1] &= hatch.g;
					pixel[2] &= hatch.r;
				}
				break;
			case 6:
				if (25 > (i + j + bm.bmWidth) % 50) {
					pixel[0] &= hatch.b;
					pixel[1] &= hatch.g;
					pixel[2] &= hatch.r;
				}
				break;
			case 7:
				if ((25 > (i - j) % 50) && (j <= bm.bmWidth / 2) ||
					(25 < (i + j) % 50) && (j > bm.bmWidth / 2)) {
					pixel[0] &= hatch.b;
					pixel[1] &= hatch.g;
					pixel[2] &= hatch.r;
				}
				break;
			case 8:
				if ((25 > (i + j) % 50) && (j <= bm.bmWidth / 2) ||
					(25 < (i - j) % 50) && (j > bm.bmWidth / 2)) {
					pixel[0] &= hatch.b;
					pixel[1] &= hatch.g;
					pixel[2] &= hatch.r;
				}
				break;
			case 9:
				if ((25 < (i - j + 25) % 50) && (j <= bm.bmWidth / 2) ||
					(25 < (i + j + 25) % 50) && (j > bm.bmWidth / 2)) {
					pixel[0] &= hatch.b;
					pixel[1] &= hatch.g;
					pixel[2] &= hatch.r;
				}
				break;
			case 10:
				if ((25 > (i + j) % 50) && (j <= bm.bmWidth / 2) ||
					(25 > (i - j) % 50) && (j > bm.bmWidth / 2)) {
					pixel[0] &= hatch.b;
					pixel[1] &= hatch.g;
					pixel[2] &= hatch.r;
				}
				break;
			default:
				break;
			}
		}
	}

	bmpImage->SetBitmapBits(bm.bmWidthBytes * bm.bmHeight, bmpBuffer);

	return bmpImage;
}

void CVezba3View::DrawImage(int image, int x, int y, Hatch hatch)
{
	CBitmap bmpImage;
	BOOL suc = bmpImage.LoadBitmap(image);

	CBitmap bmpMask;
	BITMAP bm;
	bmpImage.GetBitmap(&bm);

	bmpMask.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	CDC* SrcDC = new CDC();
	SrcDC->CreateCompatibleDC(NULL);
	CDC* DstDC = new CDC();
	DstDC->CreateCompatibleDC(NULL);

	CBitmap* pOldSrcBmp = SrcDC->SelectObject(&bmpImage);
	CBitmap* pOldDstBmp = DstDC->SelectObject(&bmpMask);

	COLORREF clrTopLeft = SrcDC->GetPixel(0, 0);
	COLORREF clrSaveBk = SrcDC->SetBkColor(clrTopLeft);

	DstDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, SrcDC, 0, 0, SRCCOPY);

	COLORREF clrSaveDstText = SrcDC->SetTextColor(RGB(255, 255, 255));
	SrcDC->SetBkColor(RGB(0, 0, 0));
	SrcDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, DstDC, 0, 0, SRCAND);

	DstDC->SetTextColor(clrSaveDstText);
	SrcDC->SetBkColor(clrSaveBk);
	SrcDC->SelectObject(pOldSrcBmp);
	DstDC->SelectObject(pOldDstBmp);
	SrcDC->DeleteDC();
	delete SrcDC;
	DstDC->DeleteDC();
	delete DstDC;

	CDC* MemDC = new CDC();
	MemDC->CreateCompatibleDC(NULL);
	CBitmap* bmpOldT = MemDC->SelectObject(&bmpMask);
	pdc->BitBlt(x, y, bm.bmWidth, bm.bmHeight, MemDC, 0, 0, SRCAND);



	CBitmap* hatched = HatchImage(bm, &bmpImage, hatch);

	MemDC->SelectObject(hatched);
	pdc->BitBlt(x, y, bm.bmWidth, bm.bmHeight, MemDC, 0, 0, SRCPAINT);

	MemDC->SelectObject(bmpOldT);
	MemDC->DeleteDC();
	delete MemDC;
}

// CVezba3View drawing

void CVezba3View::OnDraw(CDC* pDC)
{
	SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	CVezba3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;

	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(501, 501);
	pDC->SetViewportExt(min(rect.right, rect.bottom), min(rect.right, rect.bottom));
	/*pDC->SetWindowExt(1000, 1000);
	pDC->SetWindowOrg(-500, -500);
	pDC->SetViewportExt(rect.right, rect.bottom);*/

	float multi = (float)501 / min(rect.right, rect.bottom);

	pDC->SetWindowOrg(-(rect.right - min(rect.right, rect.bottom)) / 2 * multi, -(rect.bottom - min(rect.right, rect.bottom)) / 2 * multi);

	pdc = pDC;

	DrawGrid();

	Hatch h;
	h.type = -1;
	SetTranlation(425.0, 425.0);
	SetRotation(-90.0);
	DrawImage(IDB_BITMAP1, -100.0, -37.5, h);

	h.r = 255;
	h.g = 0;
	h.b = 0;
	h.type = 9;
	SetRotation(0.0 + bigArmAngle);
	DrawImage(IDB_BITMAP2, -62.5, -290.0, h);

	h.r = 0;
	h.g = 255;
	h.b = 0;
	h.type = 3;
	SetTranlation(0.0, -254.5);
	SetRotation(90.0 + smallArmAngle);
	DrawImage(IDB_BITMAP3, -62.5, -225.0, h);

	h.type = -1;
	SetTranlation(0.0, -188.0);
	SetRotation(-90 + handAngle);
	DrawImage(IDB_BITMAP4, -37, -62, h);

	h.type = -1;
	MirrorVertical();
	SetRotation(180 + 2.0*handAngle);
	DrawImage(IDB_BITMAP4, -36, -62, h);
}


// CVezba3View printing

BOOL CVezba3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVezba3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVezba3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CVezba3View diagnostics

#ifdef _DEBUG
void CVezba3View::AssertValid() const
{
	CView::AssertValid();
}

void CVezba3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVezba3Doc* CVezba3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVezba3Doc)));
	return (CVezba3Doc*)m_pDocument;
}
#endif //_DEBUG



// CVezba3View message handlers


void CVezba3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	switch (nChar) {
	case 'q':case 'Q': bigArmAngle = (float)(bigArmAngle - (float)5); break;
	case 'w':case 'W': bigArmAngle = (float)(bigArmAngle + (float)5); break;
	case 'e':case 'E': smallArmAngle = (float)(smallArmAngle - (float)5); break;
	case 'r':case 'R': smallArmAngle = (float)(smallArmAngle + (float)5); break;
	case 't':case 'T': handAngle = (float)(handAngle - (float)5); break;
	case 'y':case 'Y': handAngle = (float)(handAngle + (float)5); break;
	}

	Invalidate();
	//CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
