#pragma once

using namespace System::Windows::Forms;
using namespace System::Drawing;


public ref class MineButton : public Button
{
    
public:
    property int Row;
    property int Col;
    property bool IsMine;
    property bool IsRevealed;
    property int AdjacentMines;
    property bool IsFlagged;
  

    MineButton(int row, int col)
    {
        Row = row;
        Col = col;
        IsMine = false;
        IsRevealed = false;
        AdjacentMines = 0;
        IsFlagged = false;

        this->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        this->FlatAppearance->BorderSize = 0;
        this->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
        this->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
        this->BackColor = System::Drawing::Color::Transparent;
        Bitmap^ image = gcnew Bitmap("Slot_Covered.png");
        this->Image = image;      
    }

    void OnMouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
    {
        if (e->Button == System::Windows::Forms::MouseButtons::Left)
        {
            if (IsMine)
            {
                this->Text = "B";

                Bitmap^ bombImage = gcnew Bitmap("Bomb_Image.png");
                this->Image = bombImage;
            }
            else
            {
                Bitmap^ uncoveredImage = gcnew Bitmap("Slot_Uncovered.png");
                this->Image = uncoveredImage;

                if (AdjacentMines > 0)
                {
                    this->Text = AdjacentMines.ToString();
                }
            }

            IsRevealed = true;
        }
        else if (e->Button == System::Windows::Forms::MouseButtons::Right)
        {
            if (!IsRevealed)
            {
                if (!IsFlagged)
                {
                    this->Text = "F";

                    Bitmap^ flaggedImage = gcnew Bitmap("Flagged_Image.png");
                    this->Image = flaggedImage;
                }
                else
                {
                    this->Text = "";

                    Bitmap^ coveredImage = gcnew Bitmap("Slot_Covered.png");
                    this->Image = coveredImage;
                }

                IsFlagged = !IsFlagged;
            }
        }
    }
};
