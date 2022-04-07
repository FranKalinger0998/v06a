#include "main.h"
#include "rc.h"

int x=8;
int y=8;
COLORREF color = RGB(33, 33, 33);

COLORREF get_color(HWND parent) {
	CHOOSECOLOR cc;                 // common dialog box structure 
	static COLORREF acrCustClr[16]; // array of custom colors 
	                    // owner window
	HBRUSH hbrush;                  // brush handle
	static DWORD rgbCurrent;        // initial color selection

	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = parent;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc) == TRUE)
	{
		hbrush = CreateSolidBrush(cc.rgbResult);
		rgbCurrent = cc.rgbResult;
	}
	return rgbCurrent;


	
}
int size_dialog::idd() const {
	return IDD_SIZE; 
}

bool size_dialog::on_init_dialog(){
	set_int(IDC_EDIT1, x);
	set_int(IDC_EDIT2, y);
	return true;
}

bool size_dialog::on_ok(){
	
	try
	{
		x=get_int(IDC_EDIT1);
		y=get_int(IDC_EDIT2);
	}
	catch (...)
	{
		return false;
	}
	return true;
	
}


void main_window::on_paint(HDC hdc){

	HBRUSH brush = CreateSolidBrush(color);
	HBRUSH brush2 = CreateSolidBrush(RGB(255,255,255));
	RECT mr;
	
	
	GetClientRect(*this, &mr);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, mr.right, mr.bottom, 0);
	
	
	SetWindowExtEx(hdc, x*2, y*2, 0);
	
	for (int i = 0; i < x*2; i += 2) {
		for (int j = (i & 2); j < y*2; j += 4) {
			RECT r = { i, j, i + 2, j + 2 };
			FillRect(hdc, &r, brush);
			// r = { i+1, j-1, i + 2, j + 2 };
			//FillRect(hdc, &r, brush2);
			
		}

	}
	DeleteObject(brush);
}

void main_window::on_command(int id){
	size_dialog s_dlg;
	s_dlg.x = x;
	s_dlg.y = y;
	switch(id){
		case ID_SIZE:
			if (s_dlg.do_modal(0, *this) == IDOK) {
				if (s_dlg.x < 0 || s_dlg.y < 0) {
					MessageBox(*this, (LPCWSTR)"Please enter positive number", (LPCWSTR)"Warning", MB_OK | MB_ICONWARNING);
				}
				else {
					x = s_dlg.x;
					y = s_dlg.y;
					InvalidateRect(*this, NULL, true);
				}

			}
			break;
			
			
		case ID_COLOR:
			color = get_color(*this);
			InvalidateRect(*this, NULL, true);

			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window wnd;	
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.run();
}
