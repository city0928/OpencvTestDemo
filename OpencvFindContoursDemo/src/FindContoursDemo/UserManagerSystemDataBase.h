#pragma once

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <iostream>

#include "IVSUserManageData.h"
#include "connection_pool.hpp"
#include "dbng.hpp"
#include "sqlite.hpp"

class UserManagerSystemDataBase : public QWidget
{
  public:
    UserManagerSystemDataBase();
    ~UserManagerSystemDataBase();

  public Q_SLOTS:
    void insertDB();
    void queryDB();
    void updateDB();
    void deleteDB();

    void insertTDB(const std::vector<IVSUserManageData>&);
    void insertTDB(const IVSUserManageData&);
    // sqlite.query<IVSUserManageData>("age=3", "order by id desc", "limit 1");
    template <typename... Args> void queryTDB(std::vector<IVSUserManageData>&, Args&&... arg);
    template <typename... Args> void updateTDB(const IVSUserManageData&, Args&... arg);
    template <typename... Args> void updateTDB(const std::vector<IVSUserManageData>&, Args&... arg);
    template <typename... Args> void deleteTDB(Args&... arg);

  public:
    QLineEdit* eidt{nullptr};
    QPushButton* btn_C{nullptr};
    QPushButton* btn_R{nullptr};
    QPushButton* btn_U{nullptr};
    QPushButton* btn_D{nullptr};

  private:
    IVSUserManageData m_DBData;
    ormpp::dbng<ormpp::sqlite> ivsSqlite;
};
