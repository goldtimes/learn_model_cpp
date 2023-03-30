#include <iostream>
using namespace std;

template <typename T, typename U> void perfectForward(T &&t, U &Func) {
  cout << t << "\tforwarded..." << endl;
  Func(forward<T>(t));
}

void runCode(double &&m) { cout << "code" << endl; };
void runHome(double &&h) { cout << "home" << endl; };
void runStation(double &&s) { cout << "station" << endl; };

int main() {
  perfectForward(1.5, runHome);
  perfectForward(8, runCode);
  perfectForward(1.5, runStation);

  return 0;
}