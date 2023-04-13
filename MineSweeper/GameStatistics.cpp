using namespace System::IO;
using namespace System;

public ref class GameStatistics {
public:
    int bestTime;
    int gamesPlayed;
    int gamesWon;
    double winPercentage;
    int longestWinStreak;
    int longestLoseStreak;
    int currentStreak;

    void LoadFromFile()
    {
        String^ fileName = "statistics.txt";

        if (System::IO::File::Exists(fileName))
        {
            try
            {
                System::IO::StreamReader^ reader = gcnew System::IO::StreamReader(fileName);

                bestTime = Int32::Parse(reader->ReadLine());
                gamesPlayed = Int32::Parse(reader->ReadLine());
                gamesWon = Int32::Parse(reader->ReadLine());
                winPercentage = Double::Parse(reader->ReadLine());
                longestWinStreak = Int32::Parse(reader->ReadLine());
                longestLoseStreak = Int32::Parse(reader->ReadLine());
                currentStreak = Int32::Parse(reader->ReadLine());

                reader->Close();
            }
            catch (Exception^ ex)
            {
                System::Windows::Forms::MessageBox::Show("An error occurred while loading the statistics: " + ex->Message, "Error occured", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
            }
        }
        else
        {
            bestTime = -1;
            gamesPlayed = 0;
            gamesWon = 0;
            winPercentage = 0;
            longestWinStreak = 0;
            longestLoseStreak = 0;
            currentStreak = 0;
        }
    }

};
