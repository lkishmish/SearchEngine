#include <iostream>
#include <string>
using namespace std;
string cleanToken(string token) {

  string u = "";
  for (int i = 0; i < token.length(); i++) {
if (!ispunct(token[i])) {
    if (isalpha(token[i])) {
      
        u += token[i];
      }
    } else {
     
    }
  }
  return u; // TODO:  update this.
}