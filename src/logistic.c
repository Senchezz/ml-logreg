#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logistic.h"
#include "matrix.h"


// Создание модели
LogisticRegression* logistic_create(int n_features, int max_iter, double l2) {
    LogisticRegression *model = (LogisticRegression*) malloc(sizeof(LogisticRegression));
    if (!model) return NULL;
    model->w = create_matrix(n_features, 1);
    if (!model->w) {
        free(model);
        return NULL;
    }
    model->b = 0.0;
    model->max_iter = max_iter;
    model->l2 = l2;
    return model;
}

// Освобождение памяти
void logistic_free(LogisticRegression *model) {
    if (!model) return;
    free_matrix(model->w);
    free(model);
}

// Сигмоид
double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

// Обучение градиентным спуском
void logistic_train(LogisticRegression *model, Matrix *X, Matrix *y, double lr) {
    if (!model || !X || !y) return;
    int n_samples = X->rows;
    int n_features = X->cols;

    for (int iter = 0; iter < model->max_iter; iter++) {
        // Предсказание: z = X * w + b
        Matrix *z = matmul(X, model->w);  // (n_samples x 1)
        for (int i = 0; i < n_samples; i++)
            z->data[i][0] += model->b;

        Matrix *p = mat_apply(z, sigmoid); // (n_samples x 1)
        free_matrix(z);

        // Ошибка
        Matrix *err = mat_sub(p, y);       // (n_samples x 1)
        free_matrix(p);

        // Градиент по w: grad_w = X^T * err / n + l2 * w
        Matrix *Xt = transpose(X);         // (n_features x n_samples)
        Matrix *grad_w = matmul(Xt, err);  // (n_features x 1)
        free_matrix(Xt);

        for (int i = 0; i < n_features; i++)
            grad_w->data[i][0] = grad_w->data[i][0] / n_samples + model->l2 * model->w->data[i][0];

        // Градиент по bias: grad_b = sum(err) / n
        double grad_b = 0.0;
        for (int i = 0; i < n_samples; i++)
            grad_b += err->data[i][0];
        grad_b /= n_samples;

        // Обновление весов
        Matrix *w_new = mat_sub(model->w, mat_scalar_mul(grad_w, lr));
        free_matrix(grad_w);
        free_matrix(model->w);
        model->w = w_new;

        // Обновление bias
        model->b -= lr * grad_b;

        free_matrix(err);
    }
}

// Предсказание вероятностей
Matrix* logistic_predict_proba(LogisticRegression *model, Matrix *X) {
    if (!model || !X) return NULL;
    int n_samples = X->rows;
    Matrix *z = matmul(X, model->w);
    for (int i = 0; i < n_samples; i++)
        z->data[i][0] += model->b;

    Matrix *p = mat_apply(z, sigmoid);
    free_matrix(z);
    return p;
}

// Предсказание классов 0/1
Matrix* logistic_predict(LogisticRegression *model, Matrix *X) {
    Matrix *p = logistic_predict_proba(model, X);
    if (!p) return NULL;
    for (int i = 0; i < p->rows; i++) {
        p->data[i][0] = (p->data[i][0] >= 0.5) ? 1.0 : 0.0;
    }
    return p;
}