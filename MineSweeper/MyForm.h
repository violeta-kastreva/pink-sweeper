#pragma once

namespace MineSweeper {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	#include "MineButton.h"
	#include "MineField.h"

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::Button^ button1;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		MineField^ mineField;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(581, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(41, 37);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1239, 687);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		GenerateMatrixOfButtons(20, 44, 2);
	}

	void MyForm::GenerateMatrixOfButtons(int rows, int cols, int mines)
	{
		const int buttonSize = 30;
	    const int padding = 10;
		mineField = gcnew MineField(rows, cols, mines);
		mineField->InitializeField();

		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				MineButton^ button = mineField->GetButton(i, j);
				button->Size = System::Drawing::Size(buttonSize, buttonSize);
				button->Location = Point(padding + j * (buttonSize + padding), padding + i * (buttonSize + padding));
				button->MouseDown += gcnew MouseEventHandler(this, &MyForm::Button_Click);
				this->Controls->Add(button);
			}
		}
	}

	void MyForm::DeleteMatrixOfButtons()
	{
		if (mineField == nullptr)
		{
			return;
		}

		for (int i = 0; i < mineField->NumRows; ++i)
		{
			for (int j = 0; j < mineField->NumCols; ++j)
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
			MessageBox::Show("Congratulations! You won the game!", "Minesweeper", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			MessageBox::Show("You clicked on a bomb! Game over.", "Minesweeper", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		for (int i = 0; i < mineField->NumRows; ++i)
		{
			for (int j = 0; j < mineField->NumCols; ++j)
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
		else
		{
			for (int i = -1; i <= 1; ++i)
			{
				for (int j = -1; j <= 1; ++j)
				{
					if (i == 0 && j == 0) continue;

					int newRow = button->Row + i;
					int newCol = button->Col + j;

					if (newRow >= 0 && newRow < mineField->NumRows && newCol >= 0 && newCol < mineField->NumCols)
					{
						RevealButton(mineField->GetButton(newRow, newCol));
					}
				}
			}
		}
	}

	};
}
