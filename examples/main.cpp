#include <client.hpp>
#include <iostream>

int main (){
	std::map <std::string, std::string> settings;
	
    	std::cout << "click on the link to get acces_token " << std::endl
    		  << "https://api.instagram.com/oauth/authorize/?client_id=6fd93ecd973849eabbdb6cba7925d1d1&redirect_uri=https://localhost&response_type=token"
	    	  << std::endl << " enter your acces_token:  ";
	
	std::string token;
	std::cin >> token;
	
	settings.insert(std::pair<std::string, std::string> ("acces_token", token));
    	Instagram::Client Example(settings);
    	std:: cout <<  Example.check_connection();
	return 0;
}
