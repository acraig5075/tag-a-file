#include "editpage.h"
#include "dataaccess.h"
#include "ui_editpage.h"
#include <QFileDialog>
#include <QCompleter>
#include <QFileSystemModel>
#include <QSqlQueryModel>

EditPage::EditPage(DataAccess &dal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditPage),
    m_dal(dal)
{
    ui->setupUi(this);

    ui->tagEdit->setBuddyList(ui->tagList);
    ui->tagEdit->setPlaceholderText("Enter to accept");

    m_tagModel = new QSqlQueryModel(this);
    m_dal.RefreshTagsModel(*m_tagModel);
    ui->tagEdit->setTagCompleter(*m_tagModel);

    QFileSystemModel *model = new QFileSystemModel(this);
    QCompleter *completer = new QCompleter(model, this);
    model->setRootPath("C:\\");
    completer->setModelSorting(QCompleter::CaseSensitivelySortedModel);
    ui->lineEdit->setCompleter(completer);

    QObject::connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(resetTagList()));
}

EditPage::~EditPage()
{
    delete ui;
}

void EditPage::on_browseButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select File", "", "");

    if (!filename.isEmpty())
    {
        ui->lineEdit->setText(QDir::toNativeSeparators(filename));
        resetTagList();
    }
}

void EditPage::resetTagList()
{
    ui->tagList->clear();

    QString filename = ui->lineEdit->text();

    if (!filename.isEmpty())
    {
        QStringList tags = m_dal.GetTagsForItem(filename);
        ui->tagList->addItems(tags);

        if (!tags.isEmpty())
            ui->pushButton->setText("Update");
    }
}

void EditPage::on_pushButton_clicked()
{
    QString item = ui->lineEdit->text();
    QStringList tags = ui->tagList->toStringList();

    m_dal.InsertOrUpdate(item, tags);
    m_dal.RefreshTagsModel(*m_tagModel);

    ui->lineEdit->clear();
    ui->tagEdit->clear();
    ui->tagList->clear();
    ui->lineEdit->setFocus();
    ui->tagEdit->setTagCompleter(*m_tagModel);
    ui->pushButton->setText("Add");
}

void EditPage::editContent(const QString &content)
{
    ui->lineEdit->setText(content);

    resetTagList();
}
