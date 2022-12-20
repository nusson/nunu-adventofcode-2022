#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int topN = 3;
// string dataSource = "simple.txt";
string dataSource = "input.txt";

/**
 * fetch elves calories (txt file)
 * return total calory per elve in a vector
*/
vector<int> fetchCaloriesPerElf(string file){
  int calories = 0;
  vector<int> stack;

  string line;
  ifstream datas;
  datas.open(file);

  while (getline(datas, line)) {
      // std::cout << ' ' + line;
    // if empty - new line - store total elve calories in vector
    if (line == "") {
      stack.push_back(calories);
      // std::cout << calories << endl;
      calories = 0;
    }
    else{
      // just stack calories - same elve
      calories += stoi(line);
    }
  }
  datas.close();

  return stack;
}

int main() {
  // total calories of N elves
  int total = 0;

  vector<int> calories = fetchCaloriesPerElf(dataSource);
  
  // sort bigger to lower
  sort (calories.begin(), calories.end(), greater<int>());

  // ask howmuch elves
  std::cout << "> top : ";
  string s;
  std::cin >> s;
  topN = stoi(s);

  // combine firts N
  for (vector<int>::iterator it=calories.begin(); it!=calories.begin()+topN; ++it){
    std::cout << *it << ' ';
    total += *it;
  }

  // result
  std::cout << endl << "> total : ";
  std::cout << total << endl;
}