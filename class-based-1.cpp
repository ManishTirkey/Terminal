#include <iostream>
#include <vector>
#include <string.h>
#include <map>

class Node
{
public:
    // std::map<Node*, std::string> childNodes;
    std::vector<Node *> childNodes;
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
        parent->childNodes.push_back(newNode);
    }

    void display(Node *node)
    {
        // std::cout<<"------display--"<<std::endl;
        // std::cout << "parentNode: " <<node->name << std::endl;
        // std::cout<<"childNodes: ";
        for (Node *e : node->childNodes)
        {
            std::cout << e->name << "    ";
        }
        std::cout<<std::endl;
    }

    void path(Node *node)
    {
        if(node == nullptr)
            return;
        path(node->PrevNode);
        std::cout<<node->name << " > ";
    }
};

int main()
{
    Node file_system;
    Node *root = file_system.createNode("This Pc");
    
    int ch;
    Node *current_node = root;

    do{
        std::cout<<std::endl;
        std::cout << "1. enter"<<std::endl;
        std::cout << "2. go back"<<std::endl;
        std::cout << "3. create folder"<<std::endl;
        std::cout << "4. Display"<<std::endl;
        std::cout << "5. exit"<<std::endl;
        file_system.path(current_node);
        std::cout<<" ";
        std::cin >> ch;

        std::string folder_name;

        std::cout<< "---------------OUTPUT----------------------"<<std::endl;
        switch(ch){
            case 1: 
                int index;
                std::cout<<"at which node: "; 
                std::cin>>index;
                try{
                    current_node = current_node->childNodes.at(index-1);
                }
                catch (const std::out_of_range& e)
                {
                    std::cout<<"no folder at: "<<index<<std::endl;
                }

                break;

            case 2: 
                if (current_node->PrevNode == nullptr)
                    std::cout<<"you are in root node: "<<current_node->name<<std::endl;
                
                else
                    current_node = current_node->PrevNode;

                break;

            case 3:
                
                std::cout<< "enter folder name: ";
                std::cin>>folder_name;
                file_system.createChildNode(current_node, folder_name);

                break;

            case 4:
                file_system.display(current_node);
                break;

            case 5:
                std::cout<<"good bye! have a nice day"<<std::endl;

                break;

            default: std::cout<<"invalid!"<<std::endl;
        }

        
        std::cout<< "---------------OUTPUT--END--------------------"<<std::endl;

    }while (ch != 5);


    delete current_node;
    delete root;
    return 0;
}