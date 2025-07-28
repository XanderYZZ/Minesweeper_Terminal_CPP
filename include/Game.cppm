export module Game;

export class Game
{
public:
    Game(int difficulty);
    ~Game() = default;
    void Start();

private:
    std::vector<std::vector<int>> board;
    int difficulty = 0;
    int total_mines = 0;
};