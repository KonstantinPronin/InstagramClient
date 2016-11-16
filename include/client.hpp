#include <string>
#include <map>

namespace Instagram{
	class Client{
	public:
		using dict_t = std::map<std::string, std::string>;
		Client(dict_t  settings) : _settings(settings){}
		auto check_connection() -> bool;	
		auto get_most_popular_photo() -> std::string;
	    	static auto CallbackFunction(char *ptr, size_t size, size_t nmemb, std::string *userdata) -> size_t;
   	private:
		dict_t _settings;
	};

}
