#pragma once
#include <string>
#include "Windows.h"


//GetAsyncKeyStateを使ったキー入力を更新するためのアップデート
void UpdateKeyboard();
//キーが押されたなら
bool IsKeyDown(int key);
//キーが押されているなら
bool IsKeyPressed(int key);
//キーが離されたなら
bool IsKeyReleased(int key);
//wstringにstringを変換
std::wstring StringToWString(const std::string& str);
//stringにwstringを変換
std::string WStringToString(const std::wstring& wstr);
//第1引数stringの後ろから第2引数番目から第3引数分の文字取得　API使ってないため移行するかも
std::string substrBack(std::string str, size_t pos, size_t len);
//第1引数wstringの後ろから第2引数番目から第3引数分の文字取得　API使ってないため移行するかも
std::wstring subwstrBack(std::wstring str, size_t pos, size_t len);

void PrintMemoryUsage();
//エクスプローラーを開きイメージ画像を選択でき、絶対パスを返す
std::string OpenImageFileA();

std::wstring OpenImageFileW();

std::wstring OpenJsonFileW();
//受けっとったファイルパスから実行ファイルからの相対パス取得 動作不安定？
std::string GetRelativePath(const std::string& targetPath);

//実行EXEの絶対パスを返す
std::string GetRelativePath();
//エクスプローラーを開き引数の通りにファイルを新規・上書き保存する　
// 第一引数:ファイルの初期名　第二引数:保存形式(拡張子)　第三引数:初期表示のディレクトリ場所
bool SaveFileDialog(const char* defaultName, const char* extension, const char* InitialDir);