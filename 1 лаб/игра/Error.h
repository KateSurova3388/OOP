#ifndef ERROR
#define ERROR

typedef enum ERROR {
  OUT_OF_BOUNDS = 1,  // Координаты вне границ поля
  CELL_NOT_EMPTY,     // Ячейка уже занята
  SIZE_TOO_LARGE,  // Размер корабля превышает границы поля
  INCORRECT_ORIENTATION,  // Некорректная ориентация корабля
  SURROUNDING_CHECK_FAILED  // Проверка соседних ячеек не пройдена

} error;

#endif