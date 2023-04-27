using namespace System::IO;
using namespace System;

public ref class GameStatistics {
public:
    int bestTime = -1;
    int gamesPlayed = 0;
    int gamesWon = 0;
    double winPercentage = 0;
    int longestWinStreak = 0;
    int longestLoseStreak = 0;
    int currentStreak = 0;
    bool winStreak = false;

    String^ bestTimeFormatted() {      
        if (bestTime > 0) {
            int hours = bestTime / 3600;
            int minutes = (bestTime % 3600) / 60;
            int seconds = bestTime % 60;
            return String::Format("{0:D2}:{1:D2}:{2:D2}", hours, minutes, seconds);
        } else return String::Format("{0:D2}:{1:D2}:{2:D2}", 0, 0, 0);
    }

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
