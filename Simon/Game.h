#ifndef GAME_H
#define GAME_H

#include <vector>

class Game
{
    unsigned long currentPosition;
    std::vector<bool> sequence;
  public:
    void startGame();
    int isCorrect(bool color); // false is blue, true is red. Returns percent done or -1 if wrong.
    void addToSequence();
    bool getNext();
    bool sequenceDone();
    int getSize();
};

#endif // GAME_H
