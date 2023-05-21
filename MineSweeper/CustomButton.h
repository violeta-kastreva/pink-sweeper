#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

/**
    class, not being used in the current version of the game, similar to the MineButton class
*/
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
};

