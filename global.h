#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <numeric>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace cv::ml;
namespace fs = std::filesystem;
using namespace std;

// 定义茶叶结构体
struct TeaInfo {
    int frequency;  // 出现的次数
    int tea_id;     // 茶叶编号
};

extern  map<string,TeaInfo> tea_map;
extern Ptr<SVM> svm;
extern string modelFile;

void getFilePathsInDirectory(const string& directoryPath, vector<string>& filePaths);
void preprocessImage(const Mat& image, Mat& result);
Mat extractLBPTextureFeatures(const Mat& image, int numPoints, int radius);
void normalizeFeatures(vector<float>& featureVector);
vector<float> ImageProcessing(Mat& image);
void trainModel(const vector<vector<float>>& featureVectors, const vector<int>& labels, const string& modelFile);
int predictCategory(vector<float>& featureMat, const string& modelFile);

#endif // !GLOBAL_H
