
#include <iostream>

int polyMulti(long a[], long b[], int polyDegree, long returnArr[]) {

  if (polyDegree == 0) {
     returnArr[0] = a[0] * b[0];
     return 0;
  }

  if (polyDegree == 1) {
     returnArr[0] = a[0] * b[0];
     returnArr[1] = a[0] * b[1] + a[1] * b[0];
     returnArr[2] = a[1] * b[1];
     return 0;
  }

  int p2Degree = polyDegree/2;
  int p1Degree = polyDegree - p2Degree -1;

  long a0[p1Degree+1];
  long b0[p1Degree+1];
  long a1[p2Degree+1];
  long b1[p2Degree+1];

  for (int i = 0; i <= p1Degree; i++) {
    a0[i] = a[i];
    b0[i] = b[i];
  }

  for (int i = 0; i <= p2Degree; i++) {
    a1[i] = a[p1Degree + 1 + i];
    b1[i] = b[p1Degree + 1 + i];
  }

  long asum[p2Degree+1];
  long bsum[p2Degree+1];

  for (int i = 0; i <= p1Degree; i++) {
     asum[i] = a0[i] + a1[i];
     bsum[i] = b0[i] + b1[i];
  }

  if (p1Degree < p2Degree) {
     asum[p2Degree] = a1[p2Degree];
     bsum[p2Degree] = b1[p2Degree];
  }

  long ret1[polyDegree+1] = { 0 };
  long ret2[polyDegree+1] = { 0 };
  long ret3[polyDegree+1] = { 0 };

  polyMulti(a0, b0, p1Degree, ret1);
  polyMulti(asum, bsum, p2Degree, ret2);
  polyMulti(a1, b1, p2Degree, ret3);

  for (int i = 0; i <= polyDegree; i++) {
     ret2[i] -= ret1[i] + ret3[i];
  }

  /*std::cout << "A[]";
  for (int i = 0; i <= polyDegree; i++) {
     std::cout << " " << a[i];
  }

  std::cout << "\nB[]";
  for (int i = 0; i <= polyDegree; i++) {
     std::cout << " " << b[i];
  }
  std::cout << "\n" << "PolyDegree: " << polyDegree << "\n";


  std::cout << "ret1 ret2 ret3\n";
  for (int i = 0; i <= polyDegree; i++) {
     std::cout << ret1[i] << " " << ret2[i] << " " << ret3[i] << "\n";
  }*/

  for (int i = 0; i <= polyDegree; i++) {
     returnArr[i] += ret1[i];
     returnArr[i+(polyDegree+1)/2] += ret2[i];
     returnArr[((polyDegree+1)/2)*2+i] += ret3[i];
  }
  /*std::cout << "Poly: ";

  for (int i = 0; i < polyDegree*2+1; i++) {
     std::cout << returnArr[i] << "x^" << i << " ";
  }
  std::cout << "\n";
  std::cout << "===============\n";*/

  return 2;
}

int main() {
  int polyDegree;

  std::cin >> polyDegree;

  long returnArr[polyDegree*2+1] = { 0 };
  long a[polyDegree+1];
  long b[polyDegree+1];

  for (int i = 0; i <= polyDegree; i++) {
    std::cin >> a[i];
  }
  for (int i = 0; i <= polyDegree; i++) {
    std::cin >> b[i];
  }

  polyMulti(a, b, polyDegree, returnArr);

  std::cout << returnArr[0];
  for (int i = 1; i < polyDegree*2 + 1 ; i++) {
     std::cout << " " << returnArr[i];
  }
  std::cout << "\n";
  return 0;
}

