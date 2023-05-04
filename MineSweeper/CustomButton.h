#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class CustomButton : public Button
{
public:
    CustomButton()
    {
        this->SetStyle(ControlStyles::Opaque, true);
        this->SetStyle(ControlStyles::ResizeRedraw, true);
        this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
        this->SetStyle(ControlStyles::UserPaint, true);
        this->BackColor = Color::Transparent;
    }

protected:
    virtual void OnPaint(PaintEventArgs^ e) override
    {
        // Call the base class OnPaint method first
        __super::OnPaint(e);

        // Set the button text properties
        e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
        e->Graphics->TextRenderingHint = System::Drawing::Text::TextRenderingHint::ClearTypeGridFit;

        // Draw the button text
        if (Pressed)
        {
            e->Graphics->DrawString(this->Text, this->Font, gcnew SolidBrush(this->ForeColor), Point(2, 2));
        }
        else
        {
            e->Graphics->DrawString(this->Text, this->Font, gcnew SolidBrush(this->ForeColor), Point(0, 0));
        }
    }


    virtual void OnGotFocus(EventArgs^ e) override
    {
        this->Invalidate();
    }

    virtual void OnLostFocus(EventArgs^ e) override
    {
        this->Invalidate();
    }

private:
    property bool Pressed
    {
        bool get() { return (this->MouseButtons & System::Windows::Forms::MouseButtons::Left) == System::Windows::Forms::MouseButtons::Left; }
    }
};

