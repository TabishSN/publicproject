#include <iostream>
#include "GameObject.h"

GameObject::GameObject(const string *short_name, const string *long_description, const string *keyword) :
        short_name(short_name), long_description(long_description), keyword(keyword) {
};

const string *GameObject::getName() const {
    return this->short_name;
}

const string *GameObject::getDescription() const {
    return this->long_description;
}

const string *GameObject::getKeyword() const {
    return this->keyword;
}

string GameObject::getLocation() {
    return this->roomPlacement;
}

void GameObject::setRoom(string location) {
    this->roomPlacement = location;
}
