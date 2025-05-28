#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// キャリー c_i の論理式を文字列で生成する関数（セミコロンなし）
string generate_carry_expr(int i) {
    if (i == 0) return "c0 = c0"; // 初期キャリー

    string expr;
    for (int k = 0; k < i; ++k) {
        if (!expr.empty()) expr += " | ";
        expr += "(";
        for (int j = i - 1; j > k; --j) {
            expr += "p" + to_string(j) + " & ";
        }
        expr += "g" + to_string(k) + ")";
    }

    // 最後の項: p[i-1] & ... & p0 & c0
    expr += " | (";
    for (int j = i - 1; j >= 0; --j) {
        expr += "p" + to_string(j) + " & ";
    }
    expr += "c0)";

    return "c" + to_string(i) + " = " + expr;
}

int main() {
    ofstream outfile("CLA.txt");
    if (!outfile) {
        cerr << "CLA.txt を開けませんでした。\n";
        return 1;
    }

    for (int i = 0; i <= 31; ++i) {
        string expr = generate_carry_expr(i);
        outfile << expr << "\n";
    }

    outfile.close();
    cout << "a.txt に c0〜c31 の式を出力しました。\n";
    return 0;
}
