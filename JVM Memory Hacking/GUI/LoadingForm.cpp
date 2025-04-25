#include "LoadingForm.h"

#include "GUtils/GUtils.h"
#include "../Client/Memory/Minecraft.h"
#include "../Client/Utils/Utils.h"

#include "HandleSelector.h"

#include <iostream>
#include <algorithm>
#include <windows.h>

using namespace JVM_Memory_Hacking;

Point lf_point;
bool lf_onhover_bar = false;

System::Void LoadingForm::LoadingForm_Load(System::Object^ sender, System::EventArgs^ e) {
	GUtils::applyRoundedCorners(this, 15);

	label1->ForeColor = this->BackColor;
	label1->Location = System::Drawing::Point((this->ClientSize.Width - label1->Width) / 2,
		(this->ClientSize.Height - label1->Height) / 2);

	siticoneWinProgressIndicator1->Location = System::Drawing::Point((this->ClientSize.Width - siticoneWinProgressIndicator1->Width) / 2,
		(this->ClientSize.Height - siticoneWinProgressIndicator1->Height) / 2);

	label2->Location = System::Drawing::Point((this->ClientSize.Width - label2->Width) / 2,
		((this->ClientSize.Height - label1->Height) / 2) + siticoneWinProgressIndicator1->Height);

	if (!controlBarWorker->IsBusy) controlBarWorker->RunWorkerAsync();
};

System::Void LoadingForm::LoadingForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	GUtils::dragPanelMD(this, lf_point);
};

System::Void LoadingForm::LoadingForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	GUtils::dragPanelMM(this, lf_point, e);
};

System::Void LoadingForm::LoadingForm_Shown(System::Object^ sender, System::EventArgs^ e) {
	if (!animationWorker->IsBusy) animationWorker->RunWorkerAsync();
};

System::Void LoadingForm::animationWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {

	while (Opacity < 0.92) {
		Opacity += 0.04;
		System::Threading::Thread::Sleep(10);
		this->Refresh();
	}

	System::Threading::Thread::Sleep(150);

	while (label1->ForeColor.R < 255 || label1->ForeColor.G < 255 || label1->ForeColor.B < 255) {
		label1->ForeColor = System::Drawing::Color::FromArgb(std::clamp(label1->ForeColor.R + 1, 0, 255),
			std::clamp(label1->ForeColor.G + 1, 0, 255), std::clamp(label1->ForeColor.B + 1, 0, 255));
		this->Refresh();
	}

	System::Threading::Thread::Sleep(500);

	while (label1->ForeColor.R > 0 || label1->ForeColor.G > 0 || label1->ForeColor.B > 0) {
		label1->ForeColor = System::Drawing::Color::FromArgb(std::clamp(label1->ForeColor.R - 1, 0, 255),
			std::clamp(label1->ForeColor.G - 1, 0, 255), std::clamp(label1->ForeColor.B - 1, 0, 255));
		this->Refresh();
	}

	label1->Visible = false;

	while (siticoneWinProgressIndicator1->ProgressColor.R < 255 || siticoneWinProgressIndicator1->ProgressColor.G < 255 || siticoneWinProgressIndicator1->ProgressColor.B < 255) {
		siticoneWinProgressIndicator1->ProgressColor = System::Drawing::Color::FromArgb(std::clamp(siticoneWinProgressIndicator1->ProgressColor.R + 1, 0, 255),
			std::clamp(siticoneWinProgressIndicator1->ProgressColor.G + 1, 0, 255), std::clamp(siticoneWinProgressIndicator1->ProgressColor.B + 1, 0, 255));
		label2->ForeColor = System::Drawing::Color::FromArgb(std::clamp(label2->ForeColor.R + 1, 0, 255),
			std::clamp(label2->ForeColor.G + 1, 0, 255), std::clamp(label2->ForeColor.B + 1, 0, 255));
		this->Refresh();
	}

	HandleSelector^ handle_selector = gcnew HandleSelector();
	handle_selector->ShowDialog();
	System::Threading::Thread::Sleep(500);

	while (!Minecraft::injectClient()) System::Threading::Thread::Sleep(1);

	label2->Text = "Loading Completed!";
	System::Threading::Thread::Sleep(1500);
	loading_status = true;

	this->Close();
};

System::Void LoadingForm::closeButton_Click(System::Object^ sender, System::EventArgs^ e) {
	exit(0);
};

System::Void LoadingForm::hideButton_Click(System::Object^ sender, System::EventArgs^ e) {
	this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
};

System::Void LoadingForm::controlBar_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
	lf_onhover_bar = false;
};

System::Void LoadingForm::controlBar_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
	lf_onhover_bar = true;
};

System::Void LoadingForm::controlBarWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	while (true) {
		if (lf_onhover_bar) {
			while (closeButton->Location.Y < 7) {
				closeButton->Location = System::Drawing::Point(closeButton->Location.X, closeButton->Location.Y + 1);
				System::Threading::Thread::Sleep(1);
			}

			while (hideButton->Location.Y < 7) {
				hideButton->Location = System::Drawing::Point(hideButton->Location.X, hideButton->Location.Y + 1);
				System::Threading::Thread::Sleep(1);
			}

			while (lf_onhover_bar) System::Threading::Thread::Sleep(1);

			while (hideButton->Location.Y > -closeButton->Height) {
				hideButton->Location = System::Drawing::Point(hideButton->Location.X, hideButton->Location.Y - 1);
				System::Threading::Thread::Sleep(1);
			}

			while (closeButton->Location.Y > -closeButton->Height) {
				closeButton->Location = System::Drawing::Point(closeButton->Location.X, closeButton->Location.Y - 1);
				System::Threading::Thread::Sleep(1);
			}

			System::Threading::Thread::Sleep(500);
		}
		else System::Threading::Thread::Sleep(100);
	}
};