#include "tetris.h"

#include "../gui/cli.h"

int main() {
  struct timespec sp_start, sp_end = {0, 0};
  srand(time(NULL));// Инициализация генератора случайных чисел
  initGui(); // Инициализация графического интерфейса
  initGame(); // Инициализация игры

  // Основной игровой цикл, выполняется до завершения игры
  while (tetg->state != GAMEOVER) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start); // Получение текущего времени для расчета времени выполнения
    userInput(getAction(), 0); // Получение и обработка пользовательского ввода

    GameInfo_t game_info = updateCurrentState(); // Обновление состояния игры

    if (tetg->state == GAMEOVER) { // Проверка, завершена ли игра
      freeGui(game_info, tetg->figurest->size, tetg->field->height); // Освобождение ресурсов графического интерфейса
      continue; // Переход к следующей итерации цикла
    } else
      printGame(game_info, sp_start, sp_end); // Отображение текущего состояния игры
  };
  freeGame(tetg); // Освобождение всех ресурсов, связанных с игрой

  endwin();

  return 0;
}