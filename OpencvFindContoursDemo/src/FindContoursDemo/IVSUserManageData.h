#pragma once

#include <QString>
#include <QDebug>

#include "dbng.hpp"
#include "utility.hpp"

struct IVSUserManageData {
    std::string useInfoWindow;
    std::string showShortCut;
    bool showBool;
    int id;
};
REGISTER_AUTO_KEY(IVSUserManageData, id)
//REGISTER_CONFLICT_KEY(IVSUserManageData, showShortCut)
REFLECTION(IVSUserManageData, id, useInfoWindow, showShortCut, showBool)