var l_color = ["#1abc9c", "#e74c3c", "#3498db", "#9b59b6", "#22a6b3", "#30336b", "#badc58", "#ff7979", "#be2edd", "#535c68"];

function showSlide2(){

    if(stack_view.currentItem !== slide_languages_2){
        stack_view.replace(slide_languages_2)
    }
}

function showSlide1(){
    if(stack_view.currentItem !== slide_languages_1){
        stack_view.replace(slide_languages_1)
    }
}

function updateSlide(new_download_process){

    if(new_download_process === true)
        Cpp.GitRepoLanguages._NewLoadingProcess(git_platform_selected);

    if(active_slide_index == 0){
        updateSlide1(new_download_process)
    }
    else{
        updateSlide2(new_download_process)
    }

}

function updateSlide1(new_download_process){

    let n_gitlab_queued_search;
    let n_github_queued_search;

    let loading_progression;

    Cpp.GitRepoLanguages._LoadChart1Data(cb_year_s1_text, cb_month_s1_text, git_platform_selected);

    if(git_platform_selected == "github"){

        n_github_queued_search = Cpp.GitRepoLanguages._GetGithubQueuedSearchN();

        if(new_download_process === true){
            loading_s1.setMaxRequest(n_github_queued_search)
        }

        loading_progression = Cpp.GitRepoLanguages._GetLoadingProgression();
        loading_s1.setProgression(loading_progression);

        if(n_github_queued_search > 0){
            loading_s1.visible = true;
            chartview_s1.visible = false;
            chartview_s2.visible = false;
        }
        else{
            loading_s1.visible = false;
            chartview_s1.visible = true;
            chartview_s2.visible = false;

            updateSlide1Chart();
        }
    }
    else if(git_platform_selected == "gitlab"){

        n_gitlab_queued_search = Cpp.GitRepoLanguages._GetGitlabQueuedSearchN();

        if(new_download_process === true){
            loading_s1.setMaxRequest(n_gitlab_queued_search)
        }

        loading_progression = Cpp.GitRepoLanguages._GetLoadingProgression();
        loading_s1.setProgression(loading_progression);

        if(n_gitlab_queued_search > 0){
            loading_s1.visible = true;
            chartview_s1.visible = false;
            chartview_s2.visible = false;
        }
        else{
            loading_s1.visible = false;
            chartview_s1.visible = true;
            chartview_s2.visible = false;

            updateSlide1Chart();
        }
    }
    showSlide1();

}

function updateSlide2(new_download_process){

    let n_gitlab_queued_search;
    let n_github_queued_search;

    let loading_progression;

    Cpp.GitRepoLanguages._LoadChart2Data(cb_year_s2_text, cb_language_s2_text, git_platform_selected);

    if(git_platform_selected == "github"){

        n_github_queued_search = Cpp.GitRepoLanguages._GetGithubQueuedSearchN();

        if(new_download_process === true){
            loading_s2.setMaxRequest(n_github_queued_search)
        }

        loading_progression = Cpp.GitRepoLanguages._GetLoadingProgression();
        loading_s2.setProgression(loading_progression);


        if(n_github_queued_search > 0){
            loading_s2.visible = true;
            chartview_s2.visible = false;
            chartview_s1.visible = false;
        }
        else{
            loading_s2.visible = false;
            chartview_s2.visible = true;
            chartview_s1.visible = false;

            updateSlide2Chart();
        }
        showSlide2();
    }
    else if(git_platform_selected == "gitlab"){

        n_gitlab_queued_search = Cpp.GitRepoLanguages._GetGitlabQueuedSearchN();

        if(new_download_process === true){
            loading_s2.setMaxRequest(n_gitlab_queued_search)
        }

        loading_progression = Cpp.GitRepoLanguages._GetLoadingProgression();
        loading_s2.setProgression(loading_progression);

        if(n_gitlab_queued_search > 0){
            loading_s2.visible = true;
            chartview_s2.visible = false;
            chartview_s1.visible = false;
        }
        else{
            loading_s2.visible = false;
            chartview_s2.visible = true;
            chartview_s1.visible = false;

            updateSlide2Chart();
        }
    }
    showSlide2();
}

function updateSlide1Chart(){

    barseries_s1.clear(); //On enlève les barres déjà présentent sur le graphique

    let hightest_value = 0;

    let data_json = Cpp.GitPlatformsData._ParseToJsonLangageData();
    let l_language = Object.entries(data_json[git_platform_selected]);

    chartview_s1.title = "Number of active repositories"



    //Ajout des catégories

    if(cb_month_s1_text != "Whole year"){

        let month_number = monthToNumber(cb_month_s1_text);
        let year = cb_year_s1_text;

        let category_string = month_number + "/" + year

        barseries_s1.axisX.categories = [category_string]
    }
    else{

        let year = cb_year_s1_text;
        barseries_s1.axisX.categories = [year]
    }




    //Ajout des points

    let l_n_repo_sorted = new Array;

    for(let [key, value] of l_language){

        let language_name = key;
        let l_year = Object.entries(value);

        for(let [key, value] of l_year){

            let year = key;
            let year_to_fetch = cb_year_s1_text;

            if(year !== year_to_fetch){
                continue
            }

            let month_index = 0;
            let n_repo_year = 0

            let l_month = Object.entries(value);
            for(let [key, value] of l_month){

                let month = key;

                if(cb_month_s1_text == "Whole year"){

                    let n_repo = Number(value);
                    n_repo_year = n_repo_year + n_repo;

                    if(month_index+1 === l_month.length){
                        l_n_repo_sorted.push([language_name, n_repo_year]);
                    }

                    if(n_repo_year
                            > hightest_value){
                        hightest_value = n_repo_year;
                    }

                }
                else{

                    let month_to_fetch = monthToNumber(cb_month_s1_text);

                    if(month_to_fetch !== month){ //On récupère seulement les données du mois choisis
                        continue;
                    }

                    let n_repo = Number(value);



                    l_n_repo_sorted.push([language_name, n_repo]);



                    if(n_repo > hightest_value){
                        hightest_value = n_repo;
                    }
                }
                month_index++;
            }
        }
    }
    barseries_s1.axisY.min = "0"
    barseries_s1.axisY.max = "" + hightest_value

    //On trie les valeurs du nombre de dépôt par ordre décroissant

    l_n_repo_sorted.sort((a, b) => {
                             return b[1] - a[1];
                         });

    for(let language_data of l_n_repo_sorted){
        barseries_s1.append(language_data[0]+ "", [language_data[1]]);
    }

}

function updateSlide2Chart(){

    chartview_s2.removeAllSeries() //On enlève les points déjà présentent sur le graphique

    let hightest_value = 0;

    let data_json = Cpp.GitPlatformsData._ParseToJsonLangageData();
    let l_language = Object.entries(data_json[git_platform_selected]);

    chartview_s2.title = "Evolution of active repositories";

    let n_repo_max = 0;
    let color_index = 0;

    //Variables pour l'option une seule année
    let l_n_repo_per_month = new Array

    //Variables pour l'option depuis toujours
    let n_repo_year = 0;
    let label_index = 0;

    for(let [key, value] of l_language){

        let language_name = key;
        let language_to_fetch = cb_language_s2_text;

        if(language_to_fetch !== language_name && language_to_fetch !== "All languages"){
            continue;
        }

        let line_series = chartview_s2.createSeries(ChartView.SeriesTypeLine, language_name);
        line_series.axisX = axisX_chart_2;

        /*if(color_index > l_color.length){
            color_index = 0
        }

        line_series.color = l_color[color_index];
        color_index = color_index + 1;*/

        let l_year = Object.entries(value);

        for(let [key, value] of l_year){

            let year = key;
            let year_to_fetch = cb_year_s2_text;

            if(year !== year_to_fetch && year_to_fetch !== "Always"){
                continue;
            }

            let point_x_index = 0;

            let l_month = Object.entries(value);
            for(let [key, value] of l_month){

                let month = parseInt(key);
                let n_repo = parseInt(value);

                if(n_repo > n_repo_max){
                    n_repo_max = n_repo;
                }

                l_n_repo_per_month[month] = n_repo;
            }

            //Ajout des catégories sur l'axe X
            for(var m = 1; m <= 12; m++){

                let month;
                if(m < 10){
                    month = "0" + m;
                }
                else{
                    month = m;
                }

                let label = month + "/" + year;
                line_series.axisX.append(label, m);
            }
        }
        line_series.axisY.max = n_repo_max;
        line_series.axisY.min = 0;

        if(cb_year_s2_text !== "Always"){
            line_series.axisX.max = 12;

            //Ajout des points
            for(var x = 0; x < 12; x++){
                var y = l_n_repo_per_month[x+1];

                if(y === 0){
                    continue;
                }

                line_series.append(x+0.5, y);
            }
        }
        else if(cb_year_s2_text === "Always"){

        }
    }
}

function monthToNumber(month_){

    let month = month_.toLowerCase()

    if(month === "january"){
        return "01"
    }
    else if(month === "february"){
        return "02"
    }
    else if(month === "march"){
        return "03"
    }
    else if(month === "april"){
        return "04"
    }
    else if(month === "may"){
        return "05"
    }
    else if(month === "june"){
        return "06"
    }
    else if(month === "july"){
        return "07"
    }
    else if(month === "august"){
        return "08"
    }
    else if(month === "september"){
        return "09"
    }
    else if(month === "october"){
        return "10"
    }
    else if(month === "november"){
        return "11"
    }
    else if(month === "december"){
        return "12"
    }
}
