//
// Created by DrMark on 10/2/2017.
//
#include <iostream>
#include "Room.h"
#include "State.h"
#include "wordwrap.h"

/**
 * Stores a static list of all rooms.
 */
std::list<Room*> Room::rooms;
std::list<GameObject *> Room::roomItems;

/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string* _name, const string *_desc) :
        name(_name), description(_desc), north(nullptr) {};

/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.remove(this);
}

/**
 * Prints the description of a room (the name and long description)
 */
void Room::describe() const {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();

    if (!objects.empty()) {
        std::cout << "The room contains: " << std::endl;
        for (auto object : objects) {
            std::cout << *object->getName() << std::endl;
        }
    }
}

/**
 * Statically creates a room and then adds it to the global list.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

/**
 * Adds an existing room to the static list.
 * @param room Pointer to the room to add.
 * @return
 */
void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}

/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
Room* Room::getNorth() const {
    return this->north;

}
Room* Room::getSouth() const {
    return this->south;

}
Room* Room::getEast() const {
    return this->east;

}
Room* Room::getWest() const {
    return this->west;

}



/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */
void Room::setNorth(Room* _north) {
    this->north = _north;
}


void Room::setSouth(Room* _south) {
    this-> south = _south;
}

void Room::setEast(Room* _east) {
    this->east = _east;
}

void Room::setWest(Room* _west) {
    this->west = _west;
}


const string *Room::getName() const {
    return this->name;
}

void Room::addInventoryItem(GameObject *object) {
    objects.push_back(object);
    roomItems.push_back(object);
}

void Room::getItem(GameObject *object) {
    objects.push_back(object);
}

void Room::setInventoryLocation() {
    string location;
    for (auto room : rooms) {
        if (room->objects.empty()) continue;
        location = *room->getName();
        for (auto object1 : room->objects) {
            object1->setRoom(location);
            const string oName = *object1->getName();
            for (auto obj : roomItems) {
                if (!(*obj->getName() == oName)) continue;
                obj->setRoom(location);
            }
        }
    }
    if (State::inventory.empty()) return;
    for (auto object : State::inventory) {
        object->setRoom("Inventory");
    }

}
Room *Room::findRoom(string name) {
    for (auto room : rooms) {
        if (name == *room->getName()) {
            return room;
        }
    }
}