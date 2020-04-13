#include "maingamepage.h"
#define OBJNAME_TILELIST "id_tileList"


MainGamePage::MainGamePage() : Page(QUrl("qrc:/MainGamePage.qml")),
    m_pViewModel(new ItemModel),
    m_nAnswerNumber(-1)
{
    initialize();
    srand((unsigned int)time(0));
}

MainGamePage::~MainGamePage()
{

}

void MainGamePage::initialize()
{
    QList<Tile> tNumberList;



    for (int i = 0; i < 9; i++)
    {
        Tile tile;
        tile.number = i + 1;
        tile.eState = occupy;

        if (8 == i)
        {
            tile.eState = vacancy;
            tile.number = -1;
        }

        tNumberList.append(tile);
    }

    for (int i = 0; i < tNumberList.length() ; i++)
    {
        int a = rand() % tNumberList.length();
        int b = rand() % tNumberList.length();
        tNumberList.swapItemsAt(a, b);
    }

    setAnswerNumber(1);

    m_pViewModel->setList(tNumberList);
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
    Tile tSelectedTile = m_pViewModel->getData(nIndex);



}

void MainGamePage::failTouch()
{

}

void MainGamePage::pushTile()
{
    int newNumber = m_tIndexMapping.size() + 1;

    Tile newTile;
    newTile.number = newNumber;

    rand() %
}

void MainGamePage::onClickedTileSignal(int nIndex)
{
    Tile tSelectedTile = m_pViewModel->getData(nIndex);

    if (tSelectedTile.number == m_nAnswerNumber)
    {
        successTouch();
    }
    else
    {
        failTouch();
    }
}

