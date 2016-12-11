#include <client.hpp>

int main() {
	try{
		std::map <std::string, std::string> settings;

		std::cout << "Click on the link to get access_token " << std::endl
		<< "https://api.instagram.com/oauth/authorize/?client_id=6fd93ecd973849eabbdb6cba7925d1d1&redirect_uri=https://localhost&response_type=token"
		<< std::endl << "Enter your access_token: ";

		std::string token;
		if (!(std::cin >> token)) throw std::logic_error("wrong format of access_token");
	
		settings.insert(std::pair<std::string, std::string>("access_token", token));
		
        	Instagram::Client example(settings);
		std::cout << "Result of connection: "  << example.check_connection() << std::endl;
        	std::cout << "Most popular photo: " << example.get_most_popular_photo() << std::endl;
		
        	std::vector<std::string> v{ "avram", "nikol", "micki", "zlatan", "citrus", "cipher" };
		for (size_t i = 0; i < 6; i++) {
			example.push_followers_cause_my_program_doesnt_work(v[i], i);
		}
		
		

		while (true) {
			std::cin.ignore();
			std::cout << "> ";
			std::string command;
			if(!std::getline(std::cin, command)) break;
			std::cout << std::endl;

			if (command == "./get_followers") example.threads_run(false);
			else if (command == "./get_followers -v") example.threads_run(true);
			else if (command == "./q") break;
			else std::cout << "Wrong command, try again.\n";

		}

	}
	catch (std::logic_error& e) {
		std::cout << std::endl << e.what();
	}

	return 0;
}
