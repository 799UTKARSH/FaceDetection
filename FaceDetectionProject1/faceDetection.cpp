#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main() {
    // Load the cascade classifier file
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("C:/Users/BLACK HAT HACKER/Downloads/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade\n";
        return -1;
    }

    // Open the default camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video capture\n";
        return -1;
    }

    cv::Mat frame;
    while (cap.read(frame)) {
        if (frame.empty()) {
            std::cerr << "No captured frame\n";
            break;
        }

        std::vector<cv::Rect> faces;
        cv::Mat frame_gray;
        cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(frame_gray, frame_gray);

        // Detect faces
        face_cascade.detectMultiScale(frame_gray, faces);

        // Draw circles around detected faces
        for (size_t i = 0; i < faces.size(); i++) {
            cv::Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
            cv::ellipse(frame, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, cv::Scalar(255, 0, 255), 2);
        }

        // Display the frame
        cv::imshow("Face Detection", frame);

        if (cv::waitKey(10) == 27) { // Wait for 'esc' key press to exit
            break;
        }
    }

    return 0;
}
