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
	void init();   //��ʼ������
	void connectSignals();  //�����ź�
	void disSpecie(int index);    //����Ԥ����������������������࣬����ʾ
private slots:
	void uploadFile();    //�ϴ��ļ�
	void startTest();   //��ʼ���
private:
	Ui::speciesIdentificationClass ui;
	std::vector<std::string> filePaths;  // ͼ��·��
	int sum;   //�ļ�����
	QStandardItemModel model;  //������ʾ
};
