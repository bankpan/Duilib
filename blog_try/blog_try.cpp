// blog_try.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "blog_try.h"


CMainFrame::CMainFrame(void)
{
}
CMainFrame::~CMainFrame(void)
{
}
LPCTSTR CMainFrame::GetWindowClassName() const //重写获取类名函数，也就是指定要新建的窗口类的类名
{ 
	return _T("UIMainFrame"); 
}
void CMainFrame::OnPrepare() 
{
}
void CMainFrame::Notify(TNotifyUI& msg)//处理窗口通知消息，响应用户的输入
{
	if( msg.sType == _T("windowinit") ) OnPrepare();

}
LRESULT CMainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled){
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);//主窗口类与窗口句柄关联
	CDialogBuilder builder;

	CControlUI* pRoot = builder.Create(_T("UISkin.xml"), (UINT)0, NULL, &m_pm);//加载XML并动态创建界面无素，与布局界面元素，核心函数单独分析
	//注意：CDialogBuilder 并不是一个对话框类
	ASSERT(pRoot && "Failed to parse XML");
	if (NULL==pRoot)//如果找不到皮肤文件则退出
	{
		MessageBox(NULL,TEXT("Cant not find the skin!"),NULL,MB_ICONHAND);
		return 0;
	}
	m_pm.AttachDialog(pRoot);//附加控件数据到HASH表中……为pRoot作为对话框结点，为其创建控件树	
	m_pm.AddNotifier(this);//增加通知处理

	return 0;
}
LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;
		switch( uMsg ) {
		case WM_CREATE: 
			//lRes = OnCreate(uMsg, wParam, lParam, bHandled); 
			{
				m_pm.Init(m_hWnd);
				CControlUI* pButton=new CButtonUI;
				pButton->SetName(_T("closebtn"));
				pButton->SetBkColor(0xFFFF0000);
				m_pm.AttachDialog(pButton);
				m_pm.AddNotifier(this);
				break;
			}
		case WM_DESTROY:
			::PostQuitMessage(0);

		default:
		bHandled = FALSE;
		}
		if( bHandled ) return lRes;
		if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);//设置程序实例
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() 
	//	+ _T("skin"));//实例句柄与渲染类关联,获得皮肤文件目录（加载皮肤文件在OnCreate之中）
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	//HRESULT Hr = ::CoInitialize(NULL);//初始化COM库, 为加载COM库提供支持
	//if( FAILED(Hr) ) 
		//return 0;

	CMainFrame* pMainFrame = new CMainFrame();//创建应用程序窗口类对象
	if( pMainFrame == NULL ) 
		return 0;
	//pMainFrame->Create(NULL, _T("AdderCalc"), UI_WNDSTYLE_DIALOG, 0);
	pMainFrame->Create(NULL, _T("AdderCalc"), UI_WNDSTYLE_FRAME,WS_EX_WINDOWEDGE);
	pMainFrame->CenterWindow();//将窗口放到桌面中央
	pMainFrame->ShowWindow(true);//显示窗口
	CPaintManagerUI::MessageLoop();//进入消息循环

	//::CoUninitialize();//退出程序并释放COM库
	return 0;
}



