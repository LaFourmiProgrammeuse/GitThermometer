#ifndef GITPLATFORMSDATA_H
#define GITPLATFORMSDATA_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>

struct Search {
    QString platform;
    QString interval_time;
    QString language;
    QString year;
    QString month;
};

class GitRepoLanguages;

#include "gitrepolanguages.h"

inline bool operator==(Search const& search_a, Search const& search_b){

    return search_a.year == search_b.year
            && search_a.month == search_b.month
            && search_a.language == search_b.language
            && search_a.platform == search_b.platform
            && search_a.interval_time == search_b.interval_time;
}

typedef QMap<QString, QMap<QString, QMap<QString, QString>>> LanguageDataPerMonth;

class GitPlatformsData : public QObject
{
    Q_OBJECT

public:
    GitPlatformsData(GitRepoLanguages *git_repo_languages);

    LanguageDataPerMonth *GetMLanguageDataGithub();
    LanguageDataPerMonth *GetMLanguageDataGitlab();

    Q_INVOKABLE QJsonObject _ParseToJsonLangageData();
    void SetDataArrayFromJson(QString json);

    void SaveData();
    void FetchSaveFile();

private:
    LanguageDataPerMonth m_language_data_github; //language / year / month
    LanguageDataPerMonth m_language_data_gitlab;

    GitRepoLanguages *git_repo_languages = nullptr;

};

#endif // GITPLATFORMSDATA_H
