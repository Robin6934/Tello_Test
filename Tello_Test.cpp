#include "Tello_Test.h"

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/core/utils/logger.hpp>
int main()
{
    cv::VideoCapture capture{ "udp://0.0.0.0:11111", cv::CAP_FFMPEG };
    std::cout << cv::getVersionString();
    Tello tello;
    if (!tello.connect()) return 0;
    tello.enable_video_stream();

    while (true) {
        cv::Mat frame;
        capture >> frame;
        if (!frame.empty()) {
            cv::imshow("Tello Stream", frame);
        }
        if (cv::waitKey(1) == 27) {
            break;

        }
    }

    return 0;

    PRINTF_WARN("Tello is connected and about to take off and fly around! Are you ready? [Press Enter]");
    std::cin.get();

    tello.takeoff();

    while (true) {
        if (kbhit()) {
            char c = getch();
            switch (c) {
            case 'w':
                std::cout << "Forward" << std::endl;
                tello.move_forward(10);
                break;
            case 'a':
                std::cout << "Left" << std::endl;
                tello.move_left(10);
                break;
            case 's':
                std::cout << "Backward" << std::endl;
                tello.move_back(10);
                break;
            case 'd':
                std::cout << "Right" << std::endl;
                tello.move_right(10);
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
