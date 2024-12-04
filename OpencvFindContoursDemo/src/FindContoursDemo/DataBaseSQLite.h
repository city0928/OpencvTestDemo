#pragma once
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <iostream>

#include "Logger.h"

#define QStr2StdStr(X) X.toStdString()

using Logur = LinkSenseAIFI::Logur;

template <typename TD>
class DataBaseSQLite
{
  public:
    explicit DataBaseSQLite(const QString& dataBaseName, const QString& tableName);
    ~DataBaseSQLite();

    bool IsExistTable(const QString& tableName);
    bool createTable();
    bool queryData();
    bool updateData();
    bool insertData();
    bool deleteData();

    /*void printMemberNamesAndValues()
    {
        hana::for_each(hana::members(m_Data), [&](const auto& member) {
            auto memberName = hana::to<char const*>(hana::first(member));
            auto memberValue = hana::second(member);
            qDebug() << "memberName: " << memberName << " memberValue: " << memberValue << '\n';
        });
    }*/

  private:
    TD m_Data;  // 使用模板类型
    QSqlDatabase m_SqlDataBase;  // SQLite 数据库连接
};

template <typename TD> 
DataBaseSQLite<TD>::DataBaseSQLite(const QString& dataBaseName, const QString& tableName)
{
    QString suffix = dataBaseName;
    if(!suffix.endsWith(".db")){
        suffix.append(".db");
    }
    m_SqlDataBase = QSqlDatabase::addDatabase("QSQLITE", tableName);
    m_SqlDataBase.setDatabaseName(dataBaseName);

    if (!m_SqlDataBase.open()) {
        Logur::i().info(QString("DataBase Name: %1, Table Name: %2, open table successful!!!").arg(suffix).arg(tableName).toStdString());
    } else {
        //printMemberNamesAndValues(m_Data);
        Logur::i().error(QString("DataBase Name: %1, Table Name: %2, open table faild!!!").arg(suffix).arg(tableName).toStdString());
    }
}
template <typename TD> 
DataBaseSQLite<TD>::~DataBaseSQLite()
{
    if (m_SqlDataBase.isOpen()) {
        m_SqlDataBase.close();
        Logur::i().warn(QString("DataBase Name: %1, close table successful!!!").arg(m_SqlDataBase.databaseName()).toStdString());
    }
}
template <typename TD> 
bool DataBaseSQLite<TD>::IsExistTable(const QString& tableName)
{
    if (!m_SqlDataBase.tables().contains(tableName)) {
        Logur::i().warn("Query ShortCut table no exits!!!");

        QString sql = "";
        QSqlQuery query(sql);
        if (!query.exec()) {
            Logur::i().error(QStr2StdStr(QString("create %1 table failed!!!").arg(tableName)));
            return false;
        } else {
            Logur::i().info(QStr2StdStr(QString("create %1 table success!!!").arg(tableName)));
            return true;
        }
    }
    return true;
}
template <typename TD> 
bool DataBaseSQLite<TD>::createTable()
{
}
template <typename TD> 
bool DataBaseSQLite<TD>::queryData()
{
}
template <typename TD> 
bool DataBaseSQLite<TD>::updateData()
{
}
template <typename TD> 
bool DataBaseSQLite<TD>::insertData()
{
}
template <typename TD> 
bool DataBaseSQLite<TD>::deleteData()
{
}