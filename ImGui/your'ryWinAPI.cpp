#include "your'ryWinAPI.h"
#include <windows.h>
#include <psapi.h>
#include <commdlg.h>
#include <filesystem>
#include <fstream>
#include <shobjidl.h>



constexpr int KEY_COUNT = 256;

bool prevKey[KEY_COUNT] = {};
bool nowKey[KEY_COUNT] = {};
std::string m_lastFolder;
std::wstring m_wlastFolder;

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

std::wstring subwstrBack(std::wstring str, size_t pos, size_t len) {
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

std::string OpenImageFileA()
{
    char fileName[MAX_PATH] = {};

    OPENFILENAMEA ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;

    std::string a = GetRelativePath();

    ofn.lpstrInitialDir = m_lastFolder.empty()? a.c_str() : m_lastFolder.c_str();
    // png,gif,jpg,bmpのみ表示
    ofn.lpstrFilter =
        "Image Files\0*.png;*.gif;*.jpg;*.jpeg;*.bmp\0"
        "All Files\0*.*\0";

    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
    {
            m_lastFolder = std::filesystem::path(fileName).parent_path().string();
        
        return fileName;
    }

    return "";
}
std::wstring OpenImageFileW()
{
    wchar_t fileName[MAX_PATH] = {};

    OPENFILENAMEW ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;

    std::wstring initialDir = StringToWString(GetRelativePath());

    ofn.lpstrInitialDir =
        m_wlastFolder.empty() ? initialDir.c_str() : m_wlastFolder.c_str();

    ofn.lpstrFilter =
        L"Image Files\0*.png;*.gif;*.jpg;*.jpeg;*.bmp\0"
        L"All Files\0*.*\0";

    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileNameW(&ofn))
    {
        m_wlastFolder = std::filesystem::path(fileName).parent_path().wstring();
        return fileName;
    }

    return L"";
}

std::wstring OpenJsonFileW()
{
    wchar_t fileName[MAX_PATH] = {};

    OPENFILENAMEW ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;

    std::wstring initialDir = StringToWString(GetRelativePath());

    ofn.lpstrInitialDir =
        m_wlastFolder.empty() ? initialDir.c_str() : m_wlastFolder.c_str();

    ofn.lpstrFilter =
        L"Json Files\0*.json;\0"
        L"All Files\0*.*\0";

    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileNameW(&ofn))
    {
        m_wlastFolder = std::filesystem::path(fileName).parent_path().wstring();
        return fileName;
    }

    return L"";
}

//std::string GetRelativePathaa(const std::string& targetPath)
//{
//    char exePath[MAX_PATH];
//    GetModuleFileNameA(nullptr, exePath, MAX_PATH);
//
//    std::filesystem::path exeDir =
//        std::filesystem::path(exePath).parent_path();
//
//    std::string root = exeDir.string();
//
//    if (!root.empty() && root.back() != '\\')
//        root += '\\';
//
//    if (targetPath.rfind(root, 0) == 0)
//    {
//        return targetPath.substr(root.size());
//    }
//
//    return targetPath;
//}

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

std::string SaveFileDialogString(const char* defaultName, const char* extension, const char* InitialDir) {
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

        std::string a = fileName;
        return a;
    }

    return "";
}

std::vector<std::wstring> OpenImageFilesW()
{
    std::vector<std::wstring> paths;

    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    IFileOpenDialog* pDialog = nullptr;
    hr = CoCreateInstance(
        CLSID_FileOpenDialog,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pDialog));

    if (FAILED(hr))
    {
        CoUninitialize();
        return paths;
    }

    if (!m_wlastFolder.empty())
    {
        IShellItem* pFolder = nullptr;

        hr = SHCreateItemFromParsingName(
            m_wlastFolder.c_str(),
            nullptr,
            IID_PPV_ARGS(&pFolder));

        if (SUCCEEDED(hr))
        {
            pDialog->SetDefaultFolder(pFolder);
            pFolder->Release();
        }
    }

    // オプション取得
    DWORD dwFlags = 0;
    pDialog->GetOptions(&dwFlags);

    // 複数選択可能
    pDialog->SetOptions(
        dwFlags |
        FOS_ALLOWMULTISELECT |
        FOS_FILEMUSTEXIST |
        FOS_PATHMUSTEXIST);

    // フィルタ
    COMDLG_FILTERSPEC filters[] =
    {
        {
            L"Image Files",
            L"*.png;*.gif;*.jpg;*.jpeg;*.bmp"
        },
        {
            L"All Files",
            L"*.*"
        }
    };

    pDialog->SetFileTypes(
        ARRAYSIZE(filters),
        filters);

    // 表示
    hr = pDialog->Show(nullptr);

    if (SUCCEEDED(hr))
    {
        IShellItemArray* pResults = nullptr;

        hr = pDialog->GetResults(&pResults);

        if (SUCCEEDED(hr))
        {
            DWORD count = 0;
            pResults->GetCount(&count);

            for (DWORD i = 0; i < count; i++)
            {
                IShellItem* pItem = nullptr;

                if (SUCCEEDED(
                    pResults->GetItemAt(i, &pItem)))
                {
                    PWSTR pszFile = nullptr;

                    if (SUCCEEDED(
                        pItem->GetDisplayName(
                            SIGDN_FILESYSPATH,
                            &pszFile)))
                    {
                        paths.emplace_back(pszFile);

                        CoTaskMemFree(pszFile);
                    }

                    pItem->Release();
                }
            }

            pResults->Release();
        }
    }

    if (paths.size() > 0) {
        std::filesystem::path p(paths.front());
        m_wlastFolder = p.parent_path().wstring();
    }
    pDialog->Release();
    CoUninitialize();

    return paths;
}