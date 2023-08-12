#include <iostream>
#include <string.h>
#include <map>
#include <sstream>

class Node
{
public:
    std::map<std::string, Node *> childNodes;
    Node *PrevNode;
    std::string name;

public:
    Node *createNode(std::string data)
    {
        Node *node = new Node();
        node->name = data;
        node->PrevNode = nullptr;
        return node;
    }

    void createChildNode(Node *parent, std::string childName)
    {
        Node *newNode = new Node();
        newNode->name = childName;
        newNode->PrevNode = parent;
        parent->childNodes[childName] = newNode;
    }

    void display(Node *node)
    {
        for (auto mp : node->childNodes)
        {
            std::cout << mp.first << "   ";
        }
        std::cout << std::endl;
    }

    void path(Node *node)
    {
        if (node == nullptr)
            return;
        path(node->PrevNode);
        std::cout << node->name << " / ";
    }

    void Tree(Node *node)
    {
        if (node->childNodes.empty())
        {
            std::cout << std::endl;
            return;
        }

        for (auto mp : node->childNodes)
        {
            std::cout << mp.first << ", ";
            Tree(mp.second);
        }
    }
};

int main()
{
    Node file_system;
    Node *root = file_system.createNode("This Pc");
    Node *current_node = root;

    std::map<std::string, int> cmdId;
    cmdId["ls"] = 1;
    cmdId["cd"] = 2;
    cmdId["help"] = 3;
    cmdId["cd.."] = 4;
    cmdId["exit"] = 5;
    cmdId["tree"] = 6;
    cmdId["md"] = 7;

    std::string cmd;

    do
    {
        std::cout << std::endl;
        file_system.path(current_node);
        std::cin >> cmd;

        std::string folder_name;

        std::istringstream iss;
        std::string folder_names;

        switch (cmdId[cmd])
        {
        case 2:
            int index;
            // std::cout << "at which folder: "; //can be un-comment

            std::cin >> folder_name;

            if (current_node->childNodes[folder_name])
                current_node = current_node->childNodes[folder_name];
            else
            {
                std::cout << "no such folder" << std::endl;
            }

            break;

        case 4:
            if (current_node->PrevNode == nullptr)
                std::cout << "you are in root node: " << current_node->name << std::endl;

            else
                current_node = current_node->PrevNode;

            break;

        case 7:

            // std::cout << "enter folder name: "; // can be un-comment

            std::cin.ignore(); // ignores '\n'
            std::getline(std::cin, folder_names);

            iss.clear(); // clear any previous data;
            iss.str(folder_names);
            while (iss >> folder_name)
            {
                file_system.createChildNode(current_node, folder_name);
            }
            std::cout << "successfully created" << std::endl;

            break;

        case 1:
            file_system.display(current_node);

            break;

        case 6:
            file_system.Tree(current_node);

            break;

        case 5:
            std::cout << "good bye! have a nice day" << std::endl;

            break;

        case 3:
            std::cout << "\nls --display all folders present in PWD." << std::endl;
            std::cout << "cd --change directory. --example cd folder_name " << std::endl;
            std::cout << "cd.. --move to previous directory." << std::endl;
            std::cout << "tree --prints all sub-directory." << std::endl;
            std::cout << "md --creates directory. --example md folder_name" << std::endl;
            std::cout << "exit --terminates the program." << std::endl;
            std::cout << "help --opens all present commands." << std::endl;

            break;

        default:
            std::cout << "invalid!" << std::endl;
        }

    } while (cmdId[cmd] != cmdId["exit"]);

    delete root;
    return 0;
}