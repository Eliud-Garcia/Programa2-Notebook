
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

//template when all elements are distinct
template <class T> using ordered_set = tree<T, null_type,
less<T>, rb_tree_tag,tree_order_statistics_node_update>;
//template when duplicate elements are also used
template <class T> using ordered_multiset = tree<T, null_type,
less_equal<T>, rb_tree_tag,tree_order_statistics_node_update>;

//Find # of elements smaller than X in the set
//st.order_of_key(x); // O(log n)

//Element present at the k-th index in the set
//(*st.find_by_order(k)); //// O(log n)

int main() {
  ordered_multiset<int> st;
  int arr [] = {1, 10, 2, 7, 3};
  forn(i, 5) st.insert(arr[i]);
  // st = {1 2 3 7 10}
  forn(i, 5){
    int x = (*st.find_by_order(i));
    cout << (st.order_of_key(arr[i])) << ln;
  }
  return 0;
}
