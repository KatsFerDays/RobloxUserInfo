#include <iostream>
#include <conio.h>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
	int select;
	std::string userID;
	std::string username;
	bool usernameError;
	int endSelect;
	while (true) {
		usernameError = false;
		std::cout << "Select input type" << "\n" << "[U]sername" << "\n" << "User[I]D" << "\n";
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
			json nameToIDParse = json::parse(nameToID.text);
			if (nameToIDParse.contains("errorMessage")) {
				std::cout << nameToIDParse.at("errorMessage") << "\n";
				usernameError = true;
				system("pause");
				system("cls");
			}
			else if (nameToIDParse.contains("success")) {
				if (nameToIDParse.at("success") == false) {
					std::cout << "Unknown error with username to UserID API" << "\n";
					usernameError = true;
					system("pause");
					system("cls");
				}
			}
			else {
				userID = to_string(nameToIDParse.at("Id"));
			}
		}

		while (true) {
			if (usernameError == true) {
				break;
			}
			system("cls");
			cpr::Response userInfo = cpr::Get(cpr::Url{ "https://users.roblox.com/v1/users/" + userID });
			cpr::Response onlineStat = cpr::Get(cpr::Url{ "https://api.roblox.com/users/" + userID + "/onlinestatus/" });
			if (userInfo.status_code != 200 || onlineStat.status_code != 200) {
				std::cout << "Invalid UserID" << "\n";
				system("pause");
				system("cls");
				break;
			}
			json userInfoParse = json::parse(userInfo.text);
			json onlineStatParse = json::parse(onlineStat.text);
			std::cout << "USER INFO\n---------" << "\n";
			std::cout << "UserID: " << userInfoParse.at("id") << "\n" << "Name: " << userInfoParse.at("name") << "\n" << "DisplayName: " << userInfoParse.at("displayName") << "\n" << "Description: " << userInfoParse.at("description") << "\n" << "Created: " << userInfoParse.at("created") << "\n" << "IsBanned: " << userInfoParse.at("isBanned") << "\n" << "\n";
			std::cout << "ONLINE STATUS\n-------------" << "\n";
			std::cout << "GameID: " << onlineStatParse.at("GameId") << "\n" << "PlaceID: " << onlineStatParse.at("PlaceId") << "\n" << "UniverseID: " << onlineStatParse.at("UniverseId") << "\n" << "IsOnline: " << onlineStatParse.at("IsOnline") << "\n" << "LastOnline: " << onlineStatParse.at("LastOnline") << "\n" << "LastLocation: " << onlineStatParse.at("LastLocation") << "\n" << "LocationType: " << onlineStatParse.at("LocationType") << "\n" << "PresenceType: " << onlineStatParse.at("PresenceType") << "\n" << "\n";
			
			std::cout << "[R]efresh" << "\n" << "[N]ew User" << "\n" << "[Q]uit" << "\n";
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