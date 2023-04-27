#pragma once

//!warning for the oop assistants!
//! 
//! 
//the code for the application follows the .NET conventions
//it uses standard .NET classes to provide better integration
//things such as the array and class definitions are done in a ".NET" way
//anything that doesn't look like native C++ is simply a .NET component / C++ CLI
//!

namespace MineSweeper {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Media;
    using namespace System::Resources;
    using namespace System::Reflection;

#include "MineButton.h"

#include "MineField.h"

#include "GameStatistics.cpp"


    public ref class MyForm : public System::Windows::Forms::Form {
    public: MyForm(void) {
        InitializeComponent();
        InitializeCustomFieldUI();
        InitializeMenuUI();
        InitializeStatisticsUI();
        InitializeTimer();
        gameStats = gcnew GameStatistics();
        gameStats->LoadFromFile();
        UpdateStatisticLabels(gameStats);
    }

    protected:
        ~MyForm() {
            if (components) {
                delete components;
            }
        }

    protected:

    private: System::ComponentModel::Container^ components;
           MineField^ mineField;
           TextBox^ numRowsTextBox;
           TextBox^ numColsTextBox;
           TextBox^ numBombsTextBox;
           Button^ generateCustomFieldButton;
           Button^ btnSave;
           Button^ btnLoad;
           Button^ btnHint;
           const int leftToolBarSize = 180;
           const int topToolBarSize = 50;
           const int formWidth = 1000;
           const int formHeight = 800;
           Label^ lblBestTime;
           Label^ lblGamesPlayed;
           Label^ lblGamesWon;
           Label^ lblWinPercentage;
           Label^ lblLongestWinStreak;
           Label^ lblLongestLoseStreak;
           Label^ lblCurrentStreak;
           Label^ lblStatistics;
           GameStatistics^ gameStats;
           Timer^ gameTimer;
           Label^ elapsedTimeLabel;
           int elapsedTimeInSeconds = 0;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void) {
               System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
               this->SuspendLayout();
               // 
               // MyForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::FromArgb(static_cast <System::Int32> (static_cast <System::Byte> (255)), static_cast <System::Int32> (static_cast <System::Byte> (192)),
                   static_cast <System::Int32> (static_cast <System::Byte> (203)));
               this->ClientSize = System::Drawing::Size(984, 761);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
               this->Icon = (cli::safe_cast <System::Drawing::Icon^> (resources->GetObject(L"$this.Icon")));
               this->MaximumSize = System::Drawing::Size(1000, 800);
               this->MinimumSize = System::Drawing::Size(1000, 800);
               this->Name = L"MyForm";
               this->Text = L"PinkSweeper";
               this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
               this->ResumeLayout(false);

           }
#pragma endregion
    private: System::Void MyForm_Load(Object^ sender, EventArgs^ e) {
        GenerateMatrixOfButtons(20, 10, 150, nullptr, nullptr, nullptr);
    }
           void MyForm::InitializeCustomFieldUI() //add validation!
           {
               System::Drawing::Font^ newFont = gcnew System::Drawing::Font("Arial", 15);
               numRowsTextBox = gcnew TextBox();
               numRowsTextBox->Location = Point(350, 60);
               numRowsTextBox->Size = System::Drawing::Size(100, 30);
               numRowsTextBox->Text = "10";
               numRowsTextBox->Font = newFont;
               this->Controls->Add(numRowsTextBox);

               numColsTextBox = gcnew TextBox();
               numColsTextBox->Location = Point(460, 60);
               numColsTextBox->Size = System::Drawing::Size(100, 30);
               numColsTextBox->Text = "10";
               numColsTextBox->Font = newFont;
               this->Controls->Add(numColsTextBox);

               numBombsTextBox = gcnew TextBox();
               numBombsTextBox->Location = Point(570, 60);
               numBombsTextBox->Size = System::Drawing::Size(100, 30);
               numBombsTextBox->Text = "10";
               numBombsTextBox->Font = newFont;
               this->Controls->Add(numBombsTextBox);

               generateCustomFieldButton = gcnew Button();
               generateCustomFieldButton->Location = Point(750, 30);
               generateCustomFieldButton->Size = System::Drawing::Size(120, 90);
               generateCustomFieldButton->Text = "Generate Custom Field";
               generateCustomFieldButton->Click += gcnew EventHandler(this, &MyForm::GenerateCustomFieldButton_Click);
               generateCustomFieldButton->Font = newFont;
               generateCustomFieldButton->BackColor = System::Drawing::Color::Transparent;
               generateCustomFieldButton->FlatStyle = FlatStyle::Flat;
               generateCustomFieldButton->FlatAppearance->BorderSize = 0;
               this->Controls->Add(generateCustomFieldButton);

           }

           void MyForm::InitializeMenuUI() {
               System::Drawing::Font^ newFont = gcnew System::Drawing::Font("Arial", 15);

               btnSave = gcnew Button();
               btnSave->Text = "Save";
               btnSave->Location = Point(10, 400);
               btnSave->Size = System::Drawing::Size(200, 50);
               btnSave->Font = newFont;
               btnSave->Click += gcnew EventHandler(this, &MyForm::SaveGameState);
               this->Controls->Add(btnSave);

               btnLoad = gcnew Button();
               btnLoad->Text = "Load";
               btnLoad->Font = newFont;
               btnLoad->Location = Point(10, 550); //adjust the location 
               btnLoad->Size = System::Drawing::Size(200, 50);

               btnLoad->Click += gcnew EventHandler(this, &MyForm::LoadGameState);
               this->Controls->Add(btnLoad);

               btnHint = gcnew Button();
               btnHint->Text = "Hint";
               btnHint->Location = Point(10, 700);
               btnHint->Font = newFont;
               btnHint->Size = System::Drawing::Size(200, 50);
               btnHint->Click += gcnew EventHandler(this, &MyForm::HintClick);
               this->Controls->Add(this->btnHint);

           }

           void MyForm::InitializeStatisticsUI() {
               System::Drawing::Font^ newFont = gcnew System::Drawing::Font("Arial", 15);

               lblStatistics = gcnew Label();
               lblStatistics->Location = Point(20, 20);
               lblStatistics->AutoSize = true;
               lblStatistics->Font = newFont;
               lblStatistics->Text = "Statistics";
               Controls->Add(lblStatistics);

               lblBestTime = gcnew Label();
               lblBestTime->Location = Point(10, 100);
               lblBestTime->AutoSize = true;
               lblBestTime->Font = newFont;
               Controls->Add(lblBestTime);

               lblGamesPlayed = gcnew Label();
               lblGamesPlayed->Location = Point(10, 120);
               lblGamesPlayed->AutoSize = true;
               lblGamesPlayed->Font = newFont;
               Controls->Add(lblGamesPlayed);

               lblGamesWon = gcnew Label();
               lblGamesWon->Location = Point(10, 140);
               lblGamesWon->AutoSize = true;
               lblGamesWon->Font = newFont;
               Controls->Add(lblGamesWon);

               lblWinPercentage = gcnew Label();
               lblWinPercentage->Location = Point(10, 160);
               lblWinPercentage->AutoSize = true;
               lblWinPercentage->Font = newFont;
               Controls->Add(lblWinPercentage);

               lblLongestWinStreak = gcnew Label();
               lblLongestWinStreak->Location = Point(10, 180);
               lblLongestWinStreak->AutoSize = true;
               lblLongestWinStreak->Font = newFont;
               Controls->Add(lblLongestWinStreak);

               lblLongestLoseStreak = gcnew Label();
               lblLongestLoseStreak->Location = Point(10, 200);
               lblLongestLoseStreak->AutoSize = true;
               lblLongestLoseStreak->Font = newFont;
               Controls->Add(lblLongestLoseStreak);

               lblCurrentStreak = gcnew Label();
               lblCurrentStreak->Location = Point(10, 220);
               lblCurrentStreak->AutoSize = true;
               lblCurrentStreak->Font = newFont;
               Controls->Add(lblCurrentStreak);
           }

           void MyForm::InitializeTimer() {
               System::Drawing::Font^ newFont = gcnew System::Drawing::Font("Arial", 15);

               gameTimer = gcnew Timer();
               gameTimer->Interval = 1000;
               gameTimer->Tick += gcnew EventHandler(this, &MyForm::gameTimer_Tick);

               elapsedTimeLabel = gcnew Label();
               elapsedTimeLabel->Location = Point(200, 650);
               elapsedTimeLabel->AutoSize = true;
               elapsedTimeLabel->Font = newFont;

               this->Controls->Add(elapsedTimeLabel);
           }

           void MyForm::GenerateMatrixOfButtons(int rows, int cols, int numBombs, array < array < bool >^ >^ mineData, array < array < bool >^ >^ revealedData, array < array < bool >^ >^ flaggedData) {
               const int buttonSize = 28;
               const int padding = 0;
               const int leftTotalPadding = (formWidth - (cols * (buttonSize + padding) - padding)) / 2 + leftToolBarSize;
               const int topTotalPadding = (formHeight - (rows * (buttonSize + padding) - padding)) / 2 + topToolBarSize;
               mineField = gcnew MineField(rows, cols, numBombs);
               mineField->InitializeField();

               for (int i = 0; i < rows; ++i) {
                   for (int j = 0; j < cols; ++j) {
                       MineButton^ button = gcnew MineButton(i, j);
                       button->Size = System::Drawing::Size(buttonSize, buttonSize);
                       button->Location = Point(leftTotalPadding + padding + j * (buttonSize + padding), topTotalPadding + padding + i * (buttonSize + padding));
                       button->MouseDown += gcnew MouseEventHandler(this, &MyForm::Button_Click);
                       this->Controls->Add(button);
                       mineField->SetButton(i, j, button);

                       if (mineData != nullptr && mineData[i][j]) {
                           button->IsMine = true;
                           mineField->AddMine(i, j);
                           button->AdjacentMines = mineField->GetAdjacentMineCount(i, j);
                       }

                       if (revealedData != nullptr && revealedData[i][j]) {
                           button->IsRevealed = true;
                           button->Text = mineField->GetAdjacentMineCount(i, j).ToString();
                       }

                       if (flaggedData != nullptr && flaggedData[i][j]) {
                           button->IsFlagged = true;
                           button->Text = "F";
                       }
                   }
               }

               if (mineData == nullptr) {
                   Random^ random = gcnew Random();
                   int bombsPlaced = 0;
                   while (bombsPlaced < numBombs) {
                       int row = random->Next(rows);
                       int col = random->Next(cols);
                       MineButton^ button = mineField->GetButton(row, col);
                       button->AdjacentMines = 0;

                       if (!button->IsMine) {
                           button->IsMine = true;
                           mineField->AddMine(row, col);
                           ++bombsPlaced;
                       }
                   }
               }

               for (int i = 0; i < rows; ++i) {
                   for (int j = 0; j < cols; ++j) {
                       MineButton^ button = mineField->GetButton(i, j);

                       if (!button->IsMine) {
                           button->AdjacentMines = mineField->GetAdjacentMineCount(i, j);
                       }
                   }
               }
           }

           void MyForm::DeleteMatrixOfButtons() {
               if (mineField == nullptr) {
                   return;
               }

               for (int i = 0; i < mineField->GetNumRows(); ++i) {
                   for (int j = 0; j < mineField->GetNumCols(); ++j) {
                       MineButton^ button = mineField->GetButton(i, j);
                       this->Controls->Remove(button);
                       delete button;
                   }
               }

               mineField = nullptr;
           }

           void MyForm::Button_Click(Object^ sender, MouseEventArgs^ e) {
               MineButton^ clickedButton = safe_cast <MineButton^> (sender); //stolen from chatgpt

               if (!gameTimer->Enabled) {
                   gameTimer->Start();
               }

               if (e->Button == System::Windows::Forms::MouseButtons::Left) {
                   LeftClickAction(clickedButton);
               }
               else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
                   RightClickAction(clickedButton);
               }
           }

           void MyForm::LeftClickAction(MineButton^ clickedButton) {
               System::Media::SoundPlayer^ soundPlayer = gcnew System::Media::SoundPlayer();
               soundPlayer->SoundLocation = "fieldClick.wav";
               soundPlayer->Load();
               soundPlayer->Play();

               if (clickedButton->IsFlagged || clickedButton->IsRevealed) {
                   return;
               }

               if (clickedButton->IsMine) {
                   gameStats->gamesPlayed++;
                   EndGame(false);
               }
               else {
                   RevealButton(clickedButton);

                   if (CheckWin()) {
                       gameStats->gamesPlayed++;
                       gameStats->gamesWon++;
                       EndGame(true);
                   }

               }
           }

           void MyForm::RightClickAction(MineButton^ clickedButton) {
               System::Media::SoundPlayer^ soundPlayer = gcnew System::Media::SoundPlayer();
               soundPlayer->SoundLocation = "flagClick.wav";
               soundPlayer->Load();
               soundPlayer->Play();
               clickedButton->IsFlagged = !clickedButton->IsFlagged;

               if (clickedButton->IsFlagged) {
                   clickedButton->Text = "F";
               }
               else {
                   clickedButton->Text = "";
               }
           }

           void MyForm::RevealButton(MineButton^ button) {
               if (button->IsFlagged || button->IsRevealed) {
                   return;
               }

               button->IsRevealed = true;
               button->Enabled = false;
               button->BackColor = Color::LightGray;

               if (button->AdjacentMines > 0) {
                   button->Text = button->AdjacentMines.ToString();
               }

               for (int i = -1; i <= 1; ++i) {
                   for (int j = -1; j <= 1; ++j) {
                       if (i == 0 && j == 0) continue;

                       int newRow = button->Row + i;
                       int newCol = button->Col + j;

                       if (newRow >= 0 && newRow < mineField->GetNumRows() && newCol >= 0 && newCol < mineField->GetNumCols() && !mineField->GetButton(newRow, newCol)->IsMine) {
                           RevealButton(mineField->GetButton(newRow, newCol));
                       }
                   }
               }

           }

           void MyForm::GenerateCustomFieldButton_Click(Object^ sender, EventArgs^ e) {
               int numRows = Int32::Parse(numRowsTextBox->Text);
               int numCols = Int32::Parse(numColsTextBox->Text);
               int numBombs = Int32::Parse(numBombsTextBox->Text);

               if (numRows <= 0 || numRows > 20 || numCols <= 0 || numCols > 20 || numRows * numCols <= numBombs || numBombs <= 0) {
                   MessageBox::Show("Input should be valid (grid should be between 1x1 and 20x20, and bomb count can't be greater than tiles count)");
               }
               else {
                   DeleteMatrixOfButtons();
                   GenerateMatrixOfButtons(numRows, numCols, numBombs, nullptr, nullptr, nullptr);
               }

           }

           bool MyForm::CheckWin() {
               int revealedButtons = 0;
               for (int i = 0; i < mineField->GetNumRows(); ++i) {
                   for (int j = 0; j < mineField->GetNumCols(); ++j) {
                       MineButton^ button = mineField->GetButton(i, j);
                       if (button->IsRevealed) {
                           ++revealedButtons;
                       }
                   }
               }

               return revealedButtons == (mineField->GetNumRows() * mineField->GetNumCols()) - mineField->GetNumBombs();
           }

           void MyForm::EndGame(bool isWin) {
               gameTimer->Stop();
               if (isWin) {
                   MessageBox::Show("Congratulations! You won the game!", "Pinksweeper", MessageBoxButtons::OK, MessageBoxIcon::None);
                   if (gameStats->winStreak) {
                       gameStats->currentStreak++;
                       if (gameStats->longestWinStreak < gameStats->currentStreak) gameStats->longestWinStreak = gameStats->currentStreak;
                   }
                   else {
                       gameStats->winStreak = true;
                       gameStats->currentStreak = 0;
                   }
               }
               else {
                   MessageBox::Show("You clicked on a bomb! Game over.", "Pinksweeper", MessageBoxButtons::OK, MessageBoxIcon::None);
                   if (!gameStats->winStreak) {
                       gameStats->currentStreak++;
                       if (gameStats->longestLoseStreak < gameStats->currentStreak) gameStats->longestLoseStreak = gameStats->currentStreak;
                   }
                   else {
                       gameStats->winStreak = false;
                       gameStats->currentStreak = 0;
                   }
               }
               for (int i = 0; i < mineField->GetNumRows(); ++i) {
                   for (int j = 0; j < mineField->GetNumCols(); ++j) {
                       MineButton^ button = mineField->GetButton(i, j);
                       if (button->IsMine) {
                           button->Text = "B";
                       }
                   }
               }
               gameStats->winPercentage = (double)gameStats->gamesWon / gameStats->gamesPlayed * 100;
               UpdateStatisticLabels(gameStats);
               SaveStatistics(gameStats);

           }

    private: void HintClick(Object^ sender, EventArgs^ e) {
        bool found = false;
        int x, y;
        Random^ rand = gcnew Random();

        while (!found) {
            x = rand->Next(0, mineField->GetNumRows());
            y = rand->Next(0, mineField->GetNumCols());

            if (!mineField->GetButton(x, y)->IsMine && !mineField->GetButton(x, y)->IsFlagged && !mineField->GetButton(x, y)->IsRevealed) {
                found = true;
            }
        }

        RevealButton(mineField->GetButton(x, y));

        if (CheckWin()) {
            EndGame(true);
        }
    }

           void MyForm::LoadGameState(Object^ sender, EventArgs^ e) {
               StreamReader^ sr = nullptr;
               try {
                   sr = gcnew StreamReader("gamestate.txt");

                   int numRows = Int32::Parse(sr->ReadLine());
                   int numCols = Int32::Parse(sr->ReadLine());
                   int numBombs = Int32::Parse(sr->ReadLine());

                   array < array < bool >^ >^ mineData = gcnew array < array < bool >^ >(numRows);
                   array < array < bool >^ >^ revealedData = gcnew array < array < bool >^ >(numRows);
                   array < array < bool >^ >^ flaggedData = gcnew array < array < bool >^ >(numRows);
                   for (int i = 0; i < numRows; ++i) {
                       String^ row = sr->ReadLine();
                       mineData[i] = gcnew array < bool >(numCols);
                       revealedData[i] = gcnew array < bool >(numCols);
                       flaggedData[i] = gcnew array < bool >(numCols);
                       for (int j = 0, k = 0; j < numCols; ++j, k += 3) {
                           mineData[i][j] = row[k] == '1';
                           revealedData[i][j] = row[k + 1] == '1';
                           flaggedData[i][j] = row[k + 2] == '1';
                       }
                   }

                   DeleteMatrixOfButtons();
                   GenerateMatrixOfButtons(numRows, numCols, numBombs, mineData, revealedData, flaggedData);
               }
               catch (Exception^ ex) {
                   MessageBox::Show("Error loading the game state: " + ex->Message);
               }
               finally {
                   if (sr != nullptr) {
                       sr->Close();
                   }
               }
           }

           void MyForm::SaveGameState(Object^ sender, EventArgs^ e) {
               StreamWriter^ sw = nullptr;
               try {
                   sw = gcnew StreamWriter("gamestate.txt");

                   sw->WriteLine(mineField->GetNumRows());
                   sw->WriteLine(mineField->GetNumCols());
                   sw->WriteLine(mineField->GetNumBombs());

                   for (int i = 0; i < mineField->GetNumRows(); ++i) {
                       for (int j = 0; j < mineField->GetNumCols(); ++j) {
                           MineButton^ button = mineField->GetButton(i, j);
                           sw->Write(button->IsMine ? '1' : '0');
                           sw->Write(button->IsRevealed ? '1' : '0');
                           sw->Write(button->IsFlagged ? '1' : '0');
                       }
                       sw->WriteLine();
                   }
               }
               catch (Exception^ ex) {
                   MessageBox::Show("Error saving the game state: " + ex->Message);
               }
               finally {
                   if (sw != nullptr) {
                       sw->Close();
                   }
               }
           }

           GameStatistics^ LoadStatistics() {
               GameStatistics^ stats = gcnew GameStatistics();
               try {
                   StreamReader^ inFile = gcnew StreamReader("statistics.txt");
                   stats->bestTime = Int32::Parse(inFile->ReadLine());
                   stats->gamesPlayed = Int32::Parse(inFile->ReadLine());
                   stats->gamesWon = Int32::Parse(inFile->ReadLine());
                   stats->winPercentage = Double::Parse(inFile->ReadLine());
                   stats->longestWinStreak = Int32::Parse(inFile->ReadLine());
                   stats->longestLoseStreak = Int32::Parse(inFile->ReadLine());
                   stats->currentStreak = Int32::Parse(inFile->ReadLine());
                   inFile->Close();
               }
               catch (Exception^ ex) {
                   MessageBox::Show("Unable to open statistics.txt for reading: " + ex->Message);
               }
               return stats;
           }

           void SaveStatistics(GameStatistics^ stats) {
               try {
                   StreamWriter^ outFile = gcnew StreamWriter("statistics.txt");
                   outFile->WriteLine(stats->bestTime.ToString());
                   outFile->WriteLine(stats->gamesPlayed.ToString());
                   outFile->WriteLine(stats->gamesWon.ToString());
                   outFile->WriteLine(stats->winPercentage.ToString());
                   outFile->WriteLine(stats->longestWinStreak.ToString());
                   outFile->WriteLine(stats->longestLoseStreak.ToString());
                   outFile->WriteLine(stats->currentStreak.ToString());
                   outFile->Close();
               }
               catch (Exception^ ex) {
                   MessageBox::Show("Unable to open statistics.txt for writing: " + ex->Message);
               }
           }

           void UpdateStatisticLabels(GameStatistics^ stats) {
               lblBestTime->Text = "Best Time: " + stats->bestTime + "s";
               lblGamesPlayed->Text = "Games Played: " + stats->gamesPlayed;
               lblGamesWon->Text = "Games Won: " + stats->gamesWon;
               lblWinPercentage->Text = "Win Percentage: " + Math::Round(stats->winPercentage, 0).ToString() + "%";
               lblLongestWinStreak->Text = "Longest Win Streak: " + stats->longestWinStreak;
               lblLongestLoseStreak->Text = "Longest Lose Streak: " + stats->longestLoseStreak;
               lblCurrentStreak->Text = "Current Streak: " + stats->currentStreak;
           }

           void gameTimer_Tick(System::Object^ sender, System::EventArgs^ e) { //chatgpt
               elapsedTimeInSeconds++;
               int hours = elapsedTimeInSeconds / 3600;
               int minutes = (elapsedTimeInSeconds % 3600) / 60;
               int seconds = elapsedTimeInSeconds % 60;
               elapsedTimeLabel->Text = String::Format("{0:D2}:{1:D2}:{2:D2}", hours, minutes, seconds);
           }

    };
}