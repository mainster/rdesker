#ifndef MYCLASS_H
#define MYCLASS_H

#include <QObject>

class myclass : public QObject
{
	Q_OBJECT
public:
	explicit myclass(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MYCLASS_H