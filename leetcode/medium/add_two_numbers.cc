/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
  {
    // l1.lenght != l2.length
    ListNode* head = nullptr;
    int flag = 0;
    ListNode* p_l1 = l1;
    ListNode* p_l2 = l2;
    ListNode* tail = nullptr;
    while (p_l1 != nullptr || p_l2 != nullptr)
    {
      int val_1 = p_l1 ? p_l1->val : 0;
      int val_2 = p_l2 ? p_l2->val : 0;
      int result = (val_1 + val_2 + flag) % 10;
      flag = (val_1 + val_2 + flag) / 10;
      if (head == nullptr)
      {
        head = tail = new ListNode(result);
      }
      else
      {
        tail->next = new ListNode(result);
        tail = tail->next;
      }
      if (p_l1 != nullptr)
        p_l1 = p_l1->next;
      if (p_l2 != nullptr)
        p_l2 = p_l2->next;
    }
    if (flag == 1)
    {
      tail->next = new ListNode(flag);
      tail = tail->next;
    }

    return head;
  }
};
