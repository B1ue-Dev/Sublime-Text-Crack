#include <Windows.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void clean() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool IsElevated() {
    bool isElevated = false;
    HANDLE hToken = nullptr;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION
        elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);

        if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &cbSize)) {
            isElevated = elevation.TokenIsElevated;
        }
    }

    if (hToken) {
        CloseHandle(hToken);
    }

    return isElevated;
}

void msgEnd() {
    std::cout << "\nPaying $99 for a license is stupid!\n" << std::endl;
    system("timeout /t 5");
    clean();
    std::cout << "Thank you for using. Made by @b1uedev" << std::endl;
    system("pause");
    exit(0);
}

/// Checks if sublime_text.exe is in the directory.
bool sublimeTextInDir(const std::string& sublime_path) {
    std::fstream file(sublime_path, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    return true;
}

void sublimePatch(const std::string& version, const std::string& sublime_path) {
    std::fstream file(sublime_path, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error in opening sublime_text.exe\nMake sure that you have permission, and the path is correct or Sublime Text is closed."
                  << std::endl;
        system("pause");
        exit(1);
    }

    struct OffsetData {
        unsigned long offset;
        std::vector<unsigned char> original_bytes;
        std::vector<unsigned char> modified_bytes;
    };

    std::vector<OffsetData> offsets;
    if (version == "4126") {
        offsets = {
            {0x000A7214, {0x55, 0x41, 0x57, 0x41}, {0x48, 0x31, 0xC0, 0xC3}},
            {0x000A8D53, {0x55, 0x56, 0x57, 0x48, 0x83, 0xEC, 0x30}, {0x48, 0x31, 0xC0, 0x48, 0xFF, 0xC0, 0xC3}},
            {0x000A6F0F, {0x55, 0x56, 0x57, 0x48}, {0x48, 0x31, 0xC0, 0xC3}},
            {0x0000711A, {0xE8, 0xE1, 0x36, 0x20, 0x00}, {0x90, 0x90, 0x90, 0x90, 0x90}},
            {0x00007133, {0xE8, 0xC8, 0x36, 0x20, 0x00}, {0x90, 0x90, 0x90, 0x90, 0x90}},
        };
    } else if (version == "4143") {
        offsets = {
            {0x000A9864, {0x55, 0x41, 0x57, 0x41}, {0x48, 0x31, 0xC0, 0xC3}},
            {0x000AB682, {0x55, 0x56, 0x57, 0x48, 0x83, 0xEC, 0x30}, {0x48, 0x31, 0xC0, 0x48, 0xFF, 0xC0, 0xC3}},
            {0x000A940F, {0x55, 0x56, 0x57, 0x48}, {0x48, 0x31, 0xC0, 0xC3}},
            {0x000071FE, {0xE8, 0x71, 0x8B, 0x20, 0x00}, {0x90, 0x90, 0x90, 0x90, 0x90}},
            {0x00007217, {0xE8, 0x58, 0x8B, 0x20, 0x00}, {0x90, 0x90, 0x90, 0x90, 0x90}},
        };
    } else if (version == "4152") {
        offsets = {
            {0x000A8D78, {0x55, 0x41, 0x57, 0x41}, {0x48, 0x31, 0xC0, 0xC3}},
            {0x000AAB3E, {0x55, 0x56, 0x57, 0x48, 0x83, 0xEC, 0x30}, {0x48, 0x31, 0xC0, 0x48, 0xFF, 0xC0, 0xC3}},
            {0x000A8945, {0x55, 0x56, 0x57, 0x48}, {0x48, 0x31, 0xC0, 0xC3}},
            {0x000071D0, {0xE8, 0x17, 0xFE, 0x20, 0x00}, {0x90, 0x90, 0x90, 0x90, 0x90}},
            {0x000071E9, {0xE8, 0xFE, 0xFD, 0x20, 0x00}, {0x90, 0x90, 0x90, 0x90, 0x90}},
        };
    } else if (version == "4169") {
        offsets = {
            {0x000A0DBC, {0x55, 0x41, 0x57, 0x41}, {0x48, 0x31, 0xC0, 0xC3}},
            {0x000A2B52, {0x55, 0x56, 0x57, 0x48, 0x83, 0xEC, 0x30}, {0x48, 0x31, 0xC0, 0x48, 0xFF, 0xC0, 0xC3}},
            {0x000A0983, {0x55, 0x56, 0x57, 0x48}, {0x48, 0x31, 0xC0, 0xC3}},
            {0x0000647C, {0xE8, 0x93, 0x58, 0x20, 0x00}, {0x90, 0x90, 0x90, 0x90, 0x90}},
            {0x00006495, {0xE8, 0x7A, 0x58, 0x20, 0x00}, {0x90, 0x90, 0x90, 0x90, 0x90}},
        };
    }

    for (const auto& offset : offsets) {
        file.seekp(offset.offset, std::ios::beg);
        std::vector<unsigned char> read_bytes(offset.original_bytes.size());
        file.read(reinterpret_cast<char*>(read_bytes.data()), offset.original_bytes.size());

        if (read_bytes == offset.original_bytes) {
            std::cout << "Offset: 0x" << std::hex << offset.offset << std::endl;
            std::cout << "Original Data:";
            for (unsigned char byte : read_bytes) {
                std::cout << " " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
            }
            std::cout << std::endl;

            file.seekp(offset.offset, std::ios::beg);
            file.write(reinterpret_cast<const char*>(offset.modified_bytes.data()), offset.modified_bytes.size());

            std::cout << "Modified Data:";
            for (unsigned char byte : offset.modified_bytes) {
                std::cout << " " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
            }
            std::cout << std::endl;
        }
    }

    file.close();

    msgEnd();
}

std::string toLowercase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return lowerStr;
}

int main(int argc, char* argv[]) {
    /// Needs to run as administrator.
    if (!IsElevated()) {
        std::cout << "You have to run this program as Administrator." << std::endl;
        system("PAUSE");
        return 1;
    }

    /// Get the Sublime Text path.
    std::string sublime_path = "C:\\Program Files\\Sublime Text\\sublime_text.exe";
    if (!sublimeTextInDir(sublime_path)) {
        std::cout << "Enter your Sublime Text path: ";
        std::getline(std::cin, sublime_path);
    }

    int option = 0;
    std::cout << "Sublime Text Crack by @b1uedev.\n" << std::endl;

    std::map<std::string, std::string> versionMap = {
        {toLowercase("924C781AC4FCD21A2B46C73B07D7BC27"), "4126"},
        {toLowercase("654F4259E066F90F4964E695CF808AD0"), "4143"},
        {toLowercase("15BB398D5663B89A44372EF15F70A46F"), "4152"},
        {toLowercase("5B3C8CEA0FCA4323F0E8A994209042A8"), "4169"},
    };

    for (const auto& entry : versionMap) {
        std::string hash = entry.first;
        std::string version = entry.second;
        std::string command =
            "cmd /c certutil -hashfile \"" + sublime_path  + "\" md5 | find /i \"" + hash + "\" || exit";
        LPSTR lpCommandLine = const_cast<char*>(command.c_str());

        SECURITY_ATTRIBUTES saAttr = {sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE};
        HANDLE
        hChildStdoutRd, hChildStdoutWr;

        if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0)) {
            std::cerr << "Error creating pipe." << std::endl;
            return 1;
        }

        STARTUPINFO
        si = {sizeof(STARTUPINFO)};
        PROCESS_INFORMATION
        pi;

        si.dwFlags = STARTF_USESTDHANDLES;
        si.hStdOutput = hChildStdoutWr;
        si.hStdError = hChildStdoutWr;

        if (CreateProcess(nullptr, lpCommandLine, nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi)) {
            CloseHandle(hChildStdoutWr);

            char buf[1024];
            DWORD
            bytesRead;
            std::string result;
            while (ReadFile(hChildStdoutRd, buf, sizeof(buf), &bytesRead, nullptr) && bytesRead > 0) {
                result.append(buf, bytesRead);
            }

            CloseHandle(hChildStdoutRd);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);

            std::string processedHashString = toLowercase(result);
            processedHashString.erase(std::remove_if(processedHashString.begin(), processedHashString.end(), ::isspace),
                                      processedHashString.end());

            if (entry.first == processedHashString) {
                std::cout << "You have version " << entry.second << " installed.\nPress 1 to patch and activate.\nPress 0 to quit."
                          << std::endl;
                std::cin >> option;

                switch (option) {
                case 1:
                    sublimePatch(entry.second, sublime_path);
                case 0:
                    system("PAUSE");
                    exit(0);
                default:
                    std::cout << "Invalid input." << std::endl;
                    system("PAUSE");
                    exit(1);
                }

                return 0;
            }
        }
    }

    std::cout << "Please choose your Sublime Text version:" << std::endl;
    std::cout << "1. Sublime Text version 4126" << std::endl;
    std::cout << "2. Sublime Text version 4143" << std::endl;
    std::cout << "3. Sublime Text version 4152" << std::endl;
    std::cout << "4. Sublime Text version 4169" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "\nYour choice: ";
    std::cin >> option;

    switch (option) {
    case 1:
        sublimePatch("4126", sublime_path);
        break;
    case 2:
        sublimePatch("4143", sublime_path);
        break;
    case 3:
        sublimePatch("4152", sublime_path);
        break;
    case 4:
        sublimePatch("4169", sublime_path);
        break;
    case 0:
        system("PAUSE");
        break;
    default:
        std::cout << "Invalid input." << std::endl;
    }

    return 0;
}
