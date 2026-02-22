#include <cstdlib>
#include <iostream>
#include <unordered_set>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

bool hasCycle(ListNode *head) {
    std::unordered_set<ListNode*> visited;
    ListNode* current{head};
    while (NULL != current) {
        if (visited.find(current) != visited.end()) {
            return true;
        }

        visited.insert(current);
        current = current->next;
    }

    return false;
};

int main(int argc, char* argv[]) {
    // head = [3,2,0,-4], pos = 1
    ListNode* head1 = new ListNode{3};
    head1->next = new ListNode{2};
    head1->next->next = new ListNode{0};
    head1->next->next->next = new ListNode{-4};
    head1->next->next->next->next = head1->next;

    // head = [1,2], pos = 0
    ListNode* head2 = new ListNode{1};
    head2->next = new ListNode{2};
    head2->next->next = head2;

    // head = [1], pos = -1
    ListNode* head3 = new ListNode{1};

    std::cout << (hasCycle(head1) ? "TRUE" : "FALSE") << "\n";
    std::cout << (hasCycle(head2) ? "TRUE" : "FALSE") << "\n";
    std::cout << (hasCycle(head3) ? "TRUE" : "FALSE") << "\n";

    return EXIT_SUCCESS;
}

// End of file `linked_list_cycle.cxx'
