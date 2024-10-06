#include "tetris.h"

// Освобождение памяти, занятой объектами игры
void freeGame(Game *tetg) {
  if (tetg) {
    if (tetg->figure != NULL) freeFigure(tetg->figure);
    freeField(tetg->field);
    freeFiguresT(tetg->figurest);
    freeTemplates(tetg->tet_templates);
    free(tetg->player);
    free(tetg);
  }
}

// Освобождение памяти, занятой игровым полем
void freeField(Field *tetf) {
  if (tetf) {
    for (int i = 0; i < tetf->height; i++) free(tetf->blocks[i]);
    free(tetf->blocks);
    free(tetf);
  }
}

// Освобождение памяти, занятой фигурой
void freeFigure(Figure *tf) {
  if (tf) {
    if (tf->blocks) {
      for (int i = 0; i < tf->size; i++) {
        if (tf->blocks[i]) {
          free(tf->blocks[i]);
        }
      }
      free(tf->blocks);
    }
    free(tf);
  }
}

// Освобождение памяти, занятой шаблонами фигур
void freeTemplates(Block **templates) {
  if (templates) free(templates);
}

// Освобождение памяти, занятой набором фигур
void freeFiguresT(FiguresT *tetft) {
  if (tetft) free(tetft);
}

// Освобождение памяти, занятой полем для отображения
void freePrintField(int **print_field, int height) {
  if (print_field) {
    for (int i = 0; i < height; i++) {
      if (print_field[i]) free(print_field[i]);
    }
    free(print_field);
  }
}

// Освобождение памяти, занятой следующей фигурой
void freeNextBlock(int **next, int size) {
  if (next) {
    for (int i = 0; i < size; i++) free(next[i]);
    free(next);
  }
}

// Освобождение памяти, занятой графическим интерфейсом игры
void freeGui(GameInfo_t game, int size, int height) {
  freePrintField(game.field, height);
  freeNextBlock(game.next, size);
}