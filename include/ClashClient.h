#pragma once 

#include <string>
#include <curl/curl.h>
#include <iostream>

class ClashClient {

public:  //jwt json web token, password for api
    explicit ClashClient(const std::string& token): token_(token){}

    std::string getPlayer(const std::string& playerTag) {
    std::string url = "https://api.clashroyale.com/v1/players/" + urlEncodeTag(playerTag);
    return fetch(url);
}

std::string getBattleLog(const std::string& playerTag) {
    std::string url = "https://api.clashroyale.com/v1/players/" + urlEncodeTag(playerTag) + "/battlelog";
    return fetch(url);
}

private:
    std::string token_;






//man CURLOPT_WRITEFUNCTION, must match libcurls required signature 
//libcurl calls this multiple times when response bytes arrive
static size_t libcurlCalled(void* contents, size_t size, size_t nmemb, std::string *out)
{
    
    size_t total = size * nmemb; 

    char* charContents = static_cast<char*> (contents); 

    //reads until total bytes
    (*out).append(charContents, total);

    return total; 


}

//fetch method, new curl request every time
//with url, perform http get request, return raw response as string
std:: string fetch (const std::string &url) 
{ 
    //https://curl.se/libcurl/c/

    CURL* curl =  curl_easy_init(); 
    std::string response;

    //when handle is valid
    if (curl) 
    {
        std::string authHeader =  "Authorization: Bearer " + token_; 
        
        //c library
        struct curl_slist* headers = nullptr;
        //string to const char *, builds linked list that could hold multiple headers
        headers = curl_slist_append(headers, authHeader.c_str());

        //filling in curl object

        //destination address, which url
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        //what headers go with this request 
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        //which function handles response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, libcurlCalled);
        //where the reply is stored 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        //send request 
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "curl error: " << curl_easy_strerror(res) << "\n";
        }

        //done using memory
        curl_slist_free_all(headers); 
        curl_easy_cleanup(curl); 
    }

    return response; 
}
static std::string urlEncodeTag (const std::string &tag)
{
    if (tag.empty() || tag[0] != '#')
    {
        return tag; 
    }
    //replace # with %23
    std::string url = "%23";
    for (size_t i = 1; i < tag.length(); ++i)
    {
        url.push_back(tag[i]);
    }
    return url; 
}



};