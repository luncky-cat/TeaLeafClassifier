#include "global.h"
#include "modelTrainingPage.h"
#include<qpushbutton.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qmessagebox.h>

modelTrainingPage::modelTrainingPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
	connectSignals();
}

modelTrainingPage::~modelTrainingPage()
{}

void modelTrainingPage::init()
{
	ui.label_1->setAlignment(Qt::AlignCenter);
	QFont font = ui.label_1->font();
	ui.label_1->setStyleSheet("background-color:white");

	ui.sum->setMinimumSize(120,40);
	ui.sum->setStyleSheet("background-color:white");
	ui.sum->setAlignment(Qt::AlignCenter);

	ui.tableView->verticalHeader()->setVisible(false);
	ui.tableView->horizontalHeader()->setVisible(false);
}

void modelTrainingPage::connectSignals()
{
	connect(ui.p1,&QPushButton::clicked,this, &modelTrainingPage::uploadFile);
	connect(ui.p2, &QPushButton::clicked, this, &modelTrainingPage::trainModelSlot);
}

void modelTrainingPage::uploadFile()    
{

	QString filePath =QFileDialog::getExistingDirectory(this, tr("ѡ���ļ���"), "/");
	if (filePath.isEmpty()) {
		return;
	}
	filePaths.clear();  //����ļ�·��
	for (auto& pair : tea_map) {
		pair.second.frequency = 0;
	}
	getFilePathsInDirectory(filePath.toStdString(),filePaths);
	this->sum = filePaths.size();
	ui.sum->setText(QString::number(filePaths.size()));
}

void modelTrainingPage::trainModelSlot()  
{
	featureVectors.clear();//�������
	labels.clear();
	for (const auto& filePath : filePaths) {
		Mat image = imread(filePath);
		featureVectors.push_back(ImageProcessing(image));
		bool flag = true;
		for (auto& pair : tea_map) {
			if (filePath.find(pair.first) != std::string::npos) {  
				labels.push_back(pair.second.tea_id);
				pair.second.frequency++;
				flag = false;
				break;
			}
		}
		if (flag) {

			labels.push_back(-1);
		}
	}

	int num_cols = tea_map.size();
	model.setColumnCount(num_cols+2);
	model.setItem(0, 0, new QStandardItem("����"));
	model.setItem(1, 0, new QStandardItem("����"));
	int col = 1;
	for (const auto& pair : tea_map) {
		sum -= pair.second.frequency;
		model.setItem(0, col, new QStandardItem(QString::fromStdString(pair.first)));
		model.setItem(1, col, new QStandardItem(QString::number(pair.second.frequency)));
		col++;
	}
	model.setItem(1,col-1, new QStandardItem(QString::number(sum)));
	ui.tableView->setModel(&model);
	trainModel(featureVectors, labels, "model\\svm_model.xml");	// ѵ��ģ�Ͳ�����
	QMessageBox::information(nullptr,"��ʾ","ģ��ѵ�����");
}