#ifndef INTERFACE_H
#define INTERFACE_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QDebug>

class Interface : public QObject
{
    Q_OBJECT
public:
    Interface();

    void CreateQmlInterface();

    void SetPageIndex(int index);
    int GetPageIndex();
    void UpdateSlide();

public slots:
    void onGitlabImageSelected();
    void onGithubImageSelected();

private:
    QQmlApplicationEngine engine;
    QObject *interface_qml;

    int page_index = 0;

};

#endif // INTERFACE_H
