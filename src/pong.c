#include <stdio.h>

int rack1(int rack1_y, char key1);
int rack2(int rack2_y, char key1);

int ball_cord_x(int ball_x, int ball_speed_x);
int ball_cord_y(int ball_y, int ball_speed_y);
int f_ball_speed_y(int ball_y, int ball_speed_y);

void field(int rack1_y, int rack2_y, int ball_x, int ball_y, int scr1,
           int scr2);
char score(int x, int y, int s1, int s2);
char digit(int x, int y, int d);

void ending(int num1, int num2);

int main() {
  int rack1_y = 12;  //     координата ракетки 1
  int rack2_y = 12;  //     координата ракетки 2

  int ball_y = 13;  //     кaоордината мяча по у
  int ball_x = 39;  //     координата мяча по х

  int ball_speed_x = 1;  //     скорость мяча по х
  int ball_speed_y = 1;  //     скорсоть мяча по у

  char key1;  //     то, что ввел игрок

  int scr1 = 0;  //     результат игрока 1
  int scr2 = 0;  //   результат игрока 2

  field(rack1_y, rack2_y, ball_x, ball_y, scr1, scr2);

  while ((scr1 < 21) && (scr2 < 21)) {
    scanf("%c", &key1);
    fflush(stdin);  //   очищает поток ввода
    if ((key1 == 'a') || (key1 == 'z') || (key1 == 'k') || (key1 == 'm') ||
        (key1 == ' ')) {
      ball_speed_y = f_ball_speed_y(
          ball_y, ball_speed_y);  //    ударился ли мяч об верхнуюю /нижнюю стенки

      ball_x = ball_cord_x(ball_x, ball_speed_x);
      ball_y = ball_cord_y(ball_y, ball_speed_y);

      if (ball_x == 0) {  //   промазал ли или нет
        scr2++;
        ball_y = 13;
        ball_x = 39;
        ball_speed_x = 1;
      }
      if (ball_x == 79) {
        scr1++;
        ball_y = 13;
        ball_x = 39;
        ball_speed_x = -1;
      }

      rack1_y =
          rack1(rack1_y,
                key1);  //   считает новую координату ракетки после дейсвтий игрока;
      rack2_y = rack2(rack2_y, key1);

      if (ball_x == 1) {  //   опредиляет, попал ли игрок в ракетку и если да, то
        if ((rack1_y <= ball_y) && (ball_y <= rack1_y + 2))
            ball_speed_x = -ball_speed_x;
      }
        if (ball_x == 78) {  //   аналогично для случая с правой ракеткой
        if ((rack2_y <= ball_y) && (ball_y <= rack2_y + 2))
          ball_speed_x = -ball_speed_x;
      }

      field(rack1_y, rack2_y, ball_x, ball_y, scr1, scr2);
    }
  }
  ending(scr1, scr2);
  return 0;
}

int f_ball_speed_y(int ball_y, int ball_speed_y) {
  int buf = ball_speed_y;
  if ((ball_y < 2) || (ball_y > 22))
    buf = -ball_speed_y;
  return buf;
}

int ball_cord_x(int ball_x, int ball_speed_x) { return ball_x + ball_speed_x; }

int ball_cord_y(int ball_y, int ball_speed_y) { return ball_y + ball_speed_y; }

int rack1(int rack1_y, char key1) {
  int buf = rack1_y;

  if (key1 == 'z') {
    if (rack1_y == 21)
      buf = rack1_y;
    else
      buf = ++rack1_y;
  }
  if (key1 == 'a') {
    if (rack1_y == 1)
      buf = rack1_y;
    else
      buf = --rack1_y;
  }
  if (key1 == ' ')
    buf = rack1_y;
  return buf;
}

int rack2(int rack2_y, char key1) {
  int buf = rack2_y;

  if (key1 == 'm') {
    if (rack2_y == 21)
      buf = rack2_y;
    else
      buf = ++rack2_y;
  }
  if (key1 == 'k') {
    if (rack2_y == 1)
      buf = rack2_y;
    else
      buf = --rack2_y;
  }
  if (key1 == ' ')
    buf = rack2_y;
  return buf;
}

void field(int rack1_y, int rack2_y, int ball_x, int ball_y, int scr1,
           int scr2) {
  char border = '-';
  char ball = 'O';
  char racket = 'H';
  char line = '|';
  printf("\33[0d\33[2J");   //   удаляет предыдущий кадр в коносли
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 80; j++) {
      if (i == 0 || i == 24) {
        printf("%c", border);
      } else if (j == ball_x && i == ball_y) {
        printf("%c", ball);
      } else if ((j == 0) && (i - rack1_y < 3) && (i - rack1_y >= 0)) {
        printf("%c", racket);
      } else if ((j == 79) && (i - rack2_y < 3) && (i - rack2_y >= 0)) {
        printf("%c", racket);
      } else if (j == 39) {
        printf("%c", line);
      } else {
          printf("%c", score(j, i, scr1, scr2));
      }
    }
    printf("\n");
  }
}

char score(int x, int y, int s1, int s2) {
  char res = ' ';  //    символ, который будем возвращать

  if ((y >= 4) && (y <= 8)) {  //    проверка на поля счета по y
    if ((x >= 27) && (x <= 29)) {
      x = x - 26;   //   преобразуем базис (левая часть левого тобло)
      y = y - 3;
      res = digit(x, y, s1 / 10);
    } else if ((x >= 33) && (x <= 35)) {
      x = x - 32;    //   преобразуем базис (правая часть левого тобло)
      y = y - 3;
      res = digit(x, y, s1 - (s1 / 10) * 10);
    } else if ((x >= 43) && (x <= 45)) {
      x = x - 42;    //   преобразуем базис (левая часть правого тобло)
      y = y - 3;
      res = digit(x, y, s2 / 10);
    } else if ((x >= 49) && (x <= 51)) {
      x = x - 48;   //   преобразуем базис (правая часть правого тобло)
      y = y - 3;
      res = digit(x, y, s2 - (s2 / 10) * 10);
    }
  }
  return res;
}

char digit(int x, int y, int d) {  //    отрисовка одного табло по относит. координатам
  char res = ' ';   //    символ, который будем возвращать (пробел по дефолту!)
  char buf = '*';   //    буфер с символом (чтобы поменять в одном месте, если что)

  switch (d) {
  case 0:
    if ((x == 1) || (x == 3))
      res = buf;
    else if ((y == 1) || (y == 5))
      res = buf;
    break;
  case 1:
    if (x == 3)
      res = buf;
    else if ((x == 2) && (y == 1))
      res = buf;
    break;
  case 2:
    if ((y == 1) || (y == 3) || (y == 5))
      res = buf;
    else if (((x == 3) && (y == 2)) || ((x == 1) && (y == 4)))
      res = buf;
    break;
  case 3:
    if ((y == 1) || (y == 3) || (y == 5))
      res = buf;
    else if (x == 3)
      res = buf;
    break;
  case 4:
    if (y == 3)
      res = buf;
    else if (x == 3)
      res = buf;
    else if ((x == 1) && (y < 3))
      res = buf;
    break;
  case 5:
    if ((y == 1) || (y == 3) || (y == 5))
      res = buf;
    else if (((x == 1) && (y == 2)) || ((x == 3) && (y == 4)))
      res = buf;
    break;
  case 6:
    if (x == 1)
      res = buf;
    else if ((y == 1) || (y == 3) || (y == 5))
      res = buf;
    else if ((x == 3) && (y == 4))
      res = buf;
    break;
  case 7:
    if (y == 1)
      res = buf;
    else if ((x == 2) && (y >= 3))
      res = buf;
    else if (y == 2 && x == 3)
      res = buf;
    break;
  case 8:
    if ((x == 1) || (x == 3))
      res = buf;
    else if ((y == 1) || (y == 3) || (y == 5))
      res = buf;
    break;
  case 9:
    if (x == 3)
      res = buf;
    else if ((y == 1) || (y == 3) || (y == 5))
      res = buf;
    else if ((x == 1) && (y == 2))
      res = buf;
    break;
  }
  return res;
}

void ending(int num1, int num2) {
  char hash_sign = '#';
  char border = '-';

  for (int y = 0; y < 25; y++) {
    for (int x = 0; x < 80; x++) {
        if ((y == 0) || (y == 24)) {
        printf("%c", border);
        } else if (y == 3 && num1 == 21) {
        if ((x > 18) && (x < 24))
          printf("%c", hash_sign);
        else if ((x == 27) || (x == 39) || (x == 43) || (x == 63))
          printf("%c", hash_sign);
        else if ((x > 33) && (x < 36))
          printf("%c", hash_sign);
        else if ((x > 45) && (x < 50))
          printf("%c", hash_sign);
        else if ((x > 51) && (x < 56))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if ((y == 4) && (num1 == 21)) {
        if ((x == 19) || (x == 24) || (x == 27) || (x == 33) || (x == 36) ||
            (x == 39) || (x == 43) || (x == 46) || (x == 52) || (x == 56) ||
            (x == 62) || (x == 63))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if ((y == 5) && (num1 == 21)) {
        if ((x == 19) || (x == 24) || (x == 27) || (x == 33) || (x == 36) ||
            (x == 39) || (x == 43) || (x == 46) || (x == 52) || (x == 56) ||
            (x == 61) || (x == 63))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 6 && num1 == 21) {
        if ((x == 19) || (x == 24) || (x == 27) || (x == 33) || (x == 36) ||
            (x == 40) || (x == 42) || (x == 46) || (x == 52) || (x == 56) ||
            (x == 63))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 7 && num1 == 21) {
        if ((x == 27) || (x == 41) || (x == 63))
          printf("%c", hash_sign);
        else if ((x > 18) && (x < 24))
          printf("%c", hash_sign);
        else if ((x > 32) && (x < 37))
          printf("%c", hash_sign);
        else if ((x > 45) && (x < 49))
          printf("%c", hash_sign);
        else if ((x > 51) && (x < 56))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 8 && num1 == 21) {
        if ((x == 19) || (x == 27) || (x == 33) || (x == 36) || (x == 41) ||
            (x == 46) || (x == 52) || (x == 53) || (x == 63))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 9 && num1 == 21) {
        if ((x == 19) || (x == 27) || (x == 33) || (x == 36) || (x == 41) ||
            (x == 46) || (x == 52) || (x == 54) || (x == 63))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 10 && num1 == 21) {
        if ((x == 19) || (x == 33) || (x == 36) || (x == 41) || (x == 52) ||
            (x == 55) || (x == 56))
          printf("%c", hash_sign);
        else if ((x > 26) && (x < 31))
          printf("%c", hash_sign);
        else if ((x > 45) && (x < 50))
          printf("%c", hash_sign);
        else if ((x > 60) && (x < 66))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if ((y == 3) && (num2 == 21)) {
        if ((x > 18) && (x < 24))
          printf("%c", hash_sign);
        else if ((x == 27) || (x == 39) || (x == 43) || (x == 63) || (x == 62))
          printf("%c", hash_sign);
        else if ((x > 33) && (x < 36))
          printf("%c", hash_sign);
        else if ((x > 45) && (x < 50))
          printf("%c", hash_sign);
        else if ((x > 51) && (x < 56))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if ((y == 4) && (num2 == 21)) {
        if ((x == 19) || (x == 24) || (x == 27) || (x == 33) || (x == 36) ||
            (x == 39) || (x == 43) || (x == 46) || (x == 52) || (x == 56) ||
            (x == 61) || (x == 65))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if ((y == 5) && (num2 == 21)) {
        if ((x == 19) || (x == 24) || (x == 27) || (x == 33) || (x == 36) ||
            (x == 39) || (x == 43) || (x == 46) || (x == 52) || (x == 56) ||
            (x == 61) || (x == 65))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if ((y == 6) && (num2 == 21)) {
        if ((x == 19) || (x == 24) || (x == 27) || (x == 33) || (x == 36) ||
            (x == 40) || (x == 42) || (x == 46) || (x == 52) || (x == 56) ||
            (x == 65))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if ((y == 7) && (num2 == 21)) {
        if ((x == 27) || (x == 41) || (x == 65))
          printf("%c", hash_sign);
        else if ((x > 18) && (x < 24))
          printf("%c", hash_sign);
        else if ((x > 32) && (x < 37))
          printf("%c", hash_sign);
        else if ((x > 45) && (x < 49))
          printf("%c", hash_sign);
        else if ((x > 51) && (x < 56))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if ((y == 8) && (num2 == 21)) {
        if ((x == 19) || (x == 27) || (x == 33) || (x == 36) || (x == 41) ||
            (x == 46) || (x == 52) || (x == 53) || (x == 63))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if ((y == 9) && (num2 == 21)) {
        if ((x == 19) || (x == 27) || (x == 33) || (x == 36) || (x == 41) ||
            (x == 46) || (x == 52) || (x == 54) || (x == 62))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if ((y == 10) && (num2 == 21)) {
        if ((x == 19) || (x == 33) || (x == 36) || (x == 41) || (x == 52) ||
            (x == 55) || (x == 56))
          printf("%c", hash_sign);
        else if ((x > 26) && (x < 31))
          printf("%c", hash_sign);
        else if ((x > 45) && (x < 50))
          printf("%c", hash_sign);
        else if ((x > 60) && (x < 66))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 13) {    //    вторая строка
        if ((x == 28) || (x == 36) || (x == 46) || (x == 50))
          printf("%c", hash_sign);
        else if ((x > 39) && (x < 43))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 14 || y == 15) {
        if ((x == 28) || (x == 36) || (x == 39) || (x == 43) || (x == 46) ||
            (x == 50))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 16) {
        if ((x == 28) || (x == 47) || (x == 36) || (x == 39) || (x == 43) ||
            (x == 46) || (x == 50))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 17) {
        if ((x == 28) || (x == 32) || (x == 48) || (x == 36) || (x == 39) ||
            (x == 43) || (x == 46) || (x == 50))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 18) {
        if ((x == 29) || (x == 32) || (x == 49) || (x == 35) || (x == 39) ||
            (x == 43) || (x == 46) || (x == 50))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 19) {
        if ((x == 30) || (x == 32) || (x == 34) || (x == 39) || (x == 43) ||
            (x == 46) || (x == 50))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else if (y == 20) {
        if ((x == 31) || (x == 33) || (x == 46) || (x == 50))
          printf("%c", hash_sign);
        else if ((x > 39) && (x < 43))
          printf("%c", hash_sign);
        else
          printf(" ");
      } else {
        printf(" ");
      }
    }

    printf("\n");
  }
}


