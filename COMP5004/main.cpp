
#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include <sstream>
#include <fstream>


using std::string;
using std::unique_ptr;

string commandBuffer;
string commandBuffer1;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto * r2 = new Room(&r2name, &r2desc);
    auto * r1 = new Room(&r1name, &r1desc);
    auto * r3 = new Room(&r3name, &r3desc);
    auto * r4 = new Room(&r4name, &r4desc);
    auto * r5 = new Room(&r5name, &r5desc);
    auto *o1 = new GameObject(&o1Name, &o1Description, &o1Keyword);
    auto *o2 = new GameObject(&o2Name, &o2Description, &o2Keyword);
    auto *o3 = new GameObject(&o3Name, &o3Description, &o3Keyword);
    auto *o4 = new GameObject(&o4Name, &o4Description, &o4Keyword);
    auto *o5 = new GameObject(&o5Name, &o5Description, &o5Keyword);

    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);

    r2->addInventoryItem(o1);
    r3->addInventoryItem(o2);
    r5->addInventoryItem(o3);
    r4->addInventoryItem(o4);
    r1->addInventoryItem(o5);

    r1->setNorth(r2);
    r2-> setSouth(r1);

    r1 -> setEast(r3);
    r1 -> setWest (r4);

    r5->setNorth(r1);
    r1-> setSouth(r5);

    r4 -> setEast(r1);
    r3 -> setWest (r1);

    r1->setWest(r5);
    r5->setEast(r1);
    r5->setNorth(r4);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
    currentState->getCurrentRoom()->setInventoryLocation();
}


/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));

        Room * selectedRoom;

        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
        /* Command to go north. */
        if ((commandBuffer.compare(0,endOfVerb,"north") == 0) || (commandBuffer.compare(0,endOfVerb,"n") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a north exit */
            selectedRoom = currentState->getCurrentRoom()->getNorth();
        }

        if ((commandBuffer.compare(0,endOfVerb,"south") == 0) || (commandBuffer.compare(0,endOfVerb,"s") == 0)) {
            commandOk = true;
            selectedRoom = currentState->getCurrentRoom()->getSouth();

        }

        if ((commandBuffer.compare(0,endOfVerb,"east") == 0) || (commandBuffer.compare(0,endOfVerb,"e") == 0)) {
            commandOk = true;
            selectedRoom = currentState->getCurrentRoom()->getEast();
        }

        if ((commandBuffer.compare(0,endOfVerb,"west") == 0) || (commandBuffer.compare(0,endOfVerb,"w") == 0)) {
            commandOk = true;
            selectedRoom = currentState->getCurrentRoom()->getWest();
        }

        if ((commandBuffer.compare(0,endOfVerb,"get") == 0)) {
            commandOk = true;
            uint8_t check = 0;
            inputCommand(&commandBuffer1);
            auto secondWord = static_cast<uint8_t>(commandBuffer1.find(' '));

            if (currentState->getCurrentRoom()->objects.empty()) {
                std::cout << "Room is empty" << std::endl;
            } else {
                for (auto object: currentState->getCurrentRoom()->objects) {
                    if (commandBuffer1.compare(0, secondWord, *object->getKeyword()) != 0) continue;
                    currentState->getItem(object);
                    currentState->getCurrentRoom()->objects.remove(object);
                    std::cout << *object->getName() + " added to inventory" << std::endl;
                    object->roomPlacement = "Inventory";
                    check++;
                    break;
                }
                if (check != 0) {}
                else {
                    std::cout << "Item is not present in the room" << std::endl;
                }
            }
            currentState->getCurrentRoom()->setInventoryLocation();
        }

        if ((commandBuffer.compare(0,endOfVerb,"drop") == 0)) {
            commandOk = true;
            uint8_t check = 0;
            inputCommand(&commandBuffer1);
            auto secondWord = static_cast<uint8_t>(commandBuffer1.find(' '));

            if (currentState->inventory.empty()) {
                std::cout << "Inventory is empty" << std::endl;
            } else {
                for (auto object: currentState->inventory) {
                    if (commandBuffer1.compare(0, secondWord, *object->getKeyword()) != 0) continue;
                    currentState->getCurrentRoom()->getItem(object);
                    currentState->inventory.remove(object);
                    std::cout << *object->getName() + " dropped." << std::endl;
                    check++;
                    break;
                }
                if (check != 0) {}
                else {
                    std::cout << "Item is not present in the room" << std::endl;
                }
            }
            currentState->getCurrentRoom()->setInventoryLocation();
        }

        if ((commandBuffer.compare(0,endOfVerb,"inventory") == 0)) {
            commandOk = true;
            currentState->announceInventory();
        }

        if ((commandBuffer.compare(0,endOfVerb,"examine") == 0)) {
            commandOk = true;
            uint8_t check = 0;
            inputCommand(&commandBuffer1);
            auto secondWord = static_cast<uint8_t>(commandBuffer1.find(' '));

            if ((currentState->inventory.empty()) && (currentState->getCurrentRoom()->objects.empty())) {
                std::cout << "There is nothing to examine." << std::endl;
            } else {
                for (auto object : currentState->inventory) {
                    if ((commandBuffer1.compare(0,secondWord, *object->getKeyword()) == 0)) {
                        std::cout << *object->getDescription() << std::endl;
                        check++;
                        break;
                    }
                }
                for (auto object : currentState->getCurrentRoom()->objects) {
                    if ((commandBuffer1.compare(0,secondWord, *object->getKeyword()) == 0)) {
                        std::cout << *object->getDescription() << std::endl;
                        check++;
                        break;
                    }
                }
                if (check == 0) {
                    std::cout << "Nothing to examine" << std::endl;
                }
            }
        }

        if ((commandBuffer.compare(0,endOfVerb,"save") == 0)) {
            commandOk = true;
            std::ofstream file("C:\\Users\\Tabish\\Desktop\\COMP5004\\Save.txt");
            file << *currentState->getCurrentRoom()->getName() << "\n";
            for (auto object : currentState->getCurrentRoom()->objects) {
                file << object->roomPlacement << "\n" << *object->getName() << "\n";
            }
            file.close();
            gameOver = true;
        }

        if ((commandBuffer.compare(0,endOfVerb,"load") == 0)) {
            commandOk = true;
            string line;
            std::ifstream file("C:\\Users\\Tabish\\Desktop\\COMP5004\\Save.txt");
            if (file.is_open()) {
                for (auto room : currentState->getCurrentRoom()->rooms) {
                    room->objects.clear();
                }
                (getline(file, line));
                for (auto room : currentState->getCurrentRoom()->rooms) {
                    if (*room->getName() == line) {
                        currentState->goTo(room);
                    }
                }
                while (getline(file, line)) {
                    string locationLine = line;
                    (getline(file, line));
                    string itemLine = line;
                    for (auto object : currentState->getCurrentRoom()->objects) {
                        if (itemLine == (*object->getName())) {
                            if (locationLine != "Inventory") {
                                Room *box = currentState->getCurrentRoom()->findRoom(locationLine);
                                box->getItem(object);
                            } else if (locationLine == "Inventory") {
                                currentState->getItem(object);
                            }
                        }
                    }
                }
                file.close();
            }
            currentState->getCurrentRoom()->setInventoryLocation();
        }

        if (selectedRoom == nullptr) {
            wrapOut(&badExit);
            wrapEndPara();
        } else {
            currentState->goTo(selectedRoom);
        }

        /* Quit command */
        if ((commandBuffer.compare(0,endOfVerb,"quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}



int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;

}