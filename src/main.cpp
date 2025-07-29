#include <print>
#include <iostream>
#include <string>
#include <string_view>
import Game;
import TextColors;

int main()
{
    bool running = true;

    while (running)
    {
        Game game;
        game.Start();

        char choice;
        std::print("{}Do you want to play again? ('y' or 'Y' = yes, anything else = no): ", WHITE);
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y')
        {
            running = false;
        }
    }

    return 0;
}