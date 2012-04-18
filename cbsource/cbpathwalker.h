#ifndef CBPATHWALKER_H
#define CBPATHWALKER_H

#include <QString>
#include <QFileInfo>


class CBPathWalkerCallback
{
public:
    virtual bool onDirDetected(QFileInfo dir, int depth) = 0;
    virtual bool onFileDetected(QFileInfo file, int depth) = 0;
};


class CBPathWalker
{
public:
    CBPathWalker();
    CBPathWalker(QString root);

    void go();

    QString getRoot() { return _root; }
    void setRoot(QString root) { _root = root; }
    CBPathWalkerCallback* getCallback() { return _callback; }
    void setCallback(CBPathWalkerCallback* callback) { _callback = callback; }

protected:
    void traverse(QFileInfo node, int depth);

private:
    QString _root;
    CBPathWalkerCallback* _callback;
};

#endif // CBPATHWALKER_H
