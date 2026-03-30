#include <stdlib.h>
#include <math.h>
#include <time.h>
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
    if (!ds || test_ratio <= 0 || test_ratio >= 1) return;

    int test_size = (int)(ds->n_samples * test_ratio);
    int train_size = ds->n_samples - test_size;

    // train
    *train = (Dataset*) malloc(sizeof(Dataset));
    (*train)->n_samples = train_size;
    (*train)->n_features = ds->n_features;
    (*train)->X = malloc(train_size * sizeof(double*));
    (*train)->y = malloc(train_size * sizeof(int));

    // test
    *test = (Dataset*) malloc(sizeof(Dataset));
    (*test)->n_samples = test_size;
    (*test)->n_features = ds->n_features;
    (*test)->X = malloc(test_size * sizeof(double*));
    (*test)->y = malloc(test_size * sizeof(int));

    // копирование
    for (int i = 0; i < train_size; i++) {
        (*train)->X[i] = ds->X[i];
        (*train)->y[i] = ds->y[i];
    }

    for (int i = 0; i < test_size; i++) {
        (*test)->X[i] = ds->X[train_size + i];
        (*test)->y[i] = ds->y[train_size + i];
    }
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

