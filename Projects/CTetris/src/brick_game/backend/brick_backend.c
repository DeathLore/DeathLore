#include "brick_backend.h"

GameInfo_t* getGameObject() {
  static GameInfo_t GameObject = {0};

  return &GameObject;
}

GameInfo_t updateCurrentState() { return *getGameObject(); }

void deleteGameField(GameInfo_t* GameObject) {
  for (int rows = 0; rows < BOARD_Y; ++rows) free(GameObject->field[rows]);
  free(GameObject->field);
}