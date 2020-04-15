#include "maingamepage.h"

#include "hitemmodel.h"

#define OBJNAME_TILELIST "id_tileList"
#define TILE_COUNT 8

MainGamePage::MainGamePage() : HPage(QUrl("qrc:/MainGamePage.qml")),
    m_pViewModel(new HItemModel())
{
    srand((unsigned int)time(0));
    initialize();
}

MainGamePage::~MainGamePage()
{

}

void MainGamePage::initialize()
{
    bool bConnectSuccess = connect(getComponent(OBJNAME_TILELIST), SIGNAL(clickedTileSignal(int)), this, SLOT(onClickedTileSignal(int)));
    qDebug() << Q_FUNC_INFO << "bConnectSuccess is " << bConnectSuccess;

    QList<HTile *> tNumberList;

    for (int i = 0; i < TILE_COUNT; i++)
    {
        HTile *tile = new HTile();
        tile->setNumber(i + 1);
        tile->setTileState(HTile::E_TILE_STATE_OCCUPY);
        tNumberList.append(tile);
    }


    int nLength = tNumberList.length();

    for (int i = 0; i < nLength -1 ; i++)
    {
        int a = rand() % nLength;
        int b = rand() % nLength;
        tNumberList.swapItemsAt(a, b);
    }

    HTile *vacancyTile = new HTile();
    vacancyTile->setNumber(-1);
    vacancyTile->setTileState(HTile::E_TILE_STATE_VACANCY);
    tNumberList.append(vacancyTile);

    m_pViewModel->setList(tNumberList);
    qRegisterMetaType<HItemModel*>("HItemModel*");
    getComponent(OBJNAME_TILELIST)->setProperty("model", QVariant::fromValue(m_pViewModel));

    setLastNumber(TILE_COUNT);

    qDebug() << "SUCCESS!!";
}

void MainGamePage::successTouch(const int &nIndex)
{
    qDebug() << Q_FUNC_INFO << nIndex;
    m_pViewModel->editItem(nIndex, HTile::E_TILE_STATE_VACANCY, -1);

    QList<int> tVacancyList = m_pViewModel->getVacancyIndexList();
    int nNextPushIndex = tVacancyList.at(rand() % tVacancyList.length());
    qDebug() << Q_FUNC_INFO << "nNextPushIndex" << nNextPushIndex;

    setLastNumber(m_nLastNumber + 1);
    m_pViewModel->editItem(nNextPushIndex, HTile::E_TILE_STATE_OCCUPY, m_nLastNumber);
}

void MainGamePage::failTouch(const int &nIndex)
{
    qDebug() << Q_FUNC_INFO << nIndex;
}

void MainGamePage::setLastNumber(const int &nNumber)
{
    m_nLastNumber = nNumber;
    m_nFirstNumber = m_nLastNumber - TILE_COUNT + 1;
}

void MainGamePage::onClickedTileSignal(int nIndex)
{
    qDebug() << Q_FUNC_INFO << nIndex;
    HTile *tSelectedTile = m_pViewModel->getData(nIndex);

    qDebug() << Q_FUNC_INFO << "tSelectedTile" << tSelectedTile->getNumber();

    if (tSelectedTile->getNumber() == m_nFirstNumber)
    {
        successTouch(nIndex);
    }
    else
    {
        failTouch(nIndex);
    }
}

