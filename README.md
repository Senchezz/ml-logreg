# ML LogReg - Логистическая регрессия на C

![alt text](https://img.shields.io/badge/language-C-blue.svg)

Реализация классификатора логистической регрессии на языке C для решения задачи бинарной классификации на примере датасета `Breast Cancer Dataset`.

## Описание проекта

Проект демонстрирует полный цикл разработки машинного обучения на C:
- **Загрузка и обработка данных** из CSV файла
- **Предобработка**: нормализация признаков, разделение на train/test
- **Обучение модели**: логистическая регрессия с L2 регуляризацией
- **Оценка качества**: Accuracy, Precision, Recall, F1-Score, матрица ошибок

## Структура проекта

```
ml_logreg/
├── main.c                           # Демонстрация  
├── README.md                        # Этот файл
├── data/
│   └── breast_cancer_dataset.csv    # Датасет для демонстрации (30 признаков)
├── include/                         # Заголовочные файлы (.h)
│   ├── dataset.h                    # Работа с датасетами
│   ├── logistic.h                   # Логистическая регрессия
│   ├── matrix.h                     # Матричные операции
│   ├── metrics.h                    # Метрики классификации
│   └── preprocessing.h              # Предобработка данных
├── src/                             # Исходный код (.c)
│   ├── dataset.c
│   ├── logistic.c
│   ├── matrix.c
│   ├── metrics.c
│   └── preprocessing.c
└── tests/
    ├── test_dataset.c               # Тесты загрузки данных
    ├── test_matrix.c                # Тесты матричных операций
    ├── test_metrics.c               # Тесты вычисления метрик
    └── test_preprocessing.c         # Тесты предобработки
```

## Требования

- **Компилятор**: GCC (или совместимый C компилятор)
- **ОС**: Windows, Linux, macOS
- **Библиотеки**: стандартная библиотека C

## Компиляция и запуск

### Главная программа

```bash
git clone https://github.com/Senchezz/ml-logreg

cd <ваш путь к проекту>

# Компиляция
gcc -Iinclude main.c src/dataset.c src/matrix.c src/metrics.c src/preprocessing.c src/logistic.c -o main.exe -lm

# Запуск
./main.exe
```

### Тесты

```bash
cd <ваш путь к проекту>

# Тест матричных операций
gcc -Iinclude -o test_matrix.exe src/matrix.c tests/test_matrix.c -lm
./test_matrix.exe

# Тест метрик
gcc -Iinclude src/metrics.c tests/test_metrics.c -o test_metrics.exe -lm
./test_metrics.exe

# Тест загрузки данных
gcc -Iinclude src/dataset.c tests/test_dataset.c -o test_dataset.exe -lm
./test_dataset.exe

# Тест предобработки
gcc tests/test_preprocessing.c src/dataset.c src/preprocessing.c -Iinclude -o test_preprocessing.exe
./test_preprocessing.exe
```

## О файле `main.c`

### Параметры

- `n_features = 30` - количество признаков
- `has_header = 1` - пропуск заголовка при чтении csv
- `train/test split = 0.15` - 85% обучающей выборки, 15% тестовой
- `learning rate (lr) = 0.01` - скорость обучения
- `max_iter = 1000` - максимальное количество итераций
- `l2 = 0.05` - коэффициент L2 регуляризации

### Результаты

Программа выводит метрики на обучающей и тестовой выборках, а также веса модели (при повторном запуске полученные значения метрик и весов модели могут различаться, так как разбиение данных производится случайно):

<details>
<summary>Посмотреть пример полного вывода в консоль</summary>

```text
METRICS ON TRAIN:
Accuracy: 0.9773
Precision: 0.9705
Recall: 0.9933
F1 Score: 0.9818
Confusion Matrix:
TN=177  FP=9
FN=2  TP=296

METRICS ON TEST:
Accuracy: 0.9882
Precision: 0.9833
Recall: 1.0000
F1 Score: 0.9916
Confusion Matrix:
TN=25  FP=1
FN=0  TP=59

Model weights:
w0 = -0.318049
w1 = -0.274379
w2 = -0.313414
w3 = -0.308142
w4 = -0.109315
w5 = -0.102157
w6 = -0.245235
w7 = -0.312581
w8 = -0.075976
w9 = 0.147640
w10 = -0.271497
w11 = -0.002827
w12 = -0.227571
w13 = -0.241986
w14 = 0.007812
w15 = 0.071412
w16 = 0.033824
w17 = -0.070081
w18 = 0.040915
w19 = 0.151214
w20 = -0.368355
w21 = -0.340053
w22 = -0.352800
w23 = -0.341582
w24 = -0.237715
w25 = -0.163157
w26 = -0.254543
w27 = -0.341968
w28 = -0.227442
w29 = -0.076974
Bias (b) = 0.293585
```
</details>

## Заметки разработчика

- Все операции с памятью должны быть освобождены через соответствующие функции `free` и `free_*`
- Датасет должен быть в формате CSV, без пропусков, с target-столбцом в конце
- Структура `Matrix` используется только для модели и её обучения, не используется при создании датасета и расчёте метрик 