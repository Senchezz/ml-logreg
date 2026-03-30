#ifndef MATRIX_H
#define MATRIX_H


typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

// Создание и удаление матрицы
Matrix* create_matrix(int rows, int cols);
void free_matrix(Matrix *m);

// Основные операции
Matrix* transpose(Matrix *m);                      // Транспонирование
Matrix* matmul(Matrix *a, Matrix *b);              // Умножение матриц
Matrix* mat_add(Matrix *a, Matrix *b);             // Сложение матриц
Matrix* mat_sub(Matrix *a, Matrix *b);             // Вычитание матриц
Matrix* mat_scalar_mul(Matrix *m, double scalar);  // Умножение на скаляр

// Функции поэлементного применения
Matrix* mat_apply(Matrix *m, double (*func)(double));

// Вспомогательные
Matrix* mat_sum_rows(Matrix *m);               // Сумма элементов по строкам (результат — 1xcols)
Matrix* vector_to_matrix(double *vec, int n);  // Создание матрицы из вектора (1D -> Matrix)
void print_matrix(Matrix *m);

#endif // MATRIX_H