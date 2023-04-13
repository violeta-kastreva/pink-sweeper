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


	#include "MineButton.h"
	#include "MineField.h"

	

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			InitializeCustomFieldUI();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}



	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		MineField^ mineField;
		TextBox^ numRowsTextBox;
		TextBox^ numColsTextBox;
		TextBox^ numBombsTextBox;
		Button^ generateCustomFieldButton;
		const int leftToolBarSize = 200;
		const int topToolBarSize = 50;
		const int formWidth = 1000;
		const int formHeight = 800;



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
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
		const int padding = 1;
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
		DeleteMatrixOfButtons();
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
				   MessageBox::Show("Congratulations! You won the game!", "Pinksweeper", MessageBoxButtons::OK, MessageBoxIcon::Information);
			   }
			   else
			   {
				   MessageBox::Show("You clicked on a bomb! Game over.", "Pinksweeper", MessageBoxButtons::OK, MessageBoxIcon::Error);
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

		   void MyForm::InitializeCustomFieldUI()
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


		 



	};
}
