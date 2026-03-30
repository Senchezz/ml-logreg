#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
#include "preprocessing.h"
#include "matrix.h"
#include "logistic.h"
#include "metrics.h"


int main() {
    const char *filename = "./data/breast_cancer_dataset.csv";
    int n_features = 30;   // только признаки
    int has_header = 1;

    // Загрузка датасета
    Dataset *ds = load_csv(filename, n_features, has_header);
    if (!ds) {
        printf("Ошибка загрузки CSV\n");
        return 1;
    }

    // Shuffle
    shuffle_dataset(ds);

    // Split train/test
    Dataset *train = NULL, *test = NULL;
    train_test_split(ds, 0.15, &train, &test);

    int n_train = train->n_samples;
    int n_test = test->n_samples;

    // Нормализация признаков
    double *mean = malloc(train->n_features * sizeof(double));
    double *std = malloc(train->n_features * sizeof(double));
    compute_mean_std(train, mean, std);
    normalize(train, mean, std);
    normalize(test, mean, std);

    // Создание матриц для модели
    Matrix *X_train = create_matrix(n_train, n_features);
    Matrix *y_train = create_matrix(n_train, 1);
    Matrix *X_test = create_matrix(n_test, n_features);
    Matrix *y_test = create_matrix(n_test, 1);

    for (int i = 0; i < n_train; i++) {
        for (int j = 0; j < n_features; j++)
            X_train->data[i][j] = train->X[i][j];
        y_train->data[i][0] = train->y[i];
    }
    for (int i = 0; i < n_test; i++) {
        for (int j = 0; j < n_features; j++)
            X_test->data[i][j] = test->X[i][j];
        y_test->data[i][0] = test->y[i];
    }

    // Создание модели
    double lr = 0.01;
    int max_iter = 1000;
    double l2 = 0.05;
    LogisticRegression *model = logistic_create(n_features, max_iter, l2);

    // Обучение
    logistic_train(model, X_train, y_train, lr);

    // Предсказания
    Matrix *y_pred_train = logistic_predict(model, X_train);
    Matrix *y_pred_test = logistic_predict(model, X_test);

    // Конвертация в int для метрик
    int *y_pred_train_int = malloc(n_train * sizeof(int));
    int *y_pred_test_int = malloc(n_test * sizeof(int));
    for (int i = 0; i < n_train; i++)
        y_pred_train_int[i] = (int)y_pred_train->data[i][0];
    for (int i = 0; i < n_test; i++)
        y_pred_test_int[i] = (int)y_pred_test->data[i][0];

    // Вывод метрик на train
    printf("\nMETRICS ON TRAIN:\n");
    printf("Accuracy: %.4f\n", accuracy(train->y, y_pred_train_int, n_train));
    printf("Precision: %.4f\n", precision(train->y, y_pred_train_int, n_train));
    printf("Recall: %.4f\n", recall(train->y, y_pred_train_int, n_train));
    printf("F1 Score: %.4f\n", f1_score(train->y, y_pred_train_int, n_train));

    // Confusion Matrix train
    int cm_train[4];
    confusion_matrix(train->y, y_pred_train_int, n_train, cm_train);
    printf("Confusion Matrix:\nTN=%d  FP=%d\nFN=%d  TP=%d\n", cm_train[0], cm_train[1], cm_train[2], cm_train[3]);

    // Вывод метрик на test
    printf("\nMETRICS ON TEST:\n");
    printf("Accuracy: %.4f\n", accuracy(test->y, y_pred_test_int, n_test));
    printf("Precision: %.4f\n", precision(test->y, y_pred_test_int, n_test));
    printf("Recall: %.4f\n", recall(test->y, y_pred_test_int, n_test));
    printf("F1 Score: %.4f\n", f1_score(test->y, y_pred_test_int, n_test));

    // Confusion Matrix test
    int cm_test[4];
    confusion_matrix(test->y, y_pred_test_int, n_test, cm_test);
    printf("Confusion Matrix:\nTN=%d  FP=%d\nFN=%d  TP=%d\n", cm_test[0], cm_test[1], cm_test[2], cm_test[3]);

    // Вывод весов модели
    printf("\nModel weights:\n");
    for (int i = 0; i < model->w->rows; i++) {
        printf("w%d = %.6f\n", i, model->w->data[i][0]);
    }
    printf("Bias (b) = %.6f\n", model->b);

    // Освобождение памяти
    free(y_pred_train_int);
    free(y_pred_test_int);
    free_matrix(y_pred_train);
    free_matrix(y_pred_test);
    free_matrix(X_train);
    free_matrix(y_train);
    free_matrix(X_test);
    free_matrix(y_test);
    free_dataset(ds);
    free_dataset(train);
    free_dataset(test);
    free(mean);
    free(std);
    logistic_free(model);

    return 0;
}