#include "editpage.h"
#include "dataaccess.h"
#include "ui_editpage.h"
#include "QFileDialog"

EditPage::EditPage(DataAccess &dal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditPage),
    m_dal(dal)
{
    ui->setupUi(this);
    ui->tagEdit->setBuddyList(ui->tagList);
}

EditPage::~EditPage()
{
    delete ui;
}

void EditPage::on_browseButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select File", "", "");

    if (!filename.isEmpty())
        ui->lineEdit->setText(filename);
}

void EditPage::on_pushButton_clicked()
{
    QString item = ui->lineEdit->text();
    QStringList tags = ui->tagList->toStringList();

    m_dal.InsertOrUpdate(item, tags);

    ui->lineEdit->clear();
    ui->tagEdit->clear();
    ui->tagList->clear();
    ui->lineEdit->setFocus();
}
