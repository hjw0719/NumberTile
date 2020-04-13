#ifndef MAINGAMEPAGE_H
#define MAINGAMEPAGE_H

#include "page.h"
#include "itemmodel.h"
#include "util.h"

class MainGamePage : public Page
{
public:
    MainGamePage();
    ~MainGamePage();



protected:
    void initialize();
    void setAnswerNumber(int nAnswerNumber);

    void successTouch(const int &nIndex);
    void failTouch();

    void pushTile();
protected slots:
    void onClickedTileSignal(int nIndex);

private:
    ItemModel* m_pViewModel;
    QMap<int, int> m_tIndexMapping;

    int m_nAnswerNumber;
};

#endif // MAINGAMEPAGE_H
