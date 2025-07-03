#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

class Node {
public:
    unique_ptr<Node> left;
    unique_ptr<Node> right;
    char c;
    unsigned freq;

    Node(char c, unsigned freq)
        : left(nullptr), right(nullptr), c(c), freq(freq) {}
};

class Heap {
public:
    vector<unique_ptr<Node>> heap;

    void heapify(size_t i) {
        size_t left = i * 2 + 1;
        size_t right = i * 2 + 2;
        size_t min = i;

        if (left < heap.size() && heap[left]->freq < heap[min]->freq)
            min = left;
        
        if (right < heap.size() && heap[right]->freq < heap[min]->freq)
            min = right;

        if (min != i) {
            swap(heap[min], heap[i]);
            heapify(min);
        }
    }

    void heapify_up(size_t i) {
        while (i != 0) {
            size_t parent = (i - 1) / 2;
            if (heap[parent]->freq <= heap[i]->freq)
                break;
            
            swap(heap[parent], heap[i]);
            i = parent;
        }
    }

    void build_heap() {
        for (size_t i = heap.size() / 2 - 1; true; i--) {
            heapify(i);
            if (i == 0) break;
        }
    }

    unique_ptr<Node> pop_min() {
        unique_ptr<Node> min = move(heap[0]);
        heap[0] = move(heap[heap.size() - 1]);
        heap.pop_back();
        heapify(0);
        return min;
    }

    void add(unique_ptr<Node> node){
        heap.push_back(move(node));
        heapify_up(heap.size() - 1);
    }
};

unique_ptr<Heap> parse(const string& str) {
    unordered_map<char, unsigned> freqs;
    unique_ptr<Heap> heap = make_unique<Heap>();

    for (const char c : str)
        freqs[c]++;
    
    for (const auto& [c, freq] : freqs) {
        heap->add(make_unique<Node>(c, freq));
    }

    return heap;
}

unique_ptr<Node> huffman(unique_ptr<Heap>& heap) {
    while (heap->heap.size() > 1) {
        unique_ptr<Node> left = heap->pop_min();
        unique_ptr<Node> right = heap->pop_min();

        unique_ptr<Node> combined = make_unique<Node>('\0', left->freq + right->freq);
        combined->left = move(left);
        combined->right= move(right);
        heap->add(move(combined));
    }

    return heap->pop_min();
}

void printTree(const Node* node, const string& prefix = "") {
    if (!node) return;

    if (node->c != '\0') {
        cout << node->c << ": " << prefix << endl;
    }

    printTree(node->left.get(), prefix + '0');
    printTree(node->right.get(), prefix + '1');
}

int main() {
    string abc = "aaaaaabbbdddeeeeffdfadskfbbbbbbbbbbbbgdsakfds";
    unique_ptr<Heap> heap = parse(abc);

    for (const auto& c : heap->heap)
        cout << c->c << ": " << c->freq << " ";
    cout << endl;

    unique_ptr<Node> huff = huffman(heap);
    printTree(huff.get());

    return 0;
}