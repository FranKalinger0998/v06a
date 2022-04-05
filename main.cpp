#include "main.h"
#include "rc.h"

int size_dialog::idd() const {
	return IDD_SIZE; 
}

bool size_dialog::on_init_dialog(){
	return true;
}

bool size_dialog::on_ok(){
	return true;
}


void main_window::on_paint(HDC hdc){
	
	HBRUSH brush = CreateSolidBrush(RGB(33, 33, 33));
	RECT mr;
	
	
	GetClientRect(*this, &mr);
	SetViewportExtEx(hdc, mr.right, mr.bottom, 0);
	SetMapMode(hdc, MM_ANISOTROPIC);

	SetWindowExtEx(hdc, x, y, 0);
	for (int i = 0; i < x; i++) {
		for (int j = (i & 1); j < y; j += 2) {
			RECT r = { i, j, i + 1, j + 1 };
			FillRect(hdc, &r, brush);
		}

	}
	DeleteObject(brush);
}

void main_window::on_command(int id){
	switch(id){
		case ID_SIZE:
			break;
		case ID_COLOR:
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
