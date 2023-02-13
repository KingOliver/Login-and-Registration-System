#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <fstream>


void ShowMenu();
int GetUserIntInput();
void Login();
void CreateAccount();
std::string GetUsername();
unsigned int GetPassword(std::string username);
bool AttemptLogin(std::string username, unsigned int password);
bool AttemptCreateAccount(std::string username, unsigned int password);
void CheckforFile();
bool CheckforUser(std::string username);

int main(){

    std::cout << "Welcome to the login terminal" << std::endl;

    //CheckforFile();
    bool loop = true;

    //Loop the menu and user input until exit is selected
    while (loop){
        ShowMenu();
        int option = GetUserIntInput();
        if (option > 0 && option < 4){
            switch (option){

                case 0 : {
                    break;
                }
                case 1 : {
                    Login();
                    break;
                }
                case 2 : {
                    CreateAccount();
                    break;
                }
                case 3 : {
                    loop = false;
                    break;
                }
            }
        } else {
            std::cout << "Invalid Input, please enter option again." << std::endl;
        }
    }
    
    return 0;
}

void ShowMenu(){
    std::cout << "Please select from the options below" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Create Account" << std::endl;
    std::cout << "3. Exit" << std::endl;
    return;
}

void CheckforFile(){
    //Check if Users.txt file exists, if not then create the file
    FILE *file;
    if (file = fopen("Users.txt", "r")) {
        fclose(file);
        //std::cout << "file exists" << std::endl;
    } else {
        //std::cout << "file doesn't exist, creating file" << std::endl;
        std::ofstream { "Users.txt"};
    }

    return;
}


int GetUserIntInput(){
    std::string option;
    std::getline(std::cin, option);
    for (int i = 0; i < option.size(); i++){
        if (!isdigit(option[i])){
            std::cout << "Invalid Input, not an integer!" << std::endl;
            return 0;
        }
        //convert string to int
        int iOption = stoi(option);
        return iOption;
    }
    return 0;
}

void Login(){
    std::cout << "Please enter your username and password to login." << std::endl;
    std::string username = GetUsername();
    unsigned int password = GetPassword(username);
    //Check if file of usernames and passwords exist
    std::cout << "Password = " << password << std::endl;
    if (AttemptLogin(username, password)){
        std::cout << "Login Sucessful!" << std::endl;
    } else {
        std::cout << "Login Failed!" << std::endl;
    }
    return;
}

std::string GetUsername(){
    std::string username;
    std::cout << "Username : ";
    std::getline(std::cin, username);
    return username;
}

unsigned int GetPassword(std::string username){

    #define MAX_LENGHT     128
    #define ENTER           13
    #define BACKSPACE        8

    char ch;
    char password[MAX_LENGHT];
    int pos=0;

    std::cout << "Password : ";

    while(true)
     { 
       ch=getch();
       if(pos>=MAX_LENGHT) {std::cout<<'\a'; continue;} /* beep if password is too long */
       
       if(ch==ENTER) break;  /* User have pressed ENTER*/
       
       else if(ch==BACKSPACE)  /* BACKSPACE was pressed*/
         {
           std::cout <<"\b \b";   
           password[--pos]='\0';
         }
       else/* A..Z a...z  BUG: I forgot what... */
         {
           std::cout <<"*";
           password[pos++]=ch;
           password[pos]='\0';
         }
       if(pos<=0) pos=0;
     }

    unsigned int pass_hash = std::hash<std::string>{}(password + username);
    std::cout << std::endl;
    return pass_hash;
}

void CreateAccount(){
    std::cout << "Please enter your username and password to create a new account." << std::endl;
    std::string username = GetUsername();
    unsigned int password = GetPassword(username);
    
    if (AttemptCreateAccount(username, password)){
        std::cout << "Account Created Sucessful!" << std::endl;
    } else {
        std::cout << "Account Creation Failed!" << std::endl;
    }
    return;

}

bool AttemptLogin(std::string username, unsigned int password){
    //Make object of Users.txt file
    std::ifstream users ("Users.txt");
    std::string line;
    bool checkPass = false;
    //Check if file exists
    if (users.is_open()){
        while (std::getline(users,line)){
            //Check if Username is in the file
            if (line.find(username) != std::string::npos){
                checkPass = true;
                //If Username was found, check next line if password matches
            } else if (checkPass){
                
                if (stoul(line) == password){
                    return true;
                    break;
                } else {
                    return false;
                    break;
                }
            }
        }
        users.close();
    } else {
        std::cout << "File not found!" << std::endl;
    }
    return false;
}

bool AttemptCreateAccount(std::string username, unsigned int password){
    //Check if user already Exists
    
    if (CheckforUser(username) == false){
        std::ofstream users ("Users.txt", std::ios::app);
        if (users.is_open()){
            users << username << std::endl;
            users << password << std::endl;
            users.close();
            return true;
        }
    }
    return false;
}

bool CheckforUser(std::string username){
    std::ifstream users ("Users.txt");
    std::string line;
    std::cout << "checking For User1" << std::endl;
    if (users.is_open()){
        while (std::getline(users,line)){
            std::cout << "checking For User" << std::endl;
            //Check if Username is in the file
            if (line.find(username) != std::string::npos){
                std::cout << "User Found" << std::endl;
                return true;
            }
            
        }
        users.close();
    }
    return false;
}