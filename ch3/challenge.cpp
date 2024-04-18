#include <iostream>
#include <memory>

struct SimpleNode {
  int mItem = 0;
  std::shared_ptr<SimpleNode> mNext;
};

std::shared_ptr<SimpleNode> list;

void addElement(const int value, bool add_front = false)
{
  
	// TODO: Code that appends a value to the linked list 

  //std::shared_ptr<SimpleNode> new_Node {std::shared_ptr<SimpleNode>( new SimpleNode{value})}; // OK,  comme il sagit d'une structure, l'affectation va se faire selon l'ordre dans la structure. alors Value serra attribué a mItem
  std::shared_ptr<SimpleNode> new_Node {std::shared_ptr<SimpleNode>( new SimpleNode{value, nullptr})}; // OK
  /*std::shared_ptr<SimpleNode> new_Node {std::shared_ptr<SimpleNode>( new SimpleNode{})}; 
  new_Node->mItem = value;*/

  //std::cout << "neu value = " << new_Node->mItem << " next = " << new_Node->mNext << std::endl;

  if(new_Node == nullptr){
    std::cout << "ERROR: element could not be created !" <<std::endl;
    exit(EXIT_FAILURE);
  }

  if(list == nullptr){
    list = std::shared_ptr<SimpleNode>( new SimpleNode{});
  }

  if(add_front){
    new_Node->mNext = list->mNext;
    list->mNext = new_Node;
  }
  else{
    if(list->mNext == nullptr){
      list->mNext = new_Node;
      return; // oder die folgende Anweisungen in einem else reinpacken!
    }

    std::shared_ptr<SimpleNode> current_Node {list->mNext};
    while(current_Node->mNext != nullptr){
      current_Node = current_Node->mNext;
    }
    current_Node->mNext = new_Node;
  }

}
void printList()
{
	// TODO: Print all the list items
  if(list == nullptr || list->mNext == nullptr){
    std::cout << "List ist empty!" << std::endl;
    return;
  }

  std::shared_ptr<SimpleNode> current_Node {list->mNext};
  while (current_Node != nullptr){
    std::cout << current_Node->mItem << " -> ";
    current_Node = current_Node->mNext;
  }
  std::cout << std::endl;

}

int main()
{
    addElement(12);
    addElement(22);
    addElement(342);
    addElement(145);

    printList();

    return 0;
}
