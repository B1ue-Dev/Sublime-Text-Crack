#include <iostream>
#include <cstdio>
using namespace std;

#define _WIN64

void msg_waiting() {

    system("cls");
    cout << "Sublime Text for Windows, loading...\n" << endl;
    system("timeout /t 5 /nobreak");

    system("cls");
    cout << "Paying $99 for a license is stupid.\n" << endl;
    system("timeout /t 5");

}

void msg_end() {

    system("cls");
    cout << "Thank you for using. Made by Blue.\n" << endl;

}

void patch_sublime4126() {

    system("COPY \"C:\\Program Files\\Sublime Text\\sublime_text.exe\" ");

    char m1[] = "\x48\x31\xC0\xC3";
    char m2[] = "\x90\x90\x90\x90\x90";
    char m3[] = "\x48\x31\xC0\x48\xFF\xC0\xC3";
    char m4[] = "\xC3";

    FILE *crack = fopen("sublime_text.exe", "r+b");
    fseek(crack, 0x000A7214, SEEK_SET);
    fwrite(m1, sizeof(m1[0]), 4, crack);

    fseek( crack, 0x0000711A, SEEK_SET );
    fwrite(m2, sizeof(m2[0]), 5, crack);

    fseek( crack, 0x00007133, SEEK_SET );
    fwrite(m2, sizeof(m2[0]), 5, crack);

    fseek( crack, 0x000A8D53, SEEK_SET );
    fwrite(m3, sizeof(m3[0]), 7, crack);

    fseek( crack, 0x000A6F0F, SEEK_SET );
    fwrite(m4, sizeof(m4[0]), 1, crack);

    fseek( crack, 0x00000400, SEEK_SET );
    fwrite(m4, sizeof(m4[0]), 1, crack);
    fclose(crack);

    system("MOVE sublime_text.exe \"C:\\Program Files\\Sublime Text\" ");

    msg_waiting();
    msg_end();
    system("PAUSE");

}

void patch_sublime4134 () {

    system("COPY \"C:\\Program Files\\Sublime Text\\sublime_text.exe\" ");

    char m1[] = "\x48\x31\xC0\xC3";
    char m2[] = "\x90\x90\x90\x90\x90";
    char m3[] = "\x48\x31\xC0\x48\xFF\xC0\xC3";
    char m4[] = "\xC3";

    FILE *crack = fopen("sublime_text.exe", "r+b");
    fseek(crack, 0x000A8484, SEEK_SET);
    fwrite(m1, sizeof(m1[0]), 4, crack);

    fseek(crack, 0x0000715E, SEEK_SET);
    fwrite(m2, sizeof(m2[0]), 5, crack);

    fseek(crack, 0x00007177, SEEK_SET);
    fwrite(m2, sizeof(m2[0]), 5, crack);

    fseek(crack, 0x000AA26A, SEEK_SET);
    fwrite(m3, sizeof(m3[0]), 7, crack);

    fseek(crack, 0x000A807F, SEEK_SET);
    fwrite(m4, sizeof(m4[0]), 1, crack);

    fseek(crack, 0x00000400, SEEK_SET);
    fwrite(m4, sizeof(m4[0]), 1, crack);
    fclose(crack);

    system("MOVE sublime_text.exe \"C:\\Program Files\\Sublime Text\" ");

    msg_waiting();
    msg_end();
    system("PAUSE");

}

int main () {

    int option = 0;
    int optionsublime = 0;
    int optionmerge = 0;

    cout << "Sublime Text Crack by Blue.\n" << endl;
    cout << "Please choose your Sublime Text version.\n\n1. Sublime Text version 4126\n2. Sublime Text version 4134\n3. Exit\n";
    cout << "\nYour choice: ";
    cin >> option;

    switch (option) {
    case 1:
        patch_sublime4126();
        break;
    case 2:
        patch_sublime4134();
        break;
    case 3:
        system("PAUSE");
        break;
    default:
        cout << "Invalid input." << endl;
        break;
    }

    return 0;

}
