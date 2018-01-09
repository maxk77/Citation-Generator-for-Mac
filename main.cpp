#include "navigation_page.h"
#include <QApplication>
extern void qt_set_sequence_auto_mnemonic(bool b);

int main(int argc, char *argv[])
{
//    qt_set_sequence_auto_mnemonic(true);
//    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
//    setFixedSize(this->width(),this->height());                     // 禁止拖动窗口大小

    QApplication a(argc, argv);
    Navigation_page *nav = new Navigation_page;
    nav->show();
    return a.exec();
}
