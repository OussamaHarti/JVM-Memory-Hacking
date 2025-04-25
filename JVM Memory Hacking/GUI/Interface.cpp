#include "Interface.h"

#include "GUtils/GUtils.h"
#include "../Client/Memory/World.h"

constexpr short frames_ms = 33; // 30 frames per second

using namespace JVM_Memory_Hacking;

Point if_point;
bool if_onhover_bar = false;

System::Void Interface::Interface_Load(System::Object^ sender, System::EventArgs^ e) {
	GUtils::applyRoundedCorners(this, 15);

	label1->Location = System::Drawing::Point((this->ClientSize.Width - label1->Width) / 2,
		(this->ClientSize.Height - label1->Height - controlBar->Height) / 2 + controlBar->Height);

	if (!controlBarWorker->IsBusy) controlBarWorker->RunWorkerAsync();
	if (!mapWorker->IsBusy) mapWorker->RunWorkerAsync();
};

System::Void Interface::animationWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	while (Opacity < 0.92) {
		Opacity += 0.04;
		System::Threading::Thread::Sleep(10);
		this->Refresh();
	}
};

System::Void Interface::Interface_Shown(System::Object^ sender, System::EventArgs^ e) {
	if (!animationWorker->IsBusy) animationWorker->RunWorkerAsync();
};

System::Void Interface::Interface_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	GUtils::dragPanelMD(this, if_point);
};

System::Void Interface::Interface_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	GUtils::dragPanelMM(this, if_point, e);
};

System::Void Interface::closeButton_Click(System::Object^ sender, System::EventArgs^ e) {
	exit(0);
};

System::Void Interface::hideButton_Click(System::Object^ sender, System::EventArgs^ e) {
	this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
};

System::Void Interface::controlBar_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
	if_onhover_bar = false;
};

System::Void Interface::controlBar_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
	if_onhover_bar = true;
};

System::Void Interface::controlBarWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	while (true) {
		if (if_onhover_bar) {
			while (closeButton->Location.Y < 7) {
				closeButton->Location = System::Drawing::Point(closeButton->Location.X, closeButton->Location.Y + 1);
				System::Threading::Thread::Sleep(1);
			}

			while (hideButton->Location.Y < 7) {
				hideButton->Location = System::Drawing::Point(hideButton->Location.X, hideButton->Location.Y + 1);
				System::Threading::Thread::Sleep(1);
			}

			while (if_onhover_bar) System::Threading::Thread::Sleep(1);

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

System::Drawing::Point rotateAroundPoint(System::Drawing::Point center, System::Drawing::Point point, const float angle) {
	float angle_radians = angle * M_PI / 180.0;

	float relativeX = point.X - center.X;
	float relativeY = point.Y - center.Y;

	float rotatedX = relativeX * cos(angle_radians) - relativeY * sin(angle_radians);
	float rotatedY = relativeX * sin(angle_radians) + relativeY * cos(angle_radians);

	return System::Drawing::Point(center.X - rotatedX, center.Y + rotatedY);
};

System::Void Interface::mapWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
	float vertex_x = 0, vertex_y = controlBar->Height, size_x = this->Width, size_y = this->Height - controlBar->Height, thickness = 3, radius = 10, ratio = 7.f;;
	System::Drawing::Point center_position(vertex_x + (size_x / 2), vertex_y + (size_y / 2));

	Graphics^ graphics = this->CreateGraphics();
	SolidBrush^ white_brush = gcnew SolidBrush(Color::White);
	SolidBrush^ green_brush = gcnew SolidBrush(Color::Green);

	while (true) {
		Entity::EntityStruct local_player = Entity::getEntity(Minecraft::getLocalPlayerPtr(), "", false);
		label2->Text = "X:" + ((int)local_player.position.x).ToString() + "  Y:" + ((int)local_player.position.y).ToString() + "  Z:" + ((int)local_player.position.z).ToString();

		std::string target = (checkBox1->Checked) ? "player" : "";
		std::vector<Entity::EntityStruct> entity_list = World::getEntityList(target);

		for (size_t i = 0; i < entity_list.size(); i++) {
			System::Drawing::Point buff = rotateAroundPoint(System::Drawing::Point(0, 0),
				System::Drawing::Point(-(float)local_player.position.x + (float)entity_list[i].position.x, (float)local_player.position.z - (float)entity_list[i].position.z),
				Entity::getEntityFaceX(Minecraft::getLocalPlayerAddress()));

			buff.X *= ratio;
			buff.Y *= ratio;

			if (abs(buff.X) < (size_x / 2) - (thickness + radius) && abs(buff.Y) < (size_y / 2) - (thickness + radius)) {
				(entity_list[i].entity_type == "player") ?
					graphics->FillEllipse(green_brush, (int)(center_position.X + buff.X - (radius / 2)), (int)(center_position.Y + buff.Y - (radius / 2)), (int)radius, (int)radius) :
					graphics->FillEllipse(white_brush, (int)(center_position.X + buff.X - (radius / 2)), (int)(center_position.Y + buff.Y - (radius / 2)), (int)radius, (int)radius);
			}
		}

		System::Threading::Thread::Sleep(frames_ms);
		this->Invalidate();
	}
};