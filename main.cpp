#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//KMP算法中模式串的处理
vector<int> build(string word) {
    int n = word.length();
    vector<int> next(n);
    next[0] = 0;
    int len = 0;
    int i = 1;
    while (i < n) {
        if (word[i] == word[len]) {
            len++;
            next[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = next[len - 1];
            } else {
                next[i] = 0;
                i++;
            }
        }
    }
    return next;
}

bool findSubStr(string s, string word,vector<int> next) {
    // 全部转小写以匹配用户的大小写失误
    for (char &c: s) {
        c = tolower(c);
    }
    for (char &c: word) {
        c = tolower(c);
    }

    int m = s.length();
    int n = word.length();

    int i = 0, j = 0;
    while (i < m) {
        if (word[j] == s[i]) {
            i++;
            j++;
        }
        if (j == n) {//匹配成功
            return true;
        } else if (i < m && word[j] != s[i]) {
            if (j != 0) {
                j = next[j - 1];
            } else {
                i++;
            }
        }
    }
    //匹配失败
    return false;
}

int main() {
    //从文件读取句子
    vector<string> sentences;
    for (int i = 0; i < 3; ++i) {
        string fileName = "d"+ to_string(i+1)+".txt";//从文件读取
        ifstream file(fileName);
        string d;
        getline(file, d);
        cout<<"d"<<i+1<<" = "<<d<<endl;

        sentences.push_back(d);
    }

    string word;
    do {
        //输入一个词语
        cout << "请输入一个词语：";
        cin >> word;
        for (char &c : word) {
            c = tolower(c);
        }

        //查找包含词语的所有句子编号
        vector<int> matchingSentences;
        for (int i = 0; i < sentences.size(); ++i) {
            if (findSubStr(sentences[i],word,build(word))) {//调用自定义函数判断是否为字串
                matchingSentences.push_back(i + 1);
            }
        }

        //输出
        if (matchingSentences.empty()) {
            cout << "未找到包含该词语的句子" << endl;
        } else {
            cout << "包含词语 \"" << word << "\" 的文件有：" << endl;
            for (int i = 0; i < matchingSentences.size(); ++i) {
                cout << "d" << matchingSentences[i] << ".txt " << endl;
            }
        }

        cout<<endl;
    } while (word!="quit");//输入quit退出查询
    return 0;
}


