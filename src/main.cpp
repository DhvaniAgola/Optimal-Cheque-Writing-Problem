//============================================================================
// Name        : ALGORITHMS_6651CPP_PA2v4.cpp
// Author      : Dh
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <climits>
using namespace std;

static map<int, int> mapCost;
int makeTable(int A, int N, int B) {
//	int dp[N][A * N + 1];
	int arrPrev[B + 1];
	for (int j = 0; j < (B + 1); j++)
		arrPrev[j] = -1;

	int k = 0;
	int a = A * (k + 1);
	int b = B + A * (k + 1);
//	for (int i = 0; i < N; i++)
//		dp[i][0] = 0;
	for (int j = a; j <= b && j <= 10000; j++) {
		arrPrev[j - a] = mapCost[j];
	}
	int S = INT_MAX;
	int arrCur[B + 1];

	int want_to_pay_minimum;
	for (int i = 1; i < N; i++) {
		k++;
		for (int j = 0; j < (B + 1); j++)
			arrCur[j] = -1;
		want_to_pay_minimum = A * (k + 1);
		b = B + A * (k + 1);
		for (int j = want_to_pay_minimum; j <= (want_to_pay_minimum + B); j++) {
			S = INT_MAX;
			if (b >= j) {
				for (int m = A * k; m <= (A * k + B); m++) {
					if ((j - m) <= 10000) {
						int temp = arrPrev[m - (A * k)] + mapCost[j - m];
						if (temp < S)
							S = temp;
					}
				}
				arrCur[j - (A * (k + 1))] = S;
			} else
				break;
		}
		for (int j = 0; j < (B + 1); j++)
			arrPrev[j] = arrCur[j];
	}
	return arrPrev[0];
}
int main(int c, char* args[]) {
	fstream cost(args[3]);
	ofstream outp(args[2]);
	int amt, cst;
	for (int i = 0; i <= 10000; i++) {
		cost >> amt >> cst;
		mapCost[amt] = cst;
	}
	cost.close();
	int N, A, B;
	fstream inp(args[1]);
	int n;
	inp >> n;
	for (int i = 0; i < n; i++) {
		inp >> N >> A >> B;
		int ans = 2;
		ans = makeTable(A, N, B);
		outp << ans;
		if (i != (n - 1))
			outp << "\n";
	}
	return 0;
}

