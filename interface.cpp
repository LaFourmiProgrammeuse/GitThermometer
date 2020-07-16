#include "interface.h"

Interface::Interface()
{
    qDebug() << "Constructeur Interface";

}

void Interface::CreateQmlInterface()
{
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent component(&engine, url);

    interface_qml = component.create();

    QObject::connect(interface_qml, SIGNAL(_GitlabImageSelected()), this, SLOT(onGitlabImageSelected()));
    QObject::connect(interface_qml, SIGNAL(_GithubImageSelected()), this, SLOT(onGithubImageSelected()));
}

void Interface::SetPageIndex(int index)
{
    page_index = index;
}

int Interface::GetPageIndex()
{
    return page_index;
}

void Interface::UpdateSlide()
{
    QObject *platform_charts = interface_qml->findChild<QObject *>("platform_charts");
    QMetaObject::invokeMethod(platform_charts, "updateSlide", Q_ARG(QVariant, "NULL"));
}

void Interface::onGitlabImageSelected()
{
    qDebug() << "Gitlab image clicked";

    UpdateSlide();
}

void Interface::onGithubImageSelected()
{
    qDebug() << "Github image clicked";

    UpdateSlide();
}
