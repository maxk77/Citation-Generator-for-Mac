#ifndef NEWSPAPER_H
#define NEWSPAPER_H

#include <QDialog>

namespace Ui {
class Newspaper;
}

class Newspaper : public QDialog
{
    Q_OBJECT

public:
    explicit Newspaper(QWidget *parent = 0);
    void prepro_data(QString filename);
    ~Newspaper();

private slots:
    void on_back_button_clicked();

    void on_clear_button_clicked();

    void on_author_checkBox_clicked(bool checked);

    void on_editor_check_clicked(bool checked);

    void on_translator_check_clicked(bool checked);

    void on_load_button_clicked();

    void on_get_citation_button_clicked();

private:
    Ui::Newspaper *ui;
};

#endif // NEWSPAPER_H
