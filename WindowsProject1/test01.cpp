#include <Windows.h>
#include "Resource.h"

#define	一定時間	3000 // ミリ秒単位
#define	TIMER_ID	1
WNDPROC wndproc;
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_LBUTTONDOWN:
		SetTimer
		( /*_In_opt_ HWND      hWnd       */hWnd
		, /*_In_     UINT_PTR  nIDEvent   */TIMER_ID
		, /*_In_     UINT      uElapse    */一定時間
		, /*_In_opt_ TIMERPROC lpTimerFunc*/nullptr
		);
		break;
	case WM_LBUTTONUP  :
		KillTimer
		( /*_In_opt_ HWND     hWnd    */hWnd
		, /*_In_     UINT_PTR uIDEvent*/TIMER_ID
		);
		break;
	case WM_TIMER:
		if (wParam == TIMER_ID) {
			OutputDebugStringA("時間が経過しました。\n");
			KillTimer
			( /*_In_opt_ HWND     hWnd    */hWnd
			, /*_In_     UINT_PTR uIDEvent*/TIMER_ID
			);
		}
		break;
	}
	return CallWindowProcW(wndproc, hWnd, uMsg, wParam, lParam);
}
void hook(HWND hWnd)
{
	wndproc = WNDPROC(GetWindowLongPtrW(hWnd, GWLP_WNDPROC));
	SetWindowLongPtrW(hWnd, GWLP_WNDPROC, LONG_PTR(WindowProc));
}
UINT CALLBACK ThreadProc(void* pv)
{
	return EXIT_SUCCESS;
}
HANDLE hThread;
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_INITDIALOG:
		hook(GetDlgItem(hDlg, IDOK));
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			return false;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}
int APIENTRY wWinMain
( _In_     HINSTANCE hInstance
, _In_opt_ HINSTANCE hPrevInstance
, _In_     LPWSTR    lpCmdLine
, _In_     int       nCmdShow
)
{
	DialogBoxParamW
	( /*_In_opt_ HINSTANCE hInstance     */hInstance
	, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG1)
	, /*_In_opt_ HWND      hWndParent    */nullptr
	, /*_In_opt_ DLGPROC   lpDialogFunc  */DialogProc
	, /*_In_     LPARAM    dwInitParam   */0
	);
}
/*
https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q10252934365

ID非公開さん

2021/11/23 18:26

0回答

c言語初心者です。
c言語で「一定時間ボタンを押され続けたら実行する」プログラムを組むには、どのようなソースコードにすれば良いでしょうか。
*/
