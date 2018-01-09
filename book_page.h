#ifndef BOOK_PAGE_H
#define BOOK_PAGE_H

#include <QDialog>

namespace Ui {
class Book_page;
}

class Book_page : public QDialog
{
    Q_OBJECT

public:
    explicit Book_page(QWidget *parent = 0);
    void prepro_data(QString filename);
    ~Book_page();

private slots:
    void on_back_button_clicked();

    void on_clear_button_clicked();

    void on_load_button_clicked();

    void on_editor_check_clicked(bool checked);

    void on_translator_check_clicked(bool checked);

    void on_author_multi_clicked(bool checked);

    void on_get_citation_button_clicked();

private:
    Ui::Book_page *ui;
};

#endif // BOOK_PAGE_H
