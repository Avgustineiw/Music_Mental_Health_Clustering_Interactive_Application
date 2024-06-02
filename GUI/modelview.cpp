#include "modelview.h"

#include <QFile>
#include <QTextStream>

#include <stdexcept>

ModelView::ModelView(QObject* parent)
  : QAbstractTableModel(parent)
{}

//tableView_clusterize Tab2
ModelView::ModelView(const vector<Point>& points, QObject* parent)
  : QAbstractTableModel(parent)
{
    for (unsigned int i = 0; i < points.size(); ++i)
  {
    QVector<QVariant> row2;

    //row2.append(QVariant(int(points[i].GetPointId())));
    row2.append(QVariant(double(points[i].GetX())));
    row2.append(QVariant(double(points[i].GetY())));
    row2.append(QVariant(int(points[i].GetClusterId())));

    data_.append(row2);
  }
}

//tableView Tab1
ModelView::ModelView(const QString& fileName, QObject* parent)
  : QAbstractTableModel(parent)
{
  QFile file(fileName);

  if (file.open(QIODevice::ReadOnly)) {
    QTextStream stream(&file);

    QString     head  = stream.readLine();
    QStringList parts = head.split(',');

    if (parts.size() != 33) {
      throw std::invalid_argument("wrong file");
    }

    QStringList sourceHeader = {"Timestamp", "Age", "Primary streaming service", "Hours per day", "While working",
                                "Instrumentalist", "Composer", "Fav genre", "Exploratory", "Foreign languages",
                                "BPM", "Frequency [Classical]", "Frequency [Country]", "Frequency [EDM]", "Frequency [Folk]",
                                "Frequency [Gospel]", "Frequency [Hip hop]", "Frequency [Jazz]", "Frequency [K pop]",
                                "Frequency [Latin]", "Frequency [Lofi]", "Frequency [Metal]", "Frequency [Pop]", "Frequency [R&B]",
                                "Frequency [Rap]", "Frequency [Rock]", "Frequency [Video game music]", "Anxiety", "Depression",
                                "Insomnia", "OCD", "Music effects", "Permissions"};
    for (qsizetype i = 0; i < 33; ++i)
    {
      if (parts[i] != sourceHeader[i]) {
        throw std::invalid_argument("wrong file");
      }
    }

    while (!stream.atEnd())
    {
      QString line = stream.readLine();
      auto rawData = line.split(',');

      if (rawData.size() != 33) {
          throw std::invalid_argument("wrong file");
      }
      QVector<QVariant> row;
      qsizetype i = 0;

      while (i < rawData.size())
      {
        if (i == 1 || (i >= 27 && i <= 31)) {
          if (i == 31) {
            if (rawData[i] == "Improve") {
              row.append(QVariant(int(1)));
            }
            else {
              row.append(QVariant(int(0)));
            }
          }
          else {
            row.append(QVariant(rawData[i].toUInt()));
          }
        }
        else if (i == 3) {
          row.append(QVariant(rawData[i].toDouble()));
        }
        else if (i >= 5 && i <= 6) {

          bool instrumentalist = rawData[i]     == "Yes" ? true : false;
          bool composer        = rawData[i + 1] == "Yes" ? true : false;
          row.append(QVariant(bool(instrumentalist || composer)));
          ++i;
        }
        else if (i >= 11 && i <= 26) {
          uint32_t sum = 0;
          for (; i <= 26; ++i)
          {
            if (rawData[i] == "Rarely") {
              sum += 1;
            }
            else if (rawData[i] == "Sometimes") {
              sum += 2;
            }
            else if (rawData[i] == "Very frequently") {
              sum += 3;
            }
          }
          row.append(QVariant(uint32_t(sum)));
          --i;
        }
        ++i;
      }
      data_.append(row);
    }
    file.close(); 
  }
}

int ModelView::rowCount(const QModelIndex& parent) const
{
  if (parent.isValid()) {
    return 0;
  }
  return data_.size();
}

int ModelView::columnCount(const QModelIndex& parent) const
{
  if (parent.isValid()) {
    return 0;
  }
  return header_.size();
}

QVariant ModelView::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    try {
      return data_[index.row()][index.column()];
    }
    catch (...) {
      return QVariant();
    }
  }
  return QVariant();
}

QVariant ModelView::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }
  if (orientation == Qt::Horizontal) {
    return header_[section];
  }
  return QVariant(section + 1);
}

const QVector<QVector<QVariant>>& ModelView::getData() const
{
  return data_;
}

void ModelView::setHeader(const QStringList& headers)
{
  this->header_ = headers;
}


void ModelView::addRow(const QVector<QVariant>& rowData)
{
  if (rowData.size() != this->columnCount()) {
    return;
  }
  int rowCnt = this->rowCount();
  this->beginInsertRows(QModelIndex(), rowCnt, rowCnt);
  data_.append(rowData);
  this->endInsertRows();
}

void ModelView::removeRow(const qsizetype& idxRow)
{
  beginRemoveRows(QModelIndex(), idxRow, idxRow);
  data_.remove(idxRow);
  endRemoveRows();
}

void ModelView::editRow(const qsizetype& idxRow, const ModelView::ContainerData& rowData)
{
  beginRemoveRows(QModelIndex(), idxRow, idxRow);
  data_.removeAt(idxRow);
  endRemoveRows();

  beginInsertRows(QModelIndex(), idxRow, idxRow);
  data_.insert(idxRow, rowData);
  endInsertRows();
}

const ModelView::ContainerData& ModelView::getRow(const qsizetype& idxRow) const
{
  if (idxRow < 0 || idxRow > this->rowCount()) {
    throw std::out_of_range("Row index is out of range");
  }
  return data_[idxRow];
}

void ModelView::clearData()
{
  beginResetModel();
  data_.clear();
  endResetModel();
}
