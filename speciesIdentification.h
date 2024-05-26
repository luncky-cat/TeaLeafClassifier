#pragma execution_character_set("utf-8");
#include <QWidget>
#include "ui_speciesIdentification.h"
#include "global.h"
#include <QStandardItemModel>

class speciesIdentification : public QWidget
{
	Q_OBJECT

public:
	speciesIdentification(QWidget *parent = nullptr);
	~speciesIdentification();
private:
	void init();   //初始化部件
	void connectSignals();  //链接信号
	void disSpecie(int index);    //根据预测的种类编号来给出具体种类，并显示
private slots:
	void uploadFile();    //上传文件
	void startTest();   //开始检测
private:
	Ui::speciesIdentificationClass ui;
	std::vector<std::string> filePaths;  // 图像路径
	int sum;   //文件数量
	QStandardItemModel model;  //网格显示
};
