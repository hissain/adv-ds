#include <stdio.h>
#define SZ 100
#define SIZE 100


int tree[3*SIZE];
int lz[3 * SIZE];
int data[SIZE] = {1, 3, 5, 2, 4, 7, 10};
int size = 7;

void bld(int ind, int i, int j){

	if (i == j){
		tree[ind] = data[i];
		return;
	}

	int m = i + (j - i) / 2;
	int l = 2 * ind + 1;
	int r = 2 * ind + 2;
	
	bld(l, i, m);
	bld(r, m + 1, j);
	tree[ind] = tree[l] + tree[r];
}

void upd1(int ind, int p, int i, int j, int v){

	if (p < i || p > j)
		return;

	if (i == j && i == p){

		data[p] = v;
		tree[ind] = v;
		return;
	}

	int m = i + (j - i) / 2;
	int l = 2 * ind + 1;
	int r = 2 * ind + 2;
	upd1(l, p, i, m, v);
	upd1(r, p, m + 1, j, v);

	tree[ind] = tree[l] + tree[r];
}

void upd2(int ind, int i, int j, int p, int q, int v){

	int l = 2 * ind + 1;
	int r = 2 * ind + 2;
	int m = i + (j - i) / 2;

	if (lz[ind]){

		tree[ind] += (j - i + 1) * lz[ind];

		if (i != j){
			lz[l] += lz[ind];
			lz[r] += lz[ind];
		}
		lz[ind] = 0;
	}
	

	if (i > q || j < p)
		return;

	if (i >= p && j <= q){

		lz[ind] += v;
		return;
	}

	upd2(l, i, m, p, q, v);
	upd2(l, m + 1, j, p, q, v);
	tree[ind] = tree[l] + tree[r];
}

int qry2(int ind, int i, int j, int p, int q){

	int l = 2 * ind + 1;
	int r = 2 * ind + 2;
	int m = i + (j - i) / 2;

	if (lz[ind]){

		tree[ind] += (j - i + 1)*lz[ind];

		if (i != j){

			lz[l] += lz[ind];
			lz[r] += lz[ind];
		}
		lz[ind] = 0;
	}
	

	if (i > q || j < p)
		return 0;

	if (i >= p && j <= q){

		return tree[ind];
	}

	return qry2(l, i, m, p, q) + qry2(r, m + 1, j, p, q);
}

int qry1(int ind, int i, int j, int l, int r){

	if (i > r || j < l)
		return 0;

	if (i >= l && j <= r)
		return tree[ind];

	int m = i + (j - i) / 2;

	return qry1(2 * ind + 1, i, m, l, r) + qry1(2 * ind + 2, m + 1, j, l, r);
}


void print(){

	for (register int i = 0; i < 3*size; i++)
		printf("%d ", tree[i]);
	printf("\n");
}

int main(){

	bld(0, 0, size - 1);

	printf("%d\n", qry1(0, 0, size - 1, 0, size - 1));

	upd1(0, 1, 0, size - 1, 4);

	printf("%d\n", qry1(0, 0, size - 1, 0, size - 1));

	upd2(0, 0, size - 1, 0, 2, 10);

	printf("%d\n", qry2(0, 0, size - 1, 0, size - 1));

	return 0;
}
