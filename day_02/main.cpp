/**
 * Rock|Paper|Scisor
 * ---
 * part1: 14264
 * part2: 12382
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// string dataSource = "simple.txt";
string dataSource = "input.txt";
int DEBUG = 1;

/**
 * fetch data as pair vector
*/
vector< pair <char, char> > fetchData(string file){
  vector< pair <char, char> > stack;
  pair<char, char> line;
  ifstream datas;
  datas.open(file);
  while (datas >> line.first >> line.second) {
    stack.push_back(line);
  }
  datas.close();

  return stack;
}

// part1 - score of one line
int getRoundScore(int opponent, int hero){
  int score = hero + 1;
  
  // draw
  if(opponent == hero){
    return score + 3;
  }
  // success (maginc see top comments)
  if((hero - opponent + 3) % 3 == 1){
    return score + 6;
  }
  // fail
  return score;
}

/**
 * part2 - score of one line - by logic
 *  - X lose +0 | Y draw +3 | Z win +6
 * -------------------------
 *  rock   0 A X
 *  paper  1 B Y
 *  scisor 2 C Z
*/
int LOOSE = 0;
int DRAW = 1;
int WIN = 2;
int getRoundScoreByLogic(int opponent, int hero){
  int score = 1; // start 1 not 0
  
  // draw
  if(hero == LOOSE){
    return 0 + score + ((opponent - 1 + 3) % 3);
  }
  // draw
  if(hero == DRAW){
    return 3 + score + opponent; // + opponent;
  }
  // success
  return 6 + score + ((opponent + 1) % 3);
}

/** loop and compute total score
 *  - X lose | Y draw | Z
 */
pair<int, int> computeScores(vector< pair <char, char> > data){
  int opponent = 0;
  int hero = 0;
  int match_a = 0;
  int match_b = 0;
  int part1 = 0;
  int part2 = 0;
  for (int i=0; i<data.size(); i++) {
    // if 'A'= any int; then 'C'-'A' = any int + 2 ¯\_(ツ)_/¯
    opponent  = data[i].first - 'A';
    hero      = data[i].second - 'X';

    match_a = getRoundScore(opponent, hero);
    match_b = getRoundScoreByLogic(opponent, hero);
    part1 += match_a;
    part2 += match_b;

    if(DEBUG){
      std::cout << "..." + to_string(opponent) << "|" + to_string(hero);
      std::cout << " = " + to_string(match_a)<< "|" + to_string(match_b) << endl;
    }
  }

  return make_pair(part1, part2);
}

int main() {
  vector< pair <char, char> > data = fetchData(dataSource);
  pair<int, int> scores = computeScores(data);
  
  std::cout << "part1: " + to_string(scores.first) << endl; // 14264
  std::cout << "part2: " + to_string(scores.second) << endl; // 12382
}


/**
firsts reflexions :

         L R
rock   1 A X
paper  2 B Y
scisor 3 C Z

a>c to 1-3 ? || x-z to 1-3 ?
int(char) return asci int eg `int('A') = 96 (maj)
si A = 96, B = 97...
int(L) = pair1 - 'A' + 1
int(R) = pair2 - 'X' + 1

L == R         => draw  3 + R
R - (L%3) == 1 => win   6 + R
else           => loose 0 + R
*/