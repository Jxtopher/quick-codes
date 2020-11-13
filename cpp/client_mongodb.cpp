/// 
/// @file main.cpp
/// @author Jxtopher
/// @brief jsoncpp + mongodb
/// @version 0.1
/// @date 2019-08-23
/// 
/// @compilation g++ client_mongodb.cpp -pthread -lmongoclient  -lboost_filesystem -lboost_program_options -lboost_system -ljsoncpp
/// 
///
#include <cstdlib>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <mongo/client/dbclient.h>

std::string jsonAsString(const Json::Value &json) {
    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "";
    return Json::writeString(builder, json);
}

int main() {
    try {
        // init
        mongo::client::initialize();

        // Connexion
        mongo::DBClientConnection c;
        c.connect("localhost");
        std::cout << "connected ok" << std::endl;

        // insert native
        mongo::BSONObjBuilder b;
        b.append("name", "Joe");
        b.append("age", 33);
        mongo::BSONObj p = b.obj();

        c.insert("tutorial.persons", p);

        // insert with jsoncpp
        Json::Value personne;
        personne["name"] = "Pierre";
        personne["age"] = 42;

        // doc https://api.mongodb.com/cplusplus/1.5.4/namespacemongo.html#a254c45b7b109b95b5e4a47ec7885d4cd
        mongo::BSONObj bson = mongo::fromjson(jsonAsString(personne));

        c.insert("tutorial.persons", bson);
        
    } catch (const mongo::DBException &e) {
        std::cout << "caught " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
