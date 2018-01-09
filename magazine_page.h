#ifndef MAGAZINE_PAGE_H
#define MAGAZINE_PAGE_H

#include <QDialog>

namespace Ui {
class magazine_page;
}

class magazine_page : public QDialog
{
    Q_OBJECT

public:
    explicit magazine_page(QWidget *parent = 0);
    void prepro_data(QString filename);
    ~magazine_page();

private slots:
    void on_back_button_clicked();

    void on_clear_button_clicked();

    void on_load_button_clicked();

    void on_editor_check_clicked(bool checked);

    void on_translator_check_clicked(bool checked);

    void on_author_checkBox_clicked(bool checked);

    void on_get_citation_button_clicked();

private:
    Ui::magazine_page *ui;
};

#endif // MAGAZINE_PAGE_H
