using namespace std;
#include <iostream>

template <typename T>
class LinkedList{
    public:
    struct Node{
        T data;
        Node* prev = nullptr;
        Node* next = nullptr;
        Node(T value){
            this->data = value;
            this->prev = nullptr;
            this->next = nullptr;
        }
    };
    private:
    Node* head;
    Node* tail;
    unsigned int count;
    public:
    LinkedList(){
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    Node* GetHead(){
        return head;
    }
    const Node* GetHead() const{
        return head;
    }
    Node* GetTail(){
        return tail;
    }
    const Node* GetTail() const{
        return tail;
    }
    unsigned int GetCount() const{
        return count;
    }
    LinkedList(const LinkedList<T>& list){
        this->head = nullptr;
        this->tail = nullptr;
        count = 0; // initialize head, tail and count first.
        Node* listNode = list.head; //access "other" head.
        while(listNode != nullptr){ 
          AddTail(listNode->data); 
          listNode = listNode->next;
        }
    }
        LinkedList& operator=(const LinkedList<T>& list){
        if(this == &list){
          return *this;
        }
        del();
        this->head = nullptr;
        this->tail = nullptr;
        count = 0;
        Node* listNode = list.head;
        while(listNode != nullptr){
          AddTail(listNode->data);
          listNode = listNode->next;
        }
        return *this;
    }
    void del(){
        Node* temp = head; // access the head. 
        while (temp != nullptr) {
            Node* next = temp->next; // store temp into next. why?
        // when deleting temp, the memory that temp points to is freed. so you cant do temp = temp->next bc the stuff in temp would be deleted.
            count--;
            delete temp;
            temp = next;
        }
        head = nullptr; // then make them equal to null ptr (good practice)
        tail = nullptr; 
    }
    ~LinkedList(){
      del();
    }
    void AddHead(const T& value){
        if (head == nullptr){
            head = new Node(value);
            head->next = nullptr;
            head->prev = nullptr;
            tail = head;            
            count++;
            return;
        }
        else{
            Node* newNode = new Node(value);
            newNode->next = head;
            newNode->prev = nullptr;
            head->prev = newNode;
            head = newNode;
        }
        count++;
        return;
    }
    void AddTail(const T& value){
        if (head == nullptr) { // If the list is empty
            AddHead(value);
            return;
        } 
        else{
            Node* newNode = new Node(value);
            newNode->next = nullptr;
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
        return;
    }
    void AddNodesHead(const T* ArrPtr, unsigned int count){
        for(int i = (count - 1); i > -1; i--){
            AddHead(ArrPtr[i]);
        }
    } 
    void AddNodesTail(const T* ArrPtr, unsigned int count){
        for(int i = 0; i < count; i++){
            AddTail(ArrPtr[i]);
        }
    }
    void PrintForward() const{
        Node* currentNode = head; // create a new pointer to be your head. this is how youll access the head. 
        while(currentNode != nullptr){
            cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }
    }
    void PrintReverse() const{
        Node* currentNode = tail;
        while(currentNode != nullptr){
            cout << currentNode->data << endl;
            currentNode = currentNode->prev;
        }
    }    
    Node* Find(const T& value) const{
        Node* currentNode = head;
        while(currentNode != nullptr){ // if you do currentNode->next, it wont test the tail. 
          if(currentNode->data == value){
              return currentNode;
          }
          currentNode = currentNode->next;
        }
        return nullptr;
    }
    void FindAll(vector<Node*>& outData, const T& value) const{
        Node* currentNode = head;
        while(currentNode != nullptr){
          if(currentNode->data == value){
              outData.push_back(currentNode);
          }
          currentNode = currentNode->next;
        }
    }
    Node* FindAt(int index) const{
        if((index < 0 || index >= count)){
            //conditinal: the valid indices are either 0 to count -1. 
          throw out_of_range("Index is out of range");
        }
        Node* currentNode = head;
        for(int i = 0; i < index; i++){
          currentNode = currentNode->next;
        }
        return currentNode;
    }

    T& operator[](unsigned int index){
      Node* helddata = FindAt(index);
      return helddata->data;
    }
    const T&  operator[](unsigned int index) const{
      Node* helddata = FindAt(index);
      return helddata->data;
    }

    bool operator==(const LinkedList<T>& list) const{
      Node* currentNode = this->head;
      Node* otherNode = list.head;
      while (currentNode != nullptr && otherNode != nullptr) {
        if (currentNode->data != otherNode->data) {
            return false;
        }
        currentNode = currentNode->next;
        otherNode = otherNode->next;
      }
      return currentNode == nullptr && otherNode == nullptr; // && and || are bools! dont forget.
    }

    void InsertAfter(Node* node, const T& value){
      if(head == nullptr){ // edge case: nothing in the list! 
        AddHead(value);
        return;
      }
      Node* newNode = new Node(value); // create a new node
      newNode->prev = node;
      newNode->next = node->next; // 2. change the next and prev of the new node
      if(node->next != nullptr){
        node->next->prev = newNode; // 3. now change the surrounding nodes! 
      }else{
        tail = newNode; // this is to make sure that the given node isnt the tail. if it IS the tail, the new node is your new tail.
      }
      node->next = newNode; // 4. another modification of the surrounding node - continuation of step 3
      count++; // add to count ofc. 
    }

    void InsertBefore(Node* node, const T& value){
      if(head == nullptr){
        AddHead(value);
        return;
      }
      if(node->prev = nullptr){
        AddHead(value);
        return;
      }
      Node* newNode = new Node(value);

      newNode->next = node;
      newNode->prev = node->prev;

      node->prev = newNode;
      node->prev->next = newNode;
      count++;
    }

    void InsertAt(const T& value, unsigned int index) {
      if(head == nullptr){
        AddHead(value);
        return;
      }

      Node* newNode = new Node(value);
      Node* currentNode = head;
      for(int i = 0; i < index; i++){
        currentNode = currentNode->next;
      }
      newNode->prev = currentNode;
      newNode->next = currentNode->next;
      currentNode->next = newNode;
      currentNode->next->prev = newNode;
    }
    
    bool RemoveHead(){
      if(head == nullptr){ // if list is empty
        return false;
      }
      if (head == tail){ // if one element in the list
        delete head;
        head = nullptr;
        tail = nullptr;
        count--;
        return true;
      }
      Node* newHead = head->next; // now this part is ez. 
      delete head; // delete head goes after you dont need to access any part of that value anymore. 
      newHead->prev = nullptr;
      head = newHead;
      count--;
      return true;
    }

    bool RemoveTail(){
      if(head == nullptr){
        return false;
      }
      if (head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
        count--;
        return true;
      }
      Node* newTail = tail->prev;
      delete tail;
      newTail->next = nullptr;
      tail = newTail;
      count--;
      return true;
    }

    unsigned int Remove(const T& value){
      unsigned int instances = 0;
      Node* finder = Find(value);
      while(finder != nullptr){
        if(finder == head){ // else if statements SUPER useful. check if the given value is teh head, tail, else, just vibe. 
          RemoveHead();
        } else if(finder == tail){
          RemoveTail();
        } else {
        finder->prev->next = finder->next;
        finder->next->prev = finder->prev;
        delete finder;
        count--;
        }
        instances++;
        finder = Find(value);
      }
      return instances;
    }

    bool RemoveAt(int index){
      if(head == nullptr){
        return false;
      }
      try{
        Node* finder = FindAt(index);
        if(finder == head){
          RemoveHead();
          return true;  
        } else if(finder == tail){
          RemoveTail();
          return true;
        } else {
          finder->prev->next = finder->next;
          finder->next->prev = finder->prev;
          delete finder;
          count--;
          return true;
        }
      } catch (out_of_range& e){ // this is genuinely so goated im crying bro. 
        return false;
      }

    }

    void Clear(){
      del(); 
    }

};
