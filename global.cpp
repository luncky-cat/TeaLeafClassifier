#include "global.h"
#include <QtWidgets/qmessagebox.h>
Ptr<SVM> svm;   //模型指针
string modelFile="model\\svm_model.xml";   //模型路径
map<string, TeaInfo> tea_map;

// 获取文件路径
void getFilePathsInDirectory(const string& directoryPath, vector<string>& filePaths) {
    filePaths.clear();
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            cout << "File path: " << entry.path() << endl;
            filePaths.emplace_back(entry.path().string());
        }
    }
    cout << "Total number of files: " << filePaths.size() << endl;
}

// 图像预处理
void preprocessImage(const Mat& image, Mat& result) {
    resize(image, result, Size(400, 400));
    GaussianBlur(result, result, Size(5, 5), 0);
}

// LBP 纹理特征提取函数
Mat extractLBPTextureFeatures(const Mat& image, int numPoints, int radius) {
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    Mat lbpimage = Mat::zeros(gray.size(), CV_32FC1);

    for (int y = radius; y < gray.rows - radius; y++) {
        for (int x = radius; x < gray.cols - radius; x++) {
            float center = static_cast<float>(gray.at<uchar>(y, x));
            int code = 0;
            for (int i = 0; i < numPoints; i++) {
                double angle = i * (360.0 / numPoints);
                int x_offset = static_cast<int>(radius * cos(angle * CV_PI / 180.0));
                int y_offset = static_cast<int>(radius * sin(angle * CV_PI / 180.0));
                int neighbor_x = x + x_offset;
                int neighbor_y = y + y_offset;
                if (static_cast<float>(gray.at<uchar>(neighbor_y, neighbor_x)) >= center) {
                    code |= (1 << i); // 使用左移操作符构建二进制码
                }
            }
            lbpimage.at<float>(y, x) = static_cast<float>(code);
        }
    }
    return lbpimage;
}

// 特征 向量标准化
void normalizeFeatures(vector<float>& featureVector) {
    if (!featureVector.empty()) {
        float mean = std::accumulate(featureVector.begin(), featureVector.end(), 0.0) / featureVector.size();
        float sumSq = 0.0;
        for (float value : featureVector) {
            sumSq += (value - mean) * (value - mean);
        }
        float stdDev = sqrt(sumSq / featureVector.size());
        for (float& value : featureVector) {
            value = (value - mean) / stdDev;
        }
    }
}

vector<float> ImageProcessing(Mat& image)           //处理单个图像
{
    // 声明临时变量
    Mat processedImage, lbpFeatures;
        if (!image.empty()) {
            // 图像预处理
            preprocessImage(image, processedImage);
            // 提取 LBP 特征
            lbpFeatures = extractLBPTextureFeatures(processedImage, 8, 1);
            // 特征向量化
            vector<float> featureVector(lbpFeatures.begin<float>(), lbpFeatures.end<float>());
            // 标准化
            normalizeFeatures(featureVector);

            return featureVector;
        }
}

// 训练模型
void trainModel(const vector<vector<float>>& featureVectors, const vector<int>& labels, const string& modelFile) {
    if (featureVectors.empty() || labels.empty()) {
        cout << "Empty feature vectors or labels." << endl;
        return;
    }
    Mat trainingDataMat(labels.size(), featureVectors[0].size(), CV_32FC1);
    for (size_t i = 0; i < featureVectors.size(); ++i) {
        for (size_t j = 0; j < featureVectors[i].size(); ++j) {
            trainingDataMat.at<float>(i, j) = featureVectors[i][j];
        }
    }
    Mat labelsMat(labels.size(),1, CV_32SC1);
    for (size_t i = 0; i < labels.size(); ++i) {
        labelsMat.at<int>(i, 0) = labels[i];
    }
    Ptr<TrainData> trainData = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);  //制作训练数据
    if (svm.empty()) {    //不存在模型
        try {
            svm = Algorithm::load<SVM>(modelFile);
        }
        catch (const cv::Exception& e) {
            if (svm.empty()) {
                svm = SVM::create();
                svm->setType(SVM::C_SVC);
                svm->setKernel(SVM::LINEAR);
                svm->setC(1.0);
                svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
                QMessageBox::information(nullptr, "提示", "开始");
                svm->train(trainData);
                svm->save(modelFile);
                cout << "Model saved to " << modelFile << endl;
            }
        }
    }
}

// 预测类别
int predictCategory(vector<float>& featureMat, const string& modelFile) {
    if (svm.empty()) {
       svm = Algorithm::load<SVM>(modelFile);
    }
    return svm->predict(featureMat);
}







