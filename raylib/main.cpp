#include "../include/IPlugin.hpp"
#include <cstdio>
#include <raylib.h>

#define BG_COLOR GetColor(0x42424242)
#define TILE_SIZE 32
#define SHIFT 0.1 * TILE_SIZE

class Plugin : public IPlugin {
private:
  int width;
  int height;

public:
  virtual ~Plugin() {}
  void open(int x, int y) {
    width = (x + 2) * TILE_SIZE;
    height = (y + 3) * TILE_SIZE;
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(width, height, "nibbler - raylib");
  }

  void close() { CloseWindow(); }

  Event poll_event() {

    int key = 42;
    while (key != 0) {
      key = GetKeyPressed();
      if (WindowShouldClose())
        key = KEY_ESCAPE;
      switch (key) {
      case KEY_LEFT:
        return LEFT;
      case KEY_RIGHT:
        return RIGHT;
      case KEY_UP:
        return UP;
      case KEY_DOWN:
        return DOWN;
      case KEY_ENTER:
        return ENTER;
      case KEY_ESCAPE:
        return CLOSE;
      case KEY_F1:
        return F1;
      case KEY_F2:
        return F2;
      case KEY_F3:
        return F3;
      default:
        break;
      }
    }
    return NONE;
  }

  void update_snake(const std::deque<Position> &snake, Direction direction) {
    auto pos = snake.begin();
    auto color = GetColor(0x21AA21FF);

    DrawRectangle((pos->x + 1) * TILE_SIZE,
                  (pos->y + 2) * TILE_SIZE,
				  TILE_SIZE, TILE_SIZE, BLACK);
    DrawCircle(TILE_SIZE * (pos->x + 1) + TILE_SIZE / 2.0,
               TILE_SIZE * (pos->y + 2) + TILE_SIZE / 2.0,
               (TILE_SIZE - 2 * SHIFT) / 2.0, color);
    for (++pos; pos != snake.end(); ++pos) {
      DrawRectangle((pos->x + 1) * TILE_SIZE + SHIFT,
                    (pos->y + 2) * TILE_SIZE + SHIFT, TILE_SIZE - SHIFT * 2.0,
                    TILE_SIZE - SHIFT * 2.0, color);
    }
  }

  void update_food(Position &pos)  {
    DrawRectangle((pos.x + 1) * TILE_SIZE,
                  (pos.y + 2) * TILE_SIZE,
				  TILE_SIZE, TILE_SIZE, BLACK);
    DrawCircle(TILE_SIZE * (pos.x + 1) + TILE_SIZE / 2.0,
               TILE_SIZE * (pos.y + 2) + TILE_SIZE / 2.0,
               (TILE_SIZE - 2 * SHIFT) / 2.0, RED);
  }

  void update_score(int n) {
    auto beg = width * 0.10;
    char score[10] = "";
    sprintf(score, ": %d", n);
    DrawRectangle(beg, 0.5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
    DrawText(score, beg + TILE_SIZE + SHIFT, 0.5 * TILE_SIZE, 32, WHITE);
  }

  void update_bestscore(int n) {
    auto beg = width * 0.3;
    char score[10] = "";
    sprintf(score, ": %d", n);
    DrawRectangle(beg, 0.5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
    DrawText(score, beg + TILE_SIZE + SHIFT, 0.5 * TILE_SIZE, 32,
             GetColor(0xFFD700FF));
  }

  void update_gameover() {
    Position beg = {static_cast<int>(0.2 * width), static_cast<int>(0.4 * height)};
    DrawRectangle(0, 0, width, height, GetColor(0x00000084));
    DrawRectangle(beg.x, beg.y, width - 2 * beg.x, 6 * TILE_SIZE, GetColor(0x131313FF));
    DrawText("Game Over", beg.x + TILE_SIZE * 1.8, beg.y + TILE_SIZE, 42, WHITE);
    DrawText("Press [Enter]", beg.x + TILE_SIZE * 2.7, beg.y + TILE_SIZE * 4, 22, WHITE);
  }

  void clear() {
    BeginDrawing();
    ClearBackground(BLACK);
    for (int x = 1; x < this->width / TILE_SIZE - 1; x++)

      for (int y = 2; y < this->height / TILE_SIZE - 1; y++)
        DrawRectangle(x * TILE_SIZE + SHIFT, y * TILE_SIZE + SHIFT,
                      TILE_SIZE - SHIFT * 2, TILE_SIZE - SHIFT * 2,
                      BG_COLOR);
  }

  void display() { EndDrawing(); }
};

extern "C" {
Plugin *game = NULL;

IPlugin *load() {
  try {
    if (game == NULL)
      game = new Plugin();
  } catch (...) {
    return NULL;
  }
  return game;
}

void unload() { delete game; }
}
