#include "your'ryWinAPI.h"
#include <windows.h>
#include <psapi.h>
#include <commdlg.h>
#include <filesystem>
#include <fstream>

constexpr int KEY_COUNT = 256;

bool prevKey[KEY_COUNT] = {};
bool nowKey[KEY_COUNT] = {};

void UpdateKeyboard()
{
    memcpy(prevKey, nowKey, sizeof(nowKey));

    for (int key = 0; key < KEY_COUNT; key++)
    {
        nowKey[key] = (GetAsyncKeyState(key) & 0x8000) != 0;
    }
}

bool IsKeyDown(int key)
{
    return (0 <= key && key < KEY_COUNT)? nowKey[key]: false;
}

bool IsKeyPressed(int key)
{
    return (0 <= key && key < KEY_COUNT)? nowKey[key] && !prevKey[key]: false;
}

bool IsKeyReleased(int key)
{
    return (0 <= key && key < KEY_COUNT)? !nowKey[key] && prevKey[key] : false;
}

std::wstring StringToWString(const std::string& str)
{
    // 変換に必要なサイズを取得
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);
    // 変換先のwchar_t配列を作成
    std::wstring wstr(size_needed, 0);
    // 変換を実行
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &wstr[0], size_needed);
    return wstr;
}

std::string WStringToString(const std::wstring& wstr)
{
    // 変換に必要なサイズを取得
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), NULL, 0, NULL, NULL);
    // 変換先のchar配列を作成
    std::string str(size_needed, 0);
    // 変換を実行
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), static_cast<int>(wstr.size()), &str[0], size_needed, NULL, NULL);
    return str;
}

std::string substrBack(std::string str, size_t pos, size_t len) {
    const size_t strLen = str.length();

    return str.substr(strLen - pos, len);
}

void PrintMemoryUsage() {
    //HANDLE hProcess = GetCurrentProcess();
    //PROCESS_MEMORY_COUNTERS pmc;
    //if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
    //    // Working Set Size (現在のメモリ使用量) をMB単位で表示
    //    std::string a = "useMemory:"+std::to_string(pmc.WorkingSetSize) + " B\n";
    //    OutputDebugString(a.c_str());
    //}
}

std::string OpenImageFile()
{
    char fileName[MAX_PATH] = {};

    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;


    // png,gif,jpg,bmpのみ表示
    ofn.lpstrFilter =
        "Image Files\0*.png;*.gif;*.jpg;*.jpeg;*.bmp\0"
        "All Files\0*.*\0";

    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
    {
        return fileName;
    }

    return "";
}

std::string GetRelativePath(const std::string& targetPath)
{
    char exePath[MAX_PATH];
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);

    std::filesystem::path exeDir =
        std::filesystem::path(exePath).parent_path();

    std::string root = exeDir.string();

    if (!root.empty() && root.back() != '\\')
        root += '\\';

    if (targetPath.rfind(root, 0) == 0)
    {
        return targetPath.substr(root.size());
    }

    return targetPath;
}

std::string GetRelativePath()
{
    char exePath[MAX_PATH];
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);

    std::filesystem::path exeDir =
        std::filesystem::path(exePath).parent_path();

    std::string root = exeDir.string();

    if (!root.empty() && root.back() != '\\')
        root += '\\';


    return root;
}

bool SaveFileDialog(const char* defaultName,const char* extension, const char* InitialDir)
{
    char fileName[MAX_PATH] = {};

    strcpy_s(fileName, defaultName);

    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    if (InitialDir != nullptr) {
        ofn.lpstrInitialDir = InitialDir;
    }

    ofn.lpstrDefExt = extension;
    ofn.lpstrFilter =
        "JSON Files\0*.json\0"
        "All Files\0*.*\0";

    ofn.Flags =
        OFN_PATHMUSTEXIST |
        OFN_OVERWRITEPROMPT;

    if (GetSaveFileNameA(&ofn))
    {
        std::ofstream ofs(fileName);
        return true;
    }

    return false;
}