#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>
using namespace std;

const double PIE = 3.14159265359;
const double EPS = 10e-12;
const int MAX_COUNT = 100;

//s—ñ‰Šú‰»
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

//•\¦
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

//‰ñ“]s—ñ‚Ì‘€ì
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
			double pi = 4.0 * atan(1.0);
			double kaku_value = 0;
			double kaku = 0;
			double ayx = a[y * n + x];
			double ayy = a[y * n + y];
			double axx = a[x * n + x];
			if (fabs(ayy - axx) <= EPS) {
				kaku = 0.25 * pi * ayx / fabs(ayx);
			}
			else {
				kaku = 0.5 * atan(2.0 * ayx / (ayy - axx));
			}

			double co = cos(kaku);
			double si = sin(kaku);
			double co2 = co * co;
			double si2 = si * si;
			double sico = si * co;

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
					a[i * n + x] = aiy * co - aix * si;
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

	int n = 3;

	double *A = new double[n * n];

	matrix_init(A, n);

	show(A, n);

	matirix_kaiten(A, n);

	show(A, n);

	//delete[] A;

	return 0;
}