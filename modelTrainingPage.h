#pragma execution_character_set("utf-8");
#include "global.h"
#include "ui_modelTrainingPage.h"
#include <QWidget>
#include <QStandardItemModel>
class modelTrainingPage : public QWidget
{
	Q_OBJECT
public:
	modelTrainingPage(QWidget *parent = nullptr);
	~modelTrainingPage();
private:
	void init();   //初始化部件
	void connectSignals();  //链接信号
private slots:
	void uploadFile();    //上传文件
	void trainModelSlot();   //模型训练
private:
	Ui::modelTrainingPageClass ui;
	std::vector<std::string> filePaths;  // 图像路径
	std::vector<std::vector<float>> featureVectors;  // 特征向量
	std::vector<int> labels;  // 标签
	int sum;
	QStandardItemModel model;
};
