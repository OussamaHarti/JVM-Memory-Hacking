#pragma once

namespace JVM_Memory_Hacking {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class HandleSelector : public System::Windows::Forms::Form
	{
	public:
		HandleSelector(void)
		{
			InitializeComponent();
		}

	protected:
		~HandleSelector()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::BackgroundWorker^ animationWorker;
	private: System::Windows::Forms::Label^ label1;
	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->animationWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// animationWorker
			// 
			this->animationWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &HandleSelector::animationWorker_DoWork);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 16, System::Drawing::FontStyle::Bold));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(95, 147);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(149, 98);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Select Minecraft Window";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// HandleSelector
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(14)));
			this->ClientSize = System::Drawing::Size(338, 392);
			this->Controls->Add(this->label1);
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(10)), static_cast<System::Int32>(static_cast<System::Byte>(8)),
				static_cast<System::Int32>(static_cast<System::Byte>(14)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"HandleSelector";
			this->Opacity = 0;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HandleSelector";
			this->Load += gcnew System::EventHandler(this, &HandleSelector::HandleSelector_Load);
			this->Shown += gcnew System::EventHandler(this, &HandleSelector::HandleSelector_Shown);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &HandleSelector::HandleSelector_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &HandleSelector::HandleSelector_MouseMove);
			this->ResumeLayout(false);

		}
#pragma endregion

	System::Void HandleSelector_Load(System::Object^ sender, System::EventArgs^ e);

	System::Void HandleSelector_Shown(System::Object^ sender, System::EventArgs^ e);

	System::Void animationWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);

	System::Void HandleSelector_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	System::Void HandleSelector_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	};
}
