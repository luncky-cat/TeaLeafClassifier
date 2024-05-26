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
    // ���� Page_0
    QWidget* Page_0 = new QWidget;

    // ���ر���ͼƬ�� QLabel ��
    QPixmap Pixmap("images/main.jpg");
    QPainter painter(&Pixmap);
    QFont font;
    font.setPointSize(80); // ������Ҫ���������С
    painter.setFont(font);
    painter.drawText(Pixmap.rect(), Qt::AlignCenter,"��Ҷ����ʶ��ϵͳ");

    QLabel* backgroundLabel = new QLabel;
    backgroundLabel->setPixmap(Pixmap);
    backgroundLabel->setScaledContents(true); // ����ͼƬ����Ӧ QLabel ��С
    // ��ȡҳ���С
    int pageWidth = ui.stackedWidget->width();
    int pageHeight = ui.stackedWidget->height();
    // ���� QLabel �Ĵ�СΪҳ���С
    backgroundLabel->setFixedSize(pageWidth, pageHeight);
    // �� QLabel ��ӵ�ҳ����
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
    msgBox.addButton("���ر����ļ�", QMessageBox::AcceptRole); 
    msgBox.addButton("����ģ���ļ�", QMessageBox::RejectRole);
    msgBox.setDefaultButton(QMessageBox::Cancel); 
    int selectedOption = msgBox.exec();
    if (selectedOption == QMessageBox::AcceptRole) {   //���ر���ģ��
        //���ļ�ѡ��
         QString path=QFileDialog::getOpenFileName(nullptr, tr("Open File"), "", tr("Model Files (*.xml)"));
         modelFile = path.toStdString();
         svm = Algorithm::load<SVM>(modelFile);
         if (!svm.empty()) {   //ģ�ͼ��سɹ�
             QMessageBox::information(nullptr,"��ʾ","����ģ�ͼ��سɹ�");
         }
         else {
             QMessageBox::information(nullptr, "��ʾ", "����ģ�ͼ���ʧ��");
         }
    }
    else  if(selectedOption == QMessageBox::RejectRole){    //�����µ�ģ��

    }
}

