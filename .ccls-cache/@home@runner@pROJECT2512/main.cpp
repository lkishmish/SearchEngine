#include "search.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main() {
  //  string sentence= "..onee...";
  // cout<<cleanToken(sentence)<<endl;

 
  string filename;
  map<string, set<string>> index;
  cout<<"Enter the name of the file: "<<endl;
  cin>>filename;
  searchEngine(filename);
  //
  // cout << buildIndex(filename, index) << endl;
  // for (map<string, set<string>>::const_iterator it = index.begin(){
  //      it != index.end(); ++it) {
  //   std::cout << it->first << "\n";
  // }
  //   }
  // set<string> result = findQueryMatches(index, "EGGS");
  
  // for (auto it = result.begin(); it != result.end(); ++it){
  //   cout << ' ' << *it;
  //   }
  return 0;
}
