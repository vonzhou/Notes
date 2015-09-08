
// Definition for singly-linked list.
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};


// we can not get the previous pointer, so...
// flash of inpiration, swap its value with the last node , and delete the last.
void deleteNode(ListNode* node) {

	if(node == NULL || node -> next == NULL)// need more than one node
		return;

	int t = node -> val;
	node -> val = node -> next -> val;
	node -> next -> val = t;

	ListNode *p = node -> next;
	node -> next = p -> next;

	free(p);
}
 