#ifndef MAINGAMEPAGE_H
#define MAINGAMEPAGE_H

#include "page.h"
#include "itemmodel.h"
#include "util.h"

class MainGamePage : public Page
{
    Q_OBJECT
public:
    MainGamePage();
    ~MainGamePage();



protected:
    void initialize();
    void setAnswerNumber(int nAnswerNumber);

    void successTouch(const int &nIndex);
    void failTouch(const int &nIndex);

protected slots:
    void onClickedTileSignal(int nIndex);

private:
    ItemModel* m_pViewModel;
    QMap<int, int> m_tIndexMapping;

    QList<Tile> m_tNumberList;

    int m_nAnswerNumber;
};

#endif // MAINGAMEPAGE_H
