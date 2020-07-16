#include "gitrepolanguages.h"

GitRepoLanguages::GitRepoLanguages(QObject *parent, Interface *interface) : QObject(parent)
{
    network_manager = new QNetworkAccessManager;
    this->interface = interface;

    this->git_platform_data = new GitPlatformsData(this);
    qmlRegisterSingletonInstance<GitPlatformsData>("Qt.cpp.qobjectSingleton", 1, 0, "GitPlatformsData", git_platform_data);

    sl_language.append("Javascript");
    sl_language.append("Python");
    sl_language.append("Java");
    sl_language.append("C++");
    sl_language.append("C");
    sl_language.append("PHP");
    sl_language.append("C#");
    sl_language.append("Shell");
    sl_language.append("Go");
    sl_language.append("TypeScript");

    git_platform_data->FetchSaveFile();

    connect(network_manager, &QNetworkAccessManager::finished, this, &GitRepoLanguages::ReadGithubSearch);

}

GitRepoLanguages::~GitRepoLanguages()
{
    qDebug() << "Destructeur GitRepoLanguages";

    delete network_manager;
    delete git_platform_data;
}

void GitRepoLanguages::SearchOnGithub(Search search)
{
    if(github_search_processing == true)
        return;
    else
        github_search_processing = true;

    QString url_string = github_api_url + "/search/repositories?q=";
    url_string += "pushed:" + search.interval_time;
    url_string += " language:"+ search.language;
    url_string += " stars:>1";
    url_string += " followers:>1";
    url_string += "&token=" + github_token;

    qDebug() << url_string;

    github_api_timeout_remaining = github_api_timeout;

    network_manager->get(QNetworkRequest(QUrl(url_string)));
}

void GitRepoLanguages::SearchOnGitlab(Search search)
{
    if(gitlab_search_processing == true)
        return;
    else
        gitlab_search_processing = true;

    gitlab_api_timeout_remaining = gitlab_api_timeout;

    network_manager->get(QNetworkRequest(QUrl(github_api_url)));
}

QString GitRepoLanguages::ConvertLitteralMonthToNumber(QString litteral_month)
{
    QString month_number;

    if(litteral_month == "January"){
        month_number = "01";
    }
    else if(litteral_month == "February"){
        month_number = "02";
    }
    else if(litteral_month == "March"){
        month_number = "03";
    }
    else if(litteral_month == "April"){
        month_number = "04";
    }
    else if(litteral_month == "May"){
        month_number = "05";
    }
    else if(litteral_month == "June"){
        month_number = "06";
    }
    else if(litteral_month == "July"){
        month_number = "07";
    }
    else if(litteral_month == "August"){
        month_number = "08";
    }
    else if(litteral_month == "October"){
        month_number = "09";
    }
    else if(litteral_month == "September"){
        month_number = "10";
    }
    else if(litteral_month == "November"){
        month_number = "11";
    }
    else if(litteral_month == "December"){
        month_number = "12";
    }

    return month_number;
}

int GitRepoLanguages::GetNDayInMonth(int month_number)
{
    if(month_number == 1){
        return 31;
    }
    else if(month_number == 2){
        return 28;
    }
    else if(month_number == 3){
        return 31;
    }
    else if(month_number == 4){
        return 30;
    }
    else if(month_number == 5){
        return 31;
    }
    else if(month_number == 6){
        return 30;
    }
    else if(month_number == 7){
        return 31;
    }
    else if(month_number == 8){
        return 31;
    }
    else if(month_number == 9){
        return 30;
    }
    else if(month_number == 10){
        return 30;
    }
    else if(month_number == 11){
        return 30;
    }
    else if(month_number == 12){
        return 31;
    }

    return 0;
}

bool GitRepoLanguages::DoubleEquals(double a, double b, double epsilon)
{
    return std::abs(a - b) < epsilon;
}

void GitRepoLanguages::AddQueuedSearch(QString platform, QString language, QString year, QString month)
{
    Search search;
    search.language = language;
    search.platform = platform;
    search.year = year;
    search.month = month;

    int month_number = month.toInt();
    QString n_day_in_month = QString::number(GetNDayInMonth(month_number));

    QString interval_time = year + "-" + month + "-" + "01.." + year + "-" + month + "-" + n_day_in_month;
    search.interval_time = interval_time;

    if(platform == "github"){
        if(!q_github_search.contains(search)){
            q_github_search.append(search);
        }
    }
    else if(platform == "gitlab"){
        if(!q_gitlab_search.contains(search)){
            q_gitlab_search.append(search);
        }
    }
}

void GitRepoLanguages::AddLanguageData(QString platform, QString language, QString year, QString month, QString data)
{
    LanguageDataPerMonth *m_language_data = nullptr;
    if(platform == "github"){
        m_language_data = git_platform_data->GetMLanguageDataGithub();
    }
    else if(platform == "gitlab"){
        m_language_data = git_platform_data->GetMLanguageDataGitlab();
    }

    if(!m_language_data->contains(language)){ //On a pas des données stocké pour ce language
        QMap<QString, QMap<QString, QString>> m_language_y_data;
        QMap<QString, QString> m_language_m_data;

        m_language_m_data.insert(month, data);
        m_language_y_data.insert(year, m_language_m_data);
        m_language_data->insert(language, m_language_y_data);
    }

    else {

        if(!m_language_data->find(language)->contains(year)){ //On a pas des données stocké pour ce language et cette année
            QMap<QString, QString> m_language_m_data;

            m_language_m_data.insert(month, data);
            m_language_data->find(language)->insert(year, m_language_m_data);
        }

        else {

            if(!m_language_data->find(language)->find(year)->contains(month)){ //On a pas des données stocké pour ce language, cette année et ce mois

                m_language_data->find(language)->find(year)->insert(month, data);
            }
        }
    }
}

bool GitRepoLanguages::ExistLanguageData(QString platform, QString language, QString year, QString month)
{
    LanguageDataPerMonth *m_language_data = nullptr;
    if(platform == "github"){
        m_language_data = git_platform_data->GetMLanguageDataGithub();
    }
    else if(platform == "gitlab") {
        m_language_data = git_platform_data->GetMLanguageDataGitlab();
    }


    if(!m_language_data->contains(language)){ //On a pas des données stocké pour ce language

        return false;
    }

    else {

        if(!m_language_data->value(language).contains(year)){ //On a pas des données stocké pour ce language et cette année

            return false;
        }

        else {

            if(!m_language_data->value(language).value(year).contains(month)){ //On a pas des données stocké pour ce language, cette année et ce mois

                return false;
            }
        }
    }
    return true;
}

QQueue<Search> *GitRepoLanguages::GetGithubQueuedSearch()
{
    return &q_github_search;
}

QQueue<Search> *GitRepoLanguages::GetGitlabQueuedSearch()
{
    return &q_gitlab_search;
}

int GitRepoLanguages::_GetGithubQueuedSearchN()
{
    return q_github_search.length();
}

int GitRepoLanguages::_GetGitlabQueuedSearchN()
{
    return q_gitlab_search.length();
}

int GitRepoLanguages::_GetLoadingProgression()
{
    return loading_progression;
}

void GitRepoLanguages::_NewLoadingProcess(QString platform)
{
    discard_next_answer = true;

    if(platform == "github"){
        q_github_search.clear();
        github_api_timeout_remaining = 0;
    }
    else if(platform == "gitlab"){
        q_gitlab_search.clear();
        gitlab_api_timeout_remaining = 0;
    }

    loading_progression = 0;

    if(first_loading == true){
        first_loading = false;
    }
    else{
        interface->UpdateSlide();
    }

    qDebug() << "New loading process";
}

GitPlatformsData *GitRepoLanguages::_GetGitPlatformsData()
{
    return git_platform_data;
}

void GitRepoLanguages::StartTreatQueuedSearch()
{
    QElapsedTimer e_timer;
    e_timer.start();

    qDebug() << "gl: " << q_github_search.length();

    if(!q_github_search.empty() && !github_search_processing && github_api_timeout_remaining <= 0){

        github_api_timeout_remaining = github_api_timeout;

        Search search = q_github_search.at(0);
        SearchOnGithub(search);
    }

    if(!q_gitlab_search.empty() && !gitlab_search_processing && gitlab_api_timeout_remaining <= 0){

        gitlab_api_timeout_remaining = gitlab_api_timeout;

        Search search = q_gitlab_search.at(0);
        SearchOnGitlab(search);
    }


    long long time_to_wait = 400-e_timer.elapsed();
    if(time_to_wait > 0){

        github_api_timeout_remaining -= time_to_wait;
        gitlab_api_timeout_remaining -= time_to_wait;

        if(!DoubleEquals(github_api_timeout_remaining, github_api_timeout, 1)){
            github_api_timeout_remaining -= e_timer.elapsed();
        }

        if(!DoubleEquals(gitlab_api_timeout_remaining, gitlab_api_timeout, 1)){
            gitlab_api_timeout_remaining -= e_timer.elapsed();
        }

        QTimer::singleShot(time_to_wait, this, SLOT(StartTreatQueuedSearch()));
    }
    else{

        if(!DoubleEquals(github_api_timeout_remaining, github_api_timeout)){
            github_api_timeout_remaining -= e_timer.elapsed();
        }

        if(!DoubleEquals(gitlab_api_timeout_remaining, gitlab_api_timeout)){
            gitlab_api_timeout_remaining -= e_timer.elapsed();
        }

        StartTreatQueuedSearch();
    }

}

void GitRepoLanguages::ReadGithubSearch(QNetworkReply *reply)
{

    if(discard_next_answer == true){
        discard_next_answer = false;
        github_search_processing = false;

        return;
    }

    QByteArray reply_data = reply->readAll();

    QJsonDocument json_doc = QJsonDocument::fromJson(reply_data);
    QJsonObject json_object = json_doc.object();

    qDebug() << json_object["total_count"];
    double total_count_d = json_object["total_count"].toDouble(); qDebug() << total_count_d;
    QString total_count = QString::number(total_count_d);

    if(q_github_search.empty()){
        qDebug() << "no github search";
        return;
    }

    Search search;
    search = q_github_search.at(0);
    AddLanguageData(search.platform, search.language, search.year, search.month, total_count);

    q_github_search.pop_front();

    github_search_processing = false;
    loading_progression = loading_progression+1;

    if(loading_progression != 0){
        git_platform_data->SaveData();
    }

    interface->UpdateSlide();

}

void GitRepoLanguages::ReadGitlabSearch(QNetworkReply *reply)
{
    qDebug() << reply->readAll();

    //q_gitlab_search.pop_front();
    gitlab_search_processing = false;
    loading_progression++;
}

void GitRepoLanguages::_LoadChart1Data(QString cb_year, QString cb_month, QString platform)
{

    QString year = cb_year;


    if(cb_month == "Whole year"){

        for(int a = 0; a < sl_language.length(); a++){

            QString language = sl_language.at(a);

            for(int i = 1; i <= 12; i++){

                QString month_number_str = QString::number(i);
                if(i < 10){
                    month_number_str = "0" + month_number_str;
                }

                if(!ExistLanguageData(platform, language, year, month_number_str)){
                    AddQueuedSearch(platform, language, year, month_number_str);
                }
            }
        }
    }
    else{

        QString month_number_str = ConvertLitteralMonthToNumber(cb_month);

        for(int a = 0; a < sl_language.length(); a++){

            QString language = sl_language.at(a);

            if(!ExistLanguageData(platform, language, year, month_number_str)){
                AddQueuedSearch(platform, language, year, month_number_str);
            }
        }
    }
}

void GitRepoLanguages::_LoadChart2Data(QString cb_year, QString cb_language, QString platform)
{

    QDate current_date = QDate::currentDate();
    int current_year = current_date.year();

    for(int l = 0; l < sl_language.length(); l++){

        QString language = sl_language.at(l);

        if(cb_language != "All languages" && language != cb_language){
            continue;
        }

        for(int y = 2014; y <= current_year; y++){

            QString year = QString::number(y);

            if(cb_year != "Always" && year != cb_year){
                continue;
            }

            for(int m = 1; m <= 12; m++){

                QString month_number_str = QString::number(m);
                if(m < 10){
                    month_number_str = "0" + month_number_str;
                }

                if(!ExistLanguageData(platform, language, year, month_number_str)){
                    AddQueuedSearch(platform, language, year, month_number_str);
                }
            }
        }
    }
}
