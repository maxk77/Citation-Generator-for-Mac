#ifndef APA_GUIDANCE_PAGE_H
#define APA_GUIDANCE_PAGE_H

#include <QDialog>

namespace Ui {
class apa_guidance_page;
}

class apa_guidance_page : public QDialog
{
    Q_OBJECT

public:
    explicit apa_guidance_page(QWidget *parent = 0);
    ~apa_guidance_page();

private slots:
    void on_back_button_clicked();

private:
    Ui::apa_guidance_page *ui;
};

#endif // APA_GUIDANCE_PAGE_H
