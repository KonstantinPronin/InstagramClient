#include <client.hpp>
#include "catch.hpp"

SCENARIO("Connection to instagram server")
{
    GIVEN("Invalid token")
    {
        std::map <std::string, std::string> settings;
        std::string token ("aksjvbklanv");
	settings.insert(std::pair<std::string, std::string>("access_token", token));
	Instagram::Client example(settings);        

	WHEN("Trying to connect")
        {
            THEN("check_connection() return false")
            {
                REQUIRE(example.check_connection() == false);
            }
        }
    }

    GIVEN("Valid token")
    {
        std::map <std::string, std::string> settings;
        std::string token ("4081368943.6fd93ec.ca5f3257823f4a38a8a018b1596a7688");
	settings.insert(std::pair<std::string, std::string>("access_token", token));
	Instagram::Client example(settings);        

        WHEN("Trying to connect")
        {
            THEN("check_connection() must return true")
            {
                REQUIRE(example.check_connection() == true);
            }
        }
    }
}
