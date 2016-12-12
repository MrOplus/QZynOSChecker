#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <QObject>
class Decompressor : public QObject
{
    Q_OBJECT
public:
    Decompressor(QByteArray *file, QObject *parent = 0);
    QString Decompress();
private:
    char *uncompress_lzs(char *data);
    int is_endmarker(char *data, int *offset, int *index);
    char *get_nbits(int nbits, char *data, int *offset, int *index);
    char get_bit(char *data, int *offset, int *index);
    QByteArray *file ;
};

#endif // DECOMPRESSOR_H
