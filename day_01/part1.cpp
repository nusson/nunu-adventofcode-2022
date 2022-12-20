#include <iostream>
#include <fstream>

using namespace std;

int main() {
  int elve = 0;
  int calories = 0;

  // temp shits to compute stuff
  int current = 0;
  int currentIndex = 0;
  int number = 0;

  string line;

  ifstream datas;
  datas.open("input.txt");
  
  while (getline(datas, line)) {

    // if empty - new line - was it max one ?
    if (line == "") {
      if (current >= calories) {
        calories = current;
        elve = currentIndex;
      }
      current = 0;
      currentIndex += 1;
    }
    // just stack numbers
    else{
      number = stoi(line);
      current += number;
    }
  }
  datas.close();

  std::cout << elve << std::endl;
  std::cout << calories << std::endl;
}