module Game;

Game::Game(int difficulty)
{
    int i = 0, j = 0;
    switch (difficulty)
    {
    case 1:
        i = 9;
        j = 9;
        total_mines = 10;
        break;

    case 2:
        i = 16;
        j = 16;
        total_mines = 40;
        break;

    case 3:
        i = 30;
        j = 16;
        total_mines = 99;
        break;
    }
}

void Game::Start()
{
}