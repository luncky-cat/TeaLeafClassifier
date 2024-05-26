#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include "global.h"
#include <QtWidgets/qmessagebox.h>



// ���ļ��ж�ȡ��Ҷ��Ϣ����䵽 map ��
void readTeaInfoFromFile(map<string, TeaInfo>& tea_map, const string& filename) {
    // ���ļ�
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "�޷����ļ���" << endl;
        return;
    }
    // ��ȡ�ļ����ݲ�����
    string line;
    while (getline(file,line)) {
        if (!line.empty()) {
            istringstream iss(line);
            string tea_name;
            int tea_id;
            // ʹ�ÿո�ָ�ÿ������
            if (iss >> tea_name >> tea_id) {
                // �洢�� map ��
                tea_map[tea_name] = { 0, tea_id }; // ��ʼƵ����Ϊ0
            }
        }
    }
    tea_map["����"] = {0,-1};
    // �ر��ļ�
    file.close();
}


int main(int argc, char *argv[])
{
    //��ȡ��ע�ļ�

    readTeaInfoFromFile(tea_map,"D:\\biaozhu.txt");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
