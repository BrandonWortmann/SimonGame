#include "Game.h"
#include <vector>

using namespace std;

void Game::startGame()
{
    currentPosition = 0;
    sequence.clear();
    sequence.push_back(rand() % 2);
}

// false is blue, true is red. Returns percent done or -1 if wrong.
int Game::isCorrect(bool color)
{
    assert(currentPosition <= sequence.size());
    if (sequence[currentPosition] == color)
    {
        return (int)(((double)++currentPosition / (double)sequence.size()) * 100);
    }
    return -1;
}

void Game::addToSequence()
{
    currentPosition = 0;
    sequence.push_back(rand() % 2);
}

bool Game::getNext()
{
    return sequence[currentPosition++];
}

bool Game::sequenceDone()
{
    if (currentPosition >= sequence.size())
    {
        currentPosition = 0;
        return true;
    }
    return false;
}

int Game::getSize()
{
    return (int)sequence.size();
}
