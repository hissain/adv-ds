#include <stdio.h>

int A[4][4] = {
	{ 1, 1, 1, 1 },
	{ 1, 1, 1, 1 },
	{ 1, 1, 1, 1 },
	{ 1, 1, 1, 1 }
};

int sum(int i1, int j1, int i2, int j2){

	if (i1 > i2 || j1 > j2)
		return 0;

	if (i1 == i2 && j1 == j2)
		return A[i1][j1];

	int mi = i1 + (i2 - i1) / 2;
	int mj = j1 + (j2 - j1) / 2;

	int s = 0;

	s += sum(i1, j1, mi, mj);		      // upper left quad
	s += sum(i1, mj + 1, mi, j2);		  // upper right quad
	s += sum(mi + 1, mj + 1, i2, j2);	  // lower right quad
	s += sum(mi + 1, j1, i2, mj);		  // lower left quad

	return s;
}

int main(){
	int s = sum(0, 0, 3, 3);
	return 0;
}
