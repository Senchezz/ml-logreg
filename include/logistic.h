#ifndef LOGISTIC_H
#define LOGISTIC_H

#include "matrix.h"


typedef struct {
    Matrix *w;     // веса (n_features x 1)
    double b;      // bias
    int max_iter;  // максимальное число итераций
    double l2;     // коэффициент L2 регуляризации
} LogisticRegression;

// Создание модели
LogisticRegression* logistic_create(int n_features, int max_iter, double l2);

// Освобождение памяти модели
void logistic_free(LogisticRegression *model);

// Функция сигмоида
double sigmoid(double z);

// Обучение модели
void logistic_train(LogisticRegression *model, Matrix *X, Matrix *y, double lr);

// Предсказание вероятностей
Matrix* logistic_predict_proba(LogisticRegression *model, Matrix *X);

// Предсказание классов (0/1)
Matrix* logistic_predict(LogisticRegression *model, Matrix *X);

#endif // LOGISTIC_H