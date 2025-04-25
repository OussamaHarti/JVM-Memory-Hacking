#include "GUI/LoadingForm.h"
#include <windows.h>
#include "Client/Scanner/Scanner.h"
#include "Client/Memory/Minecraft.h"
#include "GUI\Interface.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
    timeBeginPeriod(1);
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    JVM_Memory_Hacking::LoadingForm loadingForm;
    Application::Run(%loadingForm);

    if (loadingForm.loading_status) {
        JVM_Memory_Hacking::Interface gui_interface;
        Application::Run(%gui_interface);
    }

    return 0;
}
