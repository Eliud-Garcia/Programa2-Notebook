#include<bits/stdc++.h>

using namespace std;

string __print(string s);
string __print(char c);
string __print(int a);
string __print(long a);
string __print(long long a);
string __print(float a);
string __print(double a);
string __print(long double a);
template<typename A, typename B> string __print(pair<A, B> p);
template<typename T, size_t Z> string __print(array<T, Z> a);
template<typename T> string __print(vector<T> v);
template<typename T> string __print(stack<T> s);
template<typename T> string __print(queue<T> q);
template<typename T> string __print(priority_queue<T> p);
template<typename T> string __print(priority_queue<T, vector<T>, greater<T>> p);
template<typename T> string __print(deque<T> v);
template<typename T> string __print(set<T> v);
template<typename T> string __print(multiset<T> v);
template<typename T> string __print(unordered_set<T> v);
template<typename F, typename S> string __print(map<F, S> v);
template<typename F, typename S> string __print(multimap<F, S> v);
