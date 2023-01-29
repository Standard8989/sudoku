#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <chrono>
#include <iomanip>
using namespace std;

void print(string);
bool check(string, int);
void solve(string, int);

// 時間計測用変数 : 開始時間, 解答生成終了時間, 全探索終了時間
chrono::system_clock::time_point start, end_ans, end_search_all;

int main(int argc, char** argv) {
    string problem;
    cout << "plz input the problem" << endl; // ガバガバ英語
    cin >> problem;

    // 入力された問題を表示
    print(problem);
    cout << "\n\n" << flush;

    start = end_ans = chrono::system_clock::now();

    solve(problem, 0);
    cout << "finished!" << endl;

    end_search_all = chrono::system_clock::now();

    long double time_ans = static_cast<long double>(chrono::duration_cast<chrono::microseconds>(end_ans - start).count() / 1000.0);
    long double time_search_all = static_cast<long double>(chrono::duration_cast<chrono::microseconds>(end_search_all - start).count() / 1000.0);

    cout << std::fixed;
    cout  << "time_ans : " << std::setprecision(10) << time_ans << endl;
    cout << "time_search_all : " << std::setprecision(10) << time_search_all << endl;

    return 0;
}

// 文字列を整えて表示する
void print(string s) {
    if(start == end_ans) {
        end_ans = chrono::system_clock::now();
    }

    for (int i = 0;i < s.length();i++) {
        putchar(s[i]);
        if (i % 27 == 26 && i != 80) {
            cout << "\n-----------\n";
        }
        else if (i % 9 == 8) {
            putchar('\n');
        }
        else if (i % 3 == 2) {
            putchar('|');
        }
    }
    cout << flush;
}

// メインの解答生成処理
// 再帰を用いて全探索する
void solve(string s, int i) {
    if (i == 81) {
        print(s);
        return;
    }
    else {
        if (s[i] == '0') { // もし対象の文字が空なら当てはまる数字を探す
            for (int j = 1;j < 10;j++) {
                string s_ = s.substr(0, i) + to_string(j) + s.substr(i + 1);
                if (check(s_, i)) { // もし一時的に追加した数字が正しいなら文字を一つすすめて再帰
                    solve(s_, i + 1);
                }
            }
        }
        else { // すでに埋まっていた場合は次に進む
            solve(s, i + 1);
        }
    }
}

// 数字を追加した文字列が正しいかどうかを判定する関数
bool check(string s, int i) {
    int temp = 0;
    // 追加した数字の行、列、ボックス内に存在する数字の集合
    set<char> there;

    // 列チェック
    temp = i % 9;
    for (int i = 0;i < 9;i++) {
        if (s[temp] >= '1' && s[temp] <= '9') {
            if (there.count(s[temp])) {
                return false;
            }
            there.insert(s[temp]);
        }
        temp += 9;
    }

    // 行チェック
    there.clear();
    temp = i - i % 9;
    for (int i = 0;i < 9;i++) {
        if (s[temp] >= '1' && s[temp] <= '9') {
            if (there.count(s[temp])) {
                return false;
            }
            there.insert(s[temp]);
        }
        temp++;
    }

    // ボックスチェック
    there.clear();
    int list[9];
    int Nc = i % 9;
    int Nr = static_cast<int>(round((i - Nc) / 9.0));
    int Ncs = Nc - Nc % 3;
    int Nrs = Nr - Nr % 3;
    int num = Ncs + Nrs * 9;

    int count = 0;
    for (int k = 0;k < 3;k++) {
        for (int j = 0;j < 3;j++) {
            list[count] = num;
            count++;
            num++;
        }
        num += 6;
    }

    for (int i = 0;i < 9;i++) {
        if (s[list[i]] >= '1' && s[list[i]] <= '9') {
            if (there.count(s[list[i]])) {
                return false;
            }
            there.insert(s[list[i]]);
        }
    }

    return true;
}
