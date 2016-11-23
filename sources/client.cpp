#include <iostream>
#include <curl/curl.h>
#include <client.hpp>
#include <json.hpp>

namespace Instagram{

	using json = nlohmann::json;

	auto Client::check_connection() -> bool {
		
        	std::string json_data;
		CURL* EasyCurl = curl_easy_init();

		curl_easy_setopt(EasyCurl, CURLOPT_URL, "https://api.instagram.com/v1/users/self/?access_token=");
		curl_easy_setopt(EasyCurl, CURLOPT_POSTFIELDS, _settings["access_token"]);
        	curl_easy_setopt(EasyCurl, CURLOPT_WRITEFUNCTION, Client::CallbackFunction);
        	curl_easy_setopt(EasyCurl, CURLOPT_WRITEDATA, &json_data);
		auto perform_result = curl_easy_perform(EasyCurl);
     
	
		if  (perform_result == CURLE_OK && json_data != "") {
       
        		json user_inf = json::parse(json_data);
           		curl_easy_cleanup(EasyCurl);
        
           		if (user_inf["meta"]["code"] == "200") 
                		return true;
           		else return false; 
		}
    

    		curl_easy_cleanup(EasyCurl);
        	return false;
	} 

	
	
	auto Client::get_most_popular_photo() -> std::string {
        	std::string json_data;
        	CURL* EasyCurl = curl_easy_init();

		curl_easy_setopt(EasyCurl, CURLOPT_URL, "https://api.instagram.com/v1/users/self/follows?access_token=");
		curl_easy_setopt(EasyCurl, CURLOPT_POSTFIELDS, _settings["access_token"]);
        	curl_easy_setopt(EasyCurl, CURLOPT_WRITEFUNCTION, Client::CallbackFunction);
        	curl_easy_setopt(EasyCurl, CURLOPT_WRITEDATA, &json_data);
		
        	if (curl_easy_perform(EasyCurl) == CURLE_OK && json_data != ""){
            		json link_to_photo = (json::parse(json_data))["data"]["link"];
            
            		curl_easy_cleanup(EasyCurl);

            		return link_to_photo;
        	}
        	else {
            		curl_easy_cleanup(EasyCurl);
            		return "Error";
        	}
	}

    	auto Client::CallbackFunction(char *ptr, size_t size, size_t nmemb, char *userdata) -> size_t{
        	size_t realsize = size * nmemb;
        	std::cout << realsize << std::endl;
        	((std::string*) userdata) -> append(ptr, 0, realsize + 1 );
         	return realsize;
    	}
}
