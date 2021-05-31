#include <QPainter>
#include <QTime>
#include "Snake.h"

#include <iostream>
#include <QDebug>

// Инициализирует игровую сцену, направление движения змеи и начало игры
Snake::Snake(QWidget *parent) : QWidget(parent) {
    // установка цвета заднего фона
    setStyleSheet("background-color:darkgray;");

    // направления движения змеи:
    upDirection   = false;
    downDirection = false;
    leftDirection = false;
    // начальное направление
    rightDirection = true;

    // запуск игры
    inGame = true;
    // установка границ игрового поля
    resize(B_WIDTH, B_HEIGHT);
    // инициализация объектов сцены
    initGame();

}

// Инициализацирует объекты игровой сцены
void Snake::initGame() {
    // счётчик сегментов тела змеи
    dots = 3;

    // отрисовка змеи на начальной позиции
    for (int z = 0; z < dots; z++) {
        // по координате x
        x[z] = 50 - z * 10;
        // по координате y
        y[z] = 50;
    }

    // генерация координат яблока
    locateApple();

    // инициализация таймера
    timer_id = startTimer(DELAY);

}

// Обработчик события отрисовки
void Snake::paintEvent(QPaintEvent *e) {
    // предотвращает чрезмерную реакцию компилятора
    // на более чем один случай, когда параметр не обработан
    Q_UNUSED(e);
    // отрисовка объектов
    doDrawing();

}

// Отрисовывает объекты игровой сцены
void Snake::doDrawing() {
    // класс, являющийся исполнителем команд рисования
    QPainter qp(this);
    // если игра запущена
    if (inGame) {
        // отрисовка яблока на сцене
        qp.drawRect(apple_x, apple_y, APPLE_WIDTH, APPLE_HEIGHT);
        //std::cout << "WAS DRAWN: APPLE" << std::endl << std::endl;
        // отрисовка змеи по частям
        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                // отрисовка головы
                qp.drawRect(x[z], y[z], HEAD_WIDTH, HEAD_HEIGHT);
                //std::cout << "WAS DRAWN: HEAD" << std::endl << std::endl;
            } else {
                // отрисовка сегментов тел
                qp.drawRect(x[z], y[z], DOT_WIDTH, DOT_HEIGHT);
                //std::cout << "WAS DRAWN: BODY" << std::endl << std::endl;
            }
        }

    } else {
        // иначе завершение игры
        gameOver(qp);
    }

}

// Завершение игры
void Snake::gameOver(QPainter &qp) {
    // Вывод заставки
    QString message = "Game over";

    // Параметры текста
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    // установка позиции текста на сцене
    qp.translate(QPoint(w/2, h/2));
    // отрисовка текста
    qp.drawText(-textWidth/2, 0, message);

}

// Проверка коллизий змеи и яблока
void Snake::checkApple() {
    // если сопрекоснулисть,
    if ((x[0] == apple_x) && (y[0] == apple_y)) {
        // то добавить сегмент змее
        dots++;
        // и сгенериировать новые координаты яблока
        locateApple();
    }

}

// Перемещение змеи
void Snake::move() {

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }


    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }

}

// Проверка коллизии змеи со своим телом и с границами игрового поля
void Snake::checkCollision() {

    for (int z = dots; z > 0; z--) {

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }

    if(!inGame) {
        killTimer(timer_id);
    }

}

// Генератор новых координат яблока
void Snake::locateApple() {
    // генерация координаты x
    int r = rand() % RAND_POS + 1;
    apple_x = (r * DOT_SIZE);

    // генерация координаты y
    r = rand() % RAND_POS + 1;
    apple_y = (r * DOT_SIZE);

}

// Обработчик таймера
void Snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);
    // если игра запущена
    if (inGame) {
        // проверяет, еслть ли яблоко на сцене
        checkApple();
        // проверка коллизий змеи и яблока
        checkCollision();
        // передвинуть змею
        move();
    }
    // отрисовать заново сцену
    repaint();

}

// Обработчик события нажатия клавиши
void Snake::keyPressEvent(QKeyEvent *e) {
    // считывание нажатия клавши
    int key = e->key();
    // направить змею по нажатию
    // соответствующей клавиши:
    // "влево"
    if ((key == Qt::Key_Left) && (!rightDirection)) {
        leftDirection   =  true;
        upDirection     = false;
        downDirection   = false;
    }
    // "вправо"
    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection  =  true;
        upDirection     = false;
        downDirection   = false;
    }
    // "вверх"
    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection     =  true;
        rightDirection  = false;
        leftDirection   = false;
    }
    // "вниз"
    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection   =  true;
        rightDirection  = false;
        leftDirection   = false;
    }

    // функция-обработчик события нажатия кнопки.
    QWidget::keyPressEvent(e);

}

// Устанавливает таймер
void Snake::setTimer() {

    timer_id = startTimer(DELAY);

}
