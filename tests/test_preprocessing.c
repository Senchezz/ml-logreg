#include <stdio.h>
#include <stdlib.h>
#include "dataset.h"
#include "preprocessing.h"


int main() {
    printf("TEST PREPROCESSING.C\n\n");

    Dataset *ds = load_csv("./data/breast_cancer_dataset.csv", 30, 1);

    if (!ds) {
        printf("load_csv FAILED\n");
        return 1;
    }

    printf("Original samples: %d\n", ds->n_samples);

    // shuffle
    shuffle_dataset(ds);
    printf("shuffle_dataset PASSED\n");

    // split
    Dataset *train, *test;
    train_test_split(ds, 0.15, &train, &test);

    printf("Train: %d, Test: %d\n", train->n_samples, test->n_samples);

    // normalization
    double *mean = malloc(ds->n_features * sizeof(double));
    double *std = malloc(ds->n_features * sizeof(double));

    compute_mean_std(train, mean, std);
    normalize(train, mean, std);
    normalize(test, mean, std);

    printf("normalize PASSED\n");

    // Освобождение памяти
    free(mean);
    free(std);
    free_dataset(ds);
    free_dataset(train);
    free_dataset(test);

    printf("\nALL PREPROCESSING TESTS DONE!!!\n");
    return 0;
}