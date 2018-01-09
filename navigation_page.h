#ifndef NAVIGATION_PAGE_H
#define NAVIGATION_PAGE_H

#include <QDialog>

namespace Ui {
class Navigation_page;
}

class Navigation_page : public QDialog
{
    Q_OBJECT

public:
    explicit Navigation_page(QWidget *parent = 0);
    ~Navigation_page();

private slots:
    void on_web_button_clicked();

    void on_journal_button_clicked();

    void on_apa_guide_button_clicked();

    void on_mla_guide_button_clicked();

    void on_magazine_button_clicked();

    void on_book_button_clicked();

    void on_newspaper_button_clicked();

private:
    Ui::Navigation_page *ui;
};

#endif // NAVIGATION_PAGE_H
