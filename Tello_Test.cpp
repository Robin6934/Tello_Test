#include "Tello_Test.h"

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
