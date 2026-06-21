#include "Windows.h"
#include "your'ryWinAPI.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int nShowCmd) {

    SaveFileDialog("NewFile", "json", GetRelativePath().c_str());
}