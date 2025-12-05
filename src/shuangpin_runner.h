#ifndef SHUANGPIN_RUNNER_H
#define SHUANGPIN_RUNNER_H

#include <KRunner/AbstractRunner>
#include "shuangpin.h"

class ShuangpinRunner : public Plasma::AbstractRunner
{
    Q_OBJECT

public:
    ShuangpinRunner(QObject *parent, const KPluginMetaData &metaData, const QVariantList &args);
    ~ShuangpinRunner() override;

    void match(Plasma::RunnerContext &context) override;
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match) override;

private:
    Shuangpin m_shuangpin;
    bool allLetters(const QString &input);
    void matchPinyin(Plasma::RunnerContext &context, const QString &pinyin);
};

#endif // SHUANGPIN_RUNNER_H
