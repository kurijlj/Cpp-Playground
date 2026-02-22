#include <cstdlib>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode *merged{nullptr}, *current_merged{nullptr}, *current1{list1}, *current2{list2};

    while (nullptr != current1 || nullptr != current2) {
        if (nullptr != current1 && nullptr != current2) {
            if (current1->val < current2->val) {
                if (nullptr == current_merged) {
                    merged = current_merged = current1;
                } else {
                    current_merged = current_merged->next = current1;
                }
                current1 = current1->next;
            } else {
                if (nullptr == current_merged) {
                    merged = current_merged = current2;
                } else {
                    current_merged = current_merged->next = current2;
                }
                current2 = current2->next;
            }
        } else if (nullptr != current1) {
            if (nullptr == current_merged) {
                merged = current_merged = current1;
            } else {
                current_merged = current_merged->next = current1;
            }
            current1 = current1->next;
        } else {
            if (nullptr == current_merged) {
                merged = current_merged = current2;
            } else {
                current_merged = current_merged->next = current2;
            }
            current2 = current2->next;
        }
    }

    return merged;
};

int main() {
    ListNode *list1{new ListNode(1, new ListNode(2, new ListNode(4)))};
    ListNode *list2{new ListNode(1, new ListNode(3, new ListNode(4)))};

    ListNode *current{list1};
    while (nullptr != current) {
        std::cout << current->val << " ";
        current = current->next;
    }
    std::cout << "\n";

    current = list2;
    while (nullptr != current) {
        std::cout << current->val << " ";
        current = current->next;
    }
    std::cout << "\n";

    ListNode *merged{mergeTwoLists(list1, list2)};

    current = merged;
    while (nullptr != current) {
        std::cout << current->val << " ";
        current = current->next;
    }
    std::cout << "\n";

    return EXIT_SUCCESS;
}

// End of file `merge_two_sorted_lists.cxx'
