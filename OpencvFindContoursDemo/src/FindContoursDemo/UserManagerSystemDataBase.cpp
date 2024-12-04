#include "UserManagerSystemDataBase.h"

#include "Logger.h"
#include "entity.hpp"
// const char* dbdir = "IVSLinkSense.db";
const char* dbName = "IVSDatabase.db";

#include <QDebug>

using Logur = LinkSenseAIFI::Logur;

UserManagerSystemDataBase::UserManagerSystemDataBase()
{
    eidt = new QLineEdit(this);
    btn_C = new QPushButton("插入", this);
    btn_R = new QPushButton("查询", this);
    btn_U = new QPushButton("修改", this);
    btn_D = new QPushButton("删除", this);
    eidt->move(130, 80);
    btn_C->move(100, 100);
    btn_R->move(200, 100);
    btn_U->move(100, 200);
    btn_D->move(200, 200);
    connect(btn_C, &QPushButton::clicked, this, [&](){
        for (int i = 0; i < 10; ++i) {
            IVSUserManageData key;
            key.showShortCut = "showShortCut_" + QString::number(i).toStdString();
            key.useInfoWindow = "useInfoWindow_" + QString::number(i).toStdString();
            key.showBool = (i%2 == 0)? true : false;
            // qDebug() << "insert result: " << ivsSqlite.insert<IVSUserManageData>(key);
            insertTDB(key);
        }
    });
    connect(btn_R, &QPushButton::clicked, this, [&](){
        std::vector<IVSUserManageData> aaaa;
        std::string str = eidt->text().toStdString();
        queryTDB(aaaa, str/*"id>=0"*/);
        qDebug() << "queryTDB result: " << aaaa.size();
        for (auto& it : aaaa) {
            qDebug() << "id: " << it.id 
                << " showShortCut " << QString::fromStdString(it.showShortCut) 
                << " useInfoWindow " << QString::fromStdString(it.useInfoWindow)
                << " showBool " << it.showBool;
        }
    });
    connect(btn_U, &QPushButton::clicked, this, [&](){
        /*std::vector<IVSUserManageData> aaaa;
        queryTDB(aaaa, "id>=0");
        for (int i = 0; i < aaaa.size(); ++i) {
            aaaa[i].showShortCut = "aaaa";
            std::string str = "id>=0";
            updateTDB(aaaa.at(i), str);
        }*/

        /*IVSUserManageData key;
        key.id = 88;
        key.showShortCut = "showShortCut_1001";
        key.useInfoWindow = "useInfoWindow_1001";
        key.showBool = true;
        std::string str = "showShortCut=showShortCut_7";
        updateTDB(key, str);*/

        std::string str = eidt->text().toStdString();
        updateDB();
    });
    connect(btn_D, &QPushButton::clicked, this, [&](){
        //std::string str = "showBool=false";
        std::string str = eidt->text().toStdString();
        deleteTDB(str);
    });

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

void UserManagerSystemDataBase::queryDB() { 
    qDebug() << "query result size: " << ivsSqlite.query<IVSUserManageData>("id>=0").size();
}

void UserManagerSystemDataBase::updateDB()
{
    IVSUserManageData key;
    key.id = 2;
    key.showShortCut = "showShortCut_1001";
    key.useInfoWindow = "useInfoWindow_1001";
    key.showBool = true;
    qDebug() << "update result: " << ivsSqlite.update<IVSUserManageData>(key, "showShortCut=showShortCut_7");
}

void UserManagerSystemDataBase::deleteDB() { 
    qDebug() << "delete result: " << ivsSqlite.delete_records<IVSUserManageData>("id=2");
}

void UserManagerSystemDataBase::insertTDB(const IVSUserManageData& key)
{
    ivsSqlite.begin();
    int num;
    if (num = ivsSqlite.insert<IVSUserManageData>(key); !num) {
        Logur::i().error("insert result single faild.");
        ivsSqlite.rollback();
        return;
    }
    ivsSqlite.commit();
    qDebug() << "insert result mum " << num;
    Logur::i().info("insert result single succefful.");
}
void UserManagerSystemDataBase::insertTDB(const std::vector<IVSUserManageData>& key)
{
    ivsSqlite.begin();
    if (!ivsSqlite.insert<std::vector<IVSUserManageData>>(key)) {
        Logur::i().error("insert result faild size: {}", key.size());
        ivsSqlite.rollback();
        Logur::i().error("insert result rollback sucefull");
        return;
    }
    ivsSqlite.commit();
    Logur::i().info("insert result succefful size: {}", key.size());
}

template<typename... Args>
void UserManagerSystemDataBase::queryTDB(std::vector<IVSUserManageData>& dataList, Args&&... arg) 
{
    ivsSqlite.begin();
    dataList = ivsSqlite.query<IVSUserManageData>(std::forward<Args>(arg)...);
    ivsSqlite.commit();
}
template<typename... Args>
void UserManagerSystemDataBase::updateTDB(const IVSUserManageData& data, Args&... arg)
{
    ivsSqlite.begin();
    if (int size = ivsSqlite.update<IVSUserManageData>(data, std::forward<Args>(arg)...); !size) {
        ivsSqlite.rollback();
        Logur::i().info("update result faild!!!");
        return;
    }
    ivsSqlite.commit();
}
template<typename... Args>
void UserManagerSystemDataBase::updateTDB(const std::vector<IVSUserManageData>& dataList, Args&... arg)
{
    ivsSqlite.begin();
    for(const auto& it : dataList){
        if(!ivsSqlite.update<IVSUserManageData>(it, std::forward<Args>(arg)...)){
            ivsSqlite.rollback();
            Logur::i().info("update result faild!!! size: {}", dataList.size());
            return;
        }
    }
    ivsSqlite.commit();
    Logur::i().info("update result succefful!!! size: {}", dataList.size());
}

template<typename... Args>
void UserManagerSystemDataBase::deleteTDB(Args&... arg)
{
    ivsSqlite.begin();
    if(!ivsSqlite.delete_records<IVSUserManageData>(std::forward<Args>(arg)...)){
        ivsSqlite.rollback();
        Logur::i().error("delete_records result faild!!!");
    }
    ivsSqlite.commit();
    Logur::i().info("delete_records result succefful!!!");
}
