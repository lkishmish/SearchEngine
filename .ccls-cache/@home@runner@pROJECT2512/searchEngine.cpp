#include <string>
#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

string cleanToken(string token);
set<string> gatherTokens(string text);
map<string, set<string> > buildIndex(map<string, set<string> > table);
void searchEngine(string filename);

void printTokens(set<string> tokens)
{
    cout << "[";
    for (set<string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
        cout << "[(" << *it << ")]" << ',';
    cout << "\b]";
}

set<string> findQueryMatches(map<string, set<string> > &index, string sentence)
{
    set<string> tokens = gatherTokens(sentence);
    // printTokens(tokens);
    // for (set<string>::iterator it = tokens.begin(); it != tokens.end(); ++it){
    //     printTokens()
    // }
    set<string>::iterator it = tokens.begin();
    set<string> urls;
    int count = 0;
    for (set<string>::iterator it = tokens.begin(); it != tokens.end(); it++)
    {
        set<string> matchedUrls = index[*it];
        for (set<string>::iterator it2 = matchedUrls.begin(); it2 != matchedUrls.end(); it2++)
        {
            urls.insert(*it2);
        }
    }
    // for (set<string>::iterator it = urls.begin(); it != urls.end(); it++)
    // {
    // cout << *it << endl;
    // count++;
    // }
    // cout << "COUNT " << count << endl;
    return urls;
}

map<string, set<string> > buildIndex(map<string, set<string> > table)
{
    map<string, set<string> > index;
    for (map<string, set<string> >::iterator it = table.begin(); it != table.end(); it++)
    {
        set<string> tokens = it->second;
        for (set<string>::iterator it2 = tokens.begin(); it2 != tokens.end(); it2++)
        {
            index[*it2].insert(it->first);
        }
    }
    return index;
}

string cleanToken(string token)
{
    string cleanedToken;
    bool alphaNum = false;
    for (char i : token)
    {
        if (ispunct(i))
        {
            continue;
        }
        if (isalpha(i))
        {
            alphaNum = true;
        }
        cleanedToken += tolower(i);
    }
    if (!alphaNum)
    {
        return "";
    }
    return cleanedToken;
}

set<string> gatherTokens(string text)
{
    // cout << endl
    //      << "Gathering tokens for " << text << "...." << endl;
    set<string> tokens;
    string token;
    stringstream X(text);
    while (getline(X, token, ' '))
    {
        tokens.insert(cleanToken(token));
    }
    // cout << "[";
    // for (set<string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
    //     cout << "[(" << *it << "),(" << cleanToken(*it) << ")]" << ',';
    // cout << "\b]";
    return tokens;
}

void searchEngine(string filename)
{
    std::ifstream myfile;
    myfile.open(filename);
    std::string mystring;
    map<string, string> table;
    while (myfile)
    {
        string url, text;
        std::getline(myfile, url);
        std::getline(myfile, text);
        table.insert(make_pair(url, text));
    }
    // for(const auto &[key, value]: table)
    // {
    //     cout<<"URL: "<<key<<"\nText: "<<value<<endl;
    // }
    // map<string,string>::iterator t = table.find("https://en.wikipedia.org/wiki/University_of_WisconsinStevens");
    // gatherTokens(t->second);
    map<string, set<string> > tokensTable;
    for (map<string, string>::iterator it = table.begin(); it != table.end(); it++)
    {
        tokensTable.insert(make_pair(it->first, gatherTokens(it->second)));
    }
    map<string, set<string> > index = buildIndex(tokensTable);
    string sentence;
    while(true){
        cout << "Enter query sentence(press enter to quit): " << endl;
        getline(cin, sentence);
        if(sentence==""){
            break;
        }
        set<string> matches = findQueryMatches(index,sentence);
        cout << "Found " << matches.size() << "  matching pages" << endl;
        set<string>::iterator iter = matches.begin();
        while (iter != matches.end()){
          cout << (*iter) << endl;
          iter++;
        }
    }
}

int main()
{
    searchEngine("wiki-uni.txt");
    return 0;
}