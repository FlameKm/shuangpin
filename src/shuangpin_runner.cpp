#include "shuangpin_runner.h"
#include <QDebug>
#include <KLocalizedString>
#include <QGuiApplication>
#include <QClipboard>
#include <unordered_set>
#include "krunner/runnermanager.h"


K_EXPORT_PLASMA_RUNNER_WITH_JSON(ShuangpinRunner, "plasma-krunner-shuangpin.json")

ShuangpinRunner::ShuangpinRunner(QObject *parent, const KPluginMetaData &metaData, const QVariantList &args)
    : Plasma::AbstractRunner(parent, metaData, args), m_shuangpin(Shuangpin::XIAOHE)
{
    addSyntax(Plasma::RunnerSyntax(QStringLiteral(":q:"), i18n("Shuangpin to Pinyin converter")));
    addSyntax(Plasma::RunnerSyntax(QStringLiteral(""), i18n("Search shuangpin combinations")));
}

ShuangpinRunner::~ShuangpinRunner()
{
}

void ShuangpinRunner::match(Plasma::RunnerContext &context)
{
    if (context.query().isEmpty()) {
        qDebug() << "[ShuangpinRunner] query is empty, returning";
        return;
    }

    QString query = context.query();

    if (!query.isEmpty() && !allLetters(query)) {
        return;
    }

    QStringList convertedPinyins = m_shuangpin.toFullPinyin(query);

    if (!convertedPinyins.isEmpty()) {
        Plasma::RunnerContext newContext(context.parent());
        newContext.reset();

        matchPinyin(newContext, convertedPinyins[0]);

        const auto matches = newContext.matches();
        for (const Plasma::QueryMatch &m : matches) {
            context.addMatch(m);
        }
    }
}

void ShuangpinRunner::matchPinyin(Plasma::RunnerContext &context, const QString &pinyin)
{
    context.setQuery(pinyin);

    auto manager = qobject_cast<Plasma::RunnerManager *>(parent());
    if (!manager) {
        qDebug() << "[ShuangpinRunner] Could not get RunnerManager from parent";
        return;
    }

    const QList<Plasma::AbstractRunner *> allRunners = manager->runners();

    std::unordered_set<QString> unmatchedIds;
    unmatchedIds.insert("krunner_kill");
    // unmatchedIds.insert("org.kde.datetime");
    unmatchedIds.insert("Dictionary");

    for (Plasma::AbstractRunner *runner : allRunners) {
        if (runner == this) {
            continue;
        }
        if (unmatchedIds.find(runner->id()) != unmatchedIds.end()) {
            continue;
        }

        runner->match(context);
    }
}


void ShuangpinRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context);

    QString convertedText = match.data().toString();
    qDebug() << "Running Shuangpin match, copying to clipboard:" << convertedText;
}

bool ShuangpinRunner::allLetters(const QString &input)
{
    for (const QChar &c : input) {
        if (!c.isLetter()) {
            return false;
        }
    }
    return true;
}

#include "shuangpin_runner.moc"
