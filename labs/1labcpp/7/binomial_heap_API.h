#ifndef INC_7_BINOMIAL_HEAP_API_H
#define INC_7_BINOMIAL_HEAP_API_H

#include <iostream>
#include <cstring>

class binomial_heap final
{
private:
    class node
    {
    public:
        int _priority;
        char *_data;
        node *_parent;
        node *_child;
        node *_sibling;
        int _degree;

        node(int new_priority, char *new_data, node *new_parent, int new_degree) : _degree(new_degree), _parent(new_parent), _priority(new_priority)
        {
            _data = new char[strlen(new_data) + 1];
            strcpy(_data, new_data);
        }
        node(char *new_data, int new_priority) : _priority(new_priority), _parent(nullptr), _child(nullptr), _sibling(nullptr)
        {
            _data = new char[strlen(new_data) + 1];
            strcpy(_data, new_data);
        }

        //~node() noexcept;
    };

    node *_max;
    node *_root;

    void cleanup_tree(node *n);
    node *tree_cpy(node *);
    void swap(node *, node *);

public:
    binomial_heap();
    binomial_heap(const binomial_heap &other);
    //~binomial_heap() noexcept;
    binomial_heap &operator=(const binomial_heap &other);

    void insert(char *new_data, int new_priority);
    [[nodiscard]]char *find_max();
    void delete_max();

    binomial_heap *merge(binomial_heap *other);
};
#endif //INC_7_BINOMIAL_HEAP_API_H
