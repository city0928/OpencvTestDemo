//#include "UserManagerSystemDataBase.h"
//
//#include "Logger.h"
//#include "entity.hpp"
//// const char* dbdir = "IVSLinkSense.db";
//
//#include <QDebug>
//
//using Logur = LinkSenseAIFI::Logur;
//
////template<class DB>
////UserManagerSystemDataBase<DB>::UserManagerSystemDataBase()
////{
////    eidt = new QLineEdit(this);
////    eidt2 = new QLineEdit("order by id desc", this);
////    btn_C = new QPushButton("插入", this);
////    btn_R = new QPushButton("查询", this);
////    btn_U = new QPushButton("修改", this);
////    btn_D = new QPushButton("删除", this);
////    eidt->move(130, 40);
////    eidt2->move(130, 75);
////    btn_C->move(100, 100);
////    btn_R->move(200, 100);
////    btn_U->move(100, 200);
////    btn_D->move(200, 200);
////    connect(btn_C, &QPushButton::clicked, this, [&](){
////        for (int i = 0; i < 10; ++i) {
////            DB key;
////            key.showShortCut = "showShortCut_" + QString::number(i).toStdString();
////            key.useInfoWindow = "useInfoWindow_" + QString::number(i).toStdString();
////            key.showBool = (i%2 == 0)? true : false;
////            // qDebug() << "insert result: " << ivsSqlite.insert<IVSUserManageData>(key);
////            insertTDB(key);
////        }
////    });
////    connect(btn_R, &QPushButton::clicked, this, [&](){
////        std::vector<DB> aaaa;
////        std::string str = eidt->text().toStdString();
////        std::string str2 = eidt2->text().toStdString();
////        queryTDB(aaaa, str, str2);
////        qDebug() << "queryTDB result: " << aaaa.size();
////        for (auto& it : aaaa) {
////            qDebug() << "id: " << it.id 
////                << " showShortCut " << QString::fromStdString(it.showShortCut) 
////                << " useInfoWindow " << QString::fromStdString(it.useInfoWindow)
////                << " showBool " << it.showBool;
////        }
////    });
////    connect(btn_U, &QPushButton::clicked, this, [&](){
////        /*std::vector<IVSUserManageData> aaaa;
////        queryTDB(aaaa, "id>=0");
////        for (int i = 0; i < aaaa.size(); ++i) {
////            aaaa[i].showShortCut = "aaaa";
////            std::string str = "id>=0";
////            updateTDB(aaaa.at(i), str);
////        }*/
////
////        /*IVSUserManageData key;
////        key.id = 88;
////        key.showShortCut = "showShortCut_1001";
////        key.useInfoWindow = "useInfoWindow_1001";
////        key.showBool = true;
////        std::string str = "showShortCut=showShortCut_7";
////        updateTDB(key, str);*/
////
////        std::string str = eidt->text().toStdString();
////        std::string str2 = eidt2->text().toStdString();
////        updateDB<DB>();
////    });
////    connect(btn_D, &QPushButton::clicked, this, [&](){
////        //std::string str = "showBool=false";
////        std::string str = eidt->text().toStdString();
////        deleteTDB<DB>(str);
////    });
////
////    ivsSqlite.connect(dbName);
////    ivsSqlite.create_datatable<DB>(ormpp_auto_key{"id"}, ormpp_not_null{{"showShortCut", "useInfoWindow", "showBool"}});
////}
////
////template<class DB>
////UserManagerSystemDataBase<DB>::~UserManagerSystemDataBase() {}
//
////void UserManagerSystemDataBase::insertDB()
////{
////    for (int i = 0; i < 10; ++i) {
////        IVSUserManageData key;
////        key.showShortCut = "showShortCut_" + QString::number(i).toStdString();
////        key.useInfoWindow = "useInfoWindow_" + QString::number(i).toStdString();
////        qDebug() << "insert result: " << ivsSqlite.insert<IVSUserManageData>(key);
////    }
////}
////
////void UserManagerSystemDataBase::queryDB() { 
////    qDebug() << "query result size: " << ivsSqlite.query<IVSUserManageData>("id>=0").size();
////}
////
////void UserManagerSystemDataBase::updateDB()
////{
////    IVSUserManageData key;
////    key.id = 2;
////    key.showShortCut = "showShortCut_1001";
////    key.useInfoWindow = "useInfoWindow_1001";
////    key.showBool = true;
////    qDebug() << "update result: " << ivsSqlite.update<IVSUserManageData>(key, "showShortCut=showShortCut_7");
////}
////
////void UserManagerSystemDataBase::deleteDB() { 
////    qDebug() << "delete result: " << ivsSqlite.delete_records<IVSUserManageData>("id=2");
////}
//
//template<class DB>
//void UserManagerSystemDataBase<DB>::insertTDB(const DB& key)
//{
//    ivsSqlite.begin();
//    int num;
//    if (num = ivsSqlite.insert<DB>(key); !num) {
//        Logur::i().error("insert result single faild.");
//        ivsSqlite.rollback();
//        return;
//    }
//    ivsSqlite.commit();
//    qDebug() << "insert result mum " << num;
//    Logur::i().info("insert result single succefful.");
//}
//template<class DB>
//void UserManagerSystemDataBase<DB>::insertTDB(const std::vector<DB>& key)
//{
//    ivsSqlite.begin();
//    if (!ivsSqlite.insert<std::vector<DB>>(key)) {
//        Logur::i().error("insert result faild size: {}", key.size());
//        ivsSqlite.rollback();
//        Logur::i().error("insert result rollback sucefull");
//        return;
//    }
//    ivsSqlite.commit();
//    Logur::i().info("insert result succefful size: {}", key.size());
//}
//
//template<class DB>
//template<typename... Args>
//void UserManagerSystemDataBase<DB>::queryTDB(std::vector<DB>& dataList, Args&&... arg) 
//{
//    ivsSqlite.begin();
//    dataList = ivsSqlite.query<DB>(std::forward<Args>(arg)...);
//    ivsSqlite.commit();
//}
//template <class DB>
//template<typename... Args>
//void UserManagerSystemDataBase<DB>::updateTDB(const DB& data, Args&&... arg)
//{
//    ivsSqlite.begin();
//    if (int size = ivsSqlite.update<DB>(data, std::forward<Args>(arg)...); !size) {
//        ivsSqlite.rollback();
//        Logur::i().info("update result faild!!!");
//        return;
//    }
//    ivsSqlite.commit();
//}
//template <class DB>
//template<typename... Args>
//void UserManagerSystemDataBase<DB>::updateTDB(const std::vector<DB>& dataList, Args&&... arg)
//{
//    ivsSqlite.begin();
//    for(const auto& it : dataList){
//        if(!ivsSqlite.update<DB>(it, std::forward<Args>(arg)...)){
//            ivsSqlite.rollback();
//            Logur::i().info("update result faild!!! size: {}", dataList.size());
//            return;
//        }
//    }
//    ivsSqlite.commit();
//    Logur::i().info("update result succefful!!! size: {}", dataList.size());
//}
//
//template <class DB>
//template<typename... Args>
//void UserManagerSystemDataBase<DB>::deleteTDB(Args&&... arg)
//{
//    ivsSqlite.begin();
//    if(!ivsSqlite.delete_records<DB>(std::forward<Args>(arg)...)){
//        ivsSqlite.rollback();
//        Logur::i().error("delete_records result faild!!!");
//    }
//    ivsSqlite.commit();
//    Logur::i().info("delete_records result succefful!!!");
//}
