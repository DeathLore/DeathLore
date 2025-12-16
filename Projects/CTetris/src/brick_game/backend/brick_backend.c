#include "./brick_backend.h"

GameInfo_t* getGameObject() {
  static GameInfo_t GameObject = {0};

  return &GameObject;
}

GameInfo_t updateCurrentState() { return *getGameObject(); }

void GameFieldCleanup(GameInfo_t* GameObject, const int board_y) {
  for (int rows = 0; rows < board_y; ++rows) free(GameObject->field[rows]);
  free(GameObject->field);
}

int readHighScoreInfo(BrickGame_t const ByGame) {
  int HighScore = 0;

  FILE* HighScoreFile = NULL;
  if (ByGame == TetrisGame) {
    fopen("./games_data/tetris.gd", "r");
  }

  if (HighScoreFile != NULL) {
    fscanf(HighScoreFile, "%d", &HighScore);
    fclose(HighScoreFile);
  } else
    HighScore = -1;

  return HighScore;
}

void saveHighScoreInfo(int HighScore, BrickGame_t const ByGame) {
  FILE* HighScoreFile = NULL;
  if (ByGame == TetrisGame) {
    fopen("./games_data/tetris.gd", "w");
  }

  if (HighScoreFile != NULL) { 
    fprintf(HighScoreFile, "%d", HighScore);
    fclose(HighScoreFile);
  }
}

void createHighScoreInfoStorage(BrickGame_t const ByGame) {
  struct stat avoidingError;
  if (stat("./games_data", &avoidingError) == -1) {
    mkdir("./games_data", 0700);
  }

  FILE* HighScoreFile = NULL;
  if (ByGame == TetrisGame) {
    fopen("./games_data/tetris.gd", "w");
  }
  if (HighScoreFile != NULL) {
    fprintf(HighScoreFile, "%d", 0);
    fclose(HighScoreFile);
  }
}