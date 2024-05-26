#include "MainWindow.h"
#include <QStackedWidget>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qfiledialog.h>
#include<QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    init();
    connectSignals();
}

MainWindow::~MainWindow()
{}

void MainWindow::init() {
    // 创建 Page_0
    QWidget* Page_0 = new QWidget;

    // 加载背景图片到 QLabel 中
    QPixmap Pixmap("images/main.jpg");
    QPainter painter(&Pixmap);
    QFont font;
    font.setPointSize(80); // 根据需要调整字体大小
    painter.setFont(font);
    painter.drawText(Pixmap.rect(), Qt::AlignCenter,"茶叶种类识别系统");

    QLabel* backgroundLabel = new QLabel;
    backgroundLabel->setPixmap(Pixmap);
    backgroundLabel->setScaledContents(true); // 缩放图片以适应 QLabel 大小
    // 获取页面大小
    int pageWidth = ui.stackedWidget->width();
    int pageHeight = ui.stackedWidget->height();
    // 设置 QLabel 的大小为页面大小
    backgroundLabel->setFixedSize(pageWidth, pageHeight);
    // 将 QLabel 添加到页面中
    QVBoxLayout* layout = new QVBoxLayout(Page_0);
    layout->addWidget(backgroundLabel);

      Page_0->setLayout(layout);
      ui.stackedWidget->addWidget(Page_0);

      modelTrainingPage *Page1 = new modelTrainingPage;
      ui.stackedWidget->addWidget(Page1);
      speciesIdentification* Page2 = new speciesIdentification;
      ui.stackedWidget->addWidget(Page2);
}

void MainWindow::switchToPage1()
{
    ui.stackedWidget->setCurrentIndex(1);
}

void MainWindow::switchToPage2()
{
    ui.stackedWidget->setCurrentIndex(2);
}


void MainWindow::connectSignals() 
{
    connect(ui.swp1,&QPushButton::clicked, this, &MainWindow::switchToPage1);
    connect(ui.swp2,&QPushButton::clicked, this,&MainWindow::switchToPage2);
    connect(ui.swp3, &QPushButton::clicked,this,&MainWindow::loadModel);
}

void MainWindow::loadModel()
{
    QMessageBox msgBox;
    msgBox.addButton("加载本地文件", QMessageBox::AcceptRole); 
    msgBox.addButton("创建模型文件", QMessageBox::RejectRole);
    msgBox.setDefaultButton(QMessageBox::Cancel); 
    int selectedOption = msgBox.exec();
    if (selectedOption == QMessageBox::AcceptRole) {   //加载本地模型
        //打开文件选择
         QString path=QFileDialog::getOpenFileName(nullptr, tr("Open File"), "", tr("Model Files (*.xml)"));
         modelFile = path.toStdString();
         svm = Algorithm::load<SVM>(modelFile);
         if (!svm.empty()) {   //模型加载成功
             QMessageBox::information(nullptr,"提示","本地模型加载成功");
         }
         else {
             QMessageBox::information(nullptr, "提示", "本地模型加载失败");
         }
    }
    else  if(selectedOption == QMessageBox::RejectRole){    //创建新的模型

    }
}

