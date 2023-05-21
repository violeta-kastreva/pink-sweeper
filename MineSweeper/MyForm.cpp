#include "MyForm.h"
/**
    loads the form 
    source: ChatGPT
*/
[System::STAThread]
void main(array <System::String^>^ args) {
    System::Windows::Forms::Application::EnableVisualStyles();
    System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);

    MineSweeper::MyForm form; 
    System::Windows::Forms::Application::Run(% form);
}