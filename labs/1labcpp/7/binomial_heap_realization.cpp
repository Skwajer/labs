#include "binomial_heap_API.h"

binomial_heap::binomial_heap() : _root(nullptr), _max(nullptr)
{}

binomial_heap::node *binomial_heap::tree_cpy(node *other_node)
{
    if (other_node == nullptr)
    {return nullptr;}

    node *new_tree = new node(other_node->_priority, other_node->_data, other_node->_parent, other_node->_degree);
    if (other_node->_sibling != nullptr)
    {
        new_tree->_sibling = tree_cpy(other_node->_sibling);
    }
    if (other_node->_child != nullptr)
    {
        new_tree->_child = tree_cpy(other_node->_child);
    }
    return new_tree;
}

void binomial_heap::cleanup_tree(binomial_heap::node *node_)
{
    if (node_->_sibling != nullptr)
    {
        cleanup_tree(node_->_sibling);
    }
    if(node_->_child != nullptr)
    {
        cleanup_tree(node_->_child);
    }
    delete[] node_->_data;
    delete node_;
}

binomial_heap::binomial_heap(const binomial_heap &other)
{
    _root = tree_cpy(other._root);
}

binomial_heap &binomial_heap::operator=(const binomial_heap &other)
{
    if (this == &other)
    {
        return *this;
    }
    cleanup_tree(_root);
    _root = tree_cpy(other._root);
    return *this;
}

/*binomial_heap::~binomial_heap() noexcept
{
    cleanup_tree(_root);
}*/

void binomial_heap::swap(binomial_heap::node *n1, binomial_heap::node *n2)
{
    node *temp = n1;
    n1 = n2;
    n2 = temp;
}

char *binomial_heap::find_max()
{
    if (_max == nullptr)
        throw std::invalid_argument("cant find max: heap is empty");

    return _max->_data;
}

binomial_heap *binomial_heap::merge(binomial_heap *other_heap)
{
    if (other_heap == nullptr)
    {return this;}

    if(_root == nullptr)
    {return other_heap;}

    node *new_root = nullptr;
    node **new_roots_for_merge = &new_root;

    node *cur = _root;
    node *other_cur = other_heap->_root;
    while ((cur != nullptr) && (other_cur != nullptr))
    {
        if (cur->_degree < other_cur->_degree)
        {
            *new_roots_for_merge = cur;
            cur = cur->_sibling;
        }
        else
        {
            *new_roots_for_merge = other_cur;
            other_cur = other_cur->_sibling;
        }
        new_roots_for_merge = &((*new_roots_for_merge)->_sibling);
    }
    /*if (cur == nullptr)
    {
        while(other_cur != nullptr)
        {
            *new_roots_for_merge = other_cur;
            other_cur = other_cur->_sibling;
            new_roots_for_merge = &((*new_roots_for_merge)->_sibling);
        }
    }
    else
    {
        while(cur != nullptr)
        {
            *new_roots_for_merge = cur;
            cur = cur->_sibling;
            new_roots_for_merge = &((*new_roots_for_merge)->_sibling);
        }
    }*/
    *new_roots_for_merge = (cur != nullptr) ? cur : other_cur;
    _root = new_root;
    _max = nullptr;

    node *cur_for_merge = _root;
    node *second_for_merge = (_root == nullptr)? nullptr : _root->_sibling;
    while (cur_for_merge->_sibling != nullptr)
    {
        if (cur_for_merge->_degree == second_for_merge->_degree)
        {
            if (cur_for_merge->_priority < second_for_merge->_priority)
            {
                swap(cur_for_merge, second_for_merge);
            }
            second_for_merge->_parent = cur_for_merge;

            if (cur_for_merge->_child == nullptr)
            {
                cur_for_merge->_child = second_for_merge;
            }
            else
            {
                node *child_iter = cur_for_merge->_child;
                while (child_iter->_sibling != nullptr)
                {
                    child_iter = child_iter->_sibling;
                }
                child_iter->_sibling = second_for_merge;
            }
            cur_for_merge->_degree++;
        }
        cur_for_merge = cur_for_merge->_sibling;
        second_for_merge = cur_for_merge->_sibling;
    }
    for (node *iter = _root; iter != nullptr; iter = iter->_sibling)
    {
        if (_max == nullptr || (iter->_priority > _max->_priority))
        {
            _max = iter;
        }
    }

    other_heap->_root = nullptr;
    other_heap->_max = nullptr;
    return this;
}

void binomial_heap::insert(char *new_data, int new_priority)
{
    binomial_heap temp;
    temp._root = new node(new_data, new_priority);
    temp._max = temp._root;
    if (_root == nullptr)
    {
        _root = merge(&temp)->_root;
        _max = _root;
    }
    merge(&temp);
}

/*void binomial_heap::delete_max()
{

}*/

int main()
{
    char str1[] = {'p', 'u', '\0'};
    char str2[] = {'p', 'u', 'p', 'u', '\0'};
    char str3[] = {'p', 'u', 'p', 'u', 'p', 'u', '\0'};
    binomial_heap heap1;
    heap1.insert(str1, -100);
    heap1.insert(str2, 1000);
    heap1.insert(str3, 0);

    std::cout << heap1.find_max();

    return 0;
}