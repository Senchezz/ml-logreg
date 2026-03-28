#ifndef METRICS_H
#define METRICS_H


// Метрики
double accuracy(int *y_true, int *y_pred, int n);
double precision(int *y_true, int *y_pred, int n);
double recall(int *y_true, int *y_pred, int n);
double f1_score(int *y_true, int *y_pred, int n);

// Confusion Matrix: int[4] {TN, FP, FN, TP}
int* confusion_matrix(int *y_true, int *y_pred, int n);

#endif // METRICS_H