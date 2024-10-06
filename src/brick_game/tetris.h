#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @enum UserAction_t
 * @brief Перечисляет возможные действия пользователя в игре.
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @enum GameState
 * @brief Перечисляет возможные состояния игры.
 */
typedef enum { INIT, DROP, MOVING, COLLISION, PAUSE, GAMEOVER } GameState;

/**
 * @struct GameInfo_t
 * @brief Содержит динамическую информацию о текущем состоянии игры.
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @struct Block
 * @brief Представляет собой отдельный блок в игре.
 */
typedef struct Block {
  int b;
} Block;

/**
 * @struct Figure
 * @brief Представляет игровую фигуру, состоящую из нескольких блоков.
 */
typedef struct Figure {
  int x;
  int y;
  int size;
  Block **blocks;
} Figure;

/**
 * @struct FiguresT
 * @brief Содержит шаблоны для всех возможных фигур в игре.
 */
typedef struct FiguresT {
  int count;
  int size;
  Block **blocks;
} FiguresT;

/**
 * @struct Field
 * @brief Представляет игровое поле.
 */
typedef struct Field {
  int width;
  int height;
  Block **blocks;
} Field;

/**
 * @struct Player
 * @brief Представляет текущее действие игрока.
 */
typedef struct Player {
  int action;
} Player;

/**
 * @struct Game
 * @brief Основная структура игры, содержащая все данные, связанные с игрой.
 */
typedef struct Game {
  Field *field;
  Figure *figure;
  FiguresT *figurest;
  Player *player;
  Block **tet_templates;

  int score;
  int high_score;
  int ticks_left;
  int ticks;
  int speed;
  int level;
  int next;

  int pause;
  int state;

} Game;

/**
 *@brief Инициализация игры.
 * Программа начинается здесь
 */
void initGame();

/**
 * @brief Создает и инициализирует основную структуру игры (Game). Устанавливает игровое поле,
 * шаблоны фигур и инициализирует параметры игры, такие как счет, рекордный счет и состояние игры.
 * @param field_width: Ширина игрового поля.
 * @param field_height: Высота игрового поля.
 * @param figures_size: Размер фигур.
 * @param count: Количество различных фигур.
 * @return Указатель на инициализированную структуру Game.
 */
Game *createGame(int field_width, int field_height, int figures_size,
                 int count);

/**
 * @brief Выделяет память и инициализирует игровое поле с заданными
 * размерами.
 * @param width: Ширина игрового поля.
 * @param height: Высота игрового поля.
 * @return Указатель на инициализированную структуру Field.
 */
Field *createField(int width, int height);

/**
 * @brief Инициализирует шаблоны для фигур Тетриса, используя предопределенные
 * массивы фигур.
 * @return Массив указателей на Block, представляющий различные шаблоны фигур.
 */
Block **createTemplates();

/**
 * @brief Создает и инициализирует структуру, хранящую шаблоны фигур
 * и их метаданные.
 * @param count: Количество различных фигур.
 * @param figures_size: Размер каждой фигуры.
 * @param figures_template: Указатель на массив шаблонов фигур.
 * @return Указатель на инициализированную структуру FiguresT.
 */
FiguresT *createFiguresT(int count, int figures_size, Block **figures_template);

/**
 * @brief Выделяет память для новой фигуры и инициализирует ее блоки нулями.
 * @param tetg: Указатель на состояние игры.
 * @return Указатель на только что созданную фигуру.
 */
Figure *createFigure(Game *tetg);

/**
 * @brief Создает печатное представление текущего игрового поля.
 * @param width: Ширина поля.
 * @param height: Высота поля.
 * @return Двумерный массив целых чисел, представляющий состояние поля.
 */
int **createPrintField(int width, int height);

/**
 * @brief Генерирует следующий блок для игры, основываясь на текущем состоянии
 * игры.
 * @param size: Размер блока.
 * @return Двумерный массив целых чисел, представляющий следующий блок.
 */
int **createNextBlock(int size);

/**
 * @brief Обрабатывает ввод пользователя и обновляет действие игрока в
 * структуре игры.
 * @param action: Действие, выполненное пользователем.
 * @param hold: Указывает, удерживается ли действие.
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Инициализирует новую фигуру в игре, устанавливает ее начальную
 * позицию, проверяет на столкновения и обновляет следующую фигуру.
 * @param tetg Указатель на состояние игры.
 */
void dropNewFigure(Game *tetg);

/**
 * @brief Обновляет и возвращает текущее состояние игры, включая представления поля и следующего блока.
 * @return Структура GameInfo_t, содержащая текущее состояние игры.
 */
GameInfo_t updateCurrentState();

/**
 * @brief Обрабатывает один тик игровой логики, обрабатывая действия пользователя и правила игры.
 * @param tetg: Указатель на структуру игры.
 */
void calculate(Game *tetg);

/**
 * @brief Обрабатывает логику одного тика игры, перемещая фигуру вниз и проверяя на коллизии.
 * @param tetg: Указатель на структуру игры.
 */
void calcOne(Game *tetg);

/**
 * @brief Перемещает текущую фигуру на одну единицу вниз.
 * @param tetg: Указатель на состояние игры.
 */
void moveFigureDown(Game *tetg);

/**
 * @brief Перемещает текущую фигуру на одну единицу вверх.
 * @param tetg: Указатель на состояние игры.
 */
void moveFigureUp(Game *tetg);

/**
 * @brief Перемещает текущую фигуру на одну единицу вправо.
 * @param tetg: Указатель на состояние игры.
 */
void moveFigureRight(Game *tetg);

/**
 * @brief Перемещает текущую фигуру на одну единицу влево.
 * @param tetg: Указатель на состояние игры.
 */
void moveFigureLeft(Game *tetg);

/**
 * @brief Проверяет, сталкивается ли текущая фигура с границами поля
 * или другими блоками.
 * @param tetg: Указатель на состояние игры.
 * @return 1, если произошло столкновение, иначе 0.
 */
int collision(Game *tetg);

/**
 * @brief Проверяет заполненные линии на поле и удаляет их, перемещая все
 * линии выше вниз.
 * @param tetg: Указатель на состояние игры.
 * @return Количество удалённых линий.
 */
int eraseLines(Game *tetg);

/**
 * @brief Проверяет, заполнена ли конкретная линия на поле полностью.
 * @param i: Индекс линии для проверки.
 * @param tfl: Указатель на поле.
 * @return 1, если линия заполнена, в противном случае 0.
 */
int lineFilled(int i, Field *tfl);

/**
 * @brief Удаляет линию из поля и сдвигает все линии выше нее вниз на одну.
 * @param i: Индекс линии для удаления.
 * @param tfl: Указатель на поле.
 */
void dropLine(int i, Field *tfl);

/**
 * @brief Создает новую фигуру в виде повёрнутой версии текущей фигуры.
 * @param tetg: Указатель на состояние игры.
 * @return Указатель на повёрнутую фигуру.
 */
Figure *rotFigure(Game *tetg);

/**
 * @brief Пытается повернуть текущую фигуру и проверяет на наличие коллизий.
 * Возвращается к предыдущему состоянию, если происходит коллизия.
 * @param tetg: Указатель на состояние игры.
 */
void handleRotation(Game *tetg);

/**
 * @brief Размещает блоки текущей фигуры на игровом поле, если они находятся
 * в пределах границ.
 * @param tetg: Указатель на состояние игры.
 */
void plantFigure(Game *tetg);

/**
 * @brief Обновляет счёт игры в зависимости от количества снесённых линий и
 * соответственно корректирует уровень и скорость игры.
 * @param tetg: Указатель на структуру игры.
 */
void countScore(Game *tetg);

/**
 * @brief Сохраняет лучший счёт в файл.
 * @param high_score: Лучший счёт для сохранения.
 */
void saveHighScore(int high_score);

/**
 * @brief Загружает лучший счёт из файла.
 * @return Лучший счёт в виде целого числа.
 */
int loadHighScore();

extern Game *tetg;

// Освобождение памяти

/**
 * @brief Освобождает всю память, выделенную для игры, включая структуру игры,
 * поле, фигуры, шаблоны и игрока.
 * @param tetg: Указатель на структуру игры, которую необходимо освободить.
 */
void freeGame(Game *tetg);

/**
 * @brief Освобождает всю память, выделенную для структуры поля, включая
 * блоки внутри поля.
 * @param tetf: Указатель на структуру поля, которую необходимо освободить.
 */
void freeField(Field *tetf);

/**
 * @brief Освобождает память, выделенную для фигуры, включая ее блоки.
 * @param tf: Указатель на фигуру, которую необходимо освободить.
 */
void freeFigure(Figure *tf);

/**
 * @brief Освобождает память, выделенную для структуры FiguresT.
 * @param tetft: Указатель на структуру FiguresT, которую необходимо освободить.
 */
void freeFiguresT(FiguresT *tetft);

/**
 * @brief Освобождает память, выделенную для шаблонов блоков.
 * @param templates: Указатель на массив шаблонов блоков, который необходимо освободить.
 */
void freeTemplates(Block **templates);

/**
 * @brief Освобождает память, выделенную для массива поля печати.
 * @param print_field: Указатель на массив поля печати, который необходимо освободить.
 * @param height: Количество строк в массиве поля печати.
 */
void freePrintField(int **print_field, int height);

/**
 * @brief Освобождает память, выделенную для массива следующего блока.
 * @param next: Указатель на массив следующего блока, который необходимо освободить.
 * @param size: Количество строк в массиве следующего блока.
 */
void freeNextBlock(int **next, int size);

/**
 * @brief Освобождает структуры, связанные с графическим интерфейсом, включая
 * печатное поле и следующий блок.
 * @param game: Структура, содержащая данные, связанные с графическим интерфейсом.
 * @param size: Параметр размера, используемый для освобождения следующего блока.
 * @param height: Параметр высоты, используемый для освобождения печатного поля.
 */
void freeGui(GameInfo_t game, int size, int height);

#endif