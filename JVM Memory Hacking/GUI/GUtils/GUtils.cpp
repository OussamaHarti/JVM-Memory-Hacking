#include "GUtils.h"
#include <Windows.h>

namespace GUtils {
    void applyRoundedCorners(System::Windows::Forms::Form^ form, unsigned short radius) {
        HRGN region = CreateRoundRectRgn(0, 0, form->Width, form->Height, radius, radius);
        SetWindowRgn((HWND)form->Handle.ToPointer(), region, TRUE);
    };

	void dragPanelMD(System::Windows::Forms::Form^ form, System::Drawing::Point& pt) {
		pt = form->Cursor->Position;
	};

	void dragPanelMM(System::Windows::Forms::Form^ form, System::Drawing::Point& pt, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			form->Location = System::Drawing::Point(form->Location.X + form->Cursor->Position.X - pt.X, form->Location.Y + form->Cursor->Position.Y - pt.Y);

			pt = form->Cursor->Position;
		}
	};
}