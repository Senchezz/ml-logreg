#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataset.h"


// Загрузка CSV
Dataset* load_csv(const char *filename, int n_features, int has_header) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    int capacity = 100;
    int n_samples = 0;

    double **X = malloc(capacity * sizeof(double*));
    int *y = malloc(capacity * sizeof(int));

    char line[1024];

    if (has_header) {
        fgets(line, sizeof(line), file);
    }

    while (fgets(line, sizeof(line), file)) {
        if (n_samples >= capacity) {
            capacity *= 2;
            X = realloc(X, capacity * sizeof(double*));
            y = realloc(y, capacity * sizeof(int));
        }

        X[n_samples] = malloc(n_features * sizeof(double));

        char *token = strtok(line, ",");
        for (int i = 0; i < n_features; i++) {
            if (!token) break;
            X[n_samples][i] = atof(token);
            token = strtok(NULL, ",");
        }

        y[n_samples] = atoi(token);
        n_samples++;
    }

    fclose(file);

    Dataset *ds = malloc(sizeof(Dataset));
    ds->X = X;
    ds->y = y;
    ds->n_samples = n_samples;
    ds->n_features = n_features;

    return ds;
}

// Сохранение CSV
int save_csv(const char *filename, Dataset *ds) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0;

    for (int i = 0; i < ds->n_samples; i++) {
        for (int j = 0; j < ds->n_features; j++) {
            fprintf(file, "%lf,", ds->X[i][j]);
        }
        fprintf(file, "%d\n", ds->y[i]);
    }

    fclose(file);
    return 1;
}

// Освобождение памяти
void free_dataset(Dataset *ds) {
    if (!ds) return;

    for (int i = 0; i < ds->n_samples; i++) {
        free(ds->X[i]);
    }

    free(ds->X);
    free(ds->y);
    free(ds);
}