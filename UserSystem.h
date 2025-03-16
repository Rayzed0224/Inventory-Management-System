class UserSystem {
private:
    map<string, string> users;
    string currentUser;
    string currentRole;
    string userFile; // changed from passwordFile

public:
    UserSystem();
    bool login();
    void registerUser();
    void logout();
    void loadUsers();
    void saveUsers();
};
