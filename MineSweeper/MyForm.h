#pragma once

//!warning for the oop assistants!
//! 
//! 
//the code for the application follows the .NET conventions
//it uses standard .NET classes to provide better integration
//things such as the array and class definitions are done in a ".NET" way
//anything that doesn't look like native C++ is simply a .NET component
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
	

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			InitializeCustomFieldUI();
			InitializeMenuUI();
			InitializeStatisticsUI();
			gameStats = gcnew GameStatistics();
			gameStats->LoadFromFile(); 
			UpdateStatisticLabels(gameStats);
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private:
		System::ComponentModel::Container^ components;
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
		GameStatistics^ gameStats;


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1000, 800);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximumSize = System::Drawing::Size(1000, 800);
			this->MinimumSize = System::Drawing::Size(1000, 800);
			this->Name = L"MyForm";
			this->Text = L"PinkSweeper";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		GenerateMatrixOfButtons(20, 10, 150, nullptr, nullptr, nullptr);
	}



	void MyForm::GenerateMatrixOfButtons(int rows, int cols, int numBombs, array<array<bool>^>^ mineData, array<array<bool>^>^ revealedData, array<array<bool>^>^ flaggedData)
	{
		const int buttonSize = 28;
		const int padding = 0;
		const int leftTotalPadding = (formWidth - (cols * (buttonSize + padding) - padding)) / 2 + leftToolBarSize;
		const int topTotalPadding = (formHeight - (rows * (buttonSize + padding) - padding)) / 2 + topToolBarSize;
		mineField = gcnew MineField(rows, cols, numBombs);
		mineField->InitializeField();

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				MineButton^ button = gcnew MineButton(i, j);
				button->Size = System::Drawing::Size(buttonSize, buttonSize);
				button->Location = Point(leftTotalPadding + padding + j * (buttonSize + padding), topTotalPadding + padding + i * (buttonSize + padding));
				button->MouseDown += gcnew MouseEventHandler(this, &MyForm::Button_Click);
				this->Controls->Add(button);
				mineField->SetButton(i, j, button);

				if (mineData != nullptr && mineData[i][j])
				{
					button->IsMine = true;
					mineField->AddMine(i, j);
					button->AdjacentMines = mineField->GetAdjacentMineCount(i, j);
				}

				if (revealedData != nullptr && revealedData[i][j])
				{
					button->IsRevealed = true;
					button->Text = mineField->GetAdjacentMineCount(i, j).ToString();
				}

				if (flaggedData != nullptr && flaggedData[i][j])
				{
					button->IsFlagged = true;
					button->Text = "F";
				}
			}
		}

		if (mineData == nullptr)
		{
			Random^ random = gcnew Random();
			int bombsPlaced = 0;
			while (bombsPlaced < numBombs)
			{
				int row = random->Next(rows);
				int col = random->Next(cols);
				MineButton^ button = mineField->GetButton(row, col);
				button->AdjacentMines = 0;

				if (!button->IsMine)
				{
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


	void MyForm::DeleteMatrixOfButtons()
	{
		if (mineField == nullptr)
		{
			return;
		}

		for (int i = 0; i < mineField->GetNumRows(); ++i)
		{
			for (int j = 0; j < mineField->GetNumCols(); ++j)
			{
				MineButton^ button = mineField->GetButton(i, j);
				this->Controls->Remove(button);
				delete button;
			}
		}

		mineField = nullptr;
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		DeleteMatrixOfButtons(); //to be removed
	}
		   void MyForm::Button_Click(Object^ sender, MouseEventArgs^ e)
		   {
			   MineButton^ clickedButton = safe_cast<MineButton^>(sender); //stolen from chatgpt

			   if (e->Button == System::Windows::Forms::MouseButtons::Left)
			   {
				   LeftClickAction(clickedButton);
			   }
			   else if (e->Button == System::Windows::Forms::MouseButtons::Right)
			   {
				   RightClickAction(clickedButton);
			   }
		   }



		   void MyForm::LeftClickAction(MineButton^ clickedButton)
		   {
			   System::Media::SoundPlayer^ soundPlayer = gcnew System::Media::SoundPlayer();
			   soundPlayer->SoundLocation = "fieldClick.wav";
			   soundPlayer->Load();
			   soundPlayer->Play();
			 
			   if (clickedButton->IsFlagged || clickedButton->IsRevealed)
			   {
				   return;
			   }

			   if (clickedButton->IsMine)
			   {
				   EndGame(false);
			   }
			   else
			   {
				   RevealButton(clickedButton);

				   if (CheckWin()) {
					   EndGame(true);
				   }				

			   }
		   }

		   void MyForm::RightClickAction(MineButton^ clickedButton)
		   {
			   System::Media::SoundPlayer^ soundPlayer = gcnew System::Media::SoundPlayer();
			   soundPlayer->SoundLocation = "flagClick.wav";
			   soundPlayer->Load();
			   soundPlayer->Play();
			   clickedButton->IsFlagged = !clickedButton->IsFlagged;

			   if (clickedButton->IsFlagged)
			   {
				   clickedButton->Text = "F";
			   }
			   else
			   {
				   clickedButton->Text = "";
			   }
		   }

		   void MyForm::EndGame(bool isWin)
		   {
			   if (isWin)
			   {
				   MessageBox::Show("Congratulations! You won the game!", "Pinksweeper", MessageBoxButtons::OK, MessageBoxIcon::None);
			   }
			   else
			   {
				   MessageBox::Show("You clicked on a bomb! Game over.", "Pinksweeper", MessageBoxButtons::OK, MessageBoxIcon::None);
			   }
			   for (int i = 0; i < mineField->GetNumRows(); ++i)
			   {
				   for (int j = 0; j < mineField->GetNumCols(); ++j)
				   {
					   MineButton^ button = mineField->GetButton(i, j);
					   if (button->IsMine)
					   {
						   button->Text = "B";
					   }
				   }
			   }
		   }

		   void MyForm::RevealButton(MineButton^ button)
		   {
			   if (button->IsFlagged || button->IsRevealed)
			   {
				   return;
			   }

			   button->IsRevealed = true;
			   button->Enabled = false;
			   button->BackColor = Color::LightGray;

			   if (button->AdjacentMines > 0)
			   {
				   button->Text = button->AdjacentMines.ToString();
			   }
			   
				   for (int i = -1; i <= 1; ++i)
				   {
					   for (int j = -1; j <= 1; ++j)
					   {
						   if (i == 0 && j == 0) continue;

						   int newRow = button->Row + i;
						   int newCol = button->Col + j;

						   if (newRow >= 0 && newRow < mineField->GetNumRows() && newCol >= 0 && newCol < mineField->GetNumCols() && !mineField->GetButton(newRow, newCol)->IsMine)
						   {
							   RevealButton(mineField->GetButton(newRow, newCol));
						   }
					   }
				   }
			   
		   }

		   void MyForm::InitializeCustomFieldUI() //add validation!
		   {
			   numRowsTextBox = gcnew TextBox();
			   numRowsTextBox->Location = Point(10, 10);
			   numRowsTextBox->Size = System::Drawing::Size(50, 20);
			   numRowsTextBox->Text = "10";
			   this->Controls->Add(numRowsTextBox);

			   numColsTextBox = gcnew TextBox();
			   numColsTextBox->Location = Point(70, 10);
			   numColsTextBox->Size = System::Drawing::Size(50, 20);
			   numColsTextBox->Text = "10";
			   this->Controls->Add(numColsTextBox);

			   numBombsTextBox = gcnew TextBox();
			   numBombsTextBox->Location = Point(130, 10);
			   numBombsTextBox->Size = System::Drawing::Size(50, 20);
			   numBombsTextBox->Text = "10";
			   this->Controls->Add(numBombsTextBox);

			   generateCustomFieldButton = gcnew Button();
			   generateCustomFieldButton->Location = Point(190, 10);
			   generateCustomFieldButton->Size = System::Drawing::Size(120, 20);
			   generateCustomFieldButton->Text = "Generate Custom Field";
			   generateCustomFieldButton->Click += gcnew EventHandler(this, &MyForm::GenerateCustomFieldButton_Click);
			   this->Controls->Add(generateCustomFieldButton);

		   }


		   void MyForm::InitializeMenuUI() {
			   btnSave = gcnew Button();
			   //btnSave->Name = "btnSave";
			   btnSave->Text = "Save";
			   btnSave->Location = Point(10, 200);
			   numRowsTextBox->Size = System::Drawing::Size(50, 20);
			   btnSave->Click += gcnew EventHandler(this, &MyForm::SaveGameState);
			   this->Controls->Add(btnSave);

			   btnLoad = gcnew Button();
			  //btnLoad->Name = "btnLoad";
			   btnLoad->Text = "Load";
			   btnLoad->Location = Point(100, 200); //adjust the location 
			   numRowsTextBox->Size = System::Drawing::Size(50, 20);
			   btnLoad->Click += gcnew EventHandler(this, &MyForm::LoadGameState);
			   this->Controls->Add(btnLoad);

			   btnHint = gcnew Button();
			   //btnHint->Name = "btnHint";
			   btnHint->Text = "Hint";
			   btnHint->Location = Point(190, 200); // Adjust the location as needed
			   btnHint->Click += gcnew EventHandler(this, &MyForm::Hint_Click);
			   this->Controls->Add(this->btnHint);


		   }

		   void MyForm::InitializeStatisticsUI() {
			   lblBestTime = gcnew Label();
			   lblBestTime->Location = Point(10, 400);
			   lblBestTime->AutoSize = true;
			   Controls->Add(lblBestTime);

			   lblGamesPlayed = gcnew Label();
			   lblGamesPlayed->Location = Point(10, 420);
			   lblGamesPlayed->AutoSize = true;
			   Controls->Add(lblGamesPlayed);

			   lblGamesWon = gcnew Label();
			   lblGamesWon->Location = Point(10, 440);
			   lblGamesWon->AutoSize = true;
			   Controls->Add(lblGamesWon);

			   lblWinPercentage = gcnew Label();
			   lblWinPercentage->Location = Point(10, 460);
			   lblWinPercentage->AutoSize = true;
			   Controls->Add(lblWinPercentage);

			   lblLongestWinStreak = gcnew Label();
			   lblLongestWinStreak->Location = Point(10, 480);
			   lblLongestWinStreak->AutoSize = true;
			   Controls->Add(lblLongestWinStreak);

			   lblLongestLoseStreak = gcnew Label();
			   lblLongestLoseStreak->Location = Point(10, 500);
			   lblLongestLoseStreak->AutoSize = true;
			   Controls->Add(lblLongestLoseStreak);

			   lblCurrentStreak = gcnew Label();
			   lblCurrentStreak->Location = Point(10, 520);
			   lblCurrentStreak->AutoSize = true;
			   Controls->Add(lblCurrentStreak);
		   }

		   void MyForm::GenerateCustomFieldButton_Click(Object^ sender, EventArgs^ e)
		   {
			   int numRows = Int32::Parse(numRowsTextBox->Text);
			   int numCols = Int32::Parse(numColsTextBox->Text);
			   int numBombs = Int32::Parse(numBombsTextBox->Text);

			   DeleteMatrixOfButtons();
			   GenerateMatrixOfButtons(numRows, numCols, numBombs, nullptr, nullptr, nullptr);
		   }

		   void MyForm::SaveGameState(Object^ sender, EventArgs^ e)
		   {
			   StreamWriter^ sw = nullptr;
			   try
			   {
				   sw = gcnew StreamWriter("gamestate.txt");

				   sw->WriteLine(mineField->GetNumRows());
				   sw->WriteLine(mineField->GetNumCols());
				   sw->WriteLine(mineField->GetNumBombs());

				   for (int i = 0; i < mineField->GetNumRows(); ++i)
				   {
					   for (int j = 0; j < mineField->GetNumCols(); ++j)
					   {
						   MineButton^ button = mineField->GetButton(i, j);
						   sw->Write(button->IsMine ? '1' : '0');
						   sw->Write(button->IsRevealed ? '1' : '0');
						   sw->Write(button->IsFlagged ? '1' : '0');
					   }
					   sw->WriteLine();
				   }
			   }
			   catch (Exception^ ex)
			   {
				   MessageBox::Show("Error saving the game state: " + ex->Message);
			   }
			   finally
			   {
				   if (sw != nullptr)
				   {
					   sw->Close();
				   }
			   }
		   }

		   void MyForm::LoadGameState(Object^ sender, EventArgs^ e)
		   {
			   StreamReader^ sr = nullptr;
			   try
			   {
				   sr = gcnew StreamReader("gamestate.txt");

				   int numRows = Int32::Parse(sr->ReadLine());
				   int numCols = Int32::Parse(sr->ReadLine());
				   int numBombs = Int32::Parse(sr->ReadLine());

				   array<array<bool>^>^ mineData = gcnew array<array<bool>^>(numRows);
				   array<array<bool>^>^ revealedData = gcnew array<array<bool>^>(numRows);
				   array<array<bool>^>^ flaggedData = gcnew array<array<bool>^>(numRows);
				   for (int i = 0; i < numRows; ++i)
				   {
					   String^ row = sr->ReadLine();
					   mineData[i] = gcnew array<bool>(numCols);
					   revealedData[i] = gcnew array<bool>(numCols);
					   flaggedData[i] = gcnew array<bool>(numCols);
					   for (int j = 0, k = 0; j < numCols; ++j, k += 3)
					   {
						   mineData[i][j] = row[k] == '1';
						   revealedData[i][j] = row[k + 1] == '1';
						   flaggedData[i][j] = row[k + 2] == '1';
					   }
				   }

				   DeleteMatrixOfButtons();
				   GenerateMatrixOfButtons(numRows, numCols, numBombs, mineData, revealedData, flaggedData);
			   }
			   catch (Exception^ ex)
			   {
				   MessageBox::Show("Error loading the game state: " + ex->Message);
			   }
			   finally
			   {
				   if (sr != nullptr)
				   {
					   sr->Close();
				   }
			   }
		   }

	
		   bool MyForm::CheckWin()
		   {
			   int revealedButtons = 0;
			   for (int i = 0; i < mineField->GetNumRows(); ++i)
			   {
				   for (int j = 0; j < mineField->GetNumCols(); ++j)
				   {
					   MineButton^ button = mineField->GetButton(i, j);
					   if (button->IsRevealed)
					   {
						   ++revealedButtons;
					   }
				   }
			   }

			   return revealedButtons == (mineField->GetNumRows() * mineField->GetNumCols()) - mineField->GetNumBombs();
		   }

		   private: void Hint_Click(System::Object^ sender, System::EventArgs^ e) {
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

			   RevealButton(mineField->GetButton(x,y));

			   if (CheckWin()) {
				   EndGame(true);
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
				} catch (Exception^ e) {
					Console::WriteLine("Unable to open statistics.txt for reading: " + e->Message);
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
				} catch (Exception^ e) {
					Console::WriteLine("Unable to open statistics.txt for writing: " + e->Message);
				}
			}

			void UpdateStatisticLabels(GameStatistics^ stats) {
				lblBestTime->Text = "Best Time: " + stats->bestTime + "s";
				lblGamesPlayed->Text = "Games Played: " + stats->gamesPlayed;
				lblGamesWon->Text = "Games Won: " + stats->gamesWon;
				lblWinPercentage->Text = "Win Percentage: " + stats->winPercentage.ToString("P") + "%";
				lblLongestWinStreak->Text = "Longest Win Streak: " + stats->longestWinStreak;
				lblLongestLoseStreak->Text = "Longest Lose Streak: " + stats->longestLoseStreak;
				lblCurrentStreak->Text = "Current Streak: " + stats->currentStreak;
			}

			

	};
}
