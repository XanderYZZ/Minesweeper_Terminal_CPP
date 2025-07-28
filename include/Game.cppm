module;

#include <random>

export module Game;

export class Game
{
public:
    Game(int difficulty);
    ~Game() = default;
    void Start();

private:
    void InitializeBoard();
    void DisplayBoard();

private:
    std::vector<std::vector<int>> board;
    int difficulty = 0;
    int total_mines = 0;
    std::random_device rd;
    std::mt19937 gen;
};