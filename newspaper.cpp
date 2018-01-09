#include "newspaper.h"
#include "ui_newspaper.h"
#include "navigation_page.h"
#include "utils.h"
#include <QComboBox>
#include <vector>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

using namespace std;


Newspaper::Newspaper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Newspaper)
{
    ui->setupUi(this);
    ui->reference_style->addItem(tr("APA"));
    ui->reference_style->addItem(tr("MLA"));

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

Newspaper::~Newspaper()
{
    delete ui;
}

void Newspaper::on_back_button_clicked()
{
    close();
    Navigation_page * navg = new Navigation_page;
    navg->show();
    delete ui;
}

void Newspaper::on_clear_button_clicked()
{
    close();
    Newspaper * nspp = new Newspaper;
    nspp->show();
    delete ui;
}


void Newspaper::prepro_data(QString filename) {
    QString data,header,info, year;

    QFile *file = new QFile(filename);
    file->open(QIODevice::ReadOnly | QIODevice::Text);

    while (true){
        //Read a line
        data = QString(file->readLine());
        header = data.mid(0,3);
        info = data.mid(3);
        if (header == QString("%0 ")){
            //Check whether the reference belong to a newspaper
            //if not, pop up a warning window
            if (info.indexOf("Newspaper") == string::npos){
                int warn_ret = QMessageBox::warning(this,tr("warn"),tr("Your loading reference does not belong to a Newspaper"),QMessageBox::Abort);
                if (warn_ret == QMessageBox::Abort) qDebug() << tr("close");
                return;
            }
        }

        else if (header == QString("%A ")) {
            //check whether the author is English
            if (!IncludeChinese(trim(info))){
                ui->English_checkBox->setChecked(true);
                if (ui->author_last_bar->text().isEmpty()) {
                    ui->author_last_bar->setText(trim(get_author_last_name(info)));
                    ui->author_first_bar->setText(trim(get_author_first_name(info)));
                } else {
                    // there is already an author
                    ui->author_checkBox->setChecked(true);
                    ui->author_last_bar->setText(ui->author_last_bar->text() + tr(",") + trim(get_author_last_name(info)));
                    ui->author_first_bar->setText(ui->author_first_bar->text() + tr(",") + trim(get_author_first_name(info)));
                }
            } else {
                //the author is Chinese
                if (ui->author_last_bar->text().isEmpty()){
                    ui->author_last_bar->setText(trim(info));
                } else {
                    // there is already an author
                    ui->author_last_bar->setText(ui->author_last_bar->text() + tr("，") +trim(info));
                    ui-> author_checkBox->setChecked(true);
                }
            }
        }

        else if (header == QString("%T ")){
            ui->article_title_line->setText(trim(info));
        }

        else if (header == QString("%J ")){
            ui->newspaper_title_line->setText(trim(info));
        }

        else if (header == QString("%8 ")){
            year = info.mid(0,4);
            ui->date_line->setText(trim(year));
        }

        else if (header == QString("%P ")) {
            continue;
        }

        else if (header == QString("%+ ")){
            continue;
        }

        else if (header == QString("%I ")) {
            continue;
        }

        else if (header == QString("%L ")) {
            continue;
        }

        else if (header == QString("%W ")){
            return;
        }

        else continue;
    }
}



void Newspaper::on_author_checkBox_clicked(bool checked)
{
    if (checked){
        int warn_ret = QMessageBox::information(this,tr("tips"),tr("You should use comma to seperate two authors. eg. Max,Welkin"),QMessageBox::Ok);
        if (warn_ret == QMessageBox::Abort) qDebug() << tr("get");
    }
}

void Newspaper::on_editor_check_clicked(bool checked)
{
    if (checked){
        ui->editor_label->show();
        ui->editor_first->show();
        ui->editor_last->show();
        ui->editor_first_bar->show();
        ui->editor_last_bar->show();
        ui->editor_multi->show();
    } else {
        ui->editor_label->hide();
        ui->editor_first->hide();
        ui->editor_last->hide();
        ui->editor_first_bar->hide();
        ui->editor_last_bar->hide();
        ui->editor_multi->hide();
    }
}

void Newspaper::on_translator_check_clicked(bool checked)
{
    if (checked){
        ui->translator_label->show();
        ui->translator_first->show();
        ui->translator_last->show();
        ui->translator_first_bar->show();
        ui->translator_last_bar->show();
        ui->translator_multi->show();
    } else {
        ui->translator_label->hide();
        ui->translator_first->hide();
        ui->translator_last->hide();
        ui->translator_first_bar->hide();
        ui->translator_last_bar->hide();
        ui->translator_multi->hide();
    }
}

void Newspaper::on_load_button_clicked()
{
//    QDir temdir;
//    QString path = temdir.rootPath();
//    qDebug() << path;
//    int time = 0;
//    int pos = 0;
//    while (time != 3){
//        pos = path.indexOf("/",pos) + 1;
//        time ++;
//        qDebug() << time << ":" << pos << endl;
//    }
//    path = path.mid(0,pos);
//    qDebug() << path;
//    path += "Downloads";
    QString path = "/Users/wangwenqi/Downloads";
    QString filename = QFileDialog::getOpenFileName(this,tr("请选择输出的txt描述文件"),path,tr("纯文本文件(*txt)"));
    qDebug() << "filename: " << filename;
    if (filename != tr(""))
    {
        prepro_data(filename);

    }

}

void Newspaper::on_get_citation_button_clicked()
{
    QString bibliography;

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



    //Check APA or MLA
    if (ui->reference_style->currentText() == QString("APA")){
        //APA Citation

        if (ui->English_checkBox->isChecked()){
            //English version

            //set citation in paper
            ui->inpaper_citation_line->setText("(" + ui->author_last_bar->text() + ", " + ui->date_line->text() + ")");

            //get bibliography
            bibliography = get_APA_EN_bibliography_newspaper(last_name_base,first_name_base,ui->date_line->text(),editor_last_name_base,
                                                  editor_first_name_base,translator_last_name_base,translator_first_name_base,ui->article_title_line->text(),
                                                           ui->newspaper_title_line->text(),ui->start_page_line->text(),ui->end_page_line->text());
        } else {
            //Chinese version

            //set citation in paper
            ui->inpaper_citation_line->setText("（" + ui->author_last_bar->text() + "，" + ui->date_line->text() + "）");

            //get bibliography
            bibliography = get_APA_CN_bibliography_newspaper(last_name_base,ui->date_line->text(), editor_last_name_base, translator_last_name_base,
                                                   ui->article_title_line->text(),ui->newspaper_title_line->text(),
                                                           ui->start_page_line->text(),ui->end_page_line->text());
        }

        //set bibliography
        ui->bibliography_line->setText(bibliography);
    }


    else if (ui->reference_style->currentText() == QString("MLA")){
        //MLA citation

        if (ui->English_checkBox->isChecked()){
            //English Version

            //set citation in paper
            if (last_name_base.size() >= 3){
                //check if the num if author is larger or equal to 3
                ui->inpaper_citation_line->setText("(" + last_name_base.front() + " et al. " + ui->start_page_line->text() + ")");
            }  else {
                //the number of authur is 1 or 2
                ui->inpaper_citation_line->setText("(" + ui->author_last_bar->text() + " " + ui->start_page_line->text() +")");
            }

            //get bibliography
            bibliography = get_MLA_EN_bibliography_newspaper(last_name_base,first_name_base,ui->date_line->text(),editor_last_name_base,
                                                   editor_first_name_base,translator_last_name_base,translator_first_name_base,
                                                           ui->article_title_line->text(),ui->newspaper_title_line->text(),ui->start_page_line->text(),ui->end_page_line->text());


        } else {
            //Chinese Version

            //set citation in paper
            ui->inpaper_citation_line->setText("（" + ui->author_last_bar->text() + " " + ui->start_page_line->text() +"）");

            bibliography = get_MLA_CN_bibliography_newspaper(last_name_base,ui->date_line->text(),
                                                   editor_last_name_base, translator_last_name_base,ui->article_title_line->text(),
                                                   ui->newspaper_title_line->text(),ui->start_page_line->text(),ui->end_page_line->text());

        }

        //set bibliography
        ui->bibliography_line->setText(bibliography);

    }
}
