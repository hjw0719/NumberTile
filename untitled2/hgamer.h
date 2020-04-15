#ifndef HGAMER_H
#define HGAMER_H

#include <QObject>

class HGamer : public QObject
{
    Q_OBJECT
public:
    explicit HGamer(QObject *parent = NULL);

private :
    qulonglong m_qullScore;
    unsigned int m_nRank;
};

#endif // HGAMER_H
