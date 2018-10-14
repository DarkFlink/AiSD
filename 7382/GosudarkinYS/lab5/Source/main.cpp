#include "treap.h"

int main()
{
    ul _search_key;
    std::cout << "Input searching element: ";
    getInt(_search_key);
    std::cout << _search_key << '\n';

    ul _level;
    std::cout << "Input level of needed deep: ";
    getInt(_level);
    std::cout << _level << '\n';

    Treap<int>* mTreap = new Treap<int>;
    Treap<int>* mTreap_L = new Treap<int>;
    Treap<int>* mTreap_R = new Treap<int>;

    std::cout << "Input keys: ";
    bool res = true;
    while(res) {
        ul curr;
        res = getInt(curr);
        if(res && curr) {
            std::cout << curr << ", ";
            mTreap->Add(curr);
        }
        else {
            std::cout << "0\n";
            break;
        }
    }

    mTreap->Status();
    std::cout << "\na) Find [" << _search_key << "] key: " << mTreap->Exist(_search_key) << "\n";
    std::cout << "b) Count of elements on [" << _level << "] level: " << mTreap->LevelLength(_level) << '\n';

    std::cout << "\nSplitting by search_key (" << _search_key << ")...\n";
    mTreap->Split(_search_key, mTreap_L, mTreap_R);

    mTreap_L->Status();
    mTreap_R->Status();

    return 0;
}
