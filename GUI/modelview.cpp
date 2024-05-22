#include "modelview.h"

#include <QFile>

#include <stdexcept>
#include "Core/clusteringResult.h"

ModelView::ModelView(QObject* parent)
  : QAbstractTableModel(parent)
{}

//ModelView::ModelView(const QVector<QVector<QVariant> >& _data, QObject* parent) //
//{
// this->data_ = _data;
//}


ModelView::ModelView(const QString& fileName, QObject* parent) //
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
