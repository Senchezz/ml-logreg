#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "preprocessing.h"


// Перемешивание (Fisher–Yates)
void shuffle_dataset(Dataset *ds) {
    if (!ds) return;

    srand(time(NULL));

    for (int i = ds->n_samples - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        // swap X
        double *tmp_x = ds->X[i];
        ds->X[i] = ds->X[j];
        ds->X[j] = tmp_x;

        // swap y
        int tmp_y = ds->y[i];
        ds->y[i] = ds->y[j];
        ds->y[j] = tmp_y;
    }
}

void train_test_split(
    Dataset *ds,
    double test_ratio,
    Dataset **train,
    Dataset **test
) {
    if (!ds || !train || !test || test_ratio <= 0.0 || test_ratio >= 1.0) return;

    int n = ds->n_samples;
    int d = ds->n_features;
    if (n <= 0 || d <= 0 || !ds->X || !ds->y) {
        *train = NULL;
        *test = NULL;
        return;
    }

    int test_size = (int) (n * test_ratio);
    int train_size = n - test_size;

    Dataset *tr = (Dataset*) malloc(sizeof(Dataset));
    Dataset *te = (Dataset*) malloc(sizeof(Dataset));
    if (!tr || !te) {
        free(tr);
        free(te);
        *train = NULL;
        *test = NULL;
        return;
    }

    tr->n_samples = train_size;
    tr->n_features = d;
    te->n_samples = test_size;
    te->n_features = d;

    tr->X = (train_size > 0) ? malloc(train_size * sizeof(double*)) : NULL;
    tr->y = (train_size > 0) ? malloc(train_size * sizeof(int)) : NULL;
    te->X = (test_size > 0) ? malloc(test_size * sizeof(double*)) : NULL;
    te->y = (test_size > 0) ? malloc(test_size * sizeof(int)) : NULL;

    if ((train_size > 0 && (!tr->X || !tr->y)) || (test_size > 0 && (!te->X || !te->y))) {
        if (tr) {
            if (tr->X) free(tr->X);
            if (tr->y) free(tr->y);
            free(tr);
        }
        if (te) {
            if (te->X) free(te->X);
            if (te->y) free(te->y);
            free(te);
        }
        *train = NULL;
        *test = NULL;
        return;
    }

    // Глубокое копирование данных в train и test
    for (int i = 0; i < train_size; i++) {
        tr->X[i] = (double*) malloc(d * sizeof(double));
        if (!tr->X[i]) {
            for (int k = 0; k < i; k++){
                free(tr->X[k]);
            }
            free(tr->X);
            free(tr->y);
            free(tr);
            if (te->X) free(te->X);
            if (te->y) free(te->y);
            free(te);
            *train = NULL;
            *test = NULL;
            return;
        }
        memcpy(tr->X[i], ds->X[i], d * sizeof(double));
        tr->y[i] = ds->y[i];
    }

    for (int i = 0; i < test_size; i++) {
        te->X[i] = (double*) malloc(d * sizeof(double));
        if (!te->X[i]) {
            for (int k = 0; k < i; k++) {
                free(te->X[k]);
            }
            free(te->X);
            free(te->y);
            free(te);
            for (int k = 0; k < train_size; k++) {
                free(tr->X[k]);
            }
            free(tr->X);
            free(tr->y);
            free(tr);
            *train = NULL;
            *test = NULL;
            return;
        }
        memcpy(te->X[i], ds->X[train_size + i], d * sizeof(double));
        te->y[i] = ds->y[train_size + i];
    }

    *train = tr;
    *test = te;
}

void compute_mean_std(Dataset *ds, double *mean, double *std) {
    if (!ds || !mean || !std) return;

    int n = ds->n_samples;
    int d = ds->n_features;

    // mean
    for (int j = 0; j < d; j++) {
        mean[j] = 0.0;
        for (int i = 0; i < n; i++) {
            mean[j] += ds->X[i][j];
        }
        mean[j] /= n;
    }

    // std
    for (int j = 0; j < d; j++) {
        std[j] = 0.0;
        for (int i = 0; i < n; i++) {
            double diff = ds->X[i][j] - mean[j];
            std[j] += diff * diff;
        }
        std[j] = sqrt(std[j] / n);

        if (std[j] == 0.0) std[j] = 1.0; // защита от деления на 0.0
    }
}

void normalize(Dataset *ds, double *mean, double *std) {
    if (!ds || !mean || !std) return;

    int n = ds->n_samples;
    int d = ds->n_features;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            ds->X[i][j] = (ds->X[i][j] - mean[j]) / std[j];
        }
    }
}

