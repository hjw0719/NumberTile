#include "maingamepage.h"

#include "hdatamanager.h"

#define OBJNAME_TILELIST "id_tileList"

MainGamePage::MainGamePage() :
    HPage(QUrl("qrc:/MainGamePage.qml"))
{
    initialize();
}

MainGamePage::~MainGamePage()
{

}


