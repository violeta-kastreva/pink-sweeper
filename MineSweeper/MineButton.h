#pragma once

using namespace System::Windows::Forms;
using namespace System::Drawing;


/**
* inherits the button class from the .NET library with added functionalities for the MineSweeper game
*/

public ref class MineButton : public Button
{
    
public:
    property int Row; //! row index at the grid
    property int Col; //! col index at the grid
    property bool IsMine; //! whether the button contains a mine or not
    property bool IsRevealed; //! whether the button is clicked on already during the game (the button becomes revealed after being left-clicked on)
    property int AdjacentMines; //! the number of adjacent mine buttons on the grid
    property bool IsFlagged; //! whether the button is "flagged" (marked by the player as a potential mine)
    property bool IsDisabled; //! the button becomes disabled if revealed, used for tracking game progress
  

    MineButton(int row, int col)
    {
        Row = row;
        Col = col;
        IsMine = false;
        IsRevealed = false;
        AdjacentMines = 0;
        IsFlagged = false;
        IsDisabled = false;

        this->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        this->FlatAppearance->BorderSize = 0;
        this->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
        this->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
        this->BackColor = System::Drawing::Color::Transparent;
        Bitmap^ image = gcnew Bitmap("Slot_Covered.png");
        this->Image = image;
    }
    /**
    * default constructor
    */
    MineButton()
    {
        Row = 0;
        Col = 0;
        IsMine = false;
        IsRevealed = false;
        AdjacentMines = 0;
        IsFlagged = false;
        IsDisabled = false;

        this->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
        this->FlatAppearance->BorderSize = 0;
        this->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
        this->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
        this->BackColor = System::Drawing::Color::Transparent;
        Bitmap^ image = gcnew Bitmap("Slot_Covered.png");
        this->Image = image;
    }

    /**
    * changing the button's look in the form once it becomes disabled
    */
    void DisableButton()
    {
        IsDisabled = true;
        this->ForeColor = System::Drawing::Color::White;
        Bitmap^ uncoveredImage = gcnew Bitmap("Slot_Uncovered.png");
        this->Image = uncoveredImage;
    }


};
