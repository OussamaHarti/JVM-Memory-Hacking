#pragma once

namespace JVM_Memory_Hacking {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Interface : public System::Windows::Forms::Form
	{
	public:
		Interface(void)
		{
			InitializeComponent();
		}

	protected:
		~Interface()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::BackgroundWorker^ animationWorker;
	private: Siticone::UI::WinForms::SiticoneCircleButton^ hideButton;
	private: Siticone::UI::WinForms::SiticoneCircleButton^ closeButton;
	private: System::Windows::Forms::Panel^ controlBar;
	private: System::ComponentModel::BackgroundWorker^ controlBarWorker;
	private: System::ComponentModel::BackgroundWorker^ mapWorker;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->animationWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->hideButton = (gcnew Siticone::UI::WinForms::SiticoneCircleButton());
			this->closeButton = (gcnew Siticone::UI::WinForms::SiticoneCircleButton());
			this->controlBar = (gcnew System::Windows::Forms::Panel());
			this->controlBarWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->mapWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// animationWorker
			// 
			this->animationWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Interface::animationWorker_DoWork);
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
			this->hideButton->TabIndex = 7;
			this->hideButton->Text = L"-";
			this->hideButton->Click += gcnew System::EventHandler(this, &Interface::hideButton_Click);
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
			this->closeButton->TabIndex = 6;
			this->closeButton->Text = L"X";
			this->closeButton->Click += gcnew System::EventHandler(this, &Interface::closeButton_Click);
			// 
			// controlBar
			// 
			this->controlBar->BackColor = System::Drawing::Color::Transparent;
			this->controlBar->ForeColor = System::Drawing::Color::Transparent;
			this->controlBar->Location = System::Drawing::Point(0, 0);
			this->controlBar->Name = L"controlBar";
			this->controlBar->Size = System::Drawing::Size(810, 38);
			this->controlBar->TabIndex = 8;
			this->controlBar->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Interface::Interface_MouseDown);
			this->controlBar->MouseEnter += gcnew System::EventHandler(this, &Interface::controlBar_MouseEnter);
			this->controlBar->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Interface::Interface_MouseMove);
			// 
			// controlBarWorker
			// 
			this->controlBarWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Interface::controlBarWorker_DoWork);
			// 
			// mapWorker
			// 
			this->mapWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Interface::mapWorker_DoWork);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.22642F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Red;
			this->label1->Location = System::Drawing::Point(394, 284);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(28, 24);
			this->label1->TabIndex = 9;
			this->label1->Text = L"◯";
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(12, 526);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(49, 16);
			this->label2->TabIndex = 10;
			this->label2->Text = L"(0,0,0)";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->BackColor = System::Drawing::Color::Transparent;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkBox1->ForeColor = System::Drawing::Color::White;
			this->checkBox1->Location = System::Drawing::Point(656, 526);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(142, 20);
			this->checkBox1->TabIndex = 11;
			this->checkBox1->Text = L"Show only players";
			this->checkBox1->UseVisualStyleBackColor = false;
			// 
			// Interface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(14)));
			this->ClientSize = System::Drawing::Size(810, 553);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->hideButton);
			this->Controls->Add(this->closeButton);
			this->Controls->Add(this->controlBar);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(14)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Interface";
			this->Opacity = 0;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Interface";
			this->Load += gcnew System::EventHandler(this, &Interface::Interface_Load);
			this->Shown += gcnew System::EventHandler(this, &Interface::Interface_Shown);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Interface::Interface_MouseDown);
			this->MouseEnter += gcnew System::EventHandler(this, &Interface::controlBar_MouseLeave);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Interface::Interface_MouseMove);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		System::Void Interface_Load(System::Object^ sender, System::EventArgs^ e);

		System::Void animationWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	
		System::Void Interface_Shown(System::Object^ sender, System::EventArgs^ e);

		System::Void Interface_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

		System::Void Interface_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

		System::Void closeButton_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void hideButton_Click(System::Object^ sender, System::EventArgs^ e);

		System::Void controlBar_MouseLeave(System::Object^ sender, System::EventArgs^ e);

		System::Void controlBar_MouseEnter(System::Object^ sender, System::EventArgs^ e);

		System::Void controlBarWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	
		System::Void mapWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
};
}
