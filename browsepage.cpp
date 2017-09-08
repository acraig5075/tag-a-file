#include "browsepage.h"
#include "ui_browsepage.h"
#include "dataaccess.h"
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QInputDialog>


BrowsePage::BrowsePage(DataAccess &dal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrowsePage),
    m_dal(dal)
{
    ui->setupUi(this);

    ui->filesButton->setCheckable(true);
    ui->tagsButton->setCheckable(true);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);

    m_filesModel = new QSqlQueryModel(this);
    m_tagsModel = new QSqlQueryModel(this);

    m_dal.RefreshItemsModel(*m_filesModel);
    m_dal.RefreshTagsModel(*m_tagsModel);

    on_filesButton_clicked();

    QAction *actionSearch = new QAction("Search", this);
    QAction *actionEdit = new QAction("Edit", this);
    QAction *actionDelete = new QAction("Delete", this);

    ui->tableView->addAction(actionSearch);
    ui->tableView->addAction(actionEdit);
    ui->tableView->addAction(actionDelete);

    QObject::connect(actionSearch, SIGNAL(triggered(bool)), this, SLOT(onSearchMenu()));
    QObject::connect(actionEdit, SIGNAL(triggered(bool)), this, SLOT(onEditMenu()));
    QObject::connect(actionDelete, SIGNAL(triggered(bool)), this, SLOT(onDeleteMenu()));
}

BrowsePage::~BrowsePage()
{
    delete ui;
}

void BrowsePage::setActive()
{
    m_dal.RefreshItemsModel(*m_filesModel);
    m_dal.RefreshTagsModel(*m_tagsModel);
}

void BrowsePage::on_filesButton_clicked()
{
    ui->filesButton->setChecked(true);
    ui->label->setText("All files:");
    ui->tableView->setModel(m_filesModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setColumnHidden(0, true);
}

void BrowsePage::on_tagsButton_clicked()
{
    ui->tagsButton->setChecked(true);
    ui->label->setText("All tags:");
    ui->tableView->setModel(m_tagsModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(false);
    ui->tableView->setColumnHidden(0, true);
}

int BrowsePage::getSelectedID()
{
    QSqlQueryModel *activeModel = nullptr;
    if (ui->filesButton->isChecked())
        activeModel = m_filesModel;
    else
        activeModel = m_tagsModel;

    QItemSelectionModel *selection = ui->tableView->selectionModel();
    if (selection && selection->hasSelection())
    {
        QModelIndexList indices = selection->selectedIndexes();
        if (indices.size() > 0)
        {
            QSqlRecord record = activeModel->record(indices[0].row());
            QVariant data = record.value(0);
            return data.toInt();
        }
    }

    return 0;
}

void BrowsePage::onSearchMenu()
{
    int id = getSelectedID();

    if (ui->filesButton->isChecked())
        emit searchFile(id);
    else
        emit searchTag(id);
}

void BrowsePage::onEditMenu()
{
    int id = getSelectedID();
    bool ok = false;

    if (ui->filesButton->isChecked())
    {
        QString oldValue = m_dal.GetItemContent(id);
        QString newValue = QInputDialog::getText(this, "Rename Item", "Enter new value for item", QLineEdit::Normal, oldValue, &ok);
        if (ok)
            ok = ValidateNewItemContent(newValue);
        if (ok)
            m_dal.SetItemContent(id, newValue);
    }
    else
    {
        QString oldValue = m_dal.GetTagTitle(id);
        QString newValue = QInputDialog::getText(this, "Rename Tag", "Enter new value for tag", QLineEdit::Normal, oldValue, &ok);
        if (ok)
            ok = ValidateNewTagTitle(newValue);
        if (ok)
            m_dal.SetTagTitle(id, newValue);
    }

    if (ok)
        refreshTableView();
}

void BrowsePage::onDeleteMenu()
{
    int id = getSelectedID();

    if (id > 0 && QMessageBox::No == QMessageBox::question(this, "Confirm", "Are you sure you want to permananently delete this value?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
        return;

    if (ui->filesButton->isChecked())
        m_dal.DeleteItem(id);
    else
        m_dal.DeleteTag(id);

    refreshTableView();
}

void BrowsePage::refreshTableView()
{
    if (ui->filesButton->isChecked())
    {
        m_dal.RefreshItemsModel(*m_filesModel);
        ui->tableView->setModel(m_filesModel);
    }
    else
    {
        m_dal.RefreshTagsModel(*m_tagsModel);
        ui->tableView->setModel(m_tagsModel);
    }
}

bool BrowsePage::ValidateNewItemContent(QString &content)
{
    if (content.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Illegal format. I expect a non-empty string.");
        return false;
    }

    int id = m_dal.GetItemID(content);
    if (id > 0)
    {
        QMessageBox::warning(this, "Warning", "This item is already in use.");
        return false;
    }

    return true;
}

bool BrowsePage::ValidateNewTagTitle(QString &title)
{
    if (title.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Illegal format. I expect a non-empty string.");
        return false;
    }

    title = title.replace(' ', '-');
    title = title.toLower();
    QRegExp rx("^[a-zA-Z0-9][a-zA-Z0-9 -]+$");
    if (rx.indexIn(title) < 0)
    {
        QMessageBox::warning(this, "Warning", "Illegal format. I expect only alphanumeric characters and hyphens.");
        return false;
    }

    int id = m_dal.GetTagID(title);
    if (id > 0)
    {
        QMessageBox::warning(this, "Warning", QString("Tag %1 is already in use.").arg(title));
        return false;
    }

    return true;
}
