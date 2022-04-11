#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"

class size_dialog : public vsite::nwp::dialog {
public:
	int x, y;
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
};

class main_window : public vsite::nwp::window {
private:
	int x, y;
	COLORREF color;
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
	int getx() { return x; };
	int gety() { return y; };
	COLORREF getcolor() { return color; };
public:
	void setx(int gx) { x = gx; };
	void sety(int gy) { y = gy; };
	void setcolor(COLORREF gcolor) { color = gcolor; };
};
