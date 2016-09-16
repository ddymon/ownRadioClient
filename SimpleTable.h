#ifndef SIMPLETABLE_H
#define SIMPLETABLE_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QObject>
#include <QTableView>
#include <Qt>
#include <QtDebug>

class SimpleTableModel : public QAbstractTableModel
{
    Q_OBJECT

    struct SimpleColumn {
        QStringList *clist;
        QString header;
    };
    int ccount, rcount;
    SimpleColumn *cdata;

public:
    SimpleTableModel(int count, QStringList *colums[], QString headers[]);
    ~SimpleTableModel();

    void adjustRows();
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
public slots:
    void incCol3AsInt(int row, int matchCount);
    void setCol4AsDbl(int row, double stdtime);
};

#endif // SIMPLETABLE_H
