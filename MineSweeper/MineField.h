#pragma once
#include "MineButton.h"


using namespace System;
using namespace System::Collections::Generic;



public ref class MineField
{

private:
    int numRows;
    int numCols;
    int numMines;
    array<MineButton^, 2>^ buttons;
    Random^ random;

public:
    MineField(int numRows, int numCols, int numMines)
    {
        this->numRows = numRows;
        this->numCols = numCols;
        this->numMines = numMines;
        this->random = gcnew Random();
        buttons = gcnew array<MineButton^, 2>(numRows, numCols);
    }

    void InitializeField()
    {
        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j < numCols; ++j)
            {
                buttons[i, j] = gcnew MineButton(i, j);
            }
        }

        for (int i = 0; i < numMines; ++i)
        {
            int row = random->Next(numRows);
            int col = random->Next(numCols);

            if (buttons[row, col]->IsMine)
            {
                --i;
            }
            else
            {
                buttons[row, col]->IsMine = true;
            }
        }

        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j < numCols; ++j)
            {
                buttons[i, j]->AdjacentMines = CountAdjacentMines(i, j);
            }
        }
    }

    MineButton^ GetButton(int row, int col)
    {
        return buttons[row, col];
    }

    int CountAdjacentMines(int row, int col)
    {
        int count = 0;

        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                if (i == 0 && j == 0) continue;

                int newRow = row + i;
                int newCol = col + j;

                if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols)
                {
                    if (buttons[newRow, newCol]->IsMine)
                    {
                        ++count;
                    }
                }
            }
        }

        return count;
    }

    property int NumRows
    {
        int get() { return numRows; }
    }

    property int NumCols
    {
        int get() { return numCols; }
    }
};
