#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>
using namespace std;

const double PIE = 3.14159265359;
const double EPS = 10e-10;
const int MAX_COUNT = 1000;

//行列初期化
void matrix_init(double *a, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i * n + j] = rand() % 20;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[j * n + i] = a[i * n + j];
		}
	}

	for (int i = 0; i < n; i++) {
		a[i * n + i] = rand() % 20 + 1;
	}
}

//表示
void show(double *a, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%lf ", a[i * n + j]);
		}
		printf("\n");
	}
	printf("\n");
}

//回転行列の操作
void matirix_kaiten(double *a, int n)
{

	double max = 0;
	int y = 0, x = 0;

	int count = 0;
	while (count <= MAX_COUNT) {
		max = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				double max_temp = fabs(a[i * n + j]);
				if (max < max_temp) {
					max = max_temp;
					y = i;
					x = j;
				}
			}
		}

		if (max <= EPS) {
			break;
		}
		else {
			double ayx = a[y * n + x];
			double ayy = a[y * n + y];
			double axx = a[x * n + x];

			double p, q, ta, s2, c2, co, si, si2, co2, sico;

			p = (ayy - axx) / 2;
		    q = ayx;
			if (fabs(p) < fabs(q)) {
				ta = p / q;
				s2 = 1 / sqrt(1 + ta * ta);
				if (q < 0) {
					s2 = -s2;
				}
				c2 = s2 * ta;
			} else {
				ta = q / p;
				c2 = 1 / sqrt(1 + ta * ta);
				if (p < 0) {
					c2 = -c2;
				}
				s2 = c2 * ta;
			}

			if (c2 > 0) {
				co = sqrt((1 + c2) / 2);
				si = s2 / (2 * co);
			}
			else {
				si = sqrt((1 - c2) / 2);
				co = s2 / (2 * si);
			}
			
			si2 = si * si;
			co2 = co * co;
			sico = si * co;

			a[y * n + y] = ayy * co2 + axx * si2 + 2.0 * ayx * sico;
			a[x * n + x] = ayy * si2 + axx * co2 - 2.0 * ayx * sico;
			a[y * n + x] = 0;
			a[x * n + y] = 0;

			for (int i = 0; i < n; i++) {
				if (i != x && i != y) {
					double aiy = a[i * n + y];
					double aix = a[i * n + x];
					a[i * n + y] = aiy * co + aix* si;
					a[y * n + i] = a[i * n + y];
					a[i * n + x] = -aiy * si + aix * co;
					a[x * n + i] = a[i * n + x];
				}
			}
			count++;
		}
	}
}

int main()
{
	srand((unsigned int)time(NULL));

	int n = 4;

	double *A = new double[n * n];

	matrix_init(A, n);

	show(A, n);

	matirix_kaiten(A, n);

	show(A, n);

	/*
	cout << "固有値は以下です。" << endl;
	for (int i = 0; i < n; i++) {
		printf("%lf\n", A[i * n + i]);
	}
	*/
	delete[] A;

	return 0;
}