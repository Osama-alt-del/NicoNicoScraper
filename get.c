// This is a simple get file to learn how to use the library I just compiled
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>
#include <stdio.h>

// also what's the point of returning in a main function? it's not like something else is going to call it right? (you can access output in the shell)

// curl_easy_perform() outputs to stdout by default.



int main() { 
    CURL *curl; // I have to understand what this is doing (opaque handler)
    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);

    if (result != CURLE_OK) {  // why is this CURLE and not CURL?
        return (int) result; // turn the result into an integer and return it
    }

    curl = curl_easy_init(); // so we initialised the object and pass pointer into the handler
    
    if (curl) {  // if it was initialized properly, then:
        
        /* This is the actual important part where we set the curl handler up */
        // it looks like these change the values of members of the object
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.nicovideo.jp/"); 
        
        // url is redirected, so we tell curl to follow location
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);


        // perform the get request, result gets the return code (GO)
        result = curl_easy_perform(curl); // so the "settings" of what we want to do are in the handler, we just need to access that info
        
        // check for errors:
        if(result != CURLE_OK) { 
            // dunno what fprintf is, but this probably prints to stderr stream
            fprintf(stderr, "curl_easy_perform() failed : %s\n", curl_easy_strerror(result));
        }

        // clean up after (maybe clear memory and stuff)
        curl_easy_cleanup(curl); // it takes the pointer (opaque handler)
    }

    // then we clean up more ?
    curl_global_cleanup();

    return (int)result; // again, I don't understand why we return result in a mian
}

