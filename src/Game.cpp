module Game;

Game::Game(int difficulty)
{
    this->difficulty = difficulty;
    Game::InitializeBoard();
}

void Game::InitializeBoard()
{
    int rows = 0, cols = 0;
    switch (difficulty)
    {
    case 1:
        rows = 9;
        cols = 9;
        total_mines = 10;
        break;

    case 2:
        rows = 16;
        cols = 16;
        total_mines = 40;
        break;

    case 3:
        rows = 30;
        cols = 16;
        total_mines = 99;
        break;
    }

    for (int i = 0; i < rows; i++) {
        std::vector<int> row(cols, 0);
        board.push_back(row);
    }
}

void Game::Start()
{

}