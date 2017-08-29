#include "editpage.h"
#include "dataaccess.h"
#include "ui_editpage.h"

EditPage::EditPage(DataAccess &dal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditPage),
    m_dal(dal)
{
    ui->setupUi(this);
}

EditPage::~EditPage()
{
    delete ui;
}

void EditPage::on_tagEdit_returnPressed()
{
    QString value = ui->tagEdit->text();

    while (value.endsWith('-'))
        value.chop(1);
    while (value.contains("--"))
        value.replace("--", "-");

    if (!value.isEmpty())
    {
        auto matches = ui->tagList->findItems(value, Qt::MatchExactly);
        if (matches.isEmpty())
        {
            ui->tagList->addItem(value);
            ui->tagEdit->clear();
            ui->tagEdit->setFocus();
        }
    }
}

void EditPage::on_pushButton_clicked()
{
    QString item = ui->lineEdit->text();
    QStringList tags = ui->tagList->toStringList();

    m_dal.InsertOrUpdate(item, tags);
}
