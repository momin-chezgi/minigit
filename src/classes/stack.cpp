

template <typename T>
class StackNode{
    
    
};

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value, Node* nxt = nullptr) :
        data(value), next(nxt) {}
    };

    Node* head;
    int count = 0;
public:
    void push(T newData) {
        newNode = Node(newData, head)
        head = *newNode
    }
};