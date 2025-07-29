#include <random>
#include <vector>
#include <unordered_map>
#include <utility>

export module Game;

export class Game
{
public:
    Game();
    ~Game() = default;
    void Start();

private:
    void PromptForDifficulty();
    void InitializeBoard();
    void PlaceMines();
    void PutAdjacentCounts();
    void RevealAdjacentCells(int row, int col);
    std::pair<int, int> GetRowAndCol();
    void RevealAllMines();
    bool CheckWinCondition();
    void DisplayBoard();

private:
    struct Cell
    {
        int row = 0, col = 0, adjacent_mines = 0;
        bool is_mine = false, is_revealed = false;

        Cell(int r, int c) : row(r), col(c), adjacent_mines(0), is_mine(false), is_revealed(false) {};
    };

    std::vector<std::vector<int>> directions = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0},
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1},
    };
    std::vector<std::vector<Cell>> board;
    std::random_device rd;
    std::mt19937 gen;

    int rows = 0, cols = 0, total_mines = 0, difficulty = 0;
};