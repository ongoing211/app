#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QPixmap>

#include <cmath>

class Image {
    cv::Mat imgMat;
    int h;
    int w;

    std::string path {"undef"};

public:
    Image() = default;
    Image(const std::string& location) {
        this->load(location);
    }

    void load(const std::string& location) {
        path = location;
        imgMat = cv::imread(path, CV_LOAD_IMAGE_UNCHANGED);
        cv::cvtColor(imgMat, imgMat, CV_BGR2RGB);

        w = imgMat.cols;
        h = imgMat.rows;
    }

    void save() const {
        cv::imwrite(path, imgMat);
    }

    void save(const std::string& location) {
        path = location;
        cv::imwrite(location, imgMat);
    }

    void apply2DFilter(const cv::Mat kernel, int ddepth, int delta) {
        cv::Mat src = imgMat;
        cv::filter2D(src, imgMat, ddepth, kernel, cv::Point(-1,-1), delta);
    }
    void applyGaussianBlur(int w, int h) {
        cv::GaussianBlur(imgMat, imgMat, cv::Size(w,h), 0);
    }
    void applyMedianBlurring(int kernelSize) {
        cv::medianBlur(imgMat, imgMat, kernelSize);
    }
    void applySharp() {
        double m[3][3] = {{-1,-1,-1},
                          {-1, 9,-1},
                          {-1,-1,-1}};
        cv::Mat kernel(3,3,CV_64F, m);
        cv::filter2D(imgMat, imgMat, 0, kernel);
    }
    void changeSize(double coef) {
        w = static_cast<int>(static_cast<double>(w) * coef);
        h = static_cast<int>(static_cast<double>(h) * coef);

        cv::Mat original = imgMat;
        cv::resize(original, imgMat, cv::Size(w, h));
    }

    bool isLoaded() {
        if (path=="undef")
            return false;
        return true;
    }

    int getH() const {
        return h;
    }
    int getW() const {
        return w;
    }

    std::string getProps() const {
        std::string result;
        if (path == "undef") return "Image not loaded";

        result += "Path: " + path + '\n';
        result += "H: " + std::to_string(h) + "\nW: " + std::to_string(w);
        return result;
    }

    QPixmap toQPixmap() const{
        QImage rawImg(imgMat.data, w, h, QImage::Format_RGB888);
        return QPixmap::fromImage(rawImg);
    }
};

#endif // IMAGE_H
