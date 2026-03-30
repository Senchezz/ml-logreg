#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"


// Создание матрицы rows x cols (все элементы = 0)
Matrix* create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;

    Matrix *m = (Matrix*) malloc(sizeof(Matrix));
    if (!m) return NULL;

    m->rows = rows;
    m->cols = cols;
    m->data = (double**) malloc(rows * sizeof(double*));
    if (!m->data) {
        free(m);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        m->data[i] = (double*) calloc(cols, sizeof(double));
        if (!m->data[i]) {
            // Освобождаем уже выделенные строки
            for (int j = 0; j < i; j++) free(m->data[j]);
            free(m->data);
            free(m);
            return NULL;
        }
    }

    return m;
}

// Освобождение памяти матрицы
void free_matrix(Matrix *m) {
    if (!m) return;

    for (int i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

// Печать матрицы на экран
void print_matrix(Matrix *m) {
    if (!m) return;

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%8.4f ", m->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Транспонирование матрицы
Matrix* transpose(Matrix *m) {
    if (!m) return NULL;

    Matrix *t = create_matrix(m->cols, m->rows);
    if (!t) return NULL;

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            t->data[j][i] = m->data[i][j];
        }
    }

    return t;
}

// Умножение матриц: c = a * b
Matrix* matmul(Matrix *a, Matrix *b) {
    if (!a || !b || a->cols != b->rows) return NULL;

    Matrix *c = create_matrix(a->rows, b->cols);
    if (!c) return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            for (int k = 0; k < a->cols; k++) {
                c->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }

    return c;
}

// Скалярное умножение матрицы: res = m * scalar
Matrix* mat_scalar_mul(Matrix *m, double scalar) {
    if (!m) return NULL;

    Matrix *res = create_matrix(m->rows, m->cols);
    if (!res) return NULL;

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            res->data[i][j] = m->data[i][j] * scalar;
        }
    }

    return res;
}

// Сложение матриц: res = a + b
Matrix* mat_add(Matrix *a, Matrix *b) {
    if (!a || !b) return NULL;
    if (a->rows != b->rows || a->cols != b->cols) return NULL;

    Matrix *res = create_matrix(a->rows, a->cols);
    if (!res) return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            res->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }

    return res;
}

// Вычитание матриц: res = a - b
Matrix* mat_sub(Matrix *a, Matrix *b) {
    if (!a || !b) return NULL;
    if (a->rows != b->rows || a->cols != b->cols) return NULL;

    Matrix *res = create_matrix(a->rows, a->cols);
    if (!res) return NULL;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            res->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }

    return res;
}

// Применение функции к каждому элементу матрицы: res[i][j] = func(m[i][j])
Matrix* mat_apply(Matrix *m, double (*func)(double)) {
    if (!m || !func) return NULL;

    Matrix *res = create_matrix(m->rows, m->cols);
    if (!res) return NULL;

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            res->data[i][j] = func(m->data[i][j]);
        }
    }

    return res;
}

// Сумма элементов по строкам: возвращает 1xcols
Matrix* mat_sum_rows(Matrix *m) {
    if (!m) return NULL;

    Matrix *res = create_matrix(1, m->cols);
    if (!res) return NULL;

    for (int j = 0; j < m->cols; j++) {
        double sum = 0;
        for (int i = 0; i < m->rows; i++) {
            sum += m->data[i][j];
        }
        res->data[0][j] = sum;
    }

    return res;
}

// Создание матрицы из массива вектора: vec[0..n-1] -> n x 1
Matrix* vector_to_matrix(double *vec, int n) {
    if (!vec || n <= 0) return NULL;

    Matrix *m = create_matrix(n, 1);
    if (!m) return NULL;

    for (int i = 0; i < n; i++) {
        m->data[i][0] = vec[i];
    }

    return m;
}