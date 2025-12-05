#ifndef SHUANGPIN_H
#define SHUANGPIN_H

#include <QString>
#include <QMap>
#include <QStringList>

class Shuangpin
{
public:
    enum Scheme {
        MS2003,
        XIAOHE,
        ZIGUANG,
        ABC,
        CUSTOMIZED
    };

    Shuangpin(Scheme scheme = XIAOHE);

    // 将单个双拼转换为拼音列表
    QStringList toPinyin(const QString &shuangpin);

    // 将连续双拼转换为所有可能的拼音组合
    QStringList toFullPinyin(const QString &input);

    // 检查输入是否有效
    bool isValid(const QString &input);

private:
    Scheme m_scheme;

    // 声母映射: 键 -> 声母
    QMap<QString, QString> m_initialMap;

    // 韵母映射: 键 -> 韵母列表
    QMap<QString, QStringList> m_finalMap;

    void initXiaoheScheme();
    void initMS2003Scheme();
    void initZiguangScheme();
    void initABCScheme();
};

#endif // SHUANGPIN_H
