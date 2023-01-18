#ifndef ASSIGNMENT_GAMEOBJECT_H
#define ASSIGNMENT_GAMEOBJECT_H

#include <string>
#include <forward_list>
#include <list>

using std::string;

class GameObject {
public:
    const string *short_name;
    const string *long_description;
    const string *keyword;
    string roomPlacement;

    GameObject(const string *short_name, const string *long_description, const string *keyword);

    const string *getName() const;

    const string *getDescription() const;

    const string *getKeyword() const;

    string getLocation();

    void setRoom(string location);
};


#endif //ASSIGNMENT_GAMEOBJECT_H