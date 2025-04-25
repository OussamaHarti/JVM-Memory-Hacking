#pragma once

namespace JVM_Memory_Hacking {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class LoadingForm : public System::Windows::Forms::Form {
	public:
		LoadingForm(void){
			InitializeComponent();
		}

	protected:
		~LoadingForm(){
			if (components) delete components;
		}

	public: bool loading_status = false;

	private: Siticone::UI::WinForms::SiticoneWinProgressIndicator^ siticoneWinProgressIndicator1;
	private: System::Windows::Forms::Label^ label1;
	private: System::ComponentModel::BackgroundWorker^ animationWorker;
	private: Siticone::UI::WinForms::SiticoneCircleButton^ closeButton;
	private: Siticone::UI::WinForms::SiticoneCircleButton^ hideButton;
	private: System::Windows::Forms::Panel^ controlBar;
	private: System::ComponentModel::BackgroundWorker^ controlBarWorker;
	private: System::Windows::Forms::Label^ label2;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void){
			this->siticoneWinProgressIndicator1 = (gcnew Siticone::UI::WinForms::SiticoneWinProgressIndicator());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->animationWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->closeButton = (gcnew Siticone::UI::WinForms::SiticoneCircleButton());
			this->hideButton = (gcnew Siticone::UI::WinForms::SiticoneCircleButton());
			this->controlBar = (gcnew System::Windows::Forms::Panel());
			this->controlBarWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// siticoneWinProgressIndicator1
			// 
			this->siticoneWinProgressIndicator1->AutoStart = true;
			this->siticoneWinProgressIndicator1->BackColor = System::Drawing::Color::Transparent;
			this->siticoneWinProgressIndicator1->CircleSize = 1;
			this->siticoneWinProgressIndicator1->Location = System::Drawing::Point(360, 230);
			this->siticoneWinProgressIndicator1->Name = L"siticoneWinProgressIndicator1";
			this->siticoneWinProgressIndicator1->ProgressColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)),
				static_cast<System::Int32>(static_cast<System::Byte>(8)), static_cast<System::Int32>(static_cast<System::Byte>(14)));
			this->siticoneWinProgressIndicator1->Size = System::Drawing::Size(90, 90);
			this->siticoneWinProgressIndicator1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 26, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(318, 256);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(174, 41);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Welcome";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// animationWorker
			// 
			this->animationWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &LoadingForm::animationWorker_DoWork);
			// 
			// closeButton
			// 
			this->closeButton->BackColor = System::Drawing::Color::Transparent;
			this->closeButton->BorderColor = System::Drawing::Color::Transparent;
			this->closeButton->CheckedState->Parent = this->closeButton;
			this->closeButton->CustomImages->Parent = this->closeButton;
			this->closeButton->FillColor = System::Drawing::Color::Transparent;
			this->closeButton->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8.18868F, System::Drawing::FontStyle::Bold));
			this->closeButton->ForeColor = System::Drawing::Color::White;
			this->closeButton->HoveredState->Parent = this->closeButton;
			this->closeButton->Location = System::Drawing::Point(782, 8);
			this->closeButton->Name = L"closeButton";
			this->closeButton->PressedColor = System::Drawing::Color::Transparent;
			this->closeButton->ShadowDecoration->Mode = Siticone::UI::WinForms::Enums::ShadowMode::Circle;
			this->closeButton->ShadowDecoration->Parent = this->closeButton;
			this->closeButton->Size = System::Drawing::Size(22, 22);
			this->closeButton->TabIndex = 3;
			this->closeButton->Text = L"X";
			this->closeButton->Click += gcnew System::EventHandler(this, &LoadingForm::closeButton_Click);
			// 
			// hideButton
			// 
			this->hideButton->BackColor = System::Drawing::Color::Transparent;
			this->hideButton->BorderColor = System::Drawing::Color::Transparent;
			this->hideButton->CheckedState->Parent = this->hideButton;
			this->hideButton->CustomImages->Parent = this->hideButton;
			this->hideButton->FillColor = System::Drawing::Color::Transparent;
			this->hideButton->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 11.18868F, System::Drawing::FontStyle::Bold));
			this->hideButton->ForeColor = System::Drawing::Color::White;
			this->hideButton->HoveredState->Parent = this->hideButton;
			this->hideButton->Location = System::Drawing::Point(754, 8);
			this->hideButton->Name = L"hideButton";
			this->hideButton->PressedColor = System::Drawing::Color::Transparent;
			this->hideButton->ShadowDecoration->Mode = Siticone::UI::WinForms::Enums::ShadowMode::Circle;
			this->hideButton->ShadowDecoration->Parent = this->hideButton;
			this->hideButton->Size = System::Drawing::Size(22, 22);
			this->hideButton->TabIndex = 4;
			this->hideButton->Text = L"-";
			this->hideButton->Click += gcnew System::EventHandler(this, &LoadingForm::hideButton_Click);
			// 
			// controlBar
			// 
			this->controlBar->BackColor = System::Drawing::Color::Transparent;
			this->controlBar->ForeColor = System::Drawing::Color::Transparent;
			this->controlBar->Location = System::Drawing::Point(0, 0);
			this->controlBar->Name = L"controlBar";
			this->controlBar->Size = System::Drawing::Size(810, 38);
			this->controlBar->TabIndex = 5;
			this->controlBar->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &LoadingForm::LoadingForm_MouseDown);
			this->controlBar->MouseEnter += gcnew System::EventHandler(this, &LoadingForm::controlBar_MouseEnter);
			this->controlBar->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &LoadingForm::LoadingForm_MouseMove);
			// 
			// controlBarWorker
			// 
			this->controlBarWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &LoadingForm::controlBarWorker_DoWork);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom));
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 10));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(14)));
			this->label2->Location = System::Drawing::Point(318, 323);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(174, 16);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Loading...";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// LoadingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(14)));
			this->ClientSize = System::Drawing::Size(810, 553);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->hideButton);
			this->Controls->Add(this->closeButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->siticoneWinProgressIndicator1);
			this->Controls->Add(this->controlBar);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(14)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"LoadingForm";
			this->Opacity = 0;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"LoadingForm";
			this->Load += gcnew System::EventHandler(this, &LoadingForm::LoadingForm_Load);
			this->Shown += gcnew System::EventHandler(this, &LoadingForm::LoadingForm_Shown);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &LoadingForm::LoadingForm_MouseDown);
			this->MouseEnter += gcnew System::EventHandler(this, &LoadingForm::controlBar_MouseLeave);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &LoadingForm::LoadingForm_MouseMove);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	System::Void LoadingForm_Load(System::Object^ sender, System::EventArgs^ e);

	System::Void LoadingForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	System::Void LoadingForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	
	System::Void LoadingForm_Shown(System::Object^ sender, System::EventArgs^ e);

	System::Void animationWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	
	System::Void closeButton_Click(System::Object^ sender, System::EventArgs^ e);
	
	System::Void hideButton_Click(System::Object^ sender, System::EventArgs^ e);

	System::Void controlBar_MouseLeave(System::Object^ sender, System::EventArgs^ e);

	System::Void controlBar_MouseEnter(System::Object^ sender, System::EventArgs^ e);

	System::Void controlBarWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
};

}
