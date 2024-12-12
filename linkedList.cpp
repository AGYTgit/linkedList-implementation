#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
    int value;
    Node* next;

    Node(int _value) : value(_value), next(nullptr) {}
};

class LinkedList {
public:
    Node* head = nullptr;
  
    void insert(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void deleteFirstNode() {
        if (!head) return;

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    bool search(int value) {
        Node* temp = head;
        while (temp) {
            if (temp->value == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void printList() {
        Node* temp = head;
        while (temp) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void reverse() {
        if (!head || !head->next) return;

        Node* temp = head;
        head = nullptr;
        while (temp) {
            insert(temp->value);
			temp = temp->next;
        }
    }

	int getLength() {
        int length = 0;
        Node* temp = head;
        while (temp) {
            length++;
            temp = temp->next;
        }
        return length;
    }

	void createCycle(int pos) {
        Node* temp = head;
        Node* cycleStartNode = nullptr;
        int count = 1;
        while (temp->next) {
            if (count == pos) {
                cycleStartNode = temp;
            }
            temp = temp->next;
            count++;
        }
        if (cycleStartNode) {
            temp->next = cycleStartNode;
        }
    }

    bool hasCycle() {
        if (!head) return false;

        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return true;
            }
        }
        return false;
    }

	void removeCycle() {
		if (!head || !head->next) return;

		Node* slow = head;
		Node* fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) {
				break;
			}
		}

		if (slow != fast) return;

		slow = head;
		if (slow == fast) {
			while (fast->next != slow) {
				fast = fast->next;
			}
		} else {
			while (slow->next != fast->next) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		fast->next = nullptr;
	}

	static LinkedList mergeSorted(LinkedList l1, LinkedList l2) {
		LinkedList list;
		Node* n1 = l1.head;
		Node* n2 = l2.head;
		while (n1 && n2) {
			if (n1->value < n2->value) {
				list.append(n1->value);
				n1 = n1->next;
				continue;
			}
			list.append(n2->value);
			n2 = n2->next;
		}
		while (n1) {
			list.append(n1->value);
			n1 = n1->next;
			return list;
		}
		while (n2) {
			list.append(n2->value);
			n2 = n2->next;
		}

		return list;
	}

	Node* mergeKSortedLists(std::vector<Node*>& lists) {
        auto cmp = [](Node* a, Node* b) { return a->value > b->value; };
        std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);

        for (Node* list : lists) {
            if (list) {
                pq.push(list);
            }
        }

        Node* dummy = new Node(0);
        Node* tail = dummy;

        while (!pq.empty()) {
            Node* minNode = pq.top();
            pq.pop();
            tail->next = minNode;
            tail = tail->next;

            if (minNode->next) {
                pq.push(minNode->next);
            }
        }

        return dummy->next;
    }


    
    static int findSubListCount(Node* head, int targetValue, int currentValue = 0, int temp = 0) {
        if (head == nullptr) return 0;

        int subListCount = 0;
        int currentValueTemp = currentValue;
        Node* currentNode = head;

        for (int i = 0; currentNode != nullptr; i++) {
            currentValue = currentValueTemp;

            if (currentValue + currentNode->value <= targetValue) {
                currentValue += currentNode->value;
            } else {
                return subListCount;
            }

            if (currentValue == targetValue) {
                subListCount++;
            }

            currentNode = currentNode->next;
            subListCount += findSubListCount(currentNode, targetValue, currentValue, temp + 1);
        }

        return subListCount;
    }
};


int main() {
    LinkedList list;

    list.append(2);
    list.append(3);
    list.append(5);
    list.append(7);

    cout << "sub list count: " << list.findSubListCount(list.head, 10) << endl;

    return 0;
}
