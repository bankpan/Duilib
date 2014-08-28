#pragma once

#include "resource.h"
class CMainFrame :
	public DuiLib::CWindowWnd,public INotifyUI//应用程序窗口类CWindowWnd
{
public:
	CMainFrame(void);
	~CMainFrame(void);

	LPCTSTR CMainFrame::GetWindowClassName() const ;

	void CMainFrame::OnPrepare() ;
	void CMainFrame::Notify(TNotifyUI& msg);

	LRESULT CMainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CPaintManagerUI m_pm;  
};
