#include "navigation_page.h"
#include "ui_navigation_page.h"
#include "web_page.h"
#include "journal_page.h"
#include "magazine_page.h"
#include "book_page.h"
#include "newspaper.h"
#include "apa_guidance_page.h"
#include "mla_guidance_page.h"
#include <QProcess>
#include <QDebug>


Navigation_page::Navigation_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Navigation_page)
{
    ui->setupUi(this);

}

Navigation_page::~Navigation_page()
{
    delete ui;
}

void Navigation_page::on_web_button_clicked()
{
    close();
    Web_page * webp = new Web_page;
    webp->show();
    delete ui;
}

void Navigation_page::on_journal_button_clicked()
{
    close();
    journal_page * magp = new journal_page ;
    magp->show();
    delete ui;
}

void Navigation_page::on_apa_guide_button_clicked()
{
    close();
    apa_guidance_page * apap = new apa_guidance_page;
    apap->show();
    delete ui;
}

void Navigation_page::on_mla_guide_button_clicked()
{
    close();
    mla_guidance_page * mlap = new mla_guidance_page;
    mlap->show();
    delete ui;
}

void Navigation_page::on_magazine_button_clicked()
{
    close();
    magazine_page * magp = new magazine_page;
    magp->show();
    delete ui;
}


void Navigation_page::on_book_button_clicked()
{
    close();
    Book_page * bop = new Book_page;
    bop->show();
    delete ui;
}

void Navigation_page::on_newspaper_button_clicked()
{
    close();
    Newspaper * nspp = new Newspaper;
    nspp->show();
    delete ui;
}

