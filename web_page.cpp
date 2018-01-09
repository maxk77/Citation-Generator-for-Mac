#include "web_page.h"
#include "ui_web_page.h"
#include "navigation_page.h"
#include "utils.h"
#include <QComboBox>
#include <vector>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

using namespace std;

Web_page::Web_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Web_page)
{
    ui->setupUi(this);

    ui->reference_style_box->addItem(tr("APA"));
    ui->reference_style_box->addItem(tr("MLA"));

    ui->editor_label->hide();
    ui->editor_first->hide();
    ui->editor_last->hide();
    ui->editor_first_bar->hide();
    ui->editor_last_bar->hide();
    ui->editor_multi->hide();

    ui->translator_label->hide();
    ui->translator_first->hide();
    ui->translator_last->hide();
    ui->translator_first_bar->hide();
    ui->translator_last_bar->hide();
    ui->translator_multi->hide();
}

Web_page::~Web_page()
{
    delete ui;
}


void Web_page::on_back_Button_clicked()
{
    close();
    Navigation_page * navg = new Navigation_page;
    navg->show();
    delete ui;
}

void Web_page::on_get_citation_Button_clicked()
{
    QString in_paper_citation, bibliography, bibliography2,website_title;
    vector<QString> container_bio;

    //generate deque<QString> of author last_name and first_name
    deque<QString> last_name_base, first_name_base;
    QString author_last_bar = ui->author_last_bar->text();
    QString author_first_bar = ui->author_first_bar->text();
    bool multi_author = ui->author_checkBox->isChecked();
    bool English = ui->English_checkBox->isChecked();
    generate_author_deque(last_name_base,first_name_base,author_last_bar,author_first_bar,multi_author, English);


    //see if we need to generate the deque<QString> of the editor's and translator's
    deque<QString> editor_last_name_base, editor_first_name_base;
    if (ui->editor_check->isChecked()){
    //we generate the deque of editor
        QString editor_last_bar = ui->editor_last_bar->text();
        QString editor_first_bar = ui->editor_first_bar->text();
        bool multi_editor = ui->editor_multi->isChecked();
        generate_author_deque(editor_last_name_base,editor_first_name_base,editor_last_bar,editor_first_bar,multi_editor,English);
    }


    deque<QString> translator_last_name_base, translator_first_name_base;
    if (ui->translator_check->isChecked()){
    //we generate the deque of translator
        QString translator_last_bar = ui->translator_last_bar->text();
        QString translator_first_bar = ui->translator_first_bar->text();
        bool multi_translator = ui->translator_multi->isChecked();
        generate_author_deque(translator_last_name_base,translator_first_name_base,translator_last_bar,translator_first_bar,multi_translator,English);
    }

    //check APA or MLA
    if (ui->reference_style_box->currentText() == QString("APA")){
        //APA Citation

        if (ui->English_checkBox->isChecked()){
            //English version

            //set citation in paper
            ui->citationInPaperCLineEdit->setText("(" + ui->author_last_bar->text() + ", " + ui->date_line->text() + ")");

            //get bibliography
            container_bio = get_APA_EN_bibliography_web(last_name_base,first_name_base,ui->date_line->text(), ui->Date_Publish_Month_Box->currentText(),
                                                       editor_last_name_base,editor_first_name_base,
                                                       translator_last_name_base,translator_first_name_base,
                                                       ui->article_title_line->text(),ui->website_title_line->text(),ui->url_line->text());

        } else {
            //Chinese version

            //set citation in paper
            ui->citationInPaperCLineEdit->setText("（" + ui->author_last_bar->text() + "，" + ui->date_line->text() + "）");

            //get bibliography
            container_bio = get_APA_CN_bibliography_web(last_name_base, ui->date_line->text(), ui->Date_Publish_Month_Box->currentText(),
                                                       editor_last_name_base, translator_last_name_base,
                                                       ui->article_title_line->text(),ui->website_title_line->text(),ui->url_line->text());


        }
    } else if (ui->reference_style_box->currentText() == QString("MLA")){
        //MLA citation

        if (ui->English_checkBox->isChecked()){
            //English version

            //set citation in paper
            if (last_name_base.size() >= 3){
                ui->citationInPaperCLineEdit->setText("(" + last_name_base.front() + " et al." + ui->date_line->text() + ")");
            } else{
                ui->citationInPaperCLineEdit->setText("(" + ui->author_last_bar->text() + ", " + ui->date_line->text() + ")");
            }
            //get bibliography
            container_bio = get_MLA_EN_bibliography_web(last_name_base,first_name_base,ui->date_line->text(), ui->Date_Publish_Month_Box->currentText(),
                                                       editor_last_name_base,editor_first_name_base,
                                                       translator_last_name_base,translator_first_name_base,
                                                       ui->article_title_line->text(),ui->website_title_line->text(),ui->url_line->text());


        } else {
            //Chinese version


            //set citation in paper
            ui->citationInPaperCLineEdit->setText("（" + ui->author_last_bar->text() + "，" + ui->date_line->text() + "）");


            //get bibliography
            container_bio = get_MLA_CN_bibliography_web(last_name_base, ui->date_line->text(), ui->Date_Publish_Month_Box->currentText(),
                                                       editor_last_name_base, translator_last_name_base,
                                                       ui->article_title_line->text(),ui->website_title_line->text(),ui->url_line->text());


        }

    }

    bibliography = container_bio[0];
    bibliography2 = container_bio[1];

    //set bibliography

    ui->bibliographyBLineEdit->append(bibliography);
    //change font of website name
    ui->bibliographyBLineEdit->setFontItalic(true);
    ui->bibliographyBLineEdit->insertPlainText(ui->website_title_line->text());
    // restore
    ui->bibliographyBLineEdit->setFontItalic(false);
    ui->bibliographyBLineEdit->insertPlainText(bibliography2);
}

void Web_page::on_clear_Button_clicked()
{
    close();
    Web_page * webp = new Web_page;
    webp->show();
    delete ui;
}


void Web_page::on_editor_check_clicked(bool checked)
{
    ui->editor_label->setVisible(checked);
    ui->editor_first->setVisible(checked);
    ui->editor_last->setVisible(checked);
    ui->editor_first_bar->setVisible(checked);
    ui->editor_last_bar->setVisible(checked);
    ui->editor_multi->setVisible(checked);
}



void Web_page::on_translator_check_clicked(bool checked)
{
    ui->translator_label->setVisible(checked);
    ui->translator_first->setVisible(checked);
    ui->translator_last->setVisible(checked);
    ui->translator_first_bar->setVisible(checked);
    ui->translator_last_bar->setVisible(checked);
    ui->translator_multi->setVisible(checked);
}


void Web_page::on_author_checkBox_clicked(bool checked)
{
    if (checked){
        int warn_ret = QMessageBox::information(this,tr("tips"),tr("you should use comma to seperate two authors. eg. Max,Welkin"),QMessageBox::Ok);
        if (warn_ret == QMessageBox::Abort) qDebug() << tr("get");
    }
}
