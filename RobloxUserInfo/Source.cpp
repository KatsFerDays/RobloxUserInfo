#include <iostream>
#include <conio.h>
#include <string>
#include <cpr/cpr.h>
#include <json/json.h>

int main() {
	int select;
	std::string userID;
	std::string username;
	bool usernameError = false;
	int endSelect;
	while (true) {
		std::cout << "Select input type" << std::endl << "[U]sername" << std::endl << "User[I]D" << std::endl;
		do {
			select = _getch();
		} while ((select != 'u') && (select != 'i'));
		system("cls");

		if (select == 'i') {
			std::cout << "Please enter a UserID: ";
			std::cin >> userID;
		}
		else if (select == 'u') {
			std::cout << "Please enter a Username: ";
			std::cin >> username;
			system("cls");
			cpr::Response nameToID = cpr::Get(cpr::Url{ "https://api.roblox.com/users/get-by-username?username=" + username });
			Json::Value nameToIDParse;
			std::istringstream nameToIDStr(nameToID.text);
			nameToIDStr >> nameToIDParse;
			if (nameToIDParse.isMember("errorMessage")) {
				std::cout << nameToIDParse["errorMessage"].asString() << std::endl;
				usernameError = true;
				system("pause");
				system("cls");
			}
			else if (nameToIDParse.isMember("success")) {
				if (nameToIDParse["success"].asBool() == false) {
					std::cout << "Unknown error with username to UserID API" << std::endl;
					usernameError = true;
					system("pause");
					system("cls");
				}
			}
			else {
				userID = nameToIDParse["Id"].asString();
			}
		}

		while (true) {
			if (usernameError == true) {
				break;
			}
			system("cls");
			cpr::Response userInfo = cpr::Get(cpr::Url{ "https://users.roblox.com/v1/users/" + userID });
			cpr::Response onlineStat = cpr::Get(cpr::Url{ "https://api.roblox.com/users/" + userID + "/onlinestatus/" });
			if (onlineStat.status_code == 404 || userInfo.status_code == 404) {
				std::cout << "Error 404: Page not found\nMost likely an incorrect UserID" << std::endl;
				system("pause");
				system("cls");
				break;
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
			
			std::cout << "[R]efresh" << std::endl << "[N]ew User" << std::endl << "[Q]uit" << std::endl;
			do {
				endSelect = _getch();
			} while ((endSelect != 'r') && (endSelect != 'n') && (endSelect != 'q'));
			
			if (endSelect == 'n') {
				system("cls");
				break;
			}
			else if (endSelect == 'q') {
				return 0;
			}
		}
	}
}