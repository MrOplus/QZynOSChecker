#include "fileutil.h"
#include <QFile>
FileUtil::FileUtil(QObject *parent) : QObject(parent)
{

}
QByteArray *FileUtil::getLZASection(QFile* RomFile){
    int fpos = 8568 ;
    int fend = 8788 ;
    int amount = 221 ;
    RomFile->seek(fpos);
    QByteArray *chunk = new QByteArray();
    while(fpos < fend){
        if(fend - fpos < amount){
            amount = fend - fpos ;
            QByteArray temp = RomFile->read(amount);
            chunk->append(temp);
            fpos += temp.length() ;
        }
    }
    return chunk ;
}
QByteArray *FileUtil::getLZASection(QByteArray* RomFile){
    QByteArray backup = *RomFile;
    QByteArray *chunk = new QByteArray();

    if(backup.length() > 8788){
        backup = backup.mid(8568,221);
    }
    chunk->append(backup) ;
    return chunk ;
}
QString FileUtil::getPassword(const QString &decoded){
    QString f = decoded.mid(20);
    f = f.mid(0,f.indexOf(QString(0xE)));
    return f ;
}
