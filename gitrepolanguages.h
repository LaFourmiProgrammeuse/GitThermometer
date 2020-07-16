#ifndef GITPLAFORMS_H
#define GITPLAFORMS_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QMap>
#include <QElapsedTimer>
#include <QQmlEngine>
#include <QApplication>
#include <QDate>

class GitPlatformsData;

#include "gitplatformsdata.h"
#include "interface.h"

class GitRepoLanguages : public QObject
{
    Q_OBJECT
public:
    GitRepoLanguages(QObject *parent = nullptr, Interface *interface = nullptr);
    ~GitRepoLanguages();

    void SearchOnGithub(Search search);
    void SearchOnGitlab(Search search);

    QString ConvertLitteralMonthToNumber(QString litteral_month);
    int GetNDayInMonth(int month_number);
    bool DoubleEquals(double a, double b, double epsilon = 0.001);

    void AddQueuedSearch(QString platform, QString language, QString year, QString month);
    void AddLanguageData(QString platform, QString language, QString year, QString month, QString data);
    bool ExistLanguageData(QString platform, QString language, QString year, QString month);

    QQueue<Search> *GetGithubQueuedSearch();
    QQueue<Search> *GetGitlabQueuedSearch();

    Q_INVOKABLE int _GetGithubQueuedSearchN();
    Q_INVOKABLE int _GetGitlabQueuedSearchN();

    Q_INVOKABLE int _GetLoadingProgression();
    Q_INVOKABLE void _NewLoadingProcess(QString platform);

    Q_INVOKABLE GitPlatformsData *_GetGitPlatformsData();


public slots:
    void ReadGithubSearch(QNetworkReply *reply);
    void ReadGitlabSearch(QNetworkReply *reply);

    Q_INVOKABLE void _LoadChart1Data(QString cb_year, QString cb_month, QString platform);
    Q_INVOKABLE void _LoadChart2Data(QString cb_year, QString language, QString platform);

    void StartTreatQueuedSearch();

private:
    QNetworkAccessManager *network_manager = nullptr;
    GitPlatformsData *git_platform_data = nullptr;
    Interface *interface = nullptr;

    QQueue<Search> q_github_search;
    QQueue<Search> q_gitlab_search;

    bool github_search_processing = false;
    bool gitlab_search_processing = false;

    const double github_api_timeout = 7600;
    const double gitlab_api_timeout = 7600;

    double github_api_timeout_remaining = 0;
    double gitlab_api_timeout_remaining = 0;

    int loading_progression = 0;
    bool discard_next_answer = false;
    bool first_loading = true;

    const QString github_api_url = "https://api.github.com";
    const QString gitlab_api_url;

    QString github_token = "ea4bbe062630801754e992c22c6332ebc77c284a";
    QString gitlab_token = "9hCw65Xmuas3Gcf2WgE4";

    QStringList sl_language;

};

#endif // GITPLAFORMS_H
