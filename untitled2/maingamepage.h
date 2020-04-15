#ifndef MAINGAMEPAGE_H
#define MAINGAMEPAGE_H

#include "page.h"
#include "itemmodel.h"
#include "htile.h"

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

    void setLastNumber(const int &nNumber);
protected slots:
    void onClickedTileSignal(int nIndex);

private:
    ItemModel* m_pViewModel;

    int m_nFirstNumber;
    int m_nLastNumber;
};

#endif // MAINGAMEPAGE_H
