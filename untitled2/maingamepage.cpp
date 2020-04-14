#include "maingamepage.h"
#define OBJNAME_TILELIST "id_tileList"


MainGamePage::MainGamePage() : Page(QUrl("qrc:/MainGamePage.qml")),
    m_pViewModel(new ItemModel)
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
    m_tNumberList.clear();

    for (int i = 0; i < 8; i++)
    {
        Tile tile;
        tile.number = i + 1;
        tile.eState = occupy;
        m_tNumberList.append(tile);
    }

    auto tempList = m_tNumberList;

    for (int i = 0; i < m_tNumberList.length() -1 ; i++)
    {
        int a = rand() % tempList.length();
        int b = rand() % tempList.length();
        tempList.swapItemsAt(a, b);
    }

    Tile vacancyTile;
    vacancyTile.number = -1;
    vacancyTile.eState = vacancy;
    tempList.append(vacancyTile);

    m_pViewModel->setList(tempList);
    qDebug() << "TRY!!";
    qRegisterMetaType<ItemModel*>("ItemModel*");
    getComponent(OBJNAME_TILELIST)->setProperty("model", QVariant::fromValue(m_pViewModel));


    qDebug() << "SUCCESS!!";
}

void MainGamePage::setAnswerNumber(int nAnswerNumber)
{
    m_nAnswerNumber = nAnswerNumber;
}

void MainGamePage::successTouch(const int &nIndex)
{
    qDebug() << Q_FUNC_INFO << nIndex;
    m_tNumberList.pop_front();


    Tile vacancyTile;
    vacancyTile.number = -1;
    vacancyTile.eState = vacancy;
    m_pViewModel->editItem(nIndex, vacancyTile);

    Tile pushTile;
    pushTile = m_tNumberList.last();
    pushTile.number++;
    pushTile.eState = occupy;


    qDebug() << Q_FUNC_INFO << pushTile.number;
    m_tNumberList.push_back(pushTile);
    QList<int> tVacancyList = m_pViewModel->getVacancyIndexList();
    int nNextPushIndex = tVacancyList.at(rand() % tVacancyList.length());
    qDebug() << Q_FUNC_INFO << "nNextPushIndex" << nNextPushIndex;
    m_pViewModel->editItem(nNextPushIndex, pushTile);
}

void MainGamePage::failTouch(const int &nIndex)
{
    qDebug() << Q_FUNC_INFO << nIndex;
}

void MainGamePage::onClickedTileSignal(int nIndex)
{
    qDebug() << Q_FUNC_INFO << nIndex;
    Tile tSelectedTile = m_pViewModel->getData(nIndex);

    qDebug() << Q_FUNC_INFO << "tSelectedTile" << tSelectedTile.number;

    if (tSelectedTile.number == m_tNumberList.first().number)
    {
        successTouch(nIndex);
    }
    else
    {
        failTouch(nIndex);
    }
}

