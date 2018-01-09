#ifndef MLA_GUIDANCE_PAGE_H
#define MLA_GUIDANCE_PAGE_H

#include <QDialog>

namespace Ui {
class mla_guidance_page;
}

class mla_guidance_page : public QDialog
{
    Q_OBJECT

public:
    explicit mla_guidance_page(QWidget *parent = 0);
    ~mla_guidance_page();

private slots:
    void on_back_button_clicked();

private:
    Ui::mla_guidance_page *ui;
};

#endif // MLA_GUIDANCE_PAGE_H
