#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
using namespace std;
ofstream fout("res.txt");

void show_matrix(int n, float A[4][4]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(14) << setprecision(8) << A[i][j] << " ";
			fout << setw(14) << setprecision(8) << A[i][j] << " ";
		}
		cout << endl;
		fout << endl;
	}
}
//умножает a на m справа, результат хранится в а
void product(int N, float a[4][4], float m[4][4]) {
	float** c = new float*[N];
	for (int i = 0; i < N; i++)
		c[i] = new float[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			c[i][j] = 0;
			for (int k = 0; k < N; k++)
				c[i][j] += a[i][k] * m[k][j];
		}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			a[i][j] = c[i][j];
		}
}
//умножает a на m_1 слева, результат хранится в а
void product2(int N, float a[4][4], float m_1[4][4]) {
	float** c = new float*[N];
	for (int i = 0; i < N; i++)
		c[i] = new float[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			c[i][j] = 0;
			for (int k = 0; k < N; k++)
				c[i][j] += m_1[i][k] * a[k][j] ;
		}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			a[i][j] = c[i][j];
		}
}
void set_matrix(int n, float **A) {
	srand(time(0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = -100 + rand() % 200; 
		}
	}
}

int main() {
	int n = 4;
	float** A = new float*[n];
	for (int i = 0; i < n; i++)
		A[i] = new float[n];
	float B[4][4] = { {2, 2, -1, 1}, {3, 3, 0, 0},{1, 3, 4, 1},{3, 0, 3, 3} };
	show_matrix(4, B);
	int sp = 0;
	for (int i = 0; i < n; i++) sp += B[i][i];
	cout << "SP of matrix = " << sp << endl;
	fout << "SP of matrix = " << sp << endl;
	
	float ***M = new float **[n];
	for (int i = 0; i < n - 1; i++) {
		if (abs(B[n - 1 - i][n - 2 - i]) < pow(0.1, 8)) cout << "Sorry =(" << endl;

		if (i == 0) {
			float M1[4][4] = { { 1, 0, 0, 0 },
							{0, 1, 0, 0},
							{ (-1)*B[3][0] / B[3][2], (-1)*B[3][1] / B[3][3], 1 / B[3][2], (-1)*B[3][3] / B[3][2] },
							{ 0, 0, 0, 1 } };
			float M1_1[4][4] = { { 1, 0, 0, 0 },{ 0, 1, 0, 0 },{ B[3][0], B[3][1], B[3][2], B[3][3] },{ 0, 0, 0, 1 } };
			product(4, B, M1);
	/*		cout << endl << endl;
			show_matrix(4, B);*/
			product2(4, B, M1_1);
			cout << endl << endl;
			show_matrix(4, B);
		}
		if (i == 1) {
			float M2[4][4] = { { 1, 0, 0, 0 },
			{ (-1)*B[2][0] / B[2][1], 1/B[2][1], (-1)*B[2][2] / B[2][1], (-1)*B[2][3] / B[2][1] },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 } };
			float M2_1[4][4] = { { 1, 0, 0, 0 },{ B[2][0], B[2][1], B[2][2], B[2][3] },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } };
			product(4, B, M2);
			/*cout << endl << endl;
			show_matrix(4, B);*/
			product2(4, B, M2_1);
			cout << endl << endl;
			show_matrix(4, B);
		}
		if (i == 2) {
			float M3[4][4] = { { 1 / B[1][0], (-1)*B[1][1] / B[1][0], (-1)*B[1][2] / B[1][0], (-1)*B[1][3] / B[1][0] },
				{ 0, 1, 0, 0 },
			
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 } };
			float M3_1[4][4] = { { B[1][0], B[1][1], B[1][2], B[1][3] } ,{ 0, 1, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } };
			product(4, B, M3);
			/*cout << endl << endl;
			show_matrix(4, B);*/
			product2(4, B, M3_1);
			cout << endl << endl;
			show_matrix(4, B);
		}
	}
	
	system("pause");
	return 0;
}