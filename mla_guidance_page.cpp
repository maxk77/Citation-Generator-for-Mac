#include "mla_guidance_page.h"
#include "ui_mla_guidance_page.h"
#include "navigation_page.h"

mla_guidance_page::mla_guidance_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mla_guidance_page)
{
    ui->setupUi(this);
}

mla_guidance_page::~mla_guidance_page()
{
    delete ui;
}

void mla_guidance_page::on_back_button_clicked()
{
    close();
    Navigation_page* navg = new Navigation_page;
    navg->show();
    delete ui;
}
