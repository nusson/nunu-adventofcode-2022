/**
 * Day 03 - https://adventofcode.com/2022/day/3
 * ---
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// const string dataSource = "simple.txt";
const string dataSource = "input.txt";
const int DEBUG = 0;

vector<char> to_chars(string s){
  vector<char> list;
  for (int i=0; i<s.length(); i++){
    list.push_back(s[i]);
  }
  return list;
}

/**
 * fetch data
*/
vector<string> fetchData(string file){
  vector<string> stack;
  string line;
  ifstream datas;

  datas.open(file);
  while (datas >> line) 
    stack.push_back( line );
  datas.close();

  return stack;
}

// return int value of a char
int charToInt(char payload) {
  int score = payload - 'a' + 1;
  if(score < 1){
    score = payload - 'A' + 1 + 26;
  }
  return score;
}


/* get intersection of two vector
(easy because 1 match only) */
int getIntersection(vector<char> a, vector<char> b){
    char matchItem;// = NULL;
    char target;
    int n = a.size();

    // for each 1st stack
    for (int i=0; i<n && !matchItem; i++){
      target = a[i];
      // for each 2nd - if a match return it
      for (int j=0; j<n && !matchItem; j++){
        if(b[j] == target){
          matchItem = target;
        };
      }
    }
    if(DEBUG) std::cout << matchItem << " ";

    // return int val of the match
    return charToInt(matchItem);
}

/* verbeux... get common char in 3 vectors */
int getCommonPerGroupOfThree(vector<char> a, vector<char> b, vector<char> c){
    char matchItem;// = NULL;
    char target;

    // for each 1st stack
    for (int i=0; i<a.size() && !matchItem; i++){
      target = a[i];
      // for each 2nd - if a match return it
      for (int j=0; j<b.size() && !matchItem; j++){
        if(b[j] == target){
          // for each 2nd - if a match return it
          for (int k=0; k<c.size() && !matchItem; k++){
            if(c[k] == target){
              matchItem = target;
            };
          }
        }
      }
    }
    if(DEBUG) std::cout << matchItem << " : ";

    // return int val of the match
    return charToInt(matchItem);
}

/* verbeux... split line in pairs */
vector<pair<vector<char>, vector<char> > > splitLinesInPairs(vector<string> lines){
  vector<pair<vector<char>, vector<char> > > stack;
  int n = 0;
  string line;

  for (int i=0; i<lines.size(); i++){
    line = lines[i];
    n = line.length() / 2;
    vector<char> a;
    vector<char> b;
    for (int i=0; i<n; i++){
      a.push_back(line[i]);
      b.push_back(line[(i+n)]);
    }
    stack.push_back( make_pair(a, b) );
  }
  return stack;
}

/* find char not uniq in each pair */
int part_one(vector<string> data){
  vector<pair<vector<char>, vector<char> > > splited = splitLinesInPairs(data);

  int total;
  for (int i=0; i<splited.size(); i++){
    int score = getIntersection(splited[i].first, splited[i].second);
    total += score;
    if(DEBUG) std::cout << " " << to_string(score) << endl;
  }
  return total;
}

/* find common char per group of three stack */
int part_two(vector<string> data){
  int total = 0;
  for (int i=0; i<data.size() - 2; i++){
    if(i%3 == 0){
      int score = getCommonPerGroupOfThree(
        to_chars(data[i]),
        to_chars(data[i + 1]),
        to_chars(data[i + 2])
      );
      // std::cout << data[i] << to_string(score) << endl;
      total += score;
    }
  }
  return total;
}

int main() {
  vector<string> data = fetchData(dataSource);
  
  int part1 = part_one(data);
  std::cout << "part1: " << to_string(part1) << endl; // 8515

  int part2 = part_two(data);
  std::cout << "part2: " << to_string(part2) << endl; // 2434
}