#pragma once

#include <QWidget>
#include <QKeyEvent>

// Дочерний класс
class Snake : public QWidget {

  public:
      // максимальное количество сегментов тела змеи
      static const int ALL_DOTS = 900;

      // Инициализирует игру и игровую сцену (конструктор)
      Snake(QWidget *parent = 0);

      // массивы, которые хранят информацию
      // о текущей позиции для каждого
      // сегмента тела змеи
      int x[ALL_DOTS];
      int y[ALL_DOTS];

      // таймер
      int timer_id;
      // счётчик сегментов тела змеи
      int dots;
      // координаты яблока по x
      int apple_x;
      // координаты яблока по y
      int apple_y;

      // показывает направление движения змеи:
      // влево
      bool leftDirection;
      // вправо
      bool rightDirection;
      // вверх
      bool upDirection;
      // вниз
      bool downDirection;
      // показывает, запущена ли игра
      bool inGame;

      // инициализирует игровые объекты сцены
      void initGame();
      // генерирует новые координат яблока
      void locateApple();
      // проверяет, съедено ли яблоко
      void checkApple();
      // проверяет коллизии
      void checkCollision();
      // перемещает змею
      void move();
      // отрисовывает объекты на игровой сцене
      void doDrawing();
      // завершает игру
      void gameOver(QPainter &);
      // устанавливает таймер
      void setTimer();


  protected:
      // обработчики событий:
      // отрисовки
      void paintEvent(QPaintEvent *);
      // обновления таймера
      void timerEvent(QTimerEvent *);
      // нажатия кнопки
      void keyPressEvent(QKeyEvent *);

  private:
      // размеры модели яблока
      static const int APPLE_HEIGHT = 10;
      static const int APPLE_WIDTH  = 10;

      // размеры модели головы
      static const int HEAD_HEIGHT  = 10;
      static const int HEAD_WIDTH   = 10;

      // размеры секций тела змеи
      static const int DOT_HEIGHT   = 10;
      static const int DOT_WIDTH    = 10;

      // размеры границ экрана
      static const int B_WIDTH     = 300;
      static const int B_HEIGHT    = 300;

      // размер одного квадрата сцены
      static const int DOT_SIZE    =  10;

      // максимальное значение
      // координат при генерации
      static const int RAND_POS    =  29;

      // время задержки
      // обновления кадров
      static const int DELAY       = 140;
};
