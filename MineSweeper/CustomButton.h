#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class CustomButton : public System::Windows::Forms::Button
{
public:
    CustomButton()
    {
        this->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        this->FlatAppearance->BorderSize = 0;
        this->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
        this->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
        this->BackColor = System::Drawing::Color::Transparent;
    }

protected:
     


    virtual void OnGotFocus(EventArgs^ e) override
    {

    }

    virtual void OnLostFocus(EventArgs^ e) override
    {
     
    }

};

