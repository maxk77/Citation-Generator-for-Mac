#include "apa_guidance_page.h"
#include "ui_apa_guidance_page.h"
#include "navigation_page.h"

apa_guidance_page::apa_guidance_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::apa_guidance_page)
{
    ui->setupUi(this);
}

apa_guidance_page::~apa_guidance_page()
{
    delete ui;
}

void apa_guidance_page::on_back_button_clicked()
{
    close();
    Navigation_page * navp = new Navigation_page;
    navp->show();
    delete ui;
}
