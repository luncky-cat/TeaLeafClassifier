#include <QtWidgets/QMainWindow>
#include <QStackedWidget>
#include "global.h"
#include "ui_MainWindow.h"
#include "modelTrainingPage.h"
#include "speciesIdentification.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void init();   //初始化部件
    void connectSignals();  //链接信号
    void loadModel();
private slots:
    void switchToPage1();  //切换到模型训练页面
    void switchToPage2();    //切换到种类识别页面
private:
    Ui::MainWindowClass ui;
};
