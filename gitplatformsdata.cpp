#include "gitplatformsdata.h"

GitPlatformsData::GitPlatformsData(GitRepoLanguages *git_repo_languages)
{
    this->git_repo_languages = git_repo_languages;
}

LanguageDataPerMonth *GitPlatformsData::GetMLanguageDataGithub()
{
    return &m_language_data_github;
}

LanguageDataPerMonth *GitPlatformsData::GetMLanguageDataGitlab()
{
    return &m_language_data_gitlab;
}

QJsonObject GitPlatformsData::_ParseToJsonLangageData()
{
    LanguageDataPerMonth *m_language_data = nullptr;

    QJsonObject json_object;

    for(int i = 0; i < 2; i++){

        if(i == 0){
            m_language_data = &m_language_data_github;
        }
        else if(i == 1){
            m_language_data = &m_language_data_gitlab;
        }

        QJsonObject language_j_array;

        LanguageDataPerMonth::const_iterator language_iterator = m_language_data->constBegin();
        while(language_iterator != m_language_data->constEnd()){

            QString language = language_iterator.key();
            QMap<QString, QMap<QString, QString>>::const_iterator year_iterator = m_language_data->value(language).constBegin();

            QJsonObject year_j_array;

            while(year_iterator != m_language_data->value(language).constEnd()){

                QString year = year_iterator.key();
                QMap<QString, QString>::const_iterator month_iterator = m_language_data->value(language).value(year).constBegin();

                QJsonObject month_j_array;

                while(month_iterator != m_language_data->value(language).value(year).constEnd()){

                    QString month = month_iterator.key();

                    QString data = m_language_data->value(language).value(year).value(month);
                    month_j_array[month] = data;

                    month_iterator++;
                }

                year_j_array[year] = month_j_array;
                year_iterator++;
            }

            language_j_array[language] = year_j_array;
            language_iterator++;
        }
        if(i == 0){
            json_object["github"] = language_j_array;
        }
        else if(i == 1){
            json_object["gitlab"] = language_j_array;
        }
    }

    return json_object;
}

void GitPlatformsData::SetDataArrayFromJson(QString json)
{
    LanguageDataPerMonth *m_language_data = nullptr;

    QJsonDocument json_document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject json_object = json_document.object();

    for(int i = 0; i < 2; i++){


        QString platform;
        if(i == 0){
            platform = "github";
        }
        else if(i == 1){
            platform = "gitlab";
        }

        QJsonObject platform_object = json_object.find(platform).value().toObject();
        QVariantMap map_language = platform_object.toVariantMap();

        QVariantMap::iterator map_language_iterator;
        for(map_language_iterator = map_language.begin(); map_language_iterator != map_language.end(); map_language_iterator++){

            QString language = map_language_iterator.key();

            QJsonObject year_object = map_language_iterator.value().toJsonObject();
            QVariantMap map_year = year_object.toVariantMap();

            QVariantMap::iterator map_year_iterator;
            for(map_year_iterator = map_year.begin(); map_year_iterator != map_year.end(); map_year_iterator++){

                QString year = map_year_iterator.key();

                QJsonObject month_object = map_year_iterator.value().toJsonObject();
                QVariantMap map_month = month_object.toVariantMap();

                QVariantMap::iterator map_month_iterator;
                for(map_month_iterator = map_month.begin(); map_month_iterator != map_month.end(); map_month_iterator++){

                    QString month = map_month_iterator.key();

                    //qDebug() << language << year << month;

                    QString data = map_month_iterator.value().toString();
                    git_repo_languages->AddLanguageData(platform, language, year, month, data);
                }
            }
        }
    }
}

void GitPlatformsData::SaveData()
{
    QJsonObject json_object = _ParseToJsonLangageData();
    QJsonDocument json_document(json_object);

    QFile save_file("./languages_data.json");
    if(!save_file.open(QIODevice::WriteOnly)){
        qDebug() << "Erreur lors de l'ouverture du fichier ./languages_data.json";
    }

    save_file.write(json_document.toJson());

    save_file.close();
}

void GitPlatformsData::FetchSaveFile()
{
    QFile save_file("./languages_data.json");
    if(!save_file.open(QIODevice::ReadOnly)){
        qDebug() << "Erreur lors de l'ouverture du fichier ./languages_data.json";
    }

    QString content = save_file.readAll();
    save_file.close();

    //qDebug() << content;

    SetDataArrayFromJson(content);
}
