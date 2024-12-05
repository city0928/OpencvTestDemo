#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <iostream>

// #include "IVSUserManageData.h"
#include "Logger.h"
#include "connection_pool.hpp"
#include "dbng.hpp"
#include "sqlite.hpp"
using Logur = LinkSenseAIFI::Logur;

template <class DB> class UserManagerSystemDataBase : public QWidget
{
  public:
    UserManagerSystemDataBase(DB data, const char* dbName = "IVSDatabase.db")
        : m_Data{data}
    {
        eidt = new QLineEdit(this);
        eidt2 = new QLineEdit("order by id desc", this);
        btn_C = new QPushButton("插入", this);
        btn_R = new QPushButton("查询", this);
        btn_U = new QPushButton("修改", this);
        btn_D = new QPushButton("删除", this);
        eidt->move(130, 40);
        eidt2->move(130, 75);
        btn_C->move(100, 100);
        btn_R->move(200, 100);
        btn_U->move(100, 200);
        btn_D->move(200, 200);
        connect(btn_C, &QPushButton::clicked, this, [&]() {
            for (int i = 0; i < 10; ++i) {
                DB key;
                key.showShortCut = "showShortCut" + QString::number(i).toStdString();
                key.useInfoWindow = "useInfoWindow" + QString::number(i).toStdString();
                key.showBool = (i % 2 == 0) ? true : false;
                // qDebug() << "insert result: " << ivsSqlite.insert<IVSUserManageData>(key);
                insertTDB(key);
            }
        });
        connect(btn_R, &QPushButton::clicked, this, [&]() {
            std::vector<DB> aaaa;
            std::string str = /*eidt->text().toStdString()*/ "id>0";
            std::string str2 = /*eidt2->text().toStdString()*/ "";
            queryTDB(aaaa, str, str2);
            qDebug() << "queryTDB result: " << aaaa.size();
            for (auto& it : aaaa) {
                qDebug() << "id: " << it.id << " showShortCut " << QString::fromStdString(it.showShortCut) << " useInfoWindow "
                         << QString::fromStdString(it.useInfoWindow) << " showBool " << it.showBool;
            }
        });
        connect(btn_U, &QPushButton::clicked, this, [&]() {
            std::vector<IVSUserManageData> aaaa;
            queryTDB(aaaa, "id>=0");
            for (int i = 0; i < aaaa.size(); ++i) {
                aaaa[i].showShortCut = "bbbbbb";
                aaaa[i].useInfoWindow = "tttttttttttt";
                updateTDB(aaaa[i] /*condition*/);
            }
        });
        connect(btn_D, &QPushButton::clicked, this, [&]() {
            // std::string str = "showBool=false";
            std::string str = eidt->text().toStdString();
            deleteTDB(str);
        });

        ivsSqlite.connect(dbName);
        ivsSqlite.create_datatable<DB>(ormpp_auto_key{"id"}, ormpp_not_null{{"showShortCut", "useInfoWindow", "showBool"}});
    }

    UserManagerSystemDataBase(const std::string& autoKeyVariableName, const char* dbName = "IVSDatabase.db")
    {
        if (ivsSqlite.connect(dbName)) {
            ivsSqlite.create_datatable<DB>(ormpp_auto_key{autoKeyVariableName} /*, ormpp_not_null{{"showShortCut", "useInfoWindow", "showBool"}}*/);

            eidt = new QLineEdit(this);
            eidt2 = new QLineEdit("order by id desc", this);
            btn_C = new QPushButton("插入", this);
            btn_R = new QPushButton("查询", this);
            btn_U = new QPushButton("修改", this);
            btn_D = new QPushButton("删除", this);
            eidt->move(130, 40);
            eidt2->move(130, 75);
            btn_C->move(100, 100);
            btn_R->move(200, 100);
            btn_U->move(100, 200);
            btn_D->move(200, 200);
            connect(btn_C, &QPushButton::clicked, this, [&]() {
                for (int i = 0; i < 10; ++i) {
                    DB key;
                    key.showShortCut = "showShortCut" + QString::number(i).toStdString();
                    key.useInfoWindow = "useInfoWindow" + QString::number(i).toStdString();
                    key.showBool = (i % 2 == 0) ? true : false;
                    // qDebug() << "insert result: " << ivsSqlite.insert<IVSUserManageData>(key);
                    insertTDB(key);
                }
            });
            connect(btn_R, &QPushButton::clicked, this, [&]() {
                std::vector<DB> aaaa;
                std::string str = /*eidt->text().toStdString()*/ "id>0";
                std::string str2 = /*eidt2->text().toStdString()*/ "";
                queryTDB(aaaa, str, str2);
                qDebug() << "queryTDB result: " << aaaa.size();
                for (auto& it : aaaa) {
                    qDebug() << "id: " << it.id << " showShortCut " << QString::fromStdString(it.showShortCut) << " useInfoWindow "
                             << QString::fromStdString(it.useInfoWindow) << " showBool " << it.showBool;
                }
            });
            connect(btn_U, &QPushButton::clicked, this, [&]() {
                std::vector<IVSUserManageData> aaaa;
                queryTDB(aaaa, "id>=0");
                for (int i = 0; i < aaaa.size(); ++i) {
                    aaaa[i].showShortCut = "bbbbbb";
                    aaaa[i].useInfoWindow = "tttttttttttt";
                    updateTDB(aaaa[i] /*condition*/);
                }
            });
            connect(btn_D, &QPushButton::clicked, this, [&]() {
                // std::string str = "showBool=false";
                std::string str = eidt->text().toStdString();
                deleteTDB(str);
            });
        }
    }

    ~UserManagerSystemDataBase() {}

  public Q_SLOTS:
    void insertTDB(const DB& data)
    {
        ivsSqlite.begin();
        if (INT_MIN == ivsSqlite.insert<DB>(data)) {
            Logur::i().error("insert result single faild.");
            ivsSqlite.rollback();
            return;
        }
        ivsSqlite.commit();
        Logur::i().info("insert result single succefful.");
    }
    void insertTDB(const std::vector<DB>& dataList)
    {
        ivsSqlite.begin();
        if (!ivsSqlite.insert<std::vector<DB>>(dataList)) {
            Logur::i().error("insert result faild!!!");
            ivsSqlite.rollback();
            Logur::i().error("insert result rollback sucefull!!!");
            return;
        }
        ivsSqlite.commit();
        Logur::i().info("insert result succefful!!!");
    }

    template <typename... Args> void queryTDB(std::vector<DB>& dataList, Args&&... arg)
    {
        ivsSqlite.begin();
        dataList = ivsSqlite.query<DB>(std::forward<Args>(arg)...);
        ivsSqlite.commit();
    }

    template <typename... Args> void updateTDB(const DB& data, Args&&... arg)
    {
        ivsSqlite.begin();
        if (INT_MIN == ivsSqlite.update<DB>(data, std::forward<Args>(arg)...)) {
            ivsSqlite.rollback();
            Logur::i().info("update result faild!!!");
            return;
        }
        ivsSqlite.commit();
        Logur::i().info("update result succefful!!!");
    }
    template <typename... Args> void updateTDB(const std::vector<DB>& dataList, Args&&... arg)
    {
        ivsSqlite.begin();
        for (const auto& it : dataList) {
            if (!ivsSqlite.update<DB>(it, std::forward<Args>(arg)...)) {
                ivsSqlite.rollback();
                Logur::i().info("update result faild!!! size: {}", dataList.size());
                return;
            }
        }
        ivsSqlite.commit();
        Logur::i().info("update result succefful!!! size: {}", dataList.size());
    }

    template <typename... Args> void deleteTDB(Args&&... arg)
    {
        ivsSqlite.begin();
        if (!ivsSqlite.delete_records<DB>(std::forward<Args>(arg)...)) {
            ivsSqlite.rollback();
            Logur::i().error("delete_records result faild!!!");
        }
        ivsSqlite.commit();
        Logur::i().info("delete_records result succefful!!!");
    }

  public:
    QLineEdit* eidt{nullptr};
    QLineEdit* eidt2{nullptr};
    QPushButton* btn_C{nullptr};
    QPushButton* btn_R{nullptr};
    QPushButton* btn_U{nullptr};
    QPushButton* btn_D{nullptr};

  private:
    DB m_Data;
    ormpp::dbng<ormpp::sqlite> ivsSqlite;
};
