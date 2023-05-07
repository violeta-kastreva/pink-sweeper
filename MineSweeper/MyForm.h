#pragma once
//mouse over hover leave


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
#include "CustomButton.h"
#include "MineField.h"
#include "LoadedFont.cpp"
#include "GameStatistics.cpp"


    public ref class MyForm : public System::Windows::Forms::Form {
    public: MyForm(void) {
        InitializeComponent();
        InitializePictures();
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
           CustomButton^ generateCustomFieldButton;
           Button^ btnSave;
           Button^ btnLoad;
           Button^ btnHint;
           Button^ btnExit;
           const int leftToolBarSize = 180;
           const int topToolBarSize = 50;
           const int formWidth = 1200;
           const int formHeight = 800;
           Label^ lblSave;
           Label^ lblLoad;
           Label^ lblHint;
           Label^ lblExit;
           Label^ lblCustomField;
           Label^ lblBestTime;           
           Label^ lblGamesPlayed;
           Label^ lblGamesWon;
           Label^ lblWinPercentage;
           Label^ lblLongestWinStreak;
           Label^ lblLongestLoseStreak;
           Label^ lblCurrentStreak;
           Label^ lblStatistics;
           Label^ lblSettings;
           Label^ lblRows;
           Label^ lblCols;
           Label^ lblBombs;
           GameStatistics^ gameStats;
           Timer^ gameTimer;
           Label^ elapsedTimeLabel;
           int elapsedTimeInSeconds = 0;
           LoadedFont^ loadedFont = LoadFont(gcnew FileInfo( "customFont.ttf" ), 40, FontStyle::Regular);
           LoadedFont^ loadedFontBigger = LoadFont(gcnew FileInfo( "customFont.ttf" ), 52, FontStyle::Regular);
           PictureBox^ timePannelPicBox = gcnew PictureBox();
           PictureBox^ logoPicBox = gcnew PictureBox();
           PictureBox^ mainSideBtnPicBox = gcnew PictureBox();
           PictureBox^ sideBtnPicBox = gcnew PictureBox();
           PictureBox^ sideBtnPicBox2 = gcnew PictureBox();
           PictureBox^ sideBtnPicBox3 = gcnew PictureBox();
           PictureBox^ sideBtnPicBox4 = gcnew PictureBox();
           PictureBox^ coveredSlotPicBox = gcnew PictureBox();
           PictureBox^ uncoveredSlotPicBox = gcnew PictureBox();
           PictureBox^ valueInputPannelPicBox = gcnew PictureBox();
           PictureBox^ valueInputPannelPicBox2 = gcnew PictureBox();
           PictureBox^ valueInputPannelPicBox3 = gcnew PictureBox();
           PictureBox^ settingsPannelPicBox = gcnew PictureBox();
           PictureBox^ bombPicBox = gcnew PictureBox();
           PictureBox^ flagPicBox = gcnew PictureBox();


#pragma region Windows Form Designer generated code
           void InitializeComponent(void) {
               System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
               this->SuspendLayout();
               // 
               // MyForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(221)),
                   static_cast<System::Int32>(static_cast<System::Byte>(232)));
               this->ClientSize = System::Drawing::Size(1184, 761);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
               this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
               this->MaximumSize = System::Drawing::Size(1200, 800);
               this->MinimumSize = System::Drawing::Size(1200, 800);
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

               lblRows = gcnew Label();
               lblRows->Location = Point(300, 697);
               lblRows->BackColor = System::Drawing::Color::FromArgb(254, 248, 150, 181);
               lblRows->AutoSize = true;
               lblRows->Font = loadedFont->Font;
               lblRows->ForeColor = Color::White;
               lblRows->Text = "rows";
               Controls->Add(lblRows);
               lblRows->BringToFront();

               numRowsTextBox = gcnew TextBox();
               numRowsTextBox->Location = Point(396, 700);
               numRowsTextBox->Size = System::Drawing::Size(100, 30);
               numRowsTextBox->ForeColor = Color::White;
               numRowsTextBox->Text = "10";
               numRowsTextBox->Font = gcnew System::Drawing::Font(L"a_Rewinder", 20, System::Drawing::FontStyle::Regular);
               numRowsTextBox->BackColor = Color::FromArgb(176, 100, 124);
               numRowsTextBox->BorderStyle = BorderStyle::None;
               this->Controls->Add(numRowsTextBox);
               numRowsTextBox->BringToFront();

               lblCols = gcnew Label();
               lblCols->Location = Point(535, 697);
               lblCols->BackColor = System::Drawing::Color::FromArgb(254, 248, 150, 181);
               lblCols->AutoSize = true;
               lblCols->Font = loadedFont->Font;
               lblCols->ForeColor = Color::White;
               lblCols->Text = "cols";
               Controls->Add(lblCols);
               lblCols->BringToFront();

               numColsTextBox = gcnew TextBox();
               numColsTextBox->Location = Point(620, 700);
               numColsTextBox->Size = System::Drawing::Size(100, 30);
               numColsTextBox->ForeColor = Color::White;
               numColsTextBox->Text = "10";
               numColsTextBox->Font = gcnew System::Drawing::Font(L"a_Rewinder", 20, System::Drawing::FontStyle::Regular);
               numColsTextBox->BackColor = Color::FromArgb(176, 100, 124);
               numColsTextBox->BorderStyle = BorderStyle::None;
               this->Controls->Add(numColsTextBox);
               numColsTextBox->BringToFront();

               lblBombs = gcnew Label();
               lblBombs->Location = Point(720, 708);
               lblBombs->BackColor = System::Drawing::Color::FromArgb(254, 248, 150, 181);
               lblBombs->AutoSize = true;
               lblBombs->Font = loadedFont->Font;
               lblBombs->ForeColor = Color::White;
               lblBombs->Text = "bombs";
               //Controls->Add(lblBombs);
               //lblBombs->BringToFront();

               numBombsTextBox = gcnew TextBox();
               numBombsTextBox->Location = Point(840, 700);
               numBombsTextBox->Size = System::Drawing::Size(100, 30);
               numBombsTextBox->ForeColor = Color::White;
               numBombsTextBox->Text = "10";
               numBombsTextBox->Font = gcnew System::Drawing::Font(L"a_Rewinder", 20, System::Drawing::FontStyle::Regular);
               numBombsTextBox->BackColor = Color::FromArgb(176, 100, 124);
               numBombsTextBox->BorderStyle = BorderStyle::None;
               this->Controls->Add(numBombsTextBox);
               numBombsTextBox->BringToFront();

               lblCustomField = gcnew Label();
               lblCustomField->Location = Point(10, 215);
               lblCustomField->Size = System::Drawing::Size(260, 50);
               lblCustomField->Text = "NEW GAME";
               lblCustomField->Click += gcnew EventHandler(this, &MyForm::lblCustomClick);
               lblCustomField->Font = loadedFontBigger->Font;
               lblCustomField->BackColor = System::Drawing::Color::FromArgb(255, 121, 159);
               lblCustomField->ForeColor = Color::White;
               lblCustomField->FlatStyle = FlatStyle::Flat;
               this->Controls->Add(lblCustomField);


               generateCustomFieldButton = gcnew CustomButton();
               generateCustomFieldButton->Location = Point(10, 230);
               generateCustomFieldButton->Size = System::Drawing::Size(180, 50);
               generateCustomFieldButton->Click += gcnew EventHandler(this, &MyForm::GenerateCustomFieldButton_Click);
               generateCustomFieldButton->Font = loadedFontBigger->Font;
               generateCustomFieldButton->ForeColor = Color::White;
               generateCustomFieldButton->BackColor = System::Drawing::Color::FromArgb(255, 121, 159);
               generateCustomFieldButton->FlatStyle = FlatStyle::Flat;
               generateCustomFieldButton->FlatAppearance->BorderSize = 0;
         
               this->Controls->Add(generateCustomFieldButton);


               lblSettings = gcnew Label();
               lblSettings->Location = Point(20, 695);
               lblSettings->BackColor = System::Drawing::Color::FromArgb(254,248,150, 181);
               lblSettings->AutoSize = true;
               lblSettings->Font = loadedFontBigger->Font;
               lblSettings->ForeColor = Color::White;
               lblSettings->Text = "Settings ";
               Controls->Add(lblSettings);
               lblSettings->BringToFront();

               lblCustomField->BringToFront();
           }

           void MyForm::InitializeMenuUI() 
           {

               lblSave = gcnew Label();
               lblSave->TextAlign = ContentAlignment::MiddleCenter;
               lblSave->Text = "SAVE";
               lblSave->Location = Point(10, 284);
               lblSave->Size = System::Drawing::Size(200, 50);
               lblSave->Font = loadedFontBigger->Font;
               lblSave->ForeColor = Color::White;
               lblSave->BackColor = System::Drawing::Color::FromArgb(248, 150, 182);
               lblSave->Click += gcnew EventHandler(this, &MyForm::lblSaveClick);
               this->Controls->Add(lblSave);


               btnSave = gcnew CustomButton();
               btnSave->Location = Point(10, 306);
               btnSave->Size = System::Drawing::Size(200, 50);
               btnSave->Font = loadedFontBigger->Font;
               btnSave->ForeColor = Color::White;
               btnSave->Click += gcnew EventHandler(this, &MyForm::SaveGameState);
               this->Controls->Add(btnSave);

               lblLoad = gcnew Label();
               lblLoad->TextAlign = ContentAlignment::MiddleCenter;
               lblLoad->Text = "LOAD";
               lblLoad->Font = loadedFontBigger->Font;
               lblLoad->Location = Point(10, 365); 
               lblLoad->Size = System::Drawing::Size(200, 50);
               lblLoad->ForeColor = Color::White;
               lblLoad->Click += gcnew EventHandler(this, &MyForm::LoadGameState);
               this->Controls->Add(lblLoad);

               btnLoad = gcnew CustomButton();
               btnLoad->Font = loadedFontBigger->Font;
               btnLoad->Location = Point(10, 365); 
               btnLoad->Size = System::Drawing::Size(200, 50);
               btnLoad->ForeColor = Color::White;
               btnLoad->Click += gcnew EventHandler(this, &MyForm::LoadGameState);
               this->Controls->Add(btnLoad);

               lblHint = gcnew Label();
               lblHint->Text = "HINT";
               lblHint->TextAlign = ContentAlignment::MiddleCenter;
               lblHint->Location = Point(10, 421);
               lblHint->Font = loadedFontBigger->Font;
               lblHint->Size = System::Drawing::Size(200, 50);
               lblHint->ForeColor = Color::White;
               lblHint->Click += gcnew EventHandler(this, &MyForm::lblHintClick);
               this->Controls->Add(this->lblHint);

               btnHint = gcnew CustomButton();
               btnHint->Location = Point(10, 421);
               btnHint->Font = loadedFontBigger->Font;
               btnHint->Size = System::Drawing::Size(200, 50);
               btnHint->ForeColor = Color::White;
               btnHint->Click += gcnew EventHandler(this, &MyForm::HintClick);
               this->Controls->Add(this->btnHint);

               Label^ lblExit = gcnew Label();
               lblExit->Text = "EXIT";
               lblExit->TextAlign = ContentAlignment::MiddleCenter;
               lblExit->Font = loadedFontBigger->Font;
               lblExit->Size = System::Drawing::Size(200, 50);
               lblExit->Location = Point(10, 480);
               lblExit->ForeColor = Color::White;
               lblExit->Click += gcnew System::EventHandler(this, &MyForm::ExitLabel_Click);
               this->Controls->Add(lblExit);

               Button^ btnExit = gcnew CustomButton();
               btnExit->Text = "";
               btnExit->Font = loadedFontBigger->Font;
               btnExit->Size = System::Drawing::Size(200, 50);
               btnExit->Location = Point(10, 440);
               btnExit->ForeColor = Color::White;
               btnExit->Click += gcnew System::EventHandler(this, &MyForm::ExitButton_Click);
               this->Controls->Add(btnExit);

               lblSave->BringToFront();

           }


           void MyForm::lblHintClick(System::Object^ sender, System::EventArgs^ e)
           {
               btnHint->PerformClick();
           }

           void MyForm::lblSaveClick(System::Object^ sender, System::EventArgs^ e)
           {
               btnSave->PerformClick();
           }
           void MyForm::lblLoadClick(System::Object^ sender, System::EventArgs^ e)
           {
               btnLoad->PerformClick();
           }
           void MyForm::lblCustomClick(Object^ sender, EventArgs^ e) {
               generateCustomFieldButton->PerformClick();
           }


           void MyForm::InitializeStatisticsUI() {
               System::Drawing::Font^ newFont = gcnew System::Drawing::Font("Arial", 15);

               lblStatistics = gcnew Label();
               lblStatistics->Location = Point(920, 20);
               lblStatistics->AutoSize = true;
               lblStatistics->Font = loadedFont->Font;
               lblStatistics->Text = "Statistics";
               lblStatistics->ForeColor = Color::White;
               Controls->Add(lblStatistics);

               lblBestTime = gcnew Label();
               lblBestTime->Location = Point(910, 100);
               lblBestTime->AutoSize = true;
               lblBestTime->Font = newFont;
               Controls->Add(lblBestTime);

               lblGamesPlayed = gcnew Label();
               lblGamesPlayed->Location = Point(910, 120);
               lblGamesPlayed->AutoSize = true;
               lblGamesPlayed->Font = newFont;
               Controls->Add(lblGamesPlayed);

               lblGamesWon = gcnew Label();
               lblGamesWon->Location = Point(910, 140);
               lblGamesWon->AutoSize = true;
               lblGamesWon->Font = newFont;
               Controls->Add(lblGamesWon);

               lblWinPercentage = gcnew Label();
               lblWinPercentage->Location = Point(910, 160);
               lblWinPercentage->AutoSize = true;
               lblWinPercentage->Font = newFont;
               Controls->Add(lblWinPercentage);

               lblLongestWinStreak = gcnew Label();
               lblLongestWinStreak->Location = Point(910, 180);
               lblLongestWinStreak->AutoSize = true;
               lblLongestWinStreak->Font = newFont;
               Controls->Add(lblLongestWinStreak);

               lblLongestLoseStreak = gcnew Label();
               lblLongestLoseStreak->Location = Point(910, 200);
               lblLongestLoseStreak->AutoSize = true;
               lblLongestLoseStreak->Font = newFont;
               Controls->Add(lblLongestLoseStreak);

               lblCurrentStreak = gcnew Label();
               lblCurrentStreak->Location = Point(910, 220);
               lblCurrentStreak->AutoSize = true;
               lblCurrentStreak->Font = newFont;
               Controls->Add(lblCurrentStreak);
           }

           void MyForm::InitializeTimer() {
               gameTimer = gcnew Timer();
               gameTimer->Interval = 1000;
               gameTimer->Tick += gcnew EventHandler(this, &MyForm::gameTimer_Tick);

               elapsedTimeLabel = gcnew Label();
               elapsedTimeLabel->Location = Point(200, 650);
               elapsedTimeLabel->AutoSize = true;
               elapsedTimeLabel->Font = loadedFont->Font;

               this->Controls->Add(elapsedTimeLabel);
           }

           void MyForm::InitializePictures() {
               //time pannel
               Bitmap^ imageTimePannel = gcnew Bitmap("Time_Pannel.png");
               timePannelPicBox->Image = imageTimePannel;
               timePannelPicBox->Size = System::Drawing::Size(600, 80);
               timePannelPicBox->SizeMode = PictureBoxSizeMode::StretchImage; 
               timePannelPicBox->Location = Point(280, 0);
               this->Controls->Add(timePannelPicBox);

         

               //settings pannel
               Bitmap^ imagePannel = gcnew Bitmap("Settings_Pannel.png");
               settingsPannelPicBox->Image = imagePannel;
               settingsPannelPicBox->Size = System::Drawing::Size(1184, 120);
               settingsPannelPicBox->SizeMode = PictureBoxSizeMode::StretchImage;
               settingsPannelPicBox->Location = Point(0, 680);
               this->Controls->Add(settingsPannelPicBox);

               //logo 
               Bitmap^ imageLogo = gcnew Bitmap("Logo.png");
               logoPicBox->Image = imageLogo;
               logoPicBox->Size = System::Drawing::Size(220, 110);
               logoPicBox->SizeMode = PictureBoxSizeMode::StretchImage;
               logoPicBox->Location = Point(5, 5);
               this->Controls->Add(logoPicBox);


               //value input pannel
               Bitmap^ imageValueInput = gcnew Bitmap("Value_Input_Pannel.png");
               valueInputPannelPicBox->Image = imageValueInput;
               valueInputPannelPicBox->Size = System::Drawing::Size(104,40);
               valueInputPannelPicBox->SizeMode = PictureBoxSizeMode::StretchImage;
               valueInputPannelPicBox->Location = Point(394, 698);
               this->Controls->Add(valueInputPannelPicBox);
               valueInputPannelPicBox->SendToBack();

               Bitmap^ imageValueInput2 = gcnew Bitmap("Value_Input_Pannel.png");
               valueInputPannelPicBox2->Image = imageValueInput2;
               valueInputPannelPicBox2->Size = System::Drawing::Size(104, 40);
               valueInputPannelPicBox2->SizeMode = PictureBoxSizeMode::StretchImage;
               valueInputPannelPicBox2->Location = Point(617, 698);
               this->Controls->Add(valueInputPannelPicBox2);
               valueInputPannelPicBox2->SendToBack();

               Bitmap^ imageValueInput3 = gcnew Bitmap("Value_Input_Pannel.png");
               valueInputPannelPicBox3->Image = imageValueInput3;
               valueInputPannelPicBox3->Size = System::Drawing::Size(104, 40);
               valueInputPannelPicBox3->SizeMode = PictureBoxSizeMode::StretchImage;
               valueInputPannelPicBox3->Location = Point(837, 698);
               this->Controls->Add(valueInputPannelPicBox3);
               valueInputPannelPicBox3->SendToBack();

               Bitmap^ imageBomb = gcnew Bitmap("Mine.png");
               bombPicBox->Image = imageBomb;
               bombPicBox->Size = System::Drawing::Size(50, 50);
               bombPicBox->SizeMode = PictureBoxSizeMode::StretchImage;
               bombPicBox->Location = Point(770, 694);
               this->Controls->Add(bombPicBox);
               bombPicBox->SendToBack();


               //logo 
               Bitmap^ mainSideButton = gcnew Bitmap("Button_2.png");
               mainSideBtnPicBox->Image = mainSideButton;
               mainSideBtnPicBox->Size = System::Drawing::Size(290, 70);
               mainSideBtnPicBox->SizeMode = PictureBoxSizeMode::StretchImage;
               mainSideBtnPicBox->Location = Point(0, 210);
               this->Controls->Add(mainSideBtnPicBox);

               Bitmap^ sideButton = gcnew Bitmap("Button_1.png");
               sideBtnPicBox->Image = sideButton;
               sideBtnPicBox->Size = System::Drawing::Size(250, 70);
               sideBtnPicBox->SizeMode = PictureBoxSizeMode::StretchImage;
               sideBtnPicBox->Location = Point(0, 341);
               this->Controls->Add(sideBtnPicBox);

               Bitmap^ sideButton2 = gcnew Bitmap("Button_1.png");
               sideBtnPicBox2->Image = sideButton2;
               sideBtnPicBox2->Size = System::Drawing::Size(250, 70);
               sideBtnPicBox2->SizeMode = PictureBoxSizeMode::StretchImage;
               sideBtnPicBox2->Location = Point(0, 408);
               this->Controls->Add(sideBtnPicBox2);

               Bitmap^ sideButton3 = gcnew Bitmap("Button_1.png");
               sideBtnPicBox3->Image = sideButton3;
               sideBtnPicBox3->Size = System::Drawing::Size(250, 70);
               sideBtnPicBox3->SizeMode = PictureBoxSizeMode::StretchImage;
               sideBtnPicBox3->Location = Point(0, 475);
               this->Controls->Add(sideBtnPicBox3);


               Bitmap^ sideButton4 = gcnew Bitmap("Button_1.png");
               sideBtnPicBox4->Image = sideButton4;
               sideBtnPicBox4->Size = System::Drawing::Size(250, 70);
               sideBtnPicBox4->SizeMode = PictureBoxSizeMode::StretchImage;
               sideBtnPicBox4->Location = Point(0, 275);
               this->Controls->Add(sideBtnPicBox4);


               settingsPannelPicBox->SendToBack();
               mainSideBtnPicBox->SendToBack();

           }

           void MyForm::GenerateMatrixOfButtons(int rows, int cols, int numBombs, array <array <bool>^ >^ mineData, array <array <bool>^ >^ revealedData, array <array <bool>^ >^ flaggedData) 
           {
               const int buttonSize = 28;
               const int padding = 0;
               const int leftTotalPadding = (formWidth - (cols * (buttonSize + padding) - padding)) / 2 - rows;
               const int topTotalPadding = (formHeight - (rows * (buttonSize + padding) - padding)) / 2 - 20;
               mineField = gcnew MineField(rows, cols, numBombs);
               mineField->InitializeField();

               for (int i = 0; i < rows; ++i) {
                   for (int j = 0; j < cols; ++j) {
                       MineButton^ button = gcnew MineButton(i, j);
                       button->Size = System::Drawing::Size(buttonSize, buttonSize);
                       button->Location = Point(leftTotalPadding + padding + j * (buttonSize + padding), topTotalPadding + padding + i * (buttonSize + padding));
                       button->MouseDown += gcnew MouseEventHandler(this, &MyForm::MineButtonClick);
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

           void MyForm::MineButtonClick(Object^ sender, MouseEventArgs^ e) {
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
      
               if (clickedButton->IsFlagged || clickedButton->IsRevealed) {
                   return;
               }

               if (clickedButton->IsMine) {

                   gameStats->gamesPlayed++;
                   soundPlayer->SoundLocation = "bombClick.wav";
                   soundPlayer->Load();
                   soundPlayer->Play();
                   EndGame(false);

               }
               else {
                   soundPlayer->SoundLocation = "fieldClick.wav";
                   soundPlayer->Load();
                   soundPlayer->Play();
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

               Random^ rand = gcnew Random();                  
               int maxAmountOfFieldsToBeRevealed = rand->Next(0, mineField->GetNumRows());

               int currentlyRevealedFields = 0;

               for (int i = -1; i <= 1; ++i) {
                   for (int j = -1; j <= 1; ++j) {
                       if (i == 0 && j == 0) continue;

                       int newRow = button->Row + i;
                       int newCol = button->Col + j;

                       if (newRow >= 0 && newRow < mineField->GetNumRows() && newCol >= 0 && newCol < mineField->GetNumCols() && !mineField->GetButton(newRow, newCol)->IsMine && currentlyRevealedFields <= maxAmountOfFieldsToBeRevealed) {
                           currentlyRevealedFields++;
                           RevealButton(mineField->GetButton(newRow, newCol));
                       }
                   }
               }

           }

           void MyForm::GenerateCustomFieldButton_Click(Object^ sender, EventArgs^ e) {
               Button^ button = safe_cast<Button^>(sender);
               button->Font = gcnew System::Drawing::Font("Arial", 106);
               int numRows, numCols, numBombs;
               if (!int::TryParse(numRowsTextBox->Text, numRows) || !int::TryParse(numColsTextBox->Text, numCols) || !int::TryParse(numBombsTextBox->Text, numBombs)) {
                   MessageBox::Show("Input should be valid (grid should be between 1x1 and 20x20, and bomb count can't be greater than tiles count)");
                   return;
               }

               numRows = Int32::Parse(numRowsTextBox->Text);
               numCols = Int32::Parse(numColsTextBox->Text);
               numBombs = Int32::Parse(numBombsTextBox->Text);

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

            void MyForm::btnMouseEnter(System::Object^ sender, EventArgs^ e) {
                Button^ button = safe_cast<Button^>(sender);
                button->Font = button->Font;

                button->BackColor = Color::Red;
            }

            private: System::Void button_MouseLeave(System::Object^ sender, EventArgs^ e) {
                Button^ button = safe_cast<Button^>(sender);
                button->Font = button->Font;
                button->BackColor = Color::Transparent;
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
               lblBestTime->Text = "Best Time: " + stats->bestTimeFormatted();
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


           void ExitLabel_Click(System::Object^ sender, System::EventArgs^ e) {
               Button^ exitButton = dynamic_cast<Button^>(this->Controls["Exit"]);
               if (exitButton != nullptr) {
                   exitButton->PerformClick();
               }
           }

           void ExitButton_Click(System::Object^ sender, System::EventArgs^ e) {
               this->Close();
           }

};


}