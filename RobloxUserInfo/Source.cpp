#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <json/json.h>

int main() {
	std::string userID;
	std::cout << "Please enter a UserID: ";
	std::cin >> userID;
	system("cls");
	cpr::Response userInfo = cpr::Get(cpr::Url{ "https://users.roblox.com/v1/users/" + userID });
	cpr::Response onlineStat = cpr::Get(cpr::Url{ "https://api.roblox.com/users/" + userID + "/onlinestatus/" });
	if (onlineStat.status_code == 404 || userInfo.status_code == 404) {
		std::cout << "Error 404: Page not found\nMost likely an incorrect UserID" << std::endl;
		system("pause");
		return 0;
	}
	Json::Value userInfoParse;
	std::istringstream userInfoStr(userInfo.text);
	userInfoStr >> userInfoParse;
	Json::Value onlineStatParse;
	std::istringstream onlineStatStr(onlineStat.text);
	onlineStatStr >> onlineStatParse;
	std::cout << "USER INFO\n---------" << std::endl;
	std::cout << "UserID: " + userInfoParse["id"].asString() << std::endl << "Name: " + userInfoParse["name"].asString() << std::endl << "DisplayName: " + userInfoParse["displayName"].asString() << std::endl << "Description: " + userInfoParse["description"].asString() << std::endl << "Created: " + userInfoParse["created"].asString() << std::endl << "IsBanned: " + userInfoParse["isBanned"].asString() << std::endl << std::endl;
	std::cout << "ONLINE STATUS\n-------------" << std::endl;
	std::cout << "GameID: " + onlineStatParse["GameID"].asString() << std::endl << "PlaceID: " + onlineStatParse["PlaceID"].asString() << std::endl << "UniverseID: " + onlineStatParse["UniverseID"].asString() << std::endl << "IsOnline: " + onlineStatParse["IsOnline"].asString() << std::endl << "LastOnline: " + onlineStatParse["LastOnline"].asString() << std::endl << "LastLocation: " + onlineStatParse["LastLocation"].asString() << std::endl << "LocationType: " + onlineStatParse["LocationType"].asString() << std::endl << "PresenceType: " + onlineStatParse["PresenceType"].asString() << std::endl << std::endl;
	system("pause");
	return 0;
}