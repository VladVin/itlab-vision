#include "photoeffects.hpp"
#include <stdlib.h>

#include "photoeffects.hpp"
#include <iostream>

using namespace cv;
using namespace std;

const char *helper =
"boost_color <img> <intensity>\n\
\t<img> - file name contained the source image, must be 3-channel, RGB-image\n\
\t<intensity> - intensity of boost color filter, must be real number from 0.0 to 1.0\n\
";

int processArguments(int argc, char **argv, Mat &img, float &intensity);

int main(int argc, char **argv)
{
    const char *srcImgWinName = "Initial image", *dstImgWinName = "Processed image";
    Mat img, dstImg;
    float intensity;
    if (processArguments(argc, argv, img, intensity) != 0)
    {
        cout << helper << endl;
        return 1;
    }
    int opRes = boost_color(img, dstImg, intensity);
    switch (opRes)
    {
        case 1:
            cout << "Incorrect image type." << endl;
            return 2;
        case 2:
            cout << "Incorrect value of intensity" << endl;
            return 2;
    }

    namedWindow(srcImgWinName);
    namedWindow(dstImgWinName);
    imshow(srcImgWinName, img);
    imshow(dstImgWinName, dstImg);
    waitKey();
    destroyAllWindows();
    return 0;
}

int processArguments(int argc, char **argv, Mat &img, float &intensity)
{
    if (argc < 3)
    {
        return 1;
    }
    img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    intensity = atof(argv[2]);
    return 0;
}