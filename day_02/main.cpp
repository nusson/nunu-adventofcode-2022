/**
 * Rock|Paper|Scisor
 * ---
 *  part1: 14264
 *  part2: 12382
 * ---
 *  rock   0 A X
 *  paper  1 B Y
 *  scisor 2 C Z
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// const string dataSource = "simple.txt";
const string dataSource = "input.txt";
const int DEBUG = 1;

/* success modifiers */
const int LOOSE = 0;
const int DRAW  = 3;
const int WIN   = 6;

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

/** part1 - score of one match */
int getMatchScore_part1(int opponent, int hero){
  int score = hero + 1; // 1-3 but get 0-2 so +1
  
  // draw
  if(opponent == hero) return score + DRAW;
  // success (maginc see top comments)
  if((hero - opponent + 3) % 3 == 1) return score + WIN;
  // fail
  return score + LOOSE;
}


/** part2 - score of one match
 * but hero adjust move by faith : 
 * X lose +0 | Y draw +3 | Z win +6
 */
const int CONDITION_LOOSE = 0;
const int CONDITION_DRAW  = 1;
const int CONDITION_WIN   = 2;
int getMatchScore_part2(int opponent, int hero){
  int score = 1; // 1-3 but get 0-2 so +1
  
  switch (hero){
    case CONDITION_LOOSE:
      return LOOSE + score + ((opponent - 1 + 3) % 3);
    case CONDITION_DRAW:
      return DRAW + score + opponent;
    default:
      return WIN + score + ((opponent + 1) % 3);
  }
}

/** loop and compute total score
 *  - X lose | Y draw | Z
 */
pair<int/*part1*/, int/*part2*/> computeScores(vector< pair <char/*opponent*/, char/*hero*/> > data){
  int opponent = 0;
  int hero    = 0;

  // use pair for part1 / part2
  pair<int, int> match; // one round (explicit to debug)
  pair<int, int> total; // increment
  
  for (int i=0; i<data.size(); i++) {
    // if 'A'= any int; then 'C'-'A' = any int + 2 ¯\_(ツ)_/¯
    opponent  = data[i].first - 'A';
    hero      = data[i].second - 'X';

    // get round (match) result following each part strategy
    match = make_pair(
      getMatchScore_part1(opponent, hero),
      getMatchScore_part2(opponent, hero)
    );

    // increment scores for each round (match)
    total = make_pair(
      total.first   + match.first,
      total.second  + match.second
    );

    if(DEBUG){
      std::cout << "..." + to_string(opponent) << "|" + to_string(hero);
      std::cout << " = " + to_string(match.first)<< "|" + to_string(match.second) << endl;
    }
  }

  return total;
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