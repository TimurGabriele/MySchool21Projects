# MySchool21Projects
*подробное описание в папке соответствующего проекта*

## Simple Bash Utils - Разработка утилит Bash по работе с текстом: cat, grep
- Программы разработаны на языке С стандарта C11 с использованием компилятора gcc.
- Код программ cat и grep находится в папках src/cat/ и src/grep/ соответственно. 
- Программы представляют собой исполняемый файл с аргументами командной строки
- Сборка программ настроена с помощью Makefile с соответствующими целями: s21_cat, s21_grep.
- Предусмотрено покрытие интеграционными тестами для всех вариантов флагов и входных значений, на базе сравнения с поведением реальных утилит Bash.

## s21_decimal - Реализована собственная библиотека s21_decimal.h 
- Библиотека разработана на языке С стандарта C11 с использованием компилятора gcc.
- Код библиотеки находиться в папке src.
- Решение оформлено как статическая библиотека с названием *s21_decimal.a* (с заголовочным файлом *s21_decimal.h*).
- Подготовлено полное покрытие unit-тестами функций библиотеки c помощью библиотеки Check.
- Предусмотрен Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_decimal.a, gcov_report).
- В цели gcov_report формируется отчёт gcov в виде html-страницы. Для этого unit-тесты запускаются с флагами gcov.

## s21_string+ - Разработана собственная реализация библиотеки string.h с дополнениями (с собственной реализацией функций sprintf и sscanf). 
- Библиотека разработана на языке С стандарта C11 с использованием компилятора gcc;
- Код библиотеки, включая заголовочные файлы, мейкфайлы и саму библиотеку, находится в папке src;
- Решение оформлено как статическая библиотека с названием *s21_string.a* (с заголовочным файлом *s21_string.h*);
- Подготовлено полное покрытие unit-тестами функций библиотеки c помощью библиотеки Check;
- Unit-тесты проверяют результаты работы путём сравнения ее с реализацией стандартной библиотеки string.h;
- Предусмотрен Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_string.a, gcov_report);
- В цели gcov_report формируется отчёт gcov в виде html страницы. Для этого unit-тесты запускаются с флагами gcov;

## s21_matrix Реализация библиотеки matrix.h.
- Библиотека разработана на языке С стандарта C11 с использованием компилятора gcc. Код библиотеки находится в папке src.
- Реализованы основные действия с матрицами: create_matrix (создание), remove_matrix (очистка и уничтожение), eq_matrix (сравнение), sum_matrix (сложение), sub_matrix (вычитание), mult_matrix (умножение), mult_number (умножение на число), transpose (транспонирование), determinant (вычисление определителя), calc_complements (вычисление матрицы алгебраических дополнений), inverse_matrix (поиск обратной матрицы).
- Решение оформлено как статическая библиотека с названием *s21_matrix.a* (с заголовочным файлом *s21_matrix.h*).
- Подготовлено полное покрытие unit-тестами функций библиотеки c помощью библиотеки Check.
- Предусмотрен Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_matrix.a, gcov_report).
- В цели gcov_report формируется отчёт gcov в виде html страницы. Для этого unit-тесты запускаются с флагами gcov.

