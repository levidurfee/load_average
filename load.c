#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

int send_load_avg(char api_url[512], double *load);

int main(int argc, char *argv[]) {
    if(argc == 1) {
        printf("Usage: %s url\n", argv[0]);
        return -1;
    }
    char api_url[512];
    double load[3];
    
    sprintf(api_url, "%s", argv[1]);
    
    if (getloadavg(load, 3) != -1) {  
        printf("Got load avg\n");
    } else {
        printf("Error getting load\n");
        return -1;
    }
    send_load_avg(api_url, load);
    return 0;
}

int send_load_avg(char api_url[512], double *load) {
    char post[2048];
    char hostname[1024];
    char load_avg[512];
    
    sprintf(load_avg, "load=%f,%f,%f", load[0], load[1], load[2]);
    gethostname(hostname, 1024);
    sprintf(post, "hostname=%s&%s", hostname, load_avg);
    
    printf("%s\n", post);
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, api_url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(post));
        
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return 0;
}