#include "book_page.h"
#include "ui_book_page.h"
#include "navigation_page.h"
#include "utils.h"
#include <QComboBox>
#include <vector>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
using namespace std;

Book_page::Book_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Book_page)
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

Book_page::~Book_page()
{
    delete ui;
}

void Book_page::prepro_data(QString filename){
    QString data,header,info;

    QFile *file = new QFile(filename);
    file->open(QIODevice::ReadOnly | QIODevice::Text);

    while (true){
        //Read a line
        data = QString(file->readLine());
        header = data.mid(0,3);
        info = data.mid(3);
        if (header == QString("%0 ")){
            //Check whether the reference belong to a journal
            //if not, pop up a warning window
            if (info.indexOf("Book") == string::npos){
                int warn_ret = QMessageBox::warning(this,tr("warn"),tr("Your loading reference does not belong to a Book"),QMessageBox::Abort);
                if (warn_ret == QMessageBox::Abort) qDebug() << tr("close");
                return;
            }
        }

        else if (header == QString("%A ")) {
            info = trim(info);
            QString author,translator;
            if (info.indexOf("；") != string::npos){
                //check whether there are both author and translator
                author = info.mid(0,info.indexOf("；"));
                translator = info.mid(info.indexOf("；") + 1);
                ui->translator_check->setChecked(true);
                //set author
                ui->author_last_bar->setText(author.mid(0,author.size()-1));
                //set translator
                ui->translator_last_bar->setText(translator.mid(0,translator.size()-1));
            }
            else{
            //set author
            ui->author_last_bar->setText(info.mid(0,info.size()-1));
            }
            ui->author_multi->setChecked(ui->author_last_bar->text().indexOf("，") != string::npos);

            //check multi translator
            if(translator.indexOf("，") != string::npos){
                ui->translator_multi->setChecked(translator.indexOf("，") != string::npos);
                Book_page::on_translator_check_clicked(true);
            }
        }

        else if (header == QString("%T ")){
            if (!IncludeChinese(trim(info))){
                ui->English_checkBox->setChecked(true);
            }
            ui->article_title_line->setText(trim(info));
        }

        else if (header == QString("%I ")){
            info = trim(info);
            QString position,publisher;
            if (info.indexOf("：") != string::npos){
                position = info.mid(0,info.indexOf("："));
                publisher = info.mid(info.indexOf("：") + 1);
                ui->position_line->setText(position);
                ui->publisher_line->setText(publisher);
            }
            else {
                ui->publisher_line->setText(info);
            }
        }

        else if (header == QString("%D ")){
            info = trim(info);
            ui->date_line->setText(info.mid(0,info.indexOf(".")));
        }

        else if (header == QString("%P ")){
            ui->page_start_line->setText(trim(info));
        }

        else if (header == QString("%X ")){
            int warn_ret = QMessageBox::information(this,tr("tips"),tr("you should erase the useless stuff in authors' or translators' name bar"),QMessageBox::Ok);
            if (warn_ret == QMessageBox::Abort) qDebug() << tr("get");
            return;
        }
        else if (header == ""){
            int warn_ret = QMessageBox::information(this,tr("tips"),tr("you should erase the useless stuff in authors' or translators' name bar"),QMessageBox::Ok);
            if (warn_ret == QMessageBox::Abort) qDebug() << tr("get");
            return;
        }
    }
}

void Book_page::on_back_button_clicked()
{
    close();
    Navigation_page * navg = new Navigation_page;
    navg->show();
    delete ui;
}


void Book_page::on_clear_button_clicked()
{
    close();
    Book_page * bop = new Book_page;
    bop->show();
    delete ui;
}

void Book_page::on_load_button_clicked()
{
//    QString path = QCoreApplication::applicationDirPath();
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

void Book_page::on_editor_check_clicked(bool checked)
{
    ui->editor_label->setVisible(checked);
    ui->editor_first->setVisible(checked);
    ui->editor_last->setVisible(checked);
    ui->editor_first_bar->setVisible(checked);
    ui->editor_last_bar->setVisible(checked);
    ui->editor_multi->setVisible(checked);
}



void Book_page::on_translator_check_clicked(bool checked)
{
    ui->translator_label->setVisible(checked);
    ui->translator_first->setVisible(checked);
    ui->translator_last->setVisible(checked);
    ui->translator_first_bar->setVisible(checked);
    ui->translator_last_bar->setVisible(checked);
    ui->translator_multi->setVisible(checked);
}

void Book_page::on_author_multi_clicked(bool checked)
{
    if (checked){
        int warn_ret = QMessageBox::information(this,tr("tips"),tr("you should use comma to seperate two authors. eg. Max,Welkin"),QMessageBox::Ok);
        if (warn_ret == QMessageBox::Abort) qDebug() << tr("get");
    }
}

void Book_page::on_get_citation_button_clicked()
{
    QString in_paper_citation, bibliography, bibliography2,book_title;
    vector<QString> container_bio;

    //generate deque<QString> of author last_name and first_name
    deque<QString> last_name_base, first_name_base;
    QString author_last_bar = ui->author_last_bar->text();
    QString author_first_bar = ui->author_first_bar->text();
    bool multi_author = ui->author_multi->isChecked();
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
            container_bio = get_APA_EN_bibliography_book(last_name_base,first_name_base,ui->date_line->text(),
                                                       editor_last_name_base,editor_first_name_base,
                                                       translator_last_name_base,translator_first_name_base,
                                                       ui->position_line->text(),ui->publisher_line->text(),ui->page_start_line->text(),ui->page_end_line->text());

        } else {
            //Chinese version

            //set citation in paper
            ui->citationInPaperCLineEdit->setText("（" + ui->author_last_bar->text() + "，" + ui->date_line->text() + "）");

            //get bibliography
            container_bio = get_APA_CN_bibliography_book(last_name_base,ui->date_line->text(),
                                                         editor_last_name_base,
                                                         translator_last_name_base,
                                                         ui->position_line->text(),ui->publisher_line->text(),ui->page_start_line->text(),ui->page_end_line->text());


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
            container_bio = get_MLA_EN_bibliography_book(last_name_base,first_name_base,ui->date_line->text(),
                                                         editor_last_name_base,editor_first_name_base,
                                                         translator_last_name_base,translator_first_name_base,
                                                         ui->position_line->text(),ui->publisher_line->text(),ui->page_start_line->text(),ui->page_end_line->text());


        } else {
            //Chinese version


            //set citation in paper
            ui->citationInPaperCLineEdit->setText("（" + ui->author_last_bar->text() + "，" + ui->date_line->text() + "）");


            //get bibliography
            container_bio = get_MLA_CN_bibliography_book(last_name_base,ui->date_line->text(),
                                                         editor_last_name_base,
                                                         translator_last_name_base,
                                                         ui->position_line->text(),ui->publisher_line->text(),ui->page_start_line->text(),ui->page_end_line->text());


        }

    }

    bibliography = container_bio[0];
    bibliography2 = container_bio[1];

    //set bibliography

    ui->bibliographyBLineEdit->append(bibliography);
    //change font of website name
    ui->bibliographyBLineEdit->setFontItalic(true);
    ui->bibliographyBLineEdit->insertPlainText(ui->article_title_line->text());
    // restore
    ui->bibliographyBLineEdit->setFontItalic(false);
    ui->bibliographyBLineEdit->insertPlainText(bibliography2);
}
