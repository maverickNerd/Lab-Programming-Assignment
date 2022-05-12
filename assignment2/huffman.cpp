#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

// Huffman Tree Node
struct Node
{
	char data;   // Input character
	int freq; // Frequency of the character
	Node *left; // Left child
    Node *right; // Right child
};

Node* getNode(char data, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->data = data;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// Compare to order the heap
struct compare
{
	bool operator()(Node* left, Node* right)
	{
		return left->freq > right->freq;
	}
};

// Encode the string
void encode(Node* root, string str,
			unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->data] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// Decode encoded string
void decode(Node* root, int &i, string str)
{
	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right)
	{
		cout << root->data;
		return;
	}

	i++;

	if (str[i] =='0')
		decode(root->left, i, str);
	else
		decode(root->right, i, str);
}

void huffmanTree(string input)
{
	unordered_map<char, int> freq;
	// counting the frequency of each character and storing it
    for (char data: input) {
		freq[data]++;
	}

	// Using template to make a priority queue, stores current node
	priority_queue<Node*, vector<Node*>, compare> prio_queue;

	for (auto node: freq) {
		prio_queue.push(getNode(node.first, node.second, nullptr, nullptr));
	}

	while (prio_queue.size() != 1)
	{
		// Remove two nodes of highest priority from queue
		Node *left = prio_queue.top(); 
        prio_queue.pop();
		Node *right = prio_queue.top();	
        prio_queue.pop();

		int sum = left->freq + right->freq;
		prio_queue.push(getNode('\0', sum, left, right));
	}

	Node* root = prio_queue.top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto node: huffmanCode) {
		cout << node.first << " " << node.second << '\n';
	}

	cout << "\nOriginal string:\n" << input << '\n' << endl;
    
	// print encoded string
	string str = "";
	for (char data: input) {
		str += huffmanCode[data];
	}

	cout << "Encoded string:\n" << str << '\n' << endl;

	// decode the encoded string
	int index = -1;
	cout << "Decoded string: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
    cout << "\n" << endl ;
}

int main()
{
	string input = "Sachin Grover";

	huffmanTree(input);

	return 0;
}
