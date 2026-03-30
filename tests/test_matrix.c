#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"


// Функция для теста mat_apply
double square(double x) {
    return x * x;
}

// Сравнение матриц с точностью 1e-6
int matrices_equal(Matrix *a, Matrix *b) {
    if (!a || !b) return 0;
    if (a->rows != b->rows || a->cols != b->cols) return 0;
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            if (fabs(a->data[i][j] - b->data[i][j]) > 1e-6) return 0;
        }
    }
    return 1;
}

int main() {
    printf("TEST MATRIX.C\n\n");

    // create_matrix
    Matrix *m1 = create_matrix(2, 3);
    if (!m1) {
        printf("create_matrix FAILED\n");
        return 1;
    }
    printf("create_matrix PASSED\n");

    // Заполним матрицу
    m1->data[0][0] = 1; m1->data[0][1] = 2; m1->data[0][2] = 3;
    m1->data[1][0] = 4; m1->data[1][1] = 5; m1->data[1][2] = 6;

    // transpose
    Matrix *t = transpose(m1);
    Matrix *t_expected = create_matrix(3, 2);
    t_expected->data[0][0] = 1; t_expected->data[0][1] = 4;
    t_expected->data[1][0] = 2; t_expected->data[1][1] = 5;
    t_expected->data[2][0] = 3; t_expected->data[2][1] = 6;
    printf("transpose %s\n", matrices_equal(t, t_expected) ? "PASSED" : "FAILED");
    free_matrix(t_expected);

    // matmul
    Matrix *m2 = create_matrix(3, 2);
    m2->data[0][0] = 7; m2->data[0][1] = 8;
    m2->data[1][0] = 9; m2->data[1][1] = 10;
    m2->data[2][0] = 11; m2->data[2][1] = 12;
    Matrix *prod = matmul(m1, m2);
    Matrix *prod_expected = create_matrix(2, 2);
    prod_expected->data[0][0] = 58; prod_expected->data[0][1] = 64;
    prod_expected->data[1][0] = 139; prod_expected->data[1][1] = 154;
    printf("matmul %s\n", matrices_equal(prod, prod_expected) ? "PASSED" : "FAILED");
    free_matrix(prod_expected);

    // mat_scalar_mul
    Matrix *sm = mat_scalar_mul(m1, 2);
    Matrix *sm_expected = create_matrix(2, 3);
    sm_expected->data[0][0] = 2; sm_expected->data[0][1] = 4; sm_expected->data[0][2] = 6;
    sm_expected->data[1][0] = 8; sm_expected->data[1][1] = 10; sm_expected->data[1][2] = 12;
    printf("mat_scalar_mul %s\n", matrices_equal(sm, sm_expected) ? "PASSED" : "FAILED");
    free_matrix(sm_expected);

    // mat_add
    Matrix *sum = mat_add(m1, sm);
    Matrix *sum_expected = create_matrix(2, 3);
    sum_expected->data[0][0] = 3; sum_expected->data[0][1] = 6; sum_expected->data[0][2] = 9;
    sum_expected->data[1][0] = 12; sum_expected->data[1][1] = 15; sum_expected->data[1][2] = 18;
    printf("mat_add %s\n", matrices_equal(sum, sum_expected) ? "PASSED" : "FAILED");
    free_matrix(sum_expected);

    // mat_sub
    Matrix *sub = mat_sub(sum, sm);  // sum - sm = m1
    printf("mat_sub %s\n", matrices_equal(sub, m1) ? "PASSED" : "FAILED");
    free_matrix(sub);

    // mat_apply
    Matrix *ap = mat_apply(m1, square);
    Matrix *ap_expected = create_matrix(2,3);
    ap_expected->data[0][0] = 1; ap_expected->data[0][1] = 4; ap_expected->data[0][2] = 9;
    ap_expected->data[1][0] = 16; ap_expected->data[1][1] = 25; ap_expected->data[1][2] = 36;
    printf("mat_apply %s\n", matrices_equal(ap, ap_expected) ? "PASSED" : "FAILED");
    free_matrix(ap_expected);

    // mat_sum_rows
    Matrix *sum_rows = mat_sum_rows(m1);
    Matrix *sum_rows_expected = create_matrix(1,3);
    sum_rows_expected->data[0][0] = 5; sum_rows_expected->data[0][1] = 7; sum_rows_expected->data[0][2] = 9;
    printf("mat_sum_rows %s\n", matrices_equal(sum_rows, sum_rows_expected) ? "PASSED" : "FAILED");
    free_matrix(sum_rows_expected);
    free_matrix(sum_rows);

    // vector_to_matrix
    double vec[3] = {10, 20, 30};
    Matrix *vec_m = vector_to_matrix(vec, 3);
    Matrix *vec_expected = create_matrix(3,1);
    vec_expected->data[0][0] = 10; vec_expected->data[1][0] = 20; vec_expected->data[2][0] = 30;
    printf("vector_to_matrix %s\n", matrices_equal(vec_m, vec_expected) ? "PASSED" : "FAILED");
    free_matrix(vec_expected);
    free_matrix(vec_m);

    // Освобождение памяти
    free_matrix(m1);
    free_matrix(m2);
    free_matrix(t);
    free_matrix(prod);
    free_matrix(sm);
    free_matrix(sum);
    free_matrix(ap);

    printf("\nALL MATRIX TESTS DONE!!!\n");
    return 0;
}