#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <QWidget>
#include <deque>
#include <QTextCodec> //for QString->char*, 有中文时不会乱码

using namespace std;

static QString trim(QString qs)
{
    string s = qs.toStdString();
    if (s.empty())
    {
        return QString("");
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    s.erase(s.find_last_not_of("\n") + 1);
    return s.c_str();
}

static QString get_author_first_name(QString qs)
{
    string s = qs.toStdString();
    if (s.empty())
    {
        return QString("");
    }
    s = s.substr(0,s.find_first_of(" "));
    return s.c_str();
}

static QString get_author_last_name(QString qs)
{
    string s = qs.toStdString();
    if (s.empty())
    {
        return QString("");
    }
    s = s.substr(s.find_first_of(" ")+1);
    return s.c_str();
}

static vector<QString> get_APA_CN_bibliography_journal(deque<QString> last_name, QString year, deque<QString> editor_last_name,
                         deque<QString> translator_last_name, QString article_title, QString journal_title,
                         QString volumn,QString issue, QString start_page, QString end_page)
{
    QString bi;
    QString bi2;

    int i = 0;
    while (!last_name.empty()){
        if (i == 0){
            bi += last_name.front();
        } else {
            bi += "," + last_name.front();
        }
        last_name.pop_front();
        i++;
    }
    bi += (year == "")? "." : ("(" + year + ")" + ".");
    bi += (article_title == "")? "" : (article_title + ".");

    //Add editor name bar's information
    bool editor_exist = !editor_last_name.empty();
    while (!editor_last_name.empty()){
        bi += editor_last_name.front() + ",";
        editor_last_name.pop_front();
    }
    bi += (editor_exist)? "编辑;" : "";

    //Add translator name bar's information
    bool translator_exist = !translator_last_name.empty();
    while (!translator_last_name.empty()){
        bi += translator_last_name.front() + ",";
        translator_last_name.pop_front();
    }
    bi += (translator_exist)? "翻译;": "";

//    bi += (journal_title == "")? "" : (journal_title);


    bi2 += "," + volumn ;
    bi2 += (issue == "")? "" : ("(" + issue + ")");
    bi2 += (start_page == "")? "" : ("," + start_page + "-");
    bi2 += (end_page == "")? "." : (end_page + ".");

    vector<QString> k = {bi,bi2};
    return k;
}

static vector<QString> get_APA_EN_bibliography_journal(deque<QString> last_name, deque<QString> first_name, QString year,
                                deque<QString> editor_last_name, deque<QString> editor_first_name,
                                deque<QString> translator_last_name, deque<QString> translator_first_name,
                            QString article_title, QString journal_title, QString volumn,
                            QString issue, QString start_page, QString end_page)
{

    //Add author information
    QString bi,bi2;
    int num_of_author = last_name.size();
    while (!last_name.empty() && !first_name.empty()){
        bi += last_name.front() + ", " + (first_name.front()[0]).toUpper() + ". ";
        last_name.pop_front();
        first_name.pop_front();
    }
    if (num_of_author >= 3){
        int au_comma_index = 0;
        for (int i = 0; i != num_of_author-1; i++){
            au_comma_index = bi.indexOf(",") + 1;
        }
        bi.replace(au_comma_index-1,1,"&");
    }

    bi += (year == "")? ". " : ("(" + year + ")" + ". ");

    bi += (article_title == "")? "" : (article_title + ". ");

    //Test whether editor or translator exist,
    //if so, we build a struct for it
    bool editor_trans_exist = !editor_last_name.empty() || !translator_last_name.empty();
    if (editor_trans_exist) bi += "(";
    //Add editor information
    if (!editor_last_name.empty() && !editor_first_name.empty()){
        int num_of_editor = last_name.size();
        while(!editor_last_name.empty() && !editor_first_name.empty()){
            bi += (editor_first_name.front()[0]).toUpper();
            bi += ". " + editor_last_name.front() + ", " ;
            editor_last_name.pop_front();
            editor_first_name.pop_front();
        }
        if (num_of_editor >= 3){
            int ed_comma_index = 0;
            for (int i = 0; i != num_of_editor -1; i++){
                ed_comma_index = bi.indexOf(",") + 1;
            }
            bi.replace(ed_comma_index-1,1,"&");
        }
        bi += "Eds.; ";
    }


    //Add translator information
    if (!translator_last_name.empty() && !translator_first_name.empty()){
        int num_of_editor = last_name.size();
        while(!translator_last_name.empty() && !translator_first_name.empty()){
            bi += (translator_first_name.front()[0]).toUpper();
            bi += ". " + translator_last_name.front() + ", " ;
            translator_last_name.pop_front();
            translator_first_name.pop_front();
        }
        if (num_of_editor >= 3){
            int ed_comma_index = 0;
            for (int i = 0; i != num_of_editor -1; i++){
                ed_comma_index = bi.indexOf(",") + 1;
            }
            bi.replace(ed_comma_index-1,1,"&");
        }
        bi += "Trans.; ";
    }
    if (editor_trans_exist) bi += "). ";


//    bi += (journal_title == "")? "" : (journal_title);

    bi2 += ", " + volumn ;
    bi2 += (issue == "")? "" : ("(" + issue + ")");
    bi2 += (start_page == "")? "" : (", " + start_page + "-");
    bi2 += (end_page == "")? "." : (end_page + ".");

    vector<QString> k = {bi,bi2};

    return k;
}


static vector<QString> get_MLA_EN_bibliography_journal(deque<QString> last_name, deque<QString> first_name, QString year,
                                deque<QString> editor_last_name, deque<QString> editor_first_name,
                                deque<QString> translator_last_name, deque<QString> translator_first_name,
                            QString article_title, QString journal_title, QString volumn,
                            QString issue, QString start_page, QString end_page)
{
    QString bi,bi2;

    //Add author information
    while (!last_name.empty() && !first_name.empty()){
        if (last_name.size() >= 3){
            bi += first_name.front() + " " + last_name.front() + " et al.";
            break;
        }
        bi += first_name.front() + " " + last_name.front() + ", ";
        last_name.pop_front();
        first_name.pop_front();
    }
    bi.replace(bi.indexOf(",",string::npos),1,". ");


    bi += (article_title == "")? "" : ("\"" + article_title + ".\" ");


//    bi += (journal_title == "")? "" : (journal_title + ", ");
    bi2 += ", ";

    //Test whether editor or translator exist,
    //if so, we build a struct for it

    //Add editor information
    if (!editor_last_name.empty() && !editor_first_name.empty()){
        bi2 += "Edited by ";
        while (!editor_last_name.empty() && !editor_first_name.empty()){
            if (editor_last_name.size() >= 3){
                bi2 += editor_first_name.front() + " " + editor_last_name.front() + " et al.";
                break;
            }
            bi2 += editor_first_name.front() + " " + editor_last_name.front() + ", ";
            editor_last_name.pop_front();
            editor_first_name.pop_front();
        }
        bi2.replace(bi2.indexOf(",",string::npos),1,". ");
    }


    //Add translator information
    if (!translator_last_name.empty() && !translator_first_name.empty()){
        bi2 += "Translated by ";
        while(!translator_last_name.empty() && !translator_first_name.empty()){
            if (translator_last_name.size() >= 3){
                bi2 += translator_first_name.front() + " " + translator_last_name.front() + " et al.";
                break;
            }
            bi2 += translator_first_name.front() + " " + translator_last_name.front() + ", ";
            translator_last_name.pop_front();
            translator_first_name.pop_front();
        }
        bi2.replace(bi2.indexOf(",",string::npos),1,". ");
    }

    bi2 += (volumn == "")? "" : ("vol. " + volumn + ".");
    bi2 += (issue == "")? "" : ( "no. " + issue + " ");
    bi2 += (year == "")? ":": ("(" + year + ")");
    bi2 += (start_page == "")? "" : (", " + start_page + "-");
    bi2 += (end_page == "")? "." : (end_page + ".");
    bi2 += "Print.";


    vector<QString> k = {bi,bi2};
    return k;
}

static vector<QString> get_MLA_CN_bibliography_journal(deque<QString> last_name, QString year,
                                deque<QString> editor_last_name, deque<QString> translator_last_name,
                            QString article_title, QString journal_title, QString volumn,
                            QString issue, QString start_page, QString end_page)
{
    QString bi,bi2;

    while (!last_name.empty()){
        bi += last_name.front() + ",";
        last_name.pop_front();
    }
    bi.replace(bi.indexOf(",",string::npos),1,".");
    bi += (article_title == "")? "" : ("\"" + article_title + ".\" ");
//    bi += (journal_title == "")? "" : (journal_title + ",");
    bi2 += ",";

    //Test whether editor or translator exist,
    //if so, we build a struct for it

    //Add editor information
    if (!editor_last_name.empty()){
        bi2 += "编辑:";
        while (!editor_last_name.empty()){
            if (editor_last_name.size() >= 3){
                bi2 += editor_last_name.front() + "等.";
                break;
            }
            bi2 += editor_last_name.front() + ", ";
            editor_last_name.pop_front();
        }
        bi2.replace(bi2.indexOf(",",string::npos),1,". ");
    }


    //Add translator information
    if (!translator_last_name.empty()){
        bi2 += ";翻译: ";
        while(!translator_last_name.empty()){
            if (translator_last_name.size() >= 3){
                bi2 += translator_last_name.front() + "等.";
                break;
            }
            bi2 += translator_last_name.front() + ", ";
            translator_last_name.pop_front();
        }
        bi2.replace(bi2.indexOf(",",string::npos),1,". ");
    }


    bi2 += (volumn == "")? "" : (volumn + ".");
    bi2 += (issue == "")? "" : ( issue + " ");
    bi2 += (year == "")? ":": ("(" + year + ")");
    bi2 += (start_page == "")? "" : ("," + start_page + "-");
    bi2 += (end_page == "")? "." : (end_page + ".");
    bi2 += "印刷.";

    vector<QString> k = {bi,bi2};
    return k;
}


static vector<QString> get_APA_EN_bibliography_web(deque<QString> last_name, deque<QString> first_name, QString year, QString month,
                                       deque<QString> editor_last_name, deque<QString> editor_first_name,
                                      deque<QString> translator_last_name, deque<QString> translator_first_name,
                                       QString article_title, QString website_title, QString web_url)
{
    QString bi;
    QString bi2;


    //Add author information
    int num_of_author = last_name.size();
    while (!last_name.empty() && !first_name.empty()){
        bi += last_name.front() + ", " + (first_name.front()[0]).toUpper() + ". ";
        last_name.pop_front();
        first_name.pop_front();
    }
    if (num_of_author >= 3){
        int au_comma_index = 0;
        for (int i = 0; i != num_of_author-1; i++){
            au_comma_index = bi.indexOf(",") + 1;
        }
        bi.replace(au_comma_index-1,1,"&");
    }


    //Add year and month
    bool year_month_flag = (year != "") || (month != "");
    if (year_month_flag) bi += "(";
    bi += (year == "")? "" : (year + ",");
    bi += (month == "")? "" : (month.left(3) + ".");
    if (year_month_flag) bi += "). ";


    //Add article title
    bi += (article_title == "")? "" : (article_title + ". ");


    //add website title
//    bi += (website_title == "")? "" : (website_title + ". ");
    bi2 += ". ";

    //Add editor
    bool editor_translator_flag = (!editor_last_name.empty() || !translator_last_name.empty());
    if (editor_translator_flag) bi2 += "(";

    int num_of_editor = editor_last_name.size();
    while (!editor_last_name.empty() && !editor_first_name.empty()){
        bi2 += editor_last_name.front() + ". " + (editor_first_name.front()[0]).toUpper() + ", ";
        editor_last_name.pop_front();
        editor_first_name.pop_front();
    }
    if (num_of_editor >= 3){
        int au_comma_index = 0;
        for (int i = 0; i != num_of_editor-1; i++){
            au_comma_index = bi2.indexOf(",") + 1;
        }
        bi2.replace(au_comma_index-1,1,"&");
    }
    if (num_of_editor != 0) bi2 += "Ed.";

    //Add translator
    int num_of_translator = translator_last_name.size();
    if (num_of_translator != 0) bi2 += "; ";
    while (!translator_last_name.empty() && !translator_first_name.empty()){
        bi2 += translator_last_name.front() + ". " + (translator_first_name.front()[0]).toUpper() + ", ";
        translator_last_name.pop_front();
        translator_first_name.pop_front();
    }
    if (num_of_translator >= 3){
        int au_comma_index = 0;
        for (int i = 0; i != num_of_translator-1; i++){
            au_comma_index = bi.indexOf(",") + 1;
        }
        bi2.replace(au_comma_index-1,1,"&");
    }
    if (num_of_translator != 0) bi2 += "Trans.";
    if (editor_translator_flag) bi2 += "). ";


    //Add url
    bi2 += "Retrieved from " + web_url;

    vector<QString> k = {bi,bi2};
    return k;
}



static vector<QString> get_APA_CN_bibliography_web(deque<QString> last_name, QString year, QString month,
                                       deque<QString> editor_last_name, deque<QString> translator_last_name,
                                       QString article_title, QString website_title, QString web_url)
{

    QString bi;
    QString bi2;

    //Add author information
    int num_of_author = last_name.size();
    while (!last_name.empty()){
        bi += last_name.front() + ",";
        last_name.pop_front();
    }



    //Add year and month
    bool year_month_flag = (year != "") || (month != "");
    if (year_month_flag) bi += "(";
    bi += (year == "")? "" : (year + ",");

    if (month == "January") bi += "01";
    else if (month == "February") bi += "02";
    else if (month == "March") bi += "03";
    else if (month == "April") bi += "04";
    else if (month == "May") bi += "05";
    else if (month == "June") bi += "06";
    else if (month == "July") bi += "07";
    else if (month == "August") bi += "08";
    else if (month == "September") bi += "09";
    else if (month == "October") bi += "10";
    else if (month == "November") bi += "11";
    else if (month == "December") bi += "12";

    if (year_month_flag) bi += ")";


    //Add article title
    bi += (article_title == "")? "" : (article_title + ". ");


    //add website title
//    bi += (website_title == "")? "" : (website_title + ". ");
    bi2 += ".";

    //Add editor
    bool editor_translator_flag = (!editor_last_name.empty() || !translator_last_name.empty());
    if (editor_translator_flag) bi2 += "(";

    int num_of_editor = editor_last_name.size();
    if (num_of_editor != 0) bi2 += "编辑:";
    while (!editor_last_name.empty()){
        bi2 += editor_last_name.front() + ",";
        editor_last_name.pop_front();
    }

    //Add translator
    int num_of_translator = translator_last_name.size();
    if (num_of_translator != 0) bi2 += ";翻译:";
    while (!translator_last_name.empty()){
        bi2 += translator_last_name.front() + ",";
        translator_last_name.pop_front();
    }

    if (editor_translator_flag) bi2 += ") ";


    //Add url
    bi2 += "引用自:" + web_url;

    vector<QString> k = {bi,bi2};
    return k;
}




static vector<QString> get_MLA_EN_bibliography_web(deque<QString> last_name, deque<QString> first_name, QString year, QString month,
                                       deque<QString> editor_last_name, deque<QString> editor_first_name,
                                       deque<QString> translator_last_name, deque<QString> translator_first_name,
                                       QString article_title, QString website_title, QString web_url)
{
    QString bi;
    QString bi2;


    //Add author information
    while (!last_name.empty() && !first_name.empty()){
        if (last_name.size() >= 3){
            bi += first_name.front() + ", " + last_name.front() + " et al.";
            break;
        }
        bi += last_name.front() + ", " + (first_name.front()[0]).toUpper() + ". ";
        last_name.pop_front();
        first_name.pop_front();
    }


    //Add article title
    bi += (article_title == "")? "" : ("\"" + article_title + ".\" ");


    //add website title
//    bi += (website_title == "")? "" : (website_title + ", ");
    bi2 += ", ";

    //Add editor
    if (!editor_last_name.empty()){
        while (!editor_last_name.empty() && !editor_first_name.empty()){
            if (editor_last_name.size() >= 3){
                bi2 += editor_first_name.front() + ". " + editor_last_name.front() + " et al.";
                break;
            }
            bi2 += editor_last_name.front() + ". " + (editor_first_name.front()[0]).toUpper() + ", ";
            editor_last_name.pop_front();
            editor_first_name.pop_front();
        }
        bi2 += "Ed.";
    }
    //Add translator
    if (!translator_last_name.empty()){
        bi2 += "; ";
        while (!translator_last_name.empty() && !translator_first_name.empty()){
            if (translator_last_name.size() >= 3){
                bi2 += translator_first_name.front() + ". " + translator_last_name.front() + " et al.";
                break;
            }
            bi2 += translator_last_name.front() + ". " + (translator_first_name.front()[0]).toUpper() + ", ";
            translator_last_name.pop_front();
            translator_first_name.pop_front();
        }
        bi2 += "Trans.";
    }

    //Add month and year
    bi2 += month.left(3) + ". ";
    bi2 += year + ", ";


    //Add url
    bi2 +=  web_url;


    vector<QString> k = {bi,bi2};
    return k;

}



static vector<QString> get_MLA_CN_bibliography_web(deque<QString> last_name, QString year, QString month,
                                       deque<QString> editor_last_name, deque<QString> translator_last_name,
                                       QString article_title, QString website_title, QString web_url)
{
    QString bi;
    QString bi2;


    //Add author information
    while (!last_name.empty()){
        if (last_name.size() >= 3){
            bi += last_name.front() + "等.";
            break;
        }
        bi += last_name.front() + "," ;
        last_name.pop_front();
    }


    //Add article title
    bi += (article_title == "")? "" : ("\"" + article_title + "\" ");


    //add website title
//    bi += (website_title == "")? "" : (website_title + ",");
    bi2 += ",";

    //Add editor
    if (!editor_last_name.empty()){
        bi2 += "编辑:";
        while (!editor_last_name.empty()){
            if (editor_last_name.size() >= 3){
                bi2 += editor_last_name.front() + "等,";
                break;
            }
            bi2 += editor_last_name.front() + ",";
            editor_last_name.pop_front();
        }
    }

    //Add translator
    if (!translator_last_name.empty()){
        bi2 += ";翻译:";
        while (!translator_last_name.empty()){
            if (translator_last_name.size() >= 3){
                bi2 += translator_last_name.front() + "等,";
                break;
            }
            bi2 += translator_last_name.front() + ",";
            translator_last_name.pop_front();
        }
    }

    //Add month and year
    if (month == "January") bi2 += "01";
    else if (month == "February") bi2 += "02";
    else if (month == "March") bi2 += "03";
    else if (month == "April") bi2 += "04";
    else if (month == "May") bi2 += "05";
    else if (month == "June") bi2 += "06";
    else if (month == "July") bi2 += "07";
    else if (month == "August") bi2 += "08";
    else if (month == "September") bi2 += "09";
    else if (month == "October") bi2 += "10";
    else if (month == "November") bi2 += "11";
    else if (month == "December") bi2 += "12";
    bi2 += " ";

    bi2 += year + ",";


    //Add url
    bi2 +=  web_url;


    vector<QString> k = {bi,bi2};
    return k;
}



static vector<QString> get_APA_EN_bibliography_book(deque<QString> last_name, deque<QString> first_name, QString year,
                                       deque<QString> editor_last_name, deque<QString> editor_first_name,
                                      deque<QString> translator_last_name, deque<QString> translator_first_name,
                                      QString position, QString publisher, QString start_page, QString end_page)  //no need for article_title
{
    QString bi;
    QString bi2;

    //Add author information
    int num_of_author = last_name.size();
    while (!last_name.empty() && !first_name.empty()){
        bi += last_name.front() + ", " + (first_name.front()[0]).toUpper() + ". ";
        last_name.pop_front();
        first_name.pop_front();
    }
    if (num_of_author >= 3){
        int au_comma_index = 0;
        for (int i = 0; i != num_of_author-1; i++){
            au_comma_index = bi.indexOf(",") + 1;
        }
        bi.replace(au_comma_index-1,1,"&");
    }


    //Add year
    bi += (year == "")? ("(" + year + ".).") : "";


    bi2 += ". ";

    //Add editor
    bool editor_translator_flag = (!editor_last_name.empty() || !translator_last_name.empty());
    if (editor_translator_flag) bi2 += "(";

    int num_of_editor = editor_last_name.size();
    while (!editor_last_name.empty() && !editor_first_name.empty()){
        bi2 += editor_last_name.front() + ". " + (editor_first_name.front()[0]).toUpper() + ", ";
        editor_last_name.pop_front();
        editor_first_name.pop_front();
    }
    if (num_of_editor >= 3){
        int au_comma_index = 0;
        for (int i = 0; i != num_of_editor-1; i++){
            au_comma_index = bi2.indexOf(",") + 1;
        }
        bi2.replace(au_comma_index-1,1,"&");
    }
    if (num_of_editor != 0) bi2 += "Ed.";


    //Add translator
    int num_of_translator = translator_last_name.size();
    if (num_of_translator != 0) bi2 += "; ";
    while (!translator_last_name.empty() && !translator_first_name.empty()){
        bi2 += translator_last_name.front() + ". " + (translator_first_name.front()[0]).toUpper() + ", ";
        translator_last_name.pop_front();
        translator_first_name.pop_front();
    }
    if (num_of_translator >= 3){
        int au_comma_index = 0;
        for (int i = 0; i != num_of_translator-1; i++){
            au_comma_index = bi.indexOf(",") + 1;
        }
        bi2.replace(au_comma_index-1,1,"&");
    }
    if (num_of_translator != 0) bi2 += "Trans.";
    if (editor_translator_flag) bi2 += "). ";


    //add page
    bi2 += (start_page != "")? ("pp." + start_page) : "";
    bi2 += (start_page != "" && end_page != "")? (" - " + end_page + ". ") : ". ";


    //add position and publisher
    bi2 += (position != "")? (position[0].toUpper() + position.mid(1)) : "";
    bi2 += (publisher != "")? ( QString(": ") + publisher[0].toUpper() + publisher.mid(1)) : "";
    if (position != "" || publisher != "") bi2 += ".";

    vector<QString> k = {bi,bi2};
    return k;
}




static vector<QString> get_APA_CN_bibliography_book(deque<QString> last_name, QString year,
                                       deque<QString> editor_last_name,
                                      deque<QString> translator_last_name,
                                      QString position, QString publisher, QString start_page, QString end_page)  //no need for article_title
{
    QString bi;
    QString bi2;

    //Add author information
    int num_of_author = last_name.size();
    while (!last_name.empty()){
        bi += last_name.front();
        last_name.pop_front();
        if (last_name.size() == 0) {
            bi += ". ";
        } else {
            bi += ",";
        }
    }


    //Add year
    bi += (year == "")? ("(" + year + ".).") : "";



    bi2 += ".";

    //Add editor
    bool editor_translator_flag = (!editor_last_name.empty() || !translator_last_name.empty());
    if (editor_translator_flag) bi2 += "(";

    int num_of_editor = editor_last_name.size();
    if (num_of_editor != 0) bi2 += "编辑:";
    while (!editor_last_name.empty()){
        bi2 += editor_last_name.front() + ",";
        editor_last_name.pop_front();
    }

    //Add translator
    int num_of_translator = translator_last_name.size();
    if (num_of_translator != 0) bi2 += ";翻译:";
    while (!translator_last_name.empty()){
        bi2 += translator_last_name.front() + ",";
        translator_last_name.pop_front();
    }

    if (editor_translator_flag) bi2 += ") ";


    //add page
    bi2 += (start_page != "")? ("pp." + start_page) : "";
    bi2 += (start_page != "" && end_page != "")? (" - " + end_page + ". ") : ". ";


    //add position and publisher
    bi2 += (position != "")? (position) : "";
    bi2 += (publisher != "")? ( ": " + publisher) : "";
    if (position != "" || publisher != "") bi2 += ".";

    vector<QString> k = {bi,bi2};
    return k;

}






static vector<QString> get_MLA_EN_bibliography_book(deque<QString> last_name, deque<QString> first_name, QString year,
                                       deque<QString> editor_last_name, deque<QString> editor_first_name,
                                      deque<QString> translator_last_name, deque<QString> translator_first_name,
                                      QString position, QString publisher, QString start_page, QString end_page)  //no need for article_title
{
    QString bi;
    QString bi2;


    //Add author information
    while (!last_name.empty() && !first_name.empty()){
        if (last_name.size() >= 3){
            bi += first_name.front() + ", " + last_name.front() + " et al.";
            break;
        }
        bi += last_name.front() + ", " + (first_name.front()[0]).toUpper() + ". ";
        last_name.pop_front();
        first_name.pop_front();
    }


    bi2 += ". ";


    //Add editor
    if (!editor_last_name.empty()){
        bi2 += "Ed. ";
        while (!editor_last_name.empty() && !editor_first_name.empty()){
            if (editor_last_name.size() >= 3){
                bi2 += editor_first_name.front() + ". " + editor_last_name.front() + " et al.";
                break;
            }
            bi2 += editor_last_name.front() + ". " + (editor_first_name.front()[0]).toUpper() + ", ";
            editor_last_name.pop_front();
            editor_first_name.pop_front();
        }
    }

    //Add translator
    if (!translator_last_name.empty()){
        bi2 += ". Trans. ";
        while (!translator_last_name.empty() && !translator_first_name.empty()){
            if (translator_last_name.size() >= 3){
                bi2 += translator_first_name.front() + ". " + translator_last_name.front() + " et al.";
                break;
            }
            bi2 += translator_last_name.front() + ". " + (translator_first_name.front()[0]).toUpper() + ", ";
            translator_last_name.pop_front();
            translator_first_name.pop_front();
        }
    }

    //add position and publisher
    bi2 += (position != "") ? (position[0].toUpper() + position.mid(1)) : "";
    bi2 += (publisher != "") ? ( QString(": ") + publisher[0].toUpper() + publisher.mid(1)) : "";
    if (position != "" || publisher != "") bi2 += ".";

    //add page
    bi2 += (start_page != "")? ("pp." + start_page) : "";
    bi2 += (start_page != "" && end_page != "")? (" - " + end_page + ", ") : ", ";


    //Add year
    bi2 += (year == "")? (year + ". ") : "";

    bi2 += "Print.";


    vector<QString> k = {bi,bi2};
    return k;

}




static vector<QString> get_MLA_CN_bibliography_book(deque<QString> last_name, QString year,
                                       deque<QString> editor_last_name,
                                      deque<QString> translator_last_name,
                                      QString position, QString publisher, QString start_page, QString end_page)  //no need for article_title
{
    QString bi;
    QString bi2;


    //Add author information
    while (!last_name.empty()){
        if (last_name.size() >= 3){
            bi += last_name.front() + "等.";
            break;
        }
        bi += last_name.front();
        last_name.pop_front();
        if (last_name.size() == 0) {
            bi += ". ";
        } else {
            bi += ",";
        }
    }


    bi2 += ". ";

    //Add editor
    if (!editor_last_name.empty()){
        bi2 += "编辑:";
        while (!editor_last_name.empty()){
            if (editor_last_name.size() >= 3){
                bi2 += editor_last_name.front() + "等,";
                break;
            }
            bi2 += editor_last_name.front() + ",";
            editor_last_name.pop_front();
        }
    }

    //Add translator
    if (!translator_last_name.empty()){
        bi2 += ";翻译:";
        while (!translator_last_name.empty()){
            if (translator_last_name.size() >= 3){
                bi2 += translator_last_name.front() + "等,";
                break;
            }
            bi2 += translator_last_name.front() + ",";
            translator_last_name.pop_front();
        }
    }


    //add position and publisher
    bi2 += (position != "")? (position) : "";
    bi2 += (publisher != "")? ( ": " + publisher) : "";
    if (position != "" || publisher != "") bi2 += ".";


    //Add year
    bi2 += (year == "")? (year + ". ") : "";

    //add page
    bi2 += (start_page != "")? ("pp." + start_page) : "";
    bi2 += (start_page != "" && end_page != "")? (" - " + end_page + ", ") : ", ";


    bi2 += "Print.";

    vector<QString> k = {bi,bi2};
    return k;

}


/*
 * This function could read the author/editor/translator's
 * lineedit, and put their names into coresponding deque.
 * trim and other string pre-process is included
 */
static void generate_author_deque(deque<QString> & last_name_base, deque<QString> & first_name_base,
                           QString last_name_line, QString first_name_line, bool multi_author, bool English){
    QString comma = (English)? ",": ",";
    if (!multi_author){ //one author
        last_name_base.push_back(last_name_line);
        first_name_base.push_back(first_name_line);
    } else {
        int stpos_last_name = 0;
        int stpos_first_name = 0;

        //generate last_name deque
        while (last_name_line.indexOf(comma,stpos_last_name) != -1){
            last_name_base.push_back(last_name_line.mid(stpos_last_name,last_name_line.indexOf(comma,stpos_last_name)-stpos_last_name));
            stpos_last_name = last_name_line.indexOf(comma,stpos_last_name) + 1;
        }
        last_name_base.push_back(last_name_line.mid(stpos_last_name));

        //generate first_name deque
        while (first_name_line.indexOf(comma,stpos_first_name) != -1 && English){
            first_name_base.push_back(first_name_line.mid(stpos_first_name,first_name_line.indexOf(comma,stpos_first_name)-stpos_first_name));
            stpos_first_name = first_name_line.indexOf(comma,stpos_first_name) + 1;
        }
        first_name_base.push_back(first_name_line.mid(stpos_first_name));
    }
}



/*
 * this function is to check whether QString qs include chinese character
 * return 0: no chinese character; 1: have chinese character
 */
static int IncludeChinese(QString qs)
{
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

   char* str;
   QByteArray ba = qs.toLocal8Bit();
   str=ba.data();
   char c;
   while(1)
   {
       c=*str++;
       if (c==0) break;  //如果到字符串尾则说明该字符串没有中文字符
       if (c&0x80)        //如果字符高位为1且下一字符高位也是1则有中文字符
               if (*str & 0x80) return 1;
   }
   return 0;
}

/*
 * this function could replace all target characters with replace_value characters in QString line
 */
static QString replace_all(QString line, QString target, QString replace_value){
    int st_pos = 0;
    while (line.indexOf(target,st_pos) != string::npos){
        line = line.replace(line.indexOf(target), 1, replace_value);
        st_pos = line.indexOf(target) + 1;
    }
    return line;
}






                            /*
                             * ///////////////    Yu's part     ///////////////
                             */


static QString get_APA_CN_bibliography_magazine(deque<QString> last_name, QString year, deque<QString> editor_last_name,
                                                deque<QString> translator_last_name, QString article_title, QString magzine_title,
                                                QString start_page, QString end_page)
{
    QString bi;
    int i = 0;
    while (!last_name.empty()){
        if (i == 0){
            bi += last_name.front();
        } else {
            bi += "," + last_name.front();
        }
        last_name.pop_front();
        i++;
    }
    bi += (year == "")? "." : ("(" + year + ")" + ".");
    bi += (article_title == "")? "" : (article_title + ".");

    //Add editor name bar's information
    while (!editor_last_name.empty()){
        bi += editor_last_name.front() + ",";
        editor_last_name.pop_front();
    }
    bi += "编辑;";

    //Add translator name bar's information
    while (!translator_last_name.empty()){
        bi += translator_last_name.front() + ",";
        translator_last_name.pop_front();
    }
    bi += "翻译;";

    bi += (magzine_title == "")? "" : (magzine_title);
    bi += (start_page == "")? "" : ("," + start_page + "-");
    bi += (end_page == "")? "." : (end_page + ".");

    return bi;
}


static QString get_APA_CN_bibliography_newspaper(deque<QString> last_name, QString year, deque<QString> editor_last_name,
                                                deque<QString> translator_last_name, QString article_title, QString newspaper_title,
                                                QString start_page, QString end_page)
{
    QString bi;
    int i = 0;
    while (!last_name.empty()){
        if (i == 0){
            bi += last_name.front();
        } else {
            bi += "," + last_name.front();
        }
        last_name.pop_front();
        i++;
    }
    bi += (year == "")? "." : ("(" + year + ")" + ".");
    bi += (article_title == "")? "" : (article_title + ".");

    //Add editor name bar's information
    while (!editor_last_name.empty()){
        bi += editor_last_name.front() + ",";
        editor_last_name.pop_front();
    }
    bi += "编辑;";

    //Add translator name bar's information
    while (!translator_last_name.empty()){
        bi += translator_last_name.front() + ",";
        translator_last_name.pop_front();
    }
    bi += "翻译;";

    bi += (newspaper_title == "")? "" : (newspaper_title);
    bi += (start_page == "")? "" : ("," + start_page + "-");
    bi += (end_page == "")? "." : (end_page + ".");

    return bi;
}

static QString get_APA_EN_bibliography_magazine(deque<QString> last_name, deque<QString> first_name, QString year,
                                deque<QString> editor_last_name, deque<QString> editor_first_name,
                                deque<QString> translator_last_name, deque<QString> translator_first_name,
                                                QString article_title, QString magazine_title, QString start_page, QString end_page)
{

    //Add author information
    QString bi;
    int num_of_author = last_name.size();
    while (!last_name.empty() && !first_name.empty()){
        bi += last_name.front() + ", " + (first_name.front()[0]).toUpper() + ". ";
        last_name.pop_front();
        first_name.pop_front();
    }
    if (num_of_author >= 3){
        int au_comma_index = 0;
        for (int i = 0; i != num_of_author-1; i++){
            au_comma_index = bi.indexOf(",") + 1;
        }
        bi.replace(au_comma_index-1,1,"&");
    }

    bi += (year == "")? ". " : ("(" + year + ")" + ". ");
    bi += (article_title == "")? "" : (article_title + ". ");

    //Test whether editor or translator exist,
    //if so, we build a struct for it
    bool editor_trans_exist = !editor_last_name.empty() || !translator_last_name.empty();
    if (editor_trans_exist) bi += "(";
    //Add editor information
    if (!editor_last_name.empty() && !editor_first_name.empty()){
        int num_of_editor = last_name.size();
        while(!editor_last_name.empty() && !editor_first_name.empty()){
            bi += (editor_first_name.front()[0]).toUpper();
            bi += ". " + editor_last_name.front() + ", " ;
            editor_last_name.pop_front();
            editor_first_name.pop_front();
        }
        if (num_of_editor >= 3){
            int ed_comma_index = 0;
            for (int i = 0; i != num_of_editor -1; i++){
                ed_comma_index = bi.indexOf(",") + 1;
            }
            bi.replace(ed_comma_index-1,1,"&");
        }
        bi += "Eds.; ";
    }
    //Add translator information
    if (!translator_last_name.empty() && !translator_first_name.empty()){
        int num_of_editor = last_name.size();
        while(!translator_last_name.empty() && !translator_first_name.empty()){
            bi += (translator_first_name.front()[0]).toUpper();
            bi += ". " + translator_last_name.front() + ", " ;
            translator_last_name.pop_front();
            translator_first_name.pop_front();
        }
        if (num_of_editor >= 3){
            int ed_comma_index = 0;
            for (int i = 0; i != num_of_editor -1; i++){
                ed_comma_index = bi.indexOf(",") + 1;
            }
            bi.replace(ed_comma_index-1,1,"&");
        }
        bi += "Trans.; ";
    }
    if (editor_trans_exist) bi += "). ";


    bi += (magazine_title == "")? "" : (magazine_title);
    bi += ". pp. ";
    bi += (start_page == "")? "" : (start_page + "-");
    bi += (end_page == "")? "." : (end_page + ".");

    return bi;
}


static QString get_APA_EN_bibliography_newspaper(deque<QString> last_name, deque<QString> first_name, QString year,
                                deque<QString> editor_last_name, deque<QString> editor_first_name,
                                deque<QString> translator_last_name, deque<QString> translator_first_name,
                                                QString article_title, QString newspaper_title, QString start_page, QString end_page)
{

    //Add author information
    QString bi;
    int num_of_author = last_name.size();
    while (!last_name.empty() && !first_name.empty()){
        bi += last_name.front() + ", " + (first_name.front()[0]).toUpper() + ". ";
        last_name.pop_front();
        first_name.pop_front();
    }
    if (num_of_author >= 3){
        int au_comma_index = 0;
        for (int i = 0; i != num_of_author-1; i++){
            au_comma_index = bi.indexOf(",") + 1;
        }
        bi.replace(au_comma_index-1,1,"&");
    }

    bi += (year == "")? ". " : ("(" + year + ")" + ". ");
    bi += (article_title == "")? "" : (article_title + ". ");

    //Test whether editor or translator exist,
    //if so, we build a struct for it
    bool editor_trans_exist = !editor_last_name.empty() || !translator_last_name.empty();
    if (editor_trans_exist) bi += "(";
    //Add editor information
    if (!editor_last_name.empty() && !editor_first_name.empty()){
        int num_of_editor = last_name.size();
        while(!editor_last_name.empty() && !editor_first_name.empty()){
            bi += (editor_first_name.front()[0]).toUpper();
            bi += ". " + editor_last_name.front() + ", " ;
            editor_last_name.pop_front();
            editor_first_name.pop_front();
        }
        if (num_of_editor >= 3){
            int ed_comma_index = 0;
            for (int i = 0; i != num_of_editor -1; i++){
                ed_comma_index = bi.indexOf(",") + 1;
            }
            bi.replace(ed_comma_index-1,1,"&");
        }
        bi += "Eds.; ";
    }
    //Add translator information
    if (!translator_last_name.empty() && !translator_first_name.empty()){
        int num_of_editor = last_name.size();
        while(!translator_last_name.empty() && !translator_first_name.empty()){
            bi += (translator_first_name.front()[0]).toUpper();
            bi += ". " + translator_last_name.front() + ", " ;
            translator_last_name.pop_front();
            translator_first_name.pop_front();
        }
        if (num_of_editor >= 3){
            int ed_comma_index = 0;
            for (int i = 0; i != num_of_editor -1; i++){
                ed_comma_index = bi.indexOf(",") + 1;
            }
            bi.replace(ed_comma_index-1,1,"&");
        }
        bi += "Trans.; ";
    }
    if (editor_trans_exist) bi += "). ";


    bi += (newspaper_title == "")? "" : (newspaper_title);
    bi += ". pp. ";
    bi += (start_page == "")? "" : (start_page + "-");
    bi += (end_page == "")? "." : (end_page + ".");

    return bi;
}

static QString get_MLA_EN_bibliography_magazine(deque<QString> last_name, deque<QString> first_name,QString year,
                                                deque<QString> editor_last_name, deque<QString> editor_first_name,
                                                deque<QString> translator_last_name, deque<QString> translator_first_name,
                                                QString article_title, QString magzine_title, QString start_page, QString end_page)
{
    QString bi;

    //Add author information
    while (!last_name.empty() && !first_name.empty()){
        if (last_name.size() >= 3){
            bi += first_name.front() + " " + last_name.front() + " et al.";
            break;
        }
        bi += first_name.front() + " " + last_name.front() + ", ";
        last_name.pop_front();
        first_name.pop_front();
    }
    bi.replace(bi.indexOf(",",string::npos),1,". ");


    bi += (article_title == "")? "" : ("\"" + article_title + ".\" ");
    bi += (magzine_title == "")? "" : (magzine_title);


    //Test whether editor or translator exist,
    //if so, we build a struct for it

    //Add editor information
    if (!editor_last_name.empty() && !editor_first_name.empty()){
        bi += "Edited by ";
        while (!editor_last_name.empty() && !editor_first_name.empty()){
            if (editor_last_name.size() >= 3){
                bi += editor_first_name.front() + " " + editor_last_name.front() + " et al.";
                break;
            }
            bi += editor_first_name.front() + " " + editor_last_name.front() + ", ";
            editor_last_name.pop_front();
            editor_first_name.pop_front();
        }
        bi.replace(bi.indexOf(",",string::npos),1,". ");
    }


    //Add translator information
    if (!translator_last_name.empty() && !translator_first_name.empty()){
        bi += "Translated by ";
        while(!translator_last_name.empty() && !translator_first_name.empty()){
            if (translator_last_name.size() >= 3){
                bi += translator_first_name.front() + " " + translator_last_name.front() + " et al.";
                break;
            }
            bi += translator_first_name.front() + " " + translator_last_name.front() + ", ";
            translator_last_name.pop_front();
            translator_first_name.pop_front();
        }
        bi.replace(bi.indexOf(",",string::npos),1,". ");
    }

    bi += (year == "")? ":": (year + ": ");
    bi += (start_page == "")? "" : (start_page + "-");
    bi += (end_page == "")? "." : (end_page + ".");
    bi += "Print.";

    return bi;
}



static QString get_MLA_EN_bibliography_newspaper(deque<QString> last_name, deque<QString> first_name,QString year,
                                                deque<QString> editor_last_name, deque<QString> editor_first_name,
                                                deque<QString> translator_last_name, deque<QString> translator_first_name,
                                                QString article_title, QString newspaper_title, QString start_page, QString end_page)
{
    QString bi;

    //Add author information
    while (!last_name.empty() && !first_name.empty()){
        if (last_name.size() >= 3){
            bi += first_name.front() + " " + last_name.front() + " et al.";
            break;
        }
        bi += first_name.front() + " " + last_name.front() + ", ";
        last_name.pop_front();
        first_name.pop_front();
    }
    bi.replace(bi.indexOf(",",string::npos),1,". ");


    bi += (article_title == "")? "" : ("\"" + article_title + ".\" ");
    bi += (newspaper_title == "")? "" : (newspaper_title);


    //Test whether editor or translator exist,
    //if so, we build a struct for it

    //Add editor information
    if (!editor_last_name.empty() && !editor_first_name.empty()){
        bi += "Edited by ";
        while (!editor_last_name.empty() && !editor_first_name.empty()){
            if (editor_last_name.size() >= 3){
                bi += editor_first_name.front() + " " + editor_last_name.front() + " et al.";
                break;
            }
            bi += editor_first_name.front() + " " + editor_last_name.front() + ", ";
            editor_last_name.pop_front();
            editor_first_name.pop_front();
        }
        bi.replace(bi.indexOf(",",string::npos),1,". ");
    }


    //Add translator information
    if (!translator_last_name.empty() && !translator_first_name.empty()){
        bi += "Translated by ";
        while(!translator_last_name.empty() && !translator_first_name.empty()){
            if (translator_last_name.size() >= 3){
                bi += translator_first_name.front() + " " + translator_last_name.front() + " et al.";
                break;
            }
            bi += translator_first_name.front() + " " + translator_last_name.front() + ", ";
            translator_last_name.pop_front();
            translator_first_name.pop_front();
        }
        bi.replace(bi.indexOf(",",string::npos),1,". ");
    }

    bi += (year == "")? ":": (year + ": ");
    bi += (start_page == "")? "" : (start_page + "-");
    bi += (end_page == "")? "." : (end_page + ".");
    bi += "Print.";

    return bi;
}

static QString get_MLA_CN_bibliography_magazine(deque<QString> last_name, QString year,
                                                deque<QString> editor_last_name, deque<QString> translator_last_name,
                                                QString article_title, QString magzine_title, QString start_page, QString end_page)
{
    QString bi;

    while (!last_name.empty()){
        bi += last_name.front() + ",";
        last_name.pop_front();
    }
    bi.replace(bi.indexOf(",",string::npos),1,".");
    bi += (article_title == "")? "" : ("\"" + article_title + ".\" ");
    bi += (magzine_title == "")? "" : (magzine_title + ",");


    //Test whether editor or translator exist,
    //if so, we build a struct for it

    //Add editor information
    if (!editor_last_name.empty()){
        bi += "编辑:";
        while (!editor_last_name.empty()){
            if (editor_last_name.size() >= 3){
                bi += editor_last_name.front() + "等.";
                break;
            }
            bi += editor_last_name.front() + ", ";
            editor_last_name.pop_front();
        }
        bi.replace(bi.indexOf(",",string::npos),1,". ");
    }


    //Add translator information
    if (!translator_last_name.empty()){
        bi += "翻译: ";
        while(!translator_last_name.empty()){
            if (translator_last_name.size() >= 3){
                bi += translator_last_name.front() + "等.";
                break;
            }
            bi += translator_last_name.front() + ", ";
            translator_last_name.pop_front();
        }
        bi.replace(bi.indexOf(",",string::npos),1,". ");
    }


    bi += (year == "")? ":": (year + ":");
    bi += (start_page == "")? "" : (" " + start_page + "-");
    bi += (end_page == "")? "." : (end_page + ".");
    bi += "印刷.";

    return bi;
}



static QString get_MLA_CN_bibliography_newspaper(deque<QString> last_name, QString year,
                                                deque<QString> editor_last_name, deque<QString> translator_last_name,
                                                QString article_title, QString newspaper_title, QString start_page, QString end_page)
{
    QString bi;

    while (!last_name.empty()){
        bi += last_name.front() + ",";
        last_name.pop_front();
    }
    bi.replace(bi.indexOf(",",string::npos),1,".");
    bi += (article_title == "")? "" : ("\"" + article_title + ".\" ");
    bi += (newspaper_title == "")? "" : (newspaper_title + ",");


    //Test whether editor or translator exist,
    //if so, we build a struct for it

    //Add editor information
    if (!editor_last_name.empty()){
        bi += "编辑:";
        while (!editor_last_name.empty()){
            if (editor_last_name.size() >= 3){
                bi += editor_last_name.front() + "等.";
                break;
            }
            bi += editor_last_name.front() + ", ";
            editor_last_name.pop_front();
        }
        bi.replace(bi.indexOf(",",string::npos),1,". ");
    }


    //Add translator information
    if (!translator_last_name.empty()){
        bi += "翻译: ";
        while(!translator_last_name.empty()){
            if (translator_last_name.size() >= 3){
                bi += translator_last_name.front() + "等.";
                break;
            }
            bi += translator_last_name.front() + ", ";
            translator_last_name.pop_front();
        }
        bi.replace(bi.indexOf(",",string::npos),1,". ");
    }


    bi += (year == "")? ":": (year + ":");
    bi += (start_page == "")? "" : (" " + start_page + "-");
    bi += (end_page == "")? "." : (end_page + ".");
    bi += "印刷.";

    return bi;
}

#endif // UTILS_H
