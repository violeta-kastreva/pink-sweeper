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
				//button->Click += gcnew EventHandler(this, &MyForm::Button_Click);
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


	void MyForm::LeftClickAction(MineButton^ clickedButton)
	{
		if (clickedButton->IsFlagged || clickedButton->IsRevealed)
		{
        // Ignore clicks on flagged or already revealed buttons
			 return;
		}

	    if (clickedButton->IsMine)
		{
        // End the game if a bomb is clicked
			EndGame(false);
		}
		else
		{
        // Reveal the button and its nearby empty spaces
			RevealButton(clickedButton);
		}
}

	void MyForm::RightClickAction(MineButton^ clickedButton)
	{
    // Toggle the flag on or off
		clickedButton->IsFlagged = !clickedButton->IsFlagged;

	    if (clickedButton->IsFlagged)
		{
        // Show flag icon or change the button text to "F" to indicate a flag
			clickedButton->Text = "F";
		}
		else
		{
        // Hide flag icon or clear the button text
			clickedButton->Text = "";
		}
	}


	};
}
