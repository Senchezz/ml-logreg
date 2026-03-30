#include <stdio.h>
#include "dataset.h"


int main() {
    printf("TEST DATASET.C\n\n");

    Dataset *ds = load_csv("./data/breast_cancer_dataset.csv", 30, 1);

    if (!ds) {
        printf("load_csv FAILED\n");
        return 1;
    }
    printf("load_csv PASSED\n");

    printf("Samples: %d\n", ds->n_samples);
    printf("Features: %d\n", ds->n_features);

    // Тест сохранения
    if (save_csv("output.csv", ds)) {
        printf("save_csv PASSED\n");
    } else {
        printf("save_csv FAILED\n");
    }

    free_dataset(ds);
    printf("free_dataset PASSED\n");

    printf("\nALL DATASET TESTS DONE!!!\n");
    return 0;
}