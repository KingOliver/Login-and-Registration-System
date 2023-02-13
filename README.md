# Login-and-Registration-System
This is a basic Login and Registration System designed to work with the console on a Windows OS.

When first starting the program it will check if a file "Users.txt" is within the directory of the main.cpp file, if there is none it will create the file.

After this the user will be presented with a welcome message and the menu with the following options.

1. Login
2. Create Account
3. Exit


1. Login : This option will ask the user to enter a username and password, the script will then check the "Users.txt" file for the username, once the username is found it will check the next line to see if the stored hashed password matches the hashed password entered by the user.

If sucessful the console will return a sucess message, otherwise is will display a message stating the login attempt failed.

2. Create Account : This option like the Login will ask the user to enter a username and password, the script will then check the "Users.txt" file for the username, however if no user is found with this username it will then add to the text file the username and password.

3. Exit : This option will cause the program to close.

Additional Information : 

1. When entering the password, it will not show the entered characters in planetext, it will instead show an asterisk in place the character.
2. All passwords will be stored hashed using the username as a salt.
