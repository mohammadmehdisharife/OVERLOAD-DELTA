#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    CURL *curl;
    CURLcode res;
    FILE *devnull;

    if(argc < 3) {
        printf("Usage: %s <URL> <NUMBER>\n", argv[0]);
        return 1;
    }

    devnull = fopen("/dev/null", "w");
    if(!devnull) {
        perror("Failed to open /dev/null");
        return 1;
    }

    int success = 0;
    int error = 0;
    for(int i = 0; i < atoi(argv[2]); i++) {
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, devnull);
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

            res = curl_easy_perform(curl);

            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                error++;
            } else {
                success++;
            }

            curl_easy_cleanup(curl);
        }
    }
    printf("ALL:     %d\n",atoi(argv[2]));
    printf("ERROR:   %d\n",error);
    printf("SUCCESS: %d\n",success);
    fclose(devnull);
    return 0;
}
