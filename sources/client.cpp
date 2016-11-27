#include <client.hpp>


namespace Instagram {

	//using json = nlohmann::json;
	std::vector<Follower> followers_;
	std::mutex client_mutex;

	//auto Client::check_connection() -> bool {
	//	
	//	std::string json_data;
	//	CURL* EasyCurl = curl_easy_init();

	//	if (!EasyCurl) throw std::logic_error(" sth wrong with easy init ");
	//	
	//	curl_easy_setopt(EasyCurl, CURLOPT_URL, "https://api.instagram.com/v1/users/self/?access_token=");
	//	curl_easy_setopt(EasyCurl, CURLOPT_POSTFIELDS, settings_["access_token"]);
	//	curl_easy_setopt(EasyCurl, CURLOPT_WRITEFUNCTION, CallbackFunction);
	//	curl_easy_setopt(EasyCurl, CURLOPT_WRITEDATA, &json_data);
	//
	//	auto perform_result = curl_easy_perform(EasyCurl);
	//	
	//	if (perform_result == CURLE_OK && !json_data.empty()) {

	//		json user_inf = json::parse(json_data);
	//		curl_easy_cleanup(EasyCurl);

	//		if (user_inf["meta"]["code"] == "200")
	//			return true;
	//		else return false;
	//	}

	//	curl_easy_cleanup(EasyCurl);
	//	return false;
	//}



	//auto Client::get_most_popular_photo() -> std::string {
	//	std::string json_data;
	//	CURL* EasyCurl = curl_easy_init();

	//	curl_easy_setopt(EasyCurl, CURLOPT_URL, "https://api.instagram.com/v1/users/self/follows?access_token=");
	//	curl_easy_setopt(EasyCurl, CURLOPT_POSTFIELDS, settings_["access_token"]);
	//	curl_easy_setopt(EasyCurl, CURLOPT_WRITEFUNCTION, Client::CallbackFunction);
	//	curl_easy_setopt(EasyCurl, CURLOPT_WRITEDATA, &json_data);

	//	auto perform_result = curl_easy_perform(EasyCurl);

	//	if (perform_result == CURLE_OK && json_data != "") {
	//		json link_to_photo = (json::parse(json_data))["data"]["link"];

	//		curl_easy_cleanup(EasyCurl);

	//		return link_to_photo;
	//	}
	//	else {
	//		curl_easy_cleanup(EasyCurl);
	//		return "Error";
	//	}
	//}

	//auto Client::CallbackFunction(char* ptr, size_t size, size_t nmemb, char* userdata) -> size_t {
	//	size_t realsize = size * nmemb;
	//	
	//	((std::string*) userdata) -> append(ptr, 0, realsize);

	//	return realsize;
	//}

	auto Client::push_followers_cause_my_program_doesnt_work(const std::string& name, const size_t& n) -> void {
		followers_.push_back(Follower(name, n));
	}
	

	auto Client::print_followers(const bool& flag, size_t i) -> void{
		
		std::unique_lock<std::mutex> m_lock(client_mutex);
		
		if (flag) {
			std::time_t start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::cout << "Thread_ID: " << std::this_thread::get_id() << std::endl << "Start time: " << ctime(&start_time);
		}

		followers_[i].PrintMe();
		
		if (flag) {
			std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::cout << "End time: " << ctime(&end_time) << std::endl;
		}
	}

	
	auto Client::threads_run(const bool& flag) -> void {
		
		if (followers_.empty()) throw std::logic_error("There is no followers");
		const int hardware_threads = std::thread::hardware_concurrency() - 1;

		std::cout << "Enter number of threads: ";
		int n;
		if (!(std::cin >> n)) return;
		
		if (n > followers_.size())
			n = followers_.size();

		if (n < 1) throw std::logic_error("Number must be more than 0");

		const size_t num_of_threads = (std::min)(hardware_threads != 0 ? hardware_threads : 1, n);

		std::vector<std::thread> threads(num_of_threads);
		size_t follower_index = 0;

		while (follower_index < followers_.size() - 1){

			for (size_t i = 0; i < num_of_threads; follower_index++, i++) {
				if (follower_index >= followers_.size()) break;
				threads[i] = std::thread(print_followers, flag, follower_index);
			}

			std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
		}
		
	}
}
