#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

typedef vector<vector<int>> Matrix;

Matrix initMatrix(int n) { return Matrix(n, vector<int>(n, 0)); }

Matrix add(Matrix A, Matrix B, int n) {
    Matrix C = initMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) C[i][j] = A[i][j] + B[i][j];
    return C;
}
Matrix sub(Matrix A, Matrix B, int n) {
    Matrix C = initMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) C[i][j] = A[i][j] - B[i][j];
    return C;
}

Matrix multiply_On3(Matrix A, Matrix B, int n) {
    Matrix C = initMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matrix strassen(Matrix A, Matrix B, int n) {
    if (n <= 64) return multiply_On3(A, B, n);

    int new_n = n / 2;
    Matrix a11 = initMatrix(new_n), a12 = initMatrix(new_n), a21 = initMatrix(new_n), a22 = initMatrix(new_n);
    Matrix b11 = initMatrix(new_n), b12 = initMatrix(new_n), b21 = initMatrix(new_n), b22 = initMatrix(new_n);

    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            a11[i][j] = A[i][j];                   a12[i][j] = A[i][j + new_n];
            a21[i][j] = A[i + new_n][j];           a22[i][j] = A[i + new_n][j + new_n];
            b11[i][j] = B[i][j];                   b12[i][j] = B[i][j + new_n];
            b21[i][j] = B[i + new_n][j];           b22[i][j] = B[i + new_n][j + new_n];
        }
    }

    Matrix p1 = strassen(a11, sub(b12, b22, new_n), new_n);
    Matrix p2 = strassen(add(a11, a12, new_n), b22, new_n);
    Matrix p3 = strassen(add(a21, a22, new_n), b11, new_n);
    Matrix p4 = strassen(a22, sub(b21, b11, new_n), new_n);
    Matrix p5 = strassen(add(a11, a22, new_n), add(b11, b22, new_n), new_n);
    Matrix p6 = strassen(sub(a12, a22, new_n), add(b21, b22, new_n), new_n);
    Matrix p7 = strassen(sub(a11, a21, new_n), add(b11, b12, new_n), new_n);

    Matrix c11 = sub(add(add(p5, p4, new_n), p6, new_n), p2, new_n);
    Matrix c12 = add(p1, p2, new_n);
    Matrix c21 = add(p3, p4, new_n);
    Matrix c22 = sub(sub(add(p5, p1, new_n), p3, new_n), p7, new_n);

    Matrix C = initMatrix(n);
    for (int i = 0; i < new_n; i++) {
        for (int j = 0; j < new_n; j++) {
            C[i][j] = c11[i][j];                   C[i][j + new_n] = c12[i][j];
            C[i + new_n][j] = c21[i][j];           C[i + new_n][j + new_n] = c22[i][j];
        }
    }
    return C;
}

int main() {
    vector<int> test_cases = {64, 128, 256, 512};
    
    ofstream file("resultados_matrices.txt");
    file << "N,Tiempo_On3,Tiempo_Strassen\n";
    
    cout << "--- Ejecutando Matrices y guardando en txt ---\n";
    for (int n : test_cases) {
        Matrix A = initMatrix(n), B = initMatrix(n);
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) { A[i][j] = rand()%10; B[i][j] = rand()%10; }

        auto start = high_resolution_clock::now();
        Matrix C1 = multiply_On3(A, B, n);
        auto stop = high_resolution_clock::now();
        auto duration_On3 = duration_cast<milliseconds>(stop - start).count();

        start = high_resolution_clock::now();
        Matrix C2 = strassen(A, B, n);
        stop = high_resolution_clock::now();
        auto duration_Strassen = duration_cast<milliseconds>(stop - start).count();

        file << n << "," << duration_On3 << "," << duration_Strassen << "\n";
        cout << "Matriz " << n << "x" << n << " completada.\n";
    }
    file.close();
    return 0;
}