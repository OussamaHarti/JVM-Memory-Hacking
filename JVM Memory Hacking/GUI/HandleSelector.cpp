#include "HandleSelector.h"
#include "GUtils/GUtils.h"

#include "../Client/Scanner/Scanner.h"

using namespace JVM_Memory_Hacking;
Point hs_point;

System::Void HandleSelector::HandleSelector_Load(System::Object^ sender, System::EventArgs^ e) {
	GUtils::applyRoundedCorners(this, 15);
};

System::Void HandleSelector::HandleSelector_Shown(System::Object^ sender, System::EventArgs^ e) {
	if (!animationWorker->IsBusy) animationWorker->RunWorkerAsync();
};

System::Void HandleSelector::HandleSelector_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	GUtils::dragPanelMD(this, hs_point);
};

System::Void HandleSelector::HandleSelector_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	GUtils::dragPanelMM(this, hs_point, e);
};

System::Void HandleSelector::animationWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	HWND hwnd = NULL;

	while (Opacity < 0.92) {
		Opacity += 0.04;
		System::Threading::Thread::Sleep(10);
		this->Refresh();
	}

	while (hwnd != FindWindowA("GLFW30", NULL) || hwnd == NULL) {
		hwnd = GetForegroundWindow();
		System::Threading::Thread::Sleep(1);
	}

	if (!Scanner::initScanners(hwnd)) {
		label1->Text = "Version Not Compatible";
		System::Threading::Thread::Sleep(1500);
		exit(0);
	}

	while (Opacity > 0.04) {
		Opacity -= 0.04;
		System::Threading::Thread::Sleep(10);
		this->Refresh();
	}

	this->Close();
};