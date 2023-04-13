#pragma once
#include "MineButton.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

ref class MineButton;

public ref class MineField
{
public:
#include "MineButton.h"
#include "MineField.h"

    MineField(int numRows, int numCols, int numBombs)
        : NumRows(numRows), NumCols(numCols), NumBombs(numBombs)
    {
        buttons = gcnew array<array<MineButton^>^>(numRows);
        adjacentMineCounts = gcnew array<array<int>^>(numRows);

        for (int i = 0; i < numRows; ++i)
        {
            buttons[i] = gcnew array<MineButton^>(numCols);
            adjacentMineCounts[i] = gcnew array<int>(numCols);
        }
    }

    void AddMine(int row, int col)
    {
        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                int newRow = row + i;
                int newCol = col + j;

                if (newRow >= 0 && newRow < NumRows && newCol >= 0 && newCol < NumCols)
                {
                    ++adjacentMineCounts[newRow][newCol];
                }
            }
        }
    }

    int GetAdjacentMineCount(int row, int col)
    {
        return adjacentMineCounts[row][col];
    }

    void SetButton(int row, int col, MineButton^ button)
    {
        buttons[row][col] = button;
    }

    MineButton^ GetButton(int row, int col)
    {
        return buttons[row][col];
    }

    int GetNumRows()
    {
        return NumRows;
    }

    int GetNumCols()
    {
        return NumCols;
    }

    int GetNumBombs()
    {
        return NumBombs;
    }

    void InitializeField()
    {
        for (int i = 0; i < NumRows; ++i)
        {
            for (int j = 0; j < NumCols; ++j)
            {
                adjacentMineCounts[i][j] = 0;
            }
        }
    }


private:
    int NumRows;
    int NumCols;
    int NumBombs;
    array<array<MineButton^>^>^ buttons;
    array<array<int>^>^ adjacentMineCounts;
};
