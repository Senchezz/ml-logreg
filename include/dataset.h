#ifndef DATASET_H
#define DATASET_H


typedef struct {
    double **X;      // признаки
    int *y;          // метки
    int n_samples;
    int n_features;
} Dataset;

// Загрузка CSV
Dataset* load_csv(const char *filename, int n_features, int has_header);

// Сохранение CSV
int save_csv(const char *filename, Dataset *ds);

// Освобождение памяти
void free_dataset(Dataset *ds);

#endif // DATASET_H