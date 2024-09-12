// Tello_Test.cpp : Defines the entry point for the application.
//

#include "Tello_Test.h"

#include <tello.hpp>
#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

int main()
{
    Tello tello;

    if (!tello.connect()) {
        return 1;
    }

    PRINTF_WARN("Tello is connected and about to take off and fly around! Are you ready? [Press Enter]");
    std::cin.get();

    tello.takeoff();

    while (true) {
        if (kbhit()) {
            char c = getch();
            switch (c) {
            case 'w':
                std::cout << "Forward" << std::endl;
                tello.move_forward(1);
                break;
            case 'a':
                std::cout << "Left" << std::endl;
                tello.move_left(1);
                break;
            case 's':
                std::cout << "Backward" << std::endl;
                tello.move_back(1);
                break;
            case 'd':
                std::cout << "Right" << std::endl;
                tello.move_right(1);
                break;
            case 27:
                std::cout << "Exit" << std::endl;
                tello.land();
                return 0;
            default:
                std::cout << "Invalid input" << std::endl;
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
	return 0;
}
