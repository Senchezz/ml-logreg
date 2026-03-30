#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "dataset.h"


// Перемешивание датасета
void shuffle_dataset(Dataset *ds);

// Разделение на train/test
void train_test_split(
    Dataset *ds,
    double test_ratio,
    Dataset **train,
    Dataset **test
);

// Вычисление mean и std по признакам
void compute_mean_std(Dataset *ds, double *mean, double *std);

// Нормализация: (x - mean) / std
void normalize(Dataset *ds, double *mean, double *std);

#endif // PREPROCESSING_H