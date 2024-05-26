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
	void init();   //��ʼ������
	void connectSignals();  //�����ź�
private slots:
	void uploadFile();    //�ϴ��ļ�
	void trainModelSlot();   //ģ��ѵ��
private:
	Ui::modelTrainingPageClass ui;
	std::vector<std::string> filePaths;  // ͼ��·��
	std::vector<std::vector<float>> featureVectors;  // ��������
	std::vector<int> labels;  // ��ǩ
	int sum;
	QStandardItemModel model;
};
