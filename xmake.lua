add_repositories("private-xrepo https://github.com/KatsFerDays/private-xrepo.git")
add_requires("librbxuserinfo")
add_rules("mode.release", "mode.debug")
set_languages("c++20")

target("RobloxUserInfo")
    set_kind("binary")
    add_files("src/main.cpp")
    add_packages("librbxuserinfo")