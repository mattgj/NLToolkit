#ifndef SAVEDATA_H
#define SAVEDATA_H

#include <QString>
#include <QFile>

class SaveData
{
public:
    static SaveData* getInstance();
    bool open(QString path);
    int getError();

    QString readString(uint offset, int len);
    void writeString(uint offset, QString str);

    quint8 readInt8(uint offset);
    void writeInt8(uint offset, quint8 value);

    quint16 readInt16(uint offset);
    void writeInt16(uint offset, quint16 value);

    quint32 readInt32(uint offset);
    void writeInt32(uint offset, quint32 value);

    bool save();
    ~SaveData();

private:
    SaveData();

    static SaveData *m_saveData;
    QString m_path;
    QByteArray m_dataByteArray;
    uchar *m_data;
    int m_error;

};

#endif // SAVEDATA_H
