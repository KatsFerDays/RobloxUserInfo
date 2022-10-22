add_requires("cpr", "nlohmann_json")

target("RobloxUserInfo")
    set_kind("binary")
    add_files("src/main.cpp")
    add_packages("cpr", "nlohmann_json")