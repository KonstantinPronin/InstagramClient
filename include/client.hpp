#include <string>
#include <map>
#include "json.hpp"
#include <exception>
#include <algorithm>
#include <vector>
#include <thread>
#include <iostream>
#include <curl/curl.h>
#include <mutex>
#include <chrono>



namespace Instagram {

	class Follower {
		std::string nickname_;
		size_t num_of_publications_;
	public:
		Follower(std::string name, size_t num) : nickname_(name), num_of_publications_(num) {}
		void PrintMe() {
			std::cout << "Nickname: " << nickname_ << std::endl
				<< "Number of publications: " << num_of_publications_ << std::endl;
		}

	};


	class Client {
	public:
		using dict_t = std::map<std::string, std::string>;
		
		Client(dict_t  settings) : settings_(settings) {}
		~Client() { std::cout << "d_tor" << std::endl; }
		
		//auto check_connection() -> bool;
		//auto get_most_popular_photo() -> std::string;
		auto threads_run(const bool&) -> void;
		auto push_followers_cause_my_program_doesnt_work(const std::string&, const size_t&) -> void;

		static auto print_followers(bool, size_t) -> void;
		//static auto CallbackFunction(char *ptr, size_t size, size_t nmemb, char *userdata) -> size_t;
	private:
		dict_t settings_;

	};

	

}
