#include "SimpleTable.h"

SimpleTableModel::SimpleTableModel(int count, QStringList *colums[], QString headers[]) {
    ccount = count;
    cdata = new SimpleColumn[ccount];
    for (int i = 0; i < ccount; i++) {
        cdata[i].clist = colums[i];
        cdata[i].header = headers[i];
    }
    rcount = cdata[0].clist->count();
}

SimpleTableModel::~SimpleTableModel() {
    delete []cdata;
}

void SimpleTableModel::adjustRows() {
    int delta = rcount - cdata[0].clist->count();
    if (delta < 0) {
        beginInsertRows(QModelIndex(), 0, -delta - 1);
        insertRows(0, -delta);
        endInsertRows();
    }
    else if (delta > 0) {
        beginRemoveRows(QModelIndex(), 0, delta - 1);
        removeRows(0, delta);
        endRemoveRows();
    }
    rcount = cdata[0].clist->count();
}

int SimpleTableModel::columnCount(const QModelIndex & /* parent */) const {
    return ccount;
}

int SimpleTableModel::rowCount(const QModelIndex & /* parent */) const {
    return cdata[0].clist->count();
}

QVariant SimpleTableModel::data(const QModelIndex &index, int role ) const {
    if (role != Qt::DisplayRole) return QVariant();
    return QVariant(cdata[index.column()].clist->at(index.row()));
}

QVariant SimpleTableModel::headerData(int section, Qt::Orientation orientation, int role ) const {
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation != Qt::Horizontal) return QVariant();
    return QVariant(cdata[section].header);
}

Qt::ItemFlags SimpleTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags rflags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if (index.column() > 2) rflags |= Qt::ItemIsEditable;
    return rflags;
}

bool SimpleTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    cdata[index.column()].clist->replace(index.row(), value.toString());
    emit dataChanged(index, index);
    return true;
    role = role;
}

void SimpleTableModel::incCol3AsInt(int row, int matchCount)
{
    QModelIndex mix = createIndex(row, 2);
    QVariant curr = data(mix);
    int currInt = curr.toString().toInt() + matchCount;
    bool rc = setData(mix, QVariant(currInt));
    if (!rc) {
        qDebug() << "incCol3AsInt failed:" << row;
    }
}

void SimpleTableModel::setCol4AsDbl(int row, double stdtime)
{
    QModelIndex mix = createIndex(row, 3);
    bool rc = setData(mix, QVariant(stdtime));
    if (!rc) {
        qDebug() << "setCol4AsDbl failed:" << row;
    }
}
