#include <iostream>
#include <conio.h>
#include <string>
#include <libRbxUserInfo.hpp>

int main() {
	std::cout.setf(std::ios::boolalpha);
	RbxUserInfo::User user;

	while (true) {
		system("cls");

		std::cout << "Select input type" << "\n" << "[U]sername" << "\n" << "User[I]D" << "\n";

		int mainSelect;
		do {
			mainSelect = _getch();
		} while ((mainSelect != 'u') && (mainSelect != 'i'));
		system("cls");

		if (mainSelect == 'i') {
			std::cout << "Please enter a UserID: ";
			int userID = -1;
			std::string in;
			std::cin >> in;
			try {
				userID = std::stoi(in);
			}
			catch (std::exception& e) {
				std::cout << "Invalid UserID\n";
				system("pause");
				continue;
			}
			user = RbxUserInfo::GetInfoByID(userID);
		}
		else if (mainSelect == 'u') {
			std::cout << "Please enter a Username: ";
			std::string username = "";
			std::cin >> username;
			user = RbxUserInfo::GetInfoByUsername(username);
		}

		while (true) {
			if (user.userID == -1) {
				std::cout << "Failed to get user info. Please confirm the username or UserID is valid!\n";
				system("pause");
				break;
			}
			system("cls");

			std::cout << "USER INFO\n---------" << "\n";
			std::cout << "UserID: " << user.userID << "\n" << "Username: " << user.username << "\n" << "Display Name: " << user.displayName << "\n" << "Description: " << user.description << "\n" << "Creation Date: " << user.creationDate << "\n" << "Banned: " << user.banned << "\n" << "\n";
			std::cout << "ONLINE STATUS\n-------------" << "\n";
			std::cout << "GameID: " << user.gameID << "\n" << "PlaceID: " << user.placeID << "\n" << "UniverseID: " << user.universeID << "\n" << "Online: " << user.isOnline << "\n" << "Last Online: " << user.lastOnline << "\n" << "Last Location: " << user.lastLocation << "\n" << "Location Type: " << user.locationType << "\n" << "Presence Type: " << user.presenceType << "\n" << "\n";
			
			std::cout << "[R]efresh" << "\n" << "[N]ew User" << "\n" << "[Q]uit" << "\n";
			int endSelect;
			do {
				endSelect = _getch();
			} while ((endSelect != 'r') && (endSelect != 'n') && (endSelect != 'q'));
			
			if (endSelect == 'r') {user = RbxUserInfo::GetInfoByID(user.userID);}
			else if (endSelect == 'n') {break;}
			else if (endSelect == 'q') {return 0;}
		}
	}
}