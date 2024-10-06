#include <locale.h>
#include <ncurses.h>
#include <time.h>
#include "cli.h"

void initGui() {
    setlocale(LC_CTYPE, "ru_RU.UTF-8"); // Установка локали для поддержки кириллицы
    initscr(); 
    curs_set(0); // Скрыть курсор
    start_color(); 

    // Инициализация цветовых пар
    init_pair(1, COLOR_BLACK, COLOR_WHITE); 
    init_pair(2, COLOR_BLUE, COLOR_BLUE);   
    init_pair(3, COLOR_WHITE, COLOR_BLACK);  
    init_pair(4, COLOR_WHITE, COLOR_BLACK);   

    cbreak(); // Включение режима "не блокировать"
    noecho(); // Отключить отображение ввода
    nodelay(stdscr, TRUE); // Неблокирующий ввод
    scrollok(stdscr, TRUE); // Разрешить прокрутку
}

void printGame(GameInfo_t game, struct timespec sp_start,
               struct timespec sp_end) {
    printField(game);
    printNextFigure(game);
    printInfo(game);
    freeGui(game, 5, 20);
    handleDelay(sp_start, sp_end, game.speed);
    refresh(); // Обновление экрана
}

void printField(GameInfo_t game) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            int sym = game.field[i][j] != 0 ? 2 : 1;
            attron(COLOR_PAIR(sym));
            mvaddch(i + 3, j * 2 + 2, ' '); // Отображение блока
            mvaddch(i + 3, j * 2 + 3, ' '); 
            attroff(COLOR_PAIR(sym));
        }
    }
}

void printNextFigure(GameInfo_t game) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int sym = game.next[i][j] != 0 ? 2 : 0;
            attron(COLOR_PAIR(sym));
            mvaddch(i + 5, j * 2 + 28, ' '); // Отображение следующей фигуры
            mvaddch(i + 5, j * 2 + 29, ' '); 
            attroff(COLOR_PAIR(sym));
        }
    }
}

void printInfo(GameInfo_t game) {
    attron(COLOR_PAIR(3));
    mvwprintw(stdscr, 1, 10, "Тетрис");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(4));
    mvwprintw(stdscr, 3, 26, "Следующая фигура:"); 
    mvwprintw(stdscr, 11, 26, "Уровень: %d", game.level); 
    mvwprintw(stdscr, 13, 26, "Скорость: %d", game.speed); 
    mvwprintw(stdscr, 15, 26, "Очки: %d", game.score); 
    clrtoeol();
    mvwprintw(stdscr, 17, 26, "Максимальные очки: %d", game.high_score); 
    if (game.pause) mvwprintw(stdscr, 12, 4, "ENTER для старта"); 
    attroff(COLOR_PAIR(4));
    
    attron(COLOR_PAIR(5));
    mvwprintw(stdscr, 24, 4, "Управление:"); 
    mvwprintw(stdscr, 24, 17, "Старт: 'Enter'");
    mvwprintw(stdscr, 25, 17, "Пауза: 'p'");
    mvwprintw(stdscr, 26, 17, "Выход: 'q'");
    mvwprintw(stdscr, 27, 17, "Стрелки для движения: '<' '>'");
    mvwprintw(stdscr, 28, 17, "Пробел для вращения: '___'");
    mvwprintw(stdscr, 29, 17, "Стрелку вниз для ускоренного падения: 'v'");
    attroff(COLOR_PAIR(5));
}

UserAction_t getAction() {
    int ch = getch(); // Получение нажатой клавиши
    switch (ch) {
        case 68:
            return Left; 
        case 67:
            return Right; 
        case ' ':
            return Up; 
        case 66:
            return Down; 
        case '\n':
            return Start; 
        case 'p':
            return Pause; 
        case 'q':
            return Terminate; 
        default:
            return Action; 
    }
}

void handleDelay(struct timespec sp_start, struct timespec sp_end,
                 int game_speed) {
    clock_gettime(CLOCK_MONOTONIC, &sp_end);
    struct timespec ts1, ts2 = {0, 0};
    if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
        (ts2.tv_nsec = (20000000 - game_speed * 1500000) -
                       (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
        nanosleep(&ts2, &ts1);
    }
}