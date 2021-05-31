#ifndef TST_TEST_H
#define TST_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

#include "../app/Snake.h"



TEST(game_init, normal) {
    Snake s;
    s.inGame = false;

    Snake(0);

    ASSERT_NE(s.inGame, true);
}



TEST(game_objects, normal) {
    Snake s;
    s.dots = 0;

    s.initGame();

    ASSERT_NE(s.dots, 0);
}



TEST(apple_spawn, normal) {
    Snake s;
    s.apple_x = -1;
    s.apple_y = -1;

    s.locateApple();

    ASSERT_NE(s.apple_x, -1);
    ASSERT_NE(s.apple_y, -1);
}



TEST(apple_check, eaten) {
    Snake s;
    s.dots = 5;

    s.apple_x = 5;
    s.apple_y = 5;

    s.x[0] = s.apple_x;
    s.y[0] = s.apple_y;

    s.checkApple();

    ASSERT_EQ(s.dots, 6);
    ASSERT_NE(s.apple_x, 5);
    ASSERT_NE(s.apple_y, 5);
}

TEST(apple_check, not_eaten) {
    Snake s;
    s.dots = 5;

    s.apple_x = 3;
    s.apple_y = 3;

    s.x[0] = 5;
    s.y[0] = 5;

    s.checkApple();

    ASSERT_EQ(s.dots, 5);
    ASSERT_EQ(s.apple_x, 3);
    ASSERT_EQ(s.apple_y, 3);
}

TEST(collision_check, small_snake_in_borders_and_not_bites_itself) {
    Snake s;
    s.inGame = true;

    s.setTimer();

    s.dots = 3;

    for (int z = 0; z < s.dots; z++) {
        s.x[z] = 50 - z * 10;
        s.y[z] = 50;
    }

    s.checkCollision();

    ASSERT_EQ(s.inGame, true);
}

TEST(collision_check, snake_in_borders_and_not_bites_itself) {
    Snake s;
    s.inGame = true;

    s.setTimer();

    s.dots = 5;

    for (int z = 0; z < s.dots; z++) {
        s.x[z] = 70 - z * 10;
        s.y[z] = 50;
    }

    s.checkCollision();

    ASSERT_EQ(s.inGame, true);
}

TEST(collision_check, in_borders_and_bites_itself) {
    Snake s;
    s.inGame = true;

    s.setTimer();

    s.dots = 7;

    s.x[6] = 70;
    s.y[6] = 40;
    s.x[5] = 70;
    s.y[5] = 50;
    s.x[4] = 70;
    s.y[4] = 60;
    s.x[3] = 60;
    s.y[3] = 60;
    s.x[2] = 60;
    s.y[2] = 50;
    s.x[1] = 60;
    s.y[1] = 40;
    s.x[0] = 70;
    s.y[0] = 40;

    s.checkCollision();

    ASSERT_EQ(s.inGame, false);
}

TEST(collision_check, out_of_left_border) {
    Snake s;
    s.inGame = true;

    s.setTimer();

    s.dots = 3;

    for (int z = 0; z < s.dots; z++) {
        s.x[z] = -10 + z * 10;
        s.y[z] = 50;
    }

    s.checkCollision();

    ASSERT_EQ(s.inGame, false);
}

TEST(collision_check, out_of_right_border) {
    Snake s;
    s.inGame = true;

    s.setTimer();

    s.dots = 3;

    for (int z = 0; z < s.dots; z++) {
        s.x[z] = 310 - z * 10;
        s.y[z] = 50;
    }

    s.checkCollision();

    ASSERT_EQ(s.inGame, false);
}

TEST(collision_check, out_of_up_border) {
    Snake s;
    s.inGame = true;

    s.setTimer();

    s.dots = 3;

    for (int z = 0; z < s.dots; z++) {
        s.x[z] = 50;
        s.y[z] = -10 + z * 10;
    }

    s.checkCollision();

    ASSERT_EQ(s.inGame, false);
}

TEST(collision_check, out_of_down_border) {
    Snake s;
    s.inGame = true;

    s.setTimer();

    s.dots = 3;

    for (int z = 0; z < s.dots; z++) {
        s.x[z] = 50;
        s.y[z] = 310 - z * 10;
    }

    s.checkCollision();

    ASSERT_EQ(s.inGame, false);
}

TEST(collision_check, game_has_alredy_ended) {
    Snake s;
    s.inGame = false;

    s.setTimer();

    s.dots = 3;

    for (int z = 0; z < s.dots; z++) {
        s.x[z] = 70 - z * 10;
        s.y[z] = 50;
    }

    s.checkCollision();

    ASSERT_EQ(s.inGame, false);
}



TEST(snake_movement, move_left) {
    Snake s;
    s.upDirection    = false;
    s.downDirection  = false;
    s.leftDirection  =  true;
    s.rightDirection = false;

    s.dots = 2;

    s.x[0] = 60;
    s.y[0] = 50;
    s.x[1] = 70;
    s.y[1] = 50;

    s.move();

    ASSERT_EQ(s.x[0], 50);
    ASSERT_EQ(s.x[1], 60);
}

TEST(snake_movement, move_right) {
    Snake s;
    s.upDirection    = false;
    s.downDirection  = false;
    s.leftDirection  = false;
    s.rightDirection =  true;

    s.dots = 2;

    s.x[0] = 70;
    s.y[0] = 50;
    s.x[1] = 60;
    s.y[1] = 50;

    s.move();

    ASSERT_EQ(s.x[0], 80);
    ASSERT_EQ(s.x[1], 70);
}

TEST(snake_movement, move_up) {
    Snake s;
    s.upDirection    =  true;
    s.downDirection  = false;
    s.leftDirection  = false;
    s.rightDirection = false;

    s.dots = 2;

    s.x[0] = 60;
    s.y[0] = 50;
    s.x[1] = 70;
    s.y[1] = 50;

    s.move();

    ASSERT_EQ(s.y[0], 40);
    ASSERT_EQ(s.y[1], 50);
}

TEST(snake_movement, move_down) {
    Snake s;
    s.upDirection    = false;
    s.downDirection  =  true;
    s.leftDirection  = false;
    s.rightDirection = false;

    s.dots = 2;

    s.x[0] = 60;
    s.y[0] = 50;
    s.x[1] = 70;
    s.y[1] = 50;

    s.move();

    ASSERT_EQ(s.y[0], 60);
    ASSERT_EQ(s.y[1], 50);
}


// устанавливает таймер
void setTimer();

#endif // TST_TEST_H
