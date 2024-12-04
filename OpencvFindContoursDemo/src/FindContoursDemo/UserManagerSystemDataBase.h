#pragma once

#include <QWidget>
#include <QPushButton>
#include <iostream>

#include "IVSUserManageData.h"
#include "connection_pool.hpp"
#include "dbng.hpp"
#include "sqlite.hpp"

struct student {
    std::string name;
    int age;
    int id;
};
REGISTER_AUTO_KEY(student, id)
REFLECTION_WITH_NAME(student, "t_student", id, name, age)

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

public:
    QPushButton* btn_C{ nullptr };
    QPushButton* btn_R{ nullptr };
    QPushButton* btn_U{ nullptr };
    QPushButton* btn_D{ nullptr };

  private:
    student m_DBData;
    ormpp::dbng<ormpp::sqlite> ivsSqlite;
};
