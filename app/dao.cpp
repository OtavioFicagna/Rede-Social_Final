#include <sqlite3.h>
#include <string>
#include "users.cpp"

bool initDb()
{
    sqlite3* db;
    char* messaggeError;
    int rc = sqlite3_open("db.db", &db);

    if (rc != SQLITE_OK) {
        return false;
    }

    std::string tableUser = "CREATE TABLE IF NOT EXISTS USER("
                      "EMAIL TEXT PRIMARY KEY NOT NULL,"
                      "NAME TEXT,"
                      "BIRTH_DATE TEXT NOT NULL,"
                      "PH_NUMBER TEXT,"
                      "CITY TEXT);";

    std::string tableFlw = "CREATE TABLE IF NOT EXISTS FOLLOWERS("
                      "USER_EMAIL TEXT NOT NULL,"
                      "FOLLOWER TEXT NOT NULL);";

    rc = sqlite3_exec(db, tableUser.c_str(), NULL, 0, &messaggeError);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }
    rc = sqlite3_exec(db, tableFlw.c_str(), NULL, 0, &messaggeError);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }
    sqlite3_close(db);
    return true;   
}

bool load_data(std::unordered_map<std::string, Users>& map_users)
{
    sqlite3* db;
    std::string sql_user = "SELECT email, name, birth_date, ph_number, city FROM User;";
    sqlite3_stmt* stmt;
    

    sqlite3_open("db.db", &db);

    int rc = sqlite3_prepare_v2(db, sql_user.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return false;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string birthDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string phNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string city = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        std::unordered_set<std::string> seguindo;
        std::unordered_set<std::string> seguidores;
        Users user(email, name, birthDate, phNumber, city, seguindo, seguidores);
        map_users[email] = user;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return true;
}

bool load_links(std::unordered_map<std::string, Users>& map_users)
{
    sqlite3* db;
    std::string sql_followers = "SELECT user_email, follower FROM Followers;";
    sqlite3_stmt* stmt;
    

    sqlite3_open("db.db", &db);

    int rc = sqlite3_prepare_v2(db, sql_followers.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return false;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string user_email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string follower = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        map_users[user_email].insertSeguidor(follower);
        map_users[follower].insertSeguindo(user_email);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return true;
}

bool save_user(Users user)
{
    sqlite3* db;
    char* messaggeError;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK) {
        return false;
    }
    std::string sql = "INSERT INTO User (email, name, birth_date, ph_number, city)" 
        "VALUES ('"+ user.getEmail() + "','" + user.getName() + "','"
        + user.getBirthDate() + "','" + user.getPhNumber() + "','"
        + user.getCity() + "');";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }
    sqlite3_close(db);
    return true;
}

bool delete_user(std::string email)
{
    sqlite3* db;
    char* messaggeError;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK) {
        return false;
    }
    std::string sql_user = "DELETE FROM User WHERE email = '"
        + email + "';";
    rc = sqlite3_exec(db, sql_user.c_str(), NULL, 0, &messaggeError);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }

    std::string sql_follower = "DELETE FROM Followers WHERE user_email = '"
        + email + "' OR follower = '" + email + "';";
    rc = sqlite3_exec(db, sql_follower.c_str(), NULL, 0, &messaggeError);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }
    sqlite3_close(db);
    return true;
}

bool save_follow(std::string user, std::string follower)
{
    sqlite3* db;
    char* messaggeError;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK) {
        return false;
    }
    std::string sql = "INSERT INTO Followers(user_email, follower) " 
        "VALUES('" + user + "','" + follower + "');";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }
    sqlite3_close(db);
    return true;
}

bool remove_follow(std::string user, std::string follower)
{
    sqlite3* db;
    char* messaggeError;
    int rc = sqlite3_open("db.db", &db);
    if (rc != SQLITE_OK) {
        return false;
    }
    std::string sql = "DELETE FROM Followers WHERE user_email = '"
        + user + "' AND follower = '" + follower +"';";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }
    sqlite3_close(db);
    return true;
}
