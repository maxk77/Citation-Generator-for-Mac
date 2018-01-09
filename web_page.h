#ifndef WEB_PAGE_H
#define WEB_PAGE_H

#include <QDialog>

namespace Ui {
class Web_page;
}

class Web_page : public QDialog
{
    Q_OBJECT

public:
    explicit Web_page(QWidget *parent = 0);
    ~Web_page();

private slots:
    void on_back_Button_clicked();

    void on_get_citation_Button_clicked();

    void on_clear_Button_clicked();


    void on_editor_check_clicked(bool checked);

    void on_translator_check_clicked(bool checked);

    void on_author_checkBox_clicked(bool checked);

private:
    Ui::Web_page *ui;
};

#endif // WEB_PAGE_H
