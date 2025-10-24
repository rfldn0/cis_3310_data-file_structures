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

 // function to calculate the length
 int countLength(string code) {
    return code.length();
 }

 int main() {
    int freq_x_length = 0;
    int length;
    string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    vector<int> freq = {77, 17,32, 42, 120, 24, 17, 50, 76, 4, 7, 42, 24, 67, 67, 20, 5, 59, 67, 85, 37, 12, 22, 4, 22, 2};
    vector<string> ans = huffmanCodes(s, freq);

    cout << "Letter    Frequency       Code           Length    Freq X Len" << endl;
    cout << "----------  ---------------  -------------  ---------  ---------------" << endl;

    for (int i=0; i< ans.size(); i++) {
        //count length
        length = countLength(ans[i]);

        //calculate the frequency times length
        int freqXLen = freq[i] * length;
        freq_x_length += freqXLen;

        printf("%-10c  %-15d  %-13s  %-9d  %-15d\n", s[i], freq[i], ans[i].c_str(), length, freqXLen);
    }

    //print the sum of the last column
    cout << "\nThe weighted minimum path length is: " << freq_x_length << endl;

    return 0;
 }