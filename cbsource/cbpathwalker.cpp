#include "cbpathwalker.h"
#include <QFileInfoList>
#include <QDir>
#include <QDebug>

CBPathWalker::CBPathWalker()
{
}

CBPathWalker::CBPathWalker(QString root)
{
    setRoot(root);
}

void CBPathWalker::go()
{
    QFileInfo rootInfo(_root);

    traverse(rootInfo, 0);
}

void CBPathWalker::traverse(QFileInfo node, int depth)
{
    if (!node.exists())
        return;

    if (node.isHidden())
        return;

    if (node.isDir())
    {
        if (_callback)
            _callback->onDirDetected(node, depth);

        QDir dir(node.absoluteFilePath());
        QFileInfoList infoList = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
        for (int i = 0; i < infoList.count(); ++i)
        {
            QFileInfo info = infoList.at(i);
            traverse(info, depth + 1);
        }
    }

    if (node.isFile())
    {
        if (_callback)
            _callback->onFileDetected(node, depth);
    }
}
