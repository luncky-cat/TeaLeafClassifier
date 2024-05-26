#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include "global.h"
#include <QtWidgets/qmessagebox.h>



// 从文件中读取茶叶信息并填充到 map 中
void readTeaInfoFromFile(map<string, TeaInfo>& tea_map, const string& filename) {
    // 打开文件
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件！" << endl;
        return;
    }
    // 读取文件内容并解析
    string line;
    while (getline(file,line)) {
        if (!line.empty()) {
            istringstream iss(line);
            string tea_name;
            int tea_id;
            // 使用空格分割每行内容
            if (iss >> tea_name >> tea_id) {
                // 存储到 map 中
                tea_map[tea_name] = { 0, tea_id }; // 初始频率设为0
            }
        }
    }
    tea_map["其他"] = {0,-1};
    // 关闭文件
    file.close();
}


int main(int argc, char *argv[])
{
    //读取标注文件

    readTeaInfoFromFile(tea_map,"D:\\biaozhu.txt");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
