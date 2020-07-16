#include <QApplication>
#include <QLoggingCategory>

#include "interface.h"
#include "gitrepolanguages.h"
#include "gitplatformsdata.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));

    Interface interface;

    GitRepoLanguages gp(nullptr, &interface);
    qmlRegisterSingletonInstance<GitRepoLanguages>("Qt.cpp.qobjectSingleton", 1, 0, "GitRepoLanguages", &gp);

    interface.CreateQmlInterface();

    gp.StartTreatQueuedSearch();


    return app.exec();
}
