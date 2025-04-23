#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include <stack>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool findNextWord(std::string& in, std::string floating, int p, std::set<std::string>& pwords,  const std::set<std::string>& dict, const std::string& original, int spaceleft);
bool canbeword(std::string& in, std::string& floating, int p, const std::set<std::string>& dict, const std::string& original, int spaceleft, bool& found);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    stack<char> removed;
    int spaceleft = 0;
    for(int i = 0; i < (int)in.size(); i++){
      if(in[i] == '-'){
        spaceleft+=1;
      }
    }
    std::string floatingc = floating;
    std::string myw = in;
    std::set<std::string> pwords;
    int p = 0;
    findNextWord(myw, floatingc, p, pwords, dict, in, spaceleft);
    return pwords;

}

// Define any helper functions here
bool findNextWord(std::string& in, std::string floating, int p, std::set<std::string>& pwords,  const std::set<std::string>& dict, const std::string& original, int spaceleft){
    if((int)in.size() < 1){
      return false;
    }
    //cout<<p<<endl;
    //cout<<in<<endl;
    bool found = false;
    if(in[p] == '-'){
      spaceleft -= 1;
      if(spaceleft > (int)floating.size()-1){
        for(in[p] = 'a'; in[p] <= 'z'; ++in[p]){
          if(canbeword(in, floating, p, dict, original, spaceleft, found)){
            if(p < (int)in.size() - 1){
              findNextWord(in, floating, p+1, pwords, dict, original, spaceleft);
            }else{
              pwords.insert(in);
            }
          }
          if(found){
            floating += in[p];
            found = false;
          }
        }
      }else{
        for(int i = 0; i < (int)floating.size(); i++){
          in[p] = floating[i];
          if(canbeword(in, floating, p, dict, original, spaceleft, found)){
            if(p < (int)in.size() - 1){
              findNextWord(in, floating, p+1, pwords, dict, original, spaceleft);
            }else{
              pwords.insert(in);
            }
          }
          if(found){
            floating += in[p];
            found = false;
          }
        }
      }
      in[p] = '-';
      return false;
    }else{
      if(p < (int)in.size() - 1){
        return findNextWord(in, floating, p+1, pwords, dict, original, spaceleft);
      }else{
        if(dict.find(in) != dict.end()){
          pwords.insert(in);
        }
        return false;
      }
    }
}

bool canbeword(std::string& in, std::string& floating, int p, const std::set<std::string>& dict, const std::string& original, int spaceleft, bool& found){
    //cout<< in<<" "<<p<< endl;
    if(original[p]=='-'){
      for(int i = 0; i < (int)floating.size(); i++){
        if(in[p] == floating[i]){
          //cout<<"found "<<floating[i] << " " << in<< endl;
          floating.erase(floating.begin()+i);
          found = true;
          break;
        }
      }
    }
    if((spaceleft - (int)floating.size()) >= 0){
      //cout<<"cbw"<<endl;
      if((int)in.size()-1 == p){
        if(dict.find(in) != dict.end()){
          return true;
        }
        return false;
      }
      return true;
    }
    return false;
}