#ifndef TREAP_H
#define TREAP_H

#include "treapNode.h"

template<class TYPE>
class Treap
{
public:
    Treap();
    ~Treap();

    void Add(const ul _key, ul _priority = std::rand() % RAND_FACTOR + 1);            // Add Node to Treap
    void Remove(const ul _key);                                                       // Remove Node from Treap
    void Split(const ul _key, Treap*& _tr1, Treap*& _tr2);                            // Splits up treap. First output treap has all keys smaller than keys of the second one.

    size_t Height();                                                                  // Returns way length from root the farthest node.
    size_t LevelLength(const size_t _level);                                          // Returns count of node on same Height
    size_t Size();                                                                    // Returns count of nodes in Treap
    bool Empty();                                                                     // Returns true if Size>0 else false
    int Exist(const ul _key);                                                         // Returns count of iterations that need to bring node

    ul operator [](const size_t _idx);                                                // Overloaded Key()

    void Status();                                                                    // Put into cout all information about Treap
    void Abort(const std::domain_error& _err_def);                                    // Exits process, puts into cerr error definition and Treap Status, before exception cought
    void DisplayTreap();                                                              // Puts into cout schemical representation of Treap

private:
    ul Key(const size_t _idx);                                                        // Returns Key by his index in upping order

    TreapNode<TYPE>* mRoot;
};

//______________________________________TREAP_METHODS___________________________________________//

//____CONSTRUCTORS____//

template<class TYPE>
Treap<TYPE>::Treap()
{
    mRoot = nullptr;
}

//____DESTRUCTOR____//

template<class TYPE>
Treap<TYPE>::~Treap()
{
    mRoot->Clear(mRoot);
}

//____OVERLOADED_OPERATORS____//

template<class TYPE>
ul Treap<TYPE>::operator[](const size_t _idx)
{
    try {
        return Key(_idx);
    } catch (std::domain_error& _err_def) {
        Abort(_err_def);
    }
}

//____TREAP_EDITING____//

template<class TYPE>
void Treap<TYPE>::Add(const ul _key, const ul _priority)
{
    if(Empty()) {
        mRoot = new TreapNode<TYPE>(_key, _priority);
        return;
    }
    if(!_key) {
        std::cerr << "WARNING: {\n   OPERATION: Add(const ul _key, const ul _priority)\n   ARGS:     "<< _key << ", " << _priority <<
                     "\n   ERR_DEF:   Node with ZERO key cannot be added to Treap.\n}\n";
        return;
    }
    if(Exist(_key) != -1) {
        std::cout << "WARNING: {\n   OPERATION: Add(const ul _key, const ul _priority)\n   ARGS:     "<< _key << ", " << _priority <<
                     "\n   ERR_DEF:   Node with that _key is already existed in Treap.\n}\n";
        return;
    }
    mRoot = mRoot->Add(_key, _priority);
}

template<class TYPE>
void Treap<TYPE>::Split(const ul _key, Treap*& _tr1, Treap*& _tr2)
{
    if(Empty())
    {
        std::cout << "WARNING: {\n   OPERATION: Split(ul _key, Treap* _tr1, Treap* _tr2)\n   ARGS:     "<< _key << ", " << _tr1 << ", " << _tr2 <<
                     "\n   ERR_DEF:   Impossible using split operation on empty Treap.\n}\n";
        return;        
    }
    if(_tr1->mRoot != nullptr || _tr2->mRoot != nullptr)
    {
        std::cout << "WARNING: {\n   OPERATION: Split(ul _key, Treap* _tr1, Treap* _tr2)\n   ARGS:     "<< _key << ", " << _tr1 << ", " << _tr2 <<
                     "\n   ERR_DEF:   Input pointers Treap* is not nullptr (cannot split into non empty treaps))\n}\n";
        return;
    }
    mRoot->Split(_key, _tr1->mRoot, _tr2->mRoot);
}


template<class TYPE>
void Treap<TYPE>::Remove(const ul _key)
{
    if(Empty())
    {
        std::cout << "WARNING: {\n   OPERATION: Remove(ul _key)\n   INPUT:     "<< _key <<
                     "\n   ERR_DEF:   Treap is empty (removing node from empty treap)\n}\n";
        return;
    }
    if(Exist(_key) == -1) //  If not Exist
    {
        std::cout << "WARNING: {\n   OPERATION: Remove(ul _key)\n   INPUT:     "<< _key <<
                     "\n   ERR_DEF:   No such node with _key in treap (removing node that not included in treap)\n}\n";
        return;
    }
    mRoot = mRoot->Remove(_key);
}

//____SEARCHING____//

template<class TYPE>
int Treap<TYPE>::Exist(const ul _key) {    return mRoot->Exist(_key);    }

template<class TYPE>
size_t Treap<TYPE>::Size() {    return TreapNode<TYPE>::SizeOf(mRoot);    }

template<class TYPE>
bool Treap<TYPE>::Empty() {    return !mRoot ? true : false;    }

template<class TYPE>
size_t Treap<TYPE>::Height() {    return mRoot->Height();    }

template<class TYPE>
size_t Treap<TYPE>::LevelLength(const size_t _level)
{
    if(Empty())
        return 0;

    if(mRoot->Height() < _level)
    {
        std::string err_def = "THROWED_EXCEPTION: \n{\n    OPERATION: LevelLength(size_t _level)\n    ARGUMENT_VALUES: ";
        err_def += std::to_string(_level);
        err_def += "\n    ERR_DEF: Input _level larger than Height of Treap.\n}\n";
        Abort(std::domain_error(err_def));
    }
    return mRoot->LevelLenght(_level);
}

template<class TYPE>
ul Treap<TYPE>::Key(const size_t _idx)
{
    if(!mRoot)
        throw std::domain_error("THROWED_EXCEPTION: {\n\tOPERATION: Key(size_t _idx)"
                     "\n\tERR_DEF:   Treap is empty (return data from empty treap exception)\n}\n");
    if(_idx >= Size())
        throw std::domain_error("THROWED_EXCEPTION: {\n\tOPERATION: Key(size_t _idx)"
                     "\n\tERR_DEF:   Too big idx (idx >= size_of_treap exception)\n}\n");

    return mRoot->Key(_idx);
}

//____DEBUG_&&_STATUS____//

template<class TYPE>
void Treap<TYPE>::Status()
{
    std::cout << "TREAP_STATUS: \n{"
                 "\n    SIZE:    " << Size() <<
                 "\n    HEIGHT:  " << Height() << '\n';
    DisplayTreap();
    std::cout << "\n}\n";
}

template<class TYPE>
void Treap<TYPE>::Abort(const std::domain_error &_err_def)
{
    std::cout << "ERROR: " << _err_def.what();
    Status();
    exit(1);
}

template<class TYPE>
void Treap<TYPE>::DisplayTreap()
{
    std::cout << "    CHART: ";
    if(Empty()) {
        std::cout << "Empty Treap";
        return;
    }
    std::cout << "\n\troot:   ";
    mRoot->Display();
}

#endif // TREAP_H
