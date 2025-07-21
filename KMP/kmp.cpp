#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 构建部分匹配表
vector<int> buildNext(const string& pattern) {
    int m = pattern.length();
    vector<int> next(m, 0);
    
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j])
            j = next[j-1];
        
        if (pattern[i] == pattern[j])
            j++;
        
        next[i] = j;
    }
    return next;
}

// KMP搜索主函数
vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> matches;
    int n = text.length();
    int m = pattern.length();
    if (m == 0) return matches;

    vector<int> next = buildNext(pattern);

    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j])
            j = next[j-1];
        
        if (text[i] == pattern[j])
            j++;

        if (j == m) {
            matches.push_back(i - m + 1);
            j = next[j-1];
        }
    }
    return matches;
}

// 测试函数
void testKMP() {
    cout << "测试1：基础测试..." << endl;
    string text1 = "ABABDABACDABABCABAB";
    string pattern1 = "ABABCABAB";
    vector<int> result1 = kmpSearch(text1, pattern1);
    cout << "匹配位置：";
    for (int pos : result1) cout << pos << " ";
    cout << "\n期望结果：10\n\n";

    cout << "测试2：多重匹配..." << endl;
    string text2 = "AAAAA";
    string pattern2 = "AA";
    vector<int> result2 = kmpSearch(text2, pattern2);
    cout << "匹配位置：";
    for (int pos : result2) cout << pos << " ";
    cout << "\n期望结果：0 1 2 3\n\n";

    cout << "测试3：无匹配情况..." << endl;
    string text3 = "ABCDEFGH";
    string pattern3 = "XYZ";
    vector<int> result3 = kmpSearch(text3, pattern3);
    if(result3.empty()) 
        cout << "未找到匹配模式\n期望结果：无匹配\n";
}

int main() {
    testKMP();
    return 0;
}