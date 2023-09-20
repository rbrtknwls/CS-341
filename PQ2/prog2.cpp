#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>

int t1, t2, t3, t4, n, depth;

std::queue<std::tuple<int, int, int, int, int>> valsToCheck;
std::vector<std::tuple<int, int, int, int, int>> savedVals;
std::stack<std::tuple<int, int, int, int, int>> printableValues;


bool visited[81][81][81][81] = { };


void rec(int s1, int s2, int s3, int s4, int p) {

   // std::cout << s1 << " " << s2 << " " << s3 << " " << s4 << " Parent: " << p << std::endl;
   if (visited[s1][s2][s3][s4] == 0) {
      valsToCheck.push({s1, s2, s3, s4, p});
      visited[s1][s2][s3][s4] = 1;
   }

}

void moveLeft(int s1, int s2, int s3, int s4, int p) {

   if (s1-1 > 0) {
      rec(s1-1, s2, s3, s4, p);
   }

   if (s1 < s2-1) {
      rec(s1, s2-1, s3, s4, p);
   }

   if (s2 < s3-1) {
      rec(s1, s2, s3-1, s4, p);
   }

   if (s3 < s4-1) {
      rec(s1, s2, s3, s4-1, p);
   }


}

void moveRight(int s1, int s2, int s3, int s4, int p) {

   if (s2 > s1+1) {
      rec(s1+1, s2, s3, s4, p);
   }

   if (s3 > s2+1) {
      rec(s1, s2+1, s3, s4, p);
   }

   if (s4 > s3+1) {
      rec(s1, s2, s3+1, s4, p);
   }

   if (s4+1 <= n) {
      rec(s1, s2, s3, s4+1, p);
   }


}

void flip (int s1, int s2, int s3, int s4, int p) {

   int s1tos2 = s2*2 - s1;
   int s2tos1 = s1*2 - s2;
   int s2tos3 = s3*2 - s2;

   int s3tos2 = s2*2 - s3;
   int s3tos4 = s4*2 - s3;
   int s4tos3 = s3*2 - s4;

   if (s3 > s1tos2) {
      // std::cout << "HERE " << s1tos2 << " " << s3 << std::endl;
      rec(s2, s1tos2, s3, s4, p);
   }

   if (s2tos1 > 0) {
      rec(s2tos1, s1, s3, s4, p);
   }

   if (s4 > s2tos3) {
      // std::cout << "HERE " << s1tos2 << " " << s4 << " | " << s2 << std::endl;
      rec(s1, s3, s2tos3, s4, p);
   }


   if (s1 < s3tos2) {
      rec(s1, s3tos2, s2, s4, p);
   }

   if (s3tos4 <= n) {
      rec(s1, s2, s4, s3tos4, p);
   }

   if (s4tos3 > s2) {
      rec(s1, s2, s4tos3, s3, p);
   }



}

void test(int s1, int s2, int s3, int s4) {



   valsToCheck.push({s1, s2, s3, s4, -1});

   int parentLoc = 0;
   while (!valsToCheck.empty()) {
      std::tuple<int, int, int, int, int> curr = valsToCheck.front();
      valsToCheck.pop();
      s1 = std::get<0>(curr);
      s2 = std::get<1>(curr);
      s3 = std::get<2>(curr);
      s4 = std::get<3>(curr);

      savedVals.push_back(curr);

      if (s1 == t1 && s2 == t2 && s3 == t3 && s4 == t4) {
         int p = std::get<4>(curr);

         printableValues.push(curr);

         while (p != -1) {
            depth++;
            std::tuple<int, int, int, int, int> curr = savedVals[p];
            printableValues.push(curr);
            p = std::get<4>(curr);
         }

         break;
      }

      moveLeft(s1, s2, s3, s4, parentLoc);
      moveRight(s1, s2, s3, s4, parentLoc);
      flip(s1, s2, s3, s4, parentLoc);

      parentLoc++;

   }

}

int main() {
  int s1, s2, s3, s4;

  std::cin >> n >> s1 >> s2 >> s3 >> s4;
  std::cin >> t1 >> t2 >> t3 >> t4;

  test(s1, s2, s3, s4);

  std::cout << depth << std::endl;


  while (!printableValues.empty()) {

      std::tuple<int, int, int, int, int> curr = printableValues.top();
      printableValues.pop();
      s1 = std::get<0>(curr);
      s2 = std::get<1>(curr);
      s3 = std::get<2>(curr);
      s4 = std::get<3>(curr);

      std::cout << s1 << " " << s2 << " " << s3 << " " << s4 << std::endl;


  }
  return 0;
}
