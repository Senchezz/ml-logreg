#ifndef METRICS_H
#define METRICS_H


// Метрики
double accuracy(int *y_true, int *y_pred, int n);
double precision(int *y_true, int *y_pred, int n);
double recall(int *y_true, int *y_pred, int n);
double f1_score(int *y_true, int *y_pred, int n);

// Confusion Matrix: cm[4] = {TN, FP, FN, TP}
void confusion_matrix(int *y_true, int *y_pred, int n, int *cm);

#endif // METRICS_H