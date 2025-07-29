#include <iostream>
import Game;

int main()
{
    bool running = true;

    while (running)
    {
        Game game;
        game.Start();

        char choice;
        std::cout << "Do you want to play again? (y = yes, anything else = no): ";
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y')
        {
            running = false;
        }
    }

    return 0;
}