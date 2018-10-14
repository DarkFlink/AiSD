#ifndef BINARYTREAP_H
#define BINARYTREAP_H

/*    TreapNode - class that implements node of Treap. Treap - abstract data structure, that unions attributes of
 *    binary search tree, and binary heap (so, you can see that: Tree + Heap = Treap). It has splitting on storable
 *    data: keys and priorities (well, if you don't want to store any user information of custom type, you store only keys)
 *    So, that data structure works like binary search tree and binary heap at the same time.
 */

#include "otherfuncs.h"
#define ONE_NODE 1
#define NO_PRIORITY 0

#define RAND_FACTOR 200

typedef unsigned long ul;

template<class TYPE>
class TreapNode
{
public:
    TreapNode();
    TreapNode(ul _key, ul _priority = std::rand() % RAND_FACTOR + 1, TreapNode* _left = nullptr, TreapNode* _right = nullptr);

    TreapNode* Merge(TreapNode* _left, TreapNode* _right);                  // Merging two treaps. Need agree with: keys of one of treaps needs to be bigger, than keys of another Treap.
    void Split(ul _key, TreapNode*& _left, TreapNode*& _right);             // Splits up treap. First output treap has all keys smaller than keys of the second one.

    TreapNode* Add(ul _key);                                                // Add Node to NON EMPTY Treap, using key. Priority changed by std::rand.
    TreapNode* Add(ul _key, ul _priority);                                  // Add Node to NON EMPTY Treap, using key and priority.
    TreapNode* Remove(ul _key);                                             // Remove Node from NON EMPTY Treap by key.

    int Exist(ul _key);                                                     // If node exsited in treap returns way lenght to him (num of sticks), else -1
    void RecalcSizeOf();                                                    // Recalculate SizeOf
    size_t Height();                                                        // Returns way length from root the farthest node.

    static void Clear(TreapNode* _treap);                                   // Destroy root this and all childs.
    static size_t SizeOf(TreapNode* _treap);                                // Returns mSizeOf field of _treap

    ul Key(size_t _idx);                                                    // Returns key of node by index in upping order of keys.
    size_t LevelLenght(size_t _level);                                      // Returns count of nodes on _level height

    void Display(size_t _depth = 0);                                        // Output hierarchial structure of treap, by inOrder going.

private:

    TreapNode* mLeft;
    TreapNode* mRight;

    ul mKey;
    ul mPriority;

    size_t mSizeOf;                                                         // Count of subtreaps + 1 (root exactly)
};

//______________________________________NODE_METHODS___________________________________________//

//____CONSTRUCTORS____//

template<class TYPE>
TreapNode<TYPE>::TreapNode()
{
    mSizeOf = ONE_NODE;
    mLeft = nullptr;
    mRight = nullptr;
    mKey = 0;
    mPriority = 0;
}

template<class TYPE>
TreapNode<TYPE>::TreapNode(ul _key, ul _priority, TreapNode* _left, TreapNode* _right) : TreapNode()
{
    mLeft = _left;
    mRight = _right;
    mKey = _key;
    mPriority = _priority;
}

//____TREAP_EDITING____//

template<class TYPE>
TreapNode<TYPE>* TreapNode<TYPE>::Merge(TreapNode* _left, TreapNode* _right)
{
    if(!_left) return _right;
    if(!_right) return _left;

    TreapNode<TYPE>* treap;
    if(_left->mPriority > _right->mPriority) {
        TreapNode<TYPE>* new_subTreap = Merge(_left->mRight, _right);
        treap = new TreapNode(_left->mKey, _left->mPriority, _left->mLeft, new_subTreap);
    } else {
        TreapNode<TYPE>* new_subTreap = Merge(_left, _right->mLeft);
        treap = new TreapNode(_right->mKey, _right->mPriority, new_subTreap, _right->mRight);
    }

    treap->RecalcSizeOf();
    return treap;
}

template<class TYPE>
void TreapNode<TYPE>::Split(ul _key, TreapNode*& _left, TreapNode*& _right)
{
    TreapNode<TYPE>* _newTreap = nullptr;
    if(mKey <= _key) {
        if(!mRight)
            _right = nullptr;
        else
            mRight->Split(_key, _newTreap, _right);
        _left = new TreapNode(mKey, mPriority, mLeft, _newTreap);
        _left->RecalcSizeOf();
    }
    else {
        if(!mLeft)
            _left = nullptr;
        else
            mLeft->Split(_key, _left, _newTreap);
        _right = new TreapNode(mKey, mPriority, _newTreap, mRight);
        _right->RecalcSizeOf();
    }
}

template<class TYPE>
TreapNode<TYPE>* TreapNode<TYPE>::Add(ul _key)
{
    TreapNode<TYPE>* _left = nullptr;
    TreapNode<TYPE>* _right = nullptr;
    Split(_key, _left, _right);
    TreapNode<TYPE>* newNode = new TreapNode(_key);
    return Merge(Merge(_left, newNode), _right);
}

template<class TYPE>
TreapNode<TYPE>* TreapNode<TYPE>::Add(ul _key,  ul _priority)
{
    TreapNode<TYPE>* _left = nullptr;
    TreapNode<TYPE>* _right = nullptr;
    Split(_key, _left, _right);
    TreapNode<TYPE>* newNode = new TreapNode(_key, _priority);
    return Merge(Merge(_left, newNode), _right);
}

template<class TYPE>
TreapNode<TYPE>* TreapNode<TYPE>::Remove(ul _key)
{
    TreapNode<TYPE>* _r = nullptr;
    TreapNode<TYPE>* _l = nullptr;
    TreapNode<TYPE>* _el = nullptr;
    Split(_key, _l, _r);
    _l->Split(_key-1, _l, _el);
    delete _el;
    return Merge(_l, _r);
}

template<class TYPE>
void TreapNode<TYPE>::Clear(TreapNode* _treap)
{
    if(_treap)
    {
        if(_treap->mLeft)
            Clear(_treap->mLeft);
        if(_treap->mRight)
            Clear(_treap->mRight);

        delete _treap;
    }
}

//____SIZE____//

template<class TYPE>
size_t TreapNode<TYPE>::SizeOf(TreapNode* _treap)
{
    return !_treap ? 0 : _treap->mSizeOf;
}

template<class TYPE>
void TreapNode<TYPE>::RecalcSizeOf()
{
    mSizeOf += SizeOf(mLeft) + SizeOf(mRight);
}

//____SEARCHING____//

template<class TYPE>
int TreapNode<TYPE>::Exist(ul _key)
{
    int index = 0;
    TreapNode<TYPE>* node = this;

    while (node)
    {
        if(node->mKey == _key) return index;
        else if(node->mKey < _key)
            node = node->mRight;
        else if(node->mKey > _key)
            node = node->mLeft;
        index++;
    }
    return -1;
}

template<class TYPE>
size_t TreapNode<TYPE>::Height()
{
    size_t index = 0;
    TreapNode<TYPE>* node = this;

    while(TreapNode<TYPE>::SizeOf(node) > 1)
    {
        if(TreapNode<TYPE>::SizeOf(node->mLeft) >= TreapNode<TYPE>::SizeOf(node->mRight))
            node = node->mLeft;
        else
            node = node->mRight;

        index++;
    }
    return index;
}

template<class TYPE>
ul TreapNode<TYPE>::Key(size_t _idx)
{
    TreapNode<TYPE>* node = this;
    while(node) {
        if(node->SizeOf(node->mLeft) == _idx)
            return node->mKey;
        else if(node->SizeOf(node->mLeft) > _idx)
            node = node->mLeft;
        else if (node->SizeOf(node->mLeft) < _idx) {
            _idx -= SizeOf(node->mLeft) + 1;
            node = node->mRight;
        }
    }
    return 0;
}

template<class TYPE>
size_t TreapNode<TYPE>::LevelLenght(size_t _level)
{
    size_t count = 0;
    for(size_t it = 0; it < mSizeOf; it++)
    {
        size_t cur_height = Exist(Key(it));
        if(cur_height == _level)
            count++;
    }
    return count;
}

template<class TYPE>
void TreapNode<TYPE>::Display(size_t _depth)
{
    std::cout << '(' << mKey << ',' << mPriority <<  ")\n";
    if(mLeft)
    {
        print_tabs(_depth+1);
        std::cout << "\tleft:\t";
        mLeft->Display(_depth + 1);
    }
    if(mRight)
    {
        print_tabs(_depth+1);
        std::cout << "\tright:\t";
        mRight->Display(_depth + 1);
    }
}

#endif // BINARYTREAP_H
