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
    void init();   //��ʼ������
    void connectSignals();  //�����ź�
    void loadModel();
private slots:
    void switchToPage1();  //�л���ģ��ѵ��ҳ��
    void switchToPage2();    //�л�������ʶ��ҳ��
private:
    Ui::MainWindowClass ui;
};
