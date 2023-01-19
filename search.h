// Name : Lakshmi
// UIN: 672897625

#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
using namespace std;

// cleanToken accepts a string as argument and removes the punctuations
// preceding the first character of the string and occurring after the last
// character of the string retaining those punctuations that are in the middle
// of the word
string cleanToken(string s) {
  int len = s.length();
while (ispunct(s[len - 1])){
        s = s.substr(0, len - 1);
  len--;
    }
  while (ispunct(s[0])){
        s = s.substr(1);
    }
    
    bool flag = false;
    for (auto& itr: s){
        if (isalpha(itr)){
            flag = true;
            itr = tolower(itr);
        }
    }
    if (!flag){
        return "";
    }
    return s;
}

// gatherTokens function accepts a text and splits the text into words by space
// between them and adds each word to a set that avoid repetition of words
set<string> gatherTokens(string text) {

  string tmp;
  stringstream str_strm(text);
  // declaring string stream to accept the body text under URLs
  set<int>::iterator itr;
  set<string> words;
  // initalizing a set and its iterator
  while (getline(str_strm, tmp, ' ')) {
    // separates each word and gets rid of preceding and trailing punctuations
    // of the words
    if (cleanToken(tmp) != ""){
    words.insert(cleanToken(tmp));
    // adding words into a set that avoids repetition
      }
  }
  return words;
}

// buildIndex accepts a filename as argument to check if the same file is open,
// and a map that has each word from the set returned by gatherTokens and a
// value that is the set of URLs whose text has the word
int buildIndex(string filename, map<string, set<string>> &index) {
  ifstream inFS;
  
  // opening a file
  inFS.open(filename);
  int urlCount = 0;
  string hurr;
  // contents of the file
  //
  string BodyText;
  set<string> StringToken;
  // gets the set from gatherTokens
  // inFS >> hurr;
  int i = 1;
  if (inFS.is_open()) {
    while (getline(inFS, hurr, '\n')) {
      // separating each line such that even number line contains the body text
      // of odd numbered lines that are the URLs
      {
        if (i % 2 == 0) {
          //
          inFS >> BodyText;
          cout<<BodyText<<endl;
          // retrives the text
        } else {
          StringToken = gatherTokens(BodyText);
          // iterating over StringToken set
          for (auto itr : StringToken) {
            index[itr].insert(hurr);
            // adds URLs as the value of map index
            urlCount++;
          }
        }
        i++;
      }
    }
  }
    for (auto it : index){
      cout<<it.first<<", "<<endl;
    }
  // else {
  //   cout<<"File not found"<<endl;
  // }
  return urlCount;
}



// findQueryMatches goes through the string if there's a + or no symbol as each word's first character, there is a union, otherwise intersection
set<string> findQueryMatches(map<string, set<string>> &index, string sentence) {
  set<string> result1;
  // set of words that have + as their first character
  set<string> result2;
  // set of words that have - as their first character
  set<string> result3;
  // set of words that have neither + nor - as their first character
  set<string> result;
  // final result after union and intersection as desired

  
  

  string word,modified_word;
  // word is string before removing + or -
  // modified_word is string after removing + or -
  stringstream str_strm(sentence);
  map<string, set<string>>::const_iterator it;

  while (getline(str_strm, word, ' ')) {
    if (word[0] == '+') {
      modified_word = word.substr(1, word.size() - 1);
// removing +
      for (it = index.begin(); it != index.end(); it++) {
        if (it->first == modified_word) {
          for (auto itr : it->second) {
            result1.insert(itr);
            // iterating through each index to see if there is a matching string in the key of map index and adds its value to the result1 set
          }
        }
      }
    }

    if (word[0] == '-') {
      // removing +
      word = word.substr(1, modified_word.size() - 1);
      for (it = index.begin(); it != index.end(); it++) {
        if (it->first == word) {
          for (auto itr : it->second) {
            result2.insert(itr);
            //  iterating through each index to see if there is a matching string in the key of map index and adds its value to the result2 set
          }
        }
      }

    }

    else {
      for (it = index.begin(); it != index.end(); it++) {
        if (it->first == modified_word) {
          for (auto itr : it->second) {
            result3.insert(itr);
           // iterating through each index to see if there is a matching string in the key of map index and adds its value to the result1 set
          }
        }
      }
    }
   
     if (word[0]=='-'){
    set_intersection(result1.begin(), result1.end(), result2.begin(), result2.end(), 
      inserter(result, result.begin()));
       // intersection in case there is a - as first character of the word
       }
       else {
    set_union(result1.begin(), result1.end(),result2.begin(), result2.end(),  
                 inserter(result, end(result)));  
     }
    // union in case there is a + as first character of the word or if there are no symbols
  
  return result;
}
  }
// Using the functions above to retrieve matching pages
void searchEngine(string filename) {
  map<string, set<string>> index;
  string sentence;
  
  int pageCount=buildIndex(filename,index);
  
cout << "Stand by while building index..." << endl;
  
  cout << "Indexed " << pageCount << " pages containing " << index.size() << " unique terms" << endl;
  
  
  set<string> matches;
  set<string>::iterator iter = matches.begin();
  while (true) {
    
    cout << "Enter query sentence(press enter to quit): " << endl;

    getline(cin, sentence);

    
    if (sentence == " ") {
      break;
    }
    matches = findQueryMatches(index, sentence);
        cout << "Found " << matches.size() << "  matching pages" << endl;
        while (iter != matches.end()){
          
          cout << (*iter) << endl;
          iter++;
        }
      
  }
}
