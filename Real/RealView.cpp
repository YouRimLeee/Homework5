﻿
// RealView.cpp: CRealView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Real.h"
#endif

#include "RealDoc.h"
#include "RealView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRealView

IMPLEMENT_DYNCREATE(CRealView, CView)

BEGIN_MESSAGE_MAP(CRealView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CRealView 생성/소멸

CRealView::CRealView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CRealView::~CRealView()
{
}

BOOL CRealView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CRealView 그리기

void CRealView::OnDraw(CDC* pDC)
{
	CRealDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CBrush brush;
	brush.CreateSolidBrush(RGB(rad % 256, 0, 0));
	pDC->SelectObject(&brush);
	pDC->Ellipse(m_pt1.x - m_Radius, m_pt1.y - m_Radius, m_pt1.x + m_Radius, m_pt1.y + m_Radius);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CRealView 인쇄

BOOL CRealView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CRealView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CRealView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CRealView 진단

#ifdef _DEBUG
void CRealView::AssertValid() const
{
	CView::AssertValid();
}

void CRealView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRealDoc* CRealView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRealDoc)));
	return (CRealDoc*)m_pDocument;
}
#endif //_DEBUG


// CRealView 메시지 처리기


int CRealView::Length(CPoint m_pt1, CPoint m_pt2)
{
	// TODO: 여기에 구현 코드 추가.
	rad = sqrt((m_pt2.x - m_pt1.x) * (m_pt2.x - m_pt1.x) + (m_pt2.y - m_pt1.y) * (m_pt2.y - m_pt1.y));
	return (rad);
}


void CRealView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pt1 = point;
	CView::OnLButtonDown(nFlags, point);
}


void CRealView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pt2 = point;
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CRealView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags & MK_LBUTTON)
	{
		m_pt2 = point;
		m_Radius = Length(m_pt1, m_pt2);
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}
