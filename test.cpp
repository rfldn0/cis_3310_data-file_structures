#include <iostream> 
#include <bits/stdc++.h>

// This is a test of huffman tree, greedy algorithm. 

/*** STEPS TO ACCOUNT FOR
 * The least frequent character is at root. Create leaf nodes for each unique characters and build a min heap of all leaf nodes.
 *  Mean heap is used as a priority queue. 
 * Extract two nodes with the minimum frequency from mthe min heap. 
 * Initialize a new internal node, where frequency is equal to the sum of the two node frequencies. 
 *      Make the first extracted node as its left and the other extracted node as its right child. And add this node to the min heap. 
 * 
 */

 //Construct the huffman tree and node


 using namespace std; 

 // class to represent huggman tree
 class Node {
    public: 
    int data; 
    Node *left, *right; 
    Node(int x) {
        data = x; 
        left = nullptr; 
        right = nullptr;
    }
 };

 // Cstom min head for Node class. 
 class Compare {
    public:
    bool operator() (Node* a, Node* b) {
        return a->data > b->data; 
    } 
 };

 // Function to traverse tree in preorder 
 // manner and push hthe huffman representation
 // of each character

 void preOrder(Node* root, vector<string> &ans, string curr) {
    if (root == nullptr) return;

    // Leaf node represents a character. 
    if (root->left == nullptr && root->right==nullptr) {
        ans.push_back(curr);
        return; 
    }

    preOrder(root->left, ans, curr + '0');
    preOrder(root->right, ans, curr + '1');
 }

 vector<string> huffmanCodes(string s, vector<int> freq) {

    int n = s.length();

    // Min heap for node class.
    priority_queue<Node*, vector<Node*>, Compare> pq; 
    for (int i=0; i<n; i++){
        Node* tmp = new Node(freq[i]);
        pq.push(tmp);
    }

    // Huffman tree
    while (pq.size()>=2){
        
        //left node
        Node* l = pq.top();
        pq.pop();

        //right node
        Node* r = pq.top();
        pq.pop(); 

        Node* newNode = new Node(l->data + r->data);
        newNode->left = l; 
        newNode->right = r;

        pq.push(newNode);
    }

    Node* root = pq.top();
    vector<string> ans;
    preOrder(root, ans, "");
    return ans;
 }

 int main() {
    string s = "abcdef"; 
    vector<int> freq = {5, 9, 12, 13, 16, 45};
    vector<string> ans = huffmanCodes(s, freq); 
    for (int i=0; i< ans.size(); i++){
        cout << ans[i] << " ";
    }

    return 0; 
 }