#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

template<typename T>
void swp_p(T*& p1, T*& p2) {
    T* tmp = p1;
    p1 = p2;
    p2 = tmp;
}

class Node {
public:
    Node* left;
    Node* right;
    char c;
    unsigned freq;

    Node(char c, unsigned freq)
        : left(nullptr), right(nullptr), c(c), freq(freq) {}
};

void heapify(vector<Node*> &heap, size_t i) {
    size_t left = i * 2 + 1;
    size_t right = i * 2 + 2;
    size_t min = i;

    if (left < heap.size() && heap[left]->freq < heap[min]->freq)
        min = left;
    
    if (right < heap.size() && heap[right]->freq < heap[min]->freq)
        min = right;

    if (min != i) {
        swp_p(heap[min], heap[i]);
        heapify(heap, min);
    }
}

void heapify_up(vector<Node*> &heap, size_t i) {
    while (i != 0) {
        size_t parent = (i - 1) / 2;
        if (heap[parent]->freq <= heap[i]->freq)
            break;
        
        swp_p(heap[parent], heap[i]);
        i = parent;
    }
}

void build_heap(vector<Node*> &heap) {
    for (size_t i = heap.size() / 2 - 1; true; i--) {
        heapify(heap, i);
        if (i == 0) break;
    }
}

vector<Node*> parse(string str) {
    unordered_map<char, unsigned> freqs;
    vector<Node *> heap;

    for (const char c : str)
        freqs[c]++;
    
    for (const auto& [c, freq] : freqs) {
        heap.push_back(new Node(c, freq));
        heapify_up(heap, heap.size() - 1);
    }

    return heap;
}

Node* pop_min(vector<Node*> &heap) {
    Node* min = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    heapify(heap, 0);
    return min;
}

void add(vector<Node*> &heap, Node* el) {
    heap.push_back(el);
    heapify_up(heap, heap.size() - 1);
}

Node* huffman(vector<Node*> &heap) {
    while (heap.size() > 1) {
        Node* left = pop_min(heap);
        Node* right = pop_min(heap);

        Node* combined = new Node(0, left->freq + right->freq);
        combined->left = left;
        combined->right= right;
        add(heap, combined);
    }

    return pop_min(heap);
}

int main() {
    string abc = "aaaaaabbbddddeeeffdfadhskfgjdsakfds";
    
    vector<Node*> heap = parse(abc);

    for (auto c : heap) {
        cout << c->c << ": " << c->freq << " ";
    }

    cout << endl;

    Node* n = huffman(heap);
    
    cout << n->c << " " << n->freq << endl;
    cout << n->left->c << " " << n->right->freq << endl;

    // unordered_map<char, unsigned> map = parse(abc);

    // for (const auto& [key, val] : map) {
    //     cout << key << ": " << val << endl;
    // }


    return 0;
}