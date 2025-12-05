#include "shuangpin.h"

Shuangpin::Shuangpin(Scheme scheme)
    : m_scheme(scheme)
{
    switch (m_scheme) {
        case XIAOHE:
            initXiaoheScheme();
            break;
        case MS2003:
            initMS2003Scheme();
            break;
        case ZIGUANG:
            initZiguangScheme();
            break;
        case ABC:
            initABCScheme();
            break;
        default:
            initXiaoheScheme();
            break;
    }
}

void Shuangpin::initXiaoheScheme()
{
    // 声母映射: 键 -> 声母
    // a 表示零声母
    m_initialMap = {
        {"a", "a"},
        {"b", "b"},
        {"p", "p"},
        {"m", "m"},
        {"f", "f"},
        {"d", "d"},
        {"t", "t"},
        {"n", "n"},
        {"l", "l"},
        {"g", "g"},
        {"k", "k"},
        {"h", "h"},
        {"j", "j"},
        {"q", "q"},
        {"x", "x"},
        {"z", "z"},
        {"c", "c"},
        {"s", "s"},
        {"r", "r"},
        {"y", "y"},
        {"w", "w"},
        {"u", "sh"},
        {"i", "ch"},
        {"v", "zh"}};

    // 韵母映射: 键 -> 韵母列表（一个键可能对应多个韵母）
    m_finalMap = {
        {"a", {"a"}},
        {"o", {"o", "uo"}},
        {"e", {"e"}},
        {"i", {"i"}},
        {"u", {"u"}},
        {"v", {"v", "ui"}},
        {"q", {"iu"}},
        {"w", {"ei"}},
        {"r", {"uan"}},
        {"t", {"ue", "ve"}},
        {"y", {"un"}},
        {"p", {"ie"}},
        {"s", {"ong", "iong"}},
        {"d", {"ai"}},
        {"f", {"en"}},
        {"g", {"eng"}},
        {"h", {"ang"}},
        {"j", {"an"}},
        {"k", {"uai", "ing"}},
        {"l", {"uang", "iang"}},
        {"z", {"ou"}},
        {"x", {"ua", "ia"}},
        {"c", {"ao"}},
        {"b", {"in"}},
        {"n", {"iao"}},
        {"m", {"ian"}}};
}

void Shuangpin::initMS2003Scheme()
{
    // TODO: 实现微软双拼方案
    initXiaoheScheme();
}

void Shuangpin::initZiguangScheme()
{
    // TODO: 实现紫光双拼方案
    initXiaoheScheme();
}

void Shuangpin::initABCScheme()
{
    // TODO: 实现ABC双拼方案
    initXiaoheScheme();
}


QStringList Shuangpin::toPinyin(const QString &shuangpin)
{
    QString input = shuangpin.toLower();
    QStringList result;

    if (input.isEmpty()) {
        return result;
    }

    if (input.length() == 1) {
        result.append(m_initialMap[input]);
        return result;
    }

    if (input.length() == 2) {
        QString initialKey = input.left(1);
        QString finalKey = input.right(1);

        QString initial;
        if (m_initialMap.contains(initialKey)) {
            initial = m_initialMap[initialKey];
        }
        else {
            return result;
        }

        QStringList finals;
        if (m_finalMap.contains(finalKey)) {
            finals = m_finalMap[finalKey];
        }
        else {
            return result;
        }

        for (const QString &final_ : finals) {
            result.append(initial + final_);
        }
    }

    return result;
}

QStringList Shuangpin::toFullPinyin(const QString &input)
{
    if (!isValid(input)) {
        return QStringList();
    }

    std::function<QStringList(const QString &, int)> recursiveConvert =
        [this, &recursiveConvert](const QString &str, int pos) -> QStringList {
        if (pos >= str.length()) {
            return QStringList("");
        }

        QStringList results;
        int remainingLength = str.length() - pos;

        if (remainingLength > 2) {
            QString twoChars = str.mid(pos, 2);
            QStringList pinyinList = toPinyin(twoChars);
            if (!pinyinList.isEmpty()) {
                QStringList restResults = recursiveConvert(str, pos + 2);
                for (const QString &pinyin : pinyinList) {
                    for (const QString &rest : restResults) {
                        results.append(pinyin + rest);
                    }
                }
            }
        }
        else {
            QString twoChars = str.mid(pos, remainingLength);
            QStringList pinyinList = toPinyin(twoChars);
            if (!pinyinList.isEmpty()) {
                for (const QString &pinyin : pinyinList) {
                    results.append(pinyin);
                }
            }
        }

        return results;
    };

    return recursiveConvert(input, 0);
}

bool Shuangpin::isValid(const QString &input)
{

    if (input.isEmpty()) {
        return false;
    }

    for (const QChar &c : input) {
        if (!c.isLetter()) {
            return false;
        }
    }

    return true;
}
