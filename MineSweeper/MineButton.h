#pragma once

using namespace System::Windows::Forms;


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

    }
};
