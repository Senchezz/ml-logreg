#include <stdlib.h>
#include "metrics.h"


double accuracy(int *y_true, int *y_pred, int n) {
    int correct = 0;
    for (int i = 0; i < n; i++) {
        if (y_true[i] == y_pred[i]) {
            correct++;
        }
    }
    return (double) correct / n;
}

double precision(int *y_true, int *y_pred, int n) {
    int tp = 0, fp = 0;
    for (int i = 0; i < n; i++) {
        if (y_pred[i] == 1) {
            if (y_true[i] == 1) {
                tp++;
            } else {
                fp++;
            }
        }
    }
    return (tp + fp == 0) ? 0.0 : (double) tp / (tp + fp);
}

double recall(int *y_true, int *y_pred, int n) {
    int tp = 0, fn = 0;
    for (int i = 0; i < n; i++) {
        if (y_true[i] == 1) {
            if (y_pred[i] == 1) {
                tp++;
            } else {
                fn++;
            }
        }
    }
    return (tp + fn == 0) ? 0.0 : (double) tp / (tp + fn);
}

double f1_score(int *y_true, int *y_pred, int n) {
    double p = precision(y_true, y_pred, n);
    double r = recall(y_true, y_pred, n);
    return (p + r == 0.0) ? 0.0 : 2 * p * r / (p + r);
}

// Confusion Matrix: {TN, FP, FN, TP}
int* confusion_matrix(int *y_true, int *y_pred, int n) {
    int tn = 0, fp = 0, fn = 0, tp = 0;
    for (int i = 0; i < n; i++) {
        if (y_true[i] == 1 && y_pred[i] == 1) {
            tp++;
        } else if (y_true[i] == 1 && y_pred[i] == 0) {
            fn++;
        } else if (y_true[i] == 0 && y_pred[i] == 1){
            fp++;
        } else if (y_true[i] == 0 && y_pred[i] == 0) {
            tn++;
        }
    }
    int *cm = (int*) malloc(4 * sizeof(int));
    cm[0] = tn; cm[1] = fp; cm[2] = fn; cm[3] = tp;
    return cm;
}