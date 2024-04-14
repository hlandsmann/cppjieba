#include "cppjieba/Jieba.hpp"

#include <cppjieba/Unicode.hpp>
#include <cstddef>
#include <iostream>
#include <limonp/StringUtil.hpp>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// /home/harmen/src/zikhron/third_party/cppjieba/
const char* const DICT_PATH = "/home/harmen/src/zikhron/third_party/cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "/home/harmen/src/zikhron/third_party/cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "/home/harmen/src/zikhron/third_party/cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "/home/harmen/src/zikhron/third_party/cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "/home/harmen/src/zikhron/third_party/cppjieba/dict/stop_words.utf8";

void testString(cppjieba::Jieba& jieba,
                const std::string& str)
{
    // vector<cppjieba::Word> jiebawords;
    vector<string> words;
    jieba.Cut(str, words, true);
    cout << "   HMM: " <<  limonp::Join(words.begin(), words.end(), "/") << endl;
    jieba.Cut(str, words, false);
    cout << "no HMM: " <<  limonp::Join(words.begin(), words.end(), "/") << endl;
    jieba.CutAll(str, words);
    cout << "CutAll: " <<  limonp::Join(words.begin(), words.end(), "/") << endl;
    jieba.CutForSearch(str, words);
    cout << "CutFS:  " <<  limonp::Join(words.begin(), words.end(), "/") << endl;


}

auto main(int argc, char** argv) -> int
{
    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);
    vector<string> words;
    vector<cppjieba::Word> jiebawords;
    string s;
    string result;

    s = "他来到了网易杭研大厦";
    testString(jieba, s);
    // cout << s << endl;
    // cout << "[demo] Cut With HMM" << endl;
    // jieba.Cut(s, words, true);
    // cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    // cout << "[demo] Cut Without HMM " << endl;
    // jieba.Cut(s, words, false);
    // cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    s = "我来到北京清华大学";
    testString(jieba, s);
    // cout << s << endl;
    // cout << "[demo] CutAll" << endl;
    // jieba.CutAll(s, words);
    // cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    s = "小明硕士毕业于中国科学院计算所，后在日本京都大学深造";
    testString(jieba, s);
    // cout << s << endl;
    // cout << "[demo] CutForSearch" << endl;
    // jieba.CutForSearch(s, words);
    // cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    cout << "[demo] Insert User Word" << endl;
    jieba.InsertUserWord("男默女泪");
    jieba.Cut("男默女泪", words);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;
    jieba.DeleteUserWord("男默女泪");
    jieba.Cut("男默女泪", words);
    cout << limonp::Join(words.begin(), words.end(), "/") << endl;

    cout << "[demo] CutForSearch Word With Offset" << endl;
    jieba.CutForSearch(s, jiebawords, true);
    cout << jiebawords << endl;

    cout << "[demo] Lookup Tag for Single Token" << endl;
    const int DemoTokenMaxLen = 32;
    char DemoTokens[][DemoTokenMaxLen] = {"拖拉机", "CEO", "123", "。"};
    vector<pair<string, string> > LookupTagres(sizeof(DemoTokens) / DemoTokenMaxLen);
    vector<pair<string, string> >::iterator it;
    for (it = LookupTagres.begin(); it != LookupTagres.end(); it++) {
        it->first = DemoTokens[it - LookupTagres.begin()];
        it->second = jieba.LookupTag(it->first);
    }
    cout << LookupTagres << endl;

    cout << "[demo] Tagging" << endl;
    vector<pair<string, string> > tagres;
    s = "我是拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上CEO，走上人生巅峰。";
    jieba.Tag(s, tagres);
    cout << s << endl;
    cout << tagres << endl;

    cout << "[demo] Keyword Extraction" << endl;
    const size_t topk = 5;
    vector<cppjieba::KeywordExtractor::Word> keywordres;
    jieba.extractor.Extract(s, keywordres, topk);
    cout << s << endl;
    cout << keywordres << endl;
    return EXIT_SUCCESS;
}
