#include "UserManagerSystemDataBase.h"

#include "entity.hpp"
// const char* dbdir = "IVSLinkSense.db";
const char* dbName = "IVSDatabase.db";

#include <QDebug>

UserManagerSystemDataBase::UserManagerSystemDataBase()
{
    btn_C = new QPushButton("插入", this);
    btn_R = new QPushButton("查询", this);
    btn_U = new QPushButton("修改", this);
    btn_D = new QPushButton("删除", this);
    btn_C->move(100, 100);
    btn_R->move(200, 100);
    btn_U->move(100, 200);
    btn_D->move(200, 200);
    connect(btn_C, &QPushButton::clicked, this, &UserManagerSystemDataBase::insertDB);
    connect(btn_R, &QPushButton::clicked, this, &UserManagerSystemDataBase::queryDB);
    connect(btn_U, &QPushButton::clicked, this, &UserManagerSystemDataBase::updateDB);
    connect(btn_D, &QPushButton::clicked, this, &UserManagerSystemDataBase::deleteDB);

    ivsSqlite.connect(dbName);
    ivsSqlite.create_datatable<IVSUserManageData>(ormpp_auto_key{"id"});
}

UserManagerSystemDataBase::~UserManagerSystemDataBase() {}

void UserManagerSystemDataBase::insertDB()
{
    for (int i = 0; i < 10; ++i) {
        IVSUserManageData key;
        key.showShortCut = "showShortCut_" + QString::number(i).toStdString();
        key.useInfoWindow = "useInfoWindow_" + QString::number(i).toStdString();
        qDebug() << "insert result: " << ivsSqlite.insert<IVSUserManageData>(key);
    }
}

void UserManagerSystemDataBase::queryDB() 
{
    qDebug() << "query result size: " << ivsSqlite.query<IVSUserManageData>("id>=0").size();
}

void UserManagerSystemDataBase::updateDB() 
{
    IVSUserManageData key;
    key.id = 88;
    key.showShortCut = "showShortCut_1001";
    key.useInfoWindow = "useInfoWindow_1001";
    qDebug() << "inupdateert result: " << ivsSqlite.update<IVSUserManageData>(key, "id=9");
}

void UserManagerSystemDataBase::deleteDB() 
{
    qDebug() << "delete result: " << ivsSqlite.delete_records<IVSUserManageData>("id=2");
}
