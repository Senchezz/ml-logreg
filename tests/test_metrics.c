#include <stdio.h>
#include <math.h>
#include "metrics.h"


// Функция для сравнения double с точностью 1e-6
int double_equal(double a, double b) {
    return fabs(a - b) < 1e-6;
}

int main() {
    printf("TEST METRICS.C\n\n");

    int y_true[6] = {1, 0, 1, 1, 0, 0};
    int y_pred[6] = {1, 0, 1, 0, 0, 1};
    int n = 6;

    // ТЕСТ accuracy
    double acc = accuracy(y_true, y_pred, n);
    printf("accuracy = %.6f %s\n",
           acc,
           double_equal(acc, 0.6666667) ? "PASSED" : "FAILED");

    // ТЕСТ precision
    double prec = precision(y_true, y_pred, n);
    printf("precision = %.6f %s\n",
           prec,
           double_equal(prec, 0.6666667) ? "PASSED" : "FAILED");

    // ТЕСТ recall
    double rec = recall(y_true, y_pred, n);
    printf("recall = %.6f %s\n",
           rec,
           double_equal(rec, 0.6666667) ? "PASSED" : "FAILED");

    // ТЕСТ f1_score
    double f1 = f1_score(y_true, y_pred, n);
    printf("f1_score = %.6f %s\n",
           f1,
           double_equal(f1, 0.6666667) ? "PASSED" : "FAILED");

    // ТЕСТ confusion_matrix
    int cm[4];
    confusion_matrix(y_true, y_pred, n, cm);

    printf("\nConfusion Matrix:\n");
    printf("TN=%d  FP=%d\nFN=%d  TP=%d\n", cm[0], cm[1], cm[2], cm[3]);

    if (cm[0] == 2 && cm[1] == 1 && cm[2] == 1 && cm[3] == 2) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }

    printf("\nALL METRICS TESTS DONE!!!\n");
    return 0;
}