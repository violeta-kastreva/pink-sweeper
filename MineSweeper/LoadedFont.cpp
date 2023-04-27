#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Text;
using namespace System::IO;

public ref struct LoadedFont
{
    property Font^ Font;
    property FontFamily^ FontFamily;
};

LoadedFont^ LoadFont(FileInfo^ file, int fontSize, FontStyle fontStyle)
{
    PrivateFontCollection^ fontCollection = gcnew PrivateFontCollection();
    fontCollection->AddFontFile(file->FullName);

    if (fontCollection->Families->Length <= 0)
    {
        throw gcnew InvalidOperationException("No font familiy found when loading font");
    }

    LoadedFont^ loadedFont = gcnew LoadedFont();
    loadedFont->FontFamily = fontCollection->Families[0];
    loadedFont->Font = gcnew Font(loadedFont->FontFamily, fontSize, fontStyle, GraphicsUnit::Pixel);
    return loadedFont;
}
