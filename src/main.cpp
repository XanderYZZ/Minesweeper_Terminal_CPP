#include <iostream>
import Game;

int main()
{
    int difficulty = 0;

    while (difficulty < 1 || difficulty > 3)
    {
        std::cout << "Select the difficulty level for the game:\n1. Easy\n2. Medium\n3. Hard\nEnter your choice (1-3): ";
        std::cin >> difficulty;
    }

    Game game(difficulty);
    game.Start();

    return 0;
}