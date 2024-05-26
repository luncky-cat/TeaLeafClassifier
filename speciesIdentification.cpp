#include "speciesIdentification.h"

#include <QPushButton>
#include <QtWidgets/qfiledialog.h>
#include<qmessagebox.h>
speciesIdentification::speciesIdentification(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
	connectSignals();
}

speciesIdentification::~speciesIdentification()
{}

void speciesIdentification::init()
{
	ui.pic->setFixedSize(200,200);

	ui.label_5->setAlignment(Qt::AlignCenter);
	ui.label_5->setStyleSheet("background-color:white");
	QFont font = ui.label_5->font();
	font.setPointSize(16);
	ui.label_5->setFont(font);

	ui.label->setAlignment(Qt::AlignCenter);
	ui.label->setStyleSheet("background-color:white");
	font = ui.label->font();
	font.setPointSize(16);
	ui.label->setFont(font);


	ui.re->setAlignment(Qt::AlignCenter);
	font = ui.re->font();
	font.setPointSize(16);
	ui.re->setFont(font);
	ui.re->setStyleSheet("background-color:white");

	ui.pic->setStyleSheet("background-color:black");

	ui.sum->setMinimumSize(120,40);
	ui.sum->setAlignment(Qt::AlignCenter);
	font = ui.sum->font();
	font.setPointSize(16);
	ui.sum->setFont(font);
	ui.sum->setStyleSheet("background-color:white");

	ui.tableView->verticalHeader()->setVisible(false);
	ui.tableView->horizontalHeader()->setVisible(false);
}

void speciesIdentification::connectSignals()
{
	connect(ui.p1,&QPushButton::clicked,this,&speciesIdentification::uploadFile);
	connect(ui.Q1, &QPushButton::clicked, this, &speciesIdentification::startTest);
}

void speciesIdentification::disSpecie(int index)
{
	for (auto& pair : tea_map) {
		if (pair.second.tea_id==index) {
			ui.re->setText(QString::fromStdString(pair.first));
			pair.second.frequency++;  //记录预测的次数
			return;
		}
	}
	ui.re->setText("未知");
}

void speciesIdentification::startTest()
{
	for (auto path:filePaths) {
		Mat image = imread(path);
		QPixmap pixmap(QString::fromStdString(path));
		ui.pic->setScaledContents(true);
		ui.pic->setPixmap(pixmap);
	    vector<float> featureVector=ImageProcessing(image);
	    int re=predictCategory(featureVector,"model\\svm_model.xml");
		QMessageBox::information(nullptr,"提示",QString::number(re));
		disSpecie(re);
	}

	int num_cols = tea_map.size();
	model.setRowCount(2);
	model.setColumnCount(num_cols);
	model.setItem(0, 0, new QStandardItem("种类"));
	model.setItem(1, 0, new QStandardItem("数量"));
	model.setItem(2, 0, new QStandardItem("实际"));
	int col = 1;
	for (const auto& pair : tea_map) {
		model.setItem(0, col, new QStandardItem(QString::fromStdString(pair.first)));
		model.setItem(1, col, new QStandardItem(QString::number(pair.second.frequency)));
		col++;
	}

	ui.tableView->setModel(&model);
}

void speciesIdentification::uploadFile() {
	filePaths.clear();
	QString filePath = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), "/");
	if (filePath.isEmpty()) {
		return;
	}
	getFilePathsInDirectory(filePath.toStdString(), filePaths);
	sum = filePaths.size();
	ui.sum->setText(QString::number(filePaths.size()));
	ui.sum->setStyleSheet("background - color:white");
}

