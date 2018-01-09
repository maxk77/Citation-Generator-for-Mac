#ifndef JOURNAL_PAGE_H
#define JOURNAL_PAGE_H

#include <QDialog>

namespace Ui {
class journal_page;
}

class journal_page : public QDialog
{
    Q_OBJECT

public:
    explicit journal_page(QWidget *parent = 0);
    void prepro_data(QString filename);
    ~journal_page();

private slots:
    void on_load_button_clicked();

    void on_get_citation_button_clicked();

    void on_back_button_clicked();

    void on_clear_button_clicked();

    void on_editor_check_clicked(bool checked);

    void on_translator_check_clicked(bool checked);

    void on_author_checkBox_clicked(bool checked);

private:
    Ui::journal_page *ui;
};

#endif // JOURNAL_PAGE_H
