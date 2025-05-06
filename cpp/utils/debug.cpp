#include "debug.h"

string __print(string s){
	return '"' + s + '"';
}

string __print(char c){
	string ret = "'";
	ret += c;
	ret += "'";
	return ret;
}

string __print(bool c){
	return (c ? "true" : "false");
}

string __print(int a){
	return to_string(a);
}

string __print(long a){
	return to_string(a);
}

string __print(long long a){
	return to_string(a);
}


string __print(float a){
	return to_string(a);
}

string __print(double a){
	return to_string(a);
}

string __print(long double a){
	return to_string(a);
}

template<typename A, typename B>
string __print(pair<A, B> p){
	return "(" + __print(p.first) + ", " + __print(p.second) + ")";
}

template<typename T, size_t Z>
string __print(array<T, Z> a){
	bool sep = false;
	string ret = "{";
	for(const T &x : a){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(x);
	}
	ret += "}";
	return ret;
}

template<typename T>
string __print(vector<T> v){
	bool sep = false;
	string ret = "{";
	for(const T &x : v){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(x);
	}
	ret += "}";
	return ret;
}

template<typename T>
string __print(stack<T> s){
	bool sep = false;
	string ret = "{";
	while(!s.empty()){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(s.top()); s.pop();
	}
	ret += "}";
	return ret;
}

template<typename T>
string __print(queue<T> q){
	bool sep = false;
	string ret = "{";
	while(!q.empty()){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(q.front()); q.pop();
	}
	ret += "}";
	return ret;
}

template<typename T>
string __print(priority_queue<T> pq){
	bool sep = false;
	string ret = "{";
	while(!pq.empty()){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(pq.top()); pq.pop();
	}
	ret += "}";
	return ret;
}

template<typename T>
string __print(priority_queue<T, vector<T>, greater<T>> pq){
	bool sep = false;
	string ret = "{";
	while(!pq.empty()){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(pq.top()); pq.pop();
	}
	ret += "}";
	return ret;
}

template<typename T>
string __print(deque<T> v){
	bool sep = false;
	string ret = "{";
	for(const T &x : v){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(x);
	}
	ret += "}";
	return ret;
}

template<typename T>
string __print(set<T> v){
	bool sep = false;
	string ret = "{";
	for(const T &x : v){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(x);
	}
	ret += "}";
	return ret;
}

template<typename T>
string __print(multiset<T> v){
	bool sep = false;
	string ret = "{";
	for(const T &x : v){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(x);
	}
	ret += "}";
	return ret;
}

template<typename T>
string __print(unordered_set<T> v){
	bool sep = false;
	string ret = "{";
	for(const T &x : v){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(x);
	}
	ret += "}";
	return ret;
}

template<typename F, typename S>
string __print(map<F, S> v){
	bool sep = false;
	string ret = "{";
	for(const auto& x : v){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(x);
	}
	ret += "}";
	return ret;
}

template<typename F, typename S>
string __print(multimap<F, S> v){
	bool sep = false;
	string ret = "{";
	for(const auto& x : v){
		if(sep) ret += ", ";
		sep = true;
		ret += __print(x);
	}
	ret += "}";
	return ret;
}


void debug() { cerr << '\n'; }


template <typename Head, typename... Tail>
void debug(Head H, Tail... T){
	cerr << ' ' << __print(H);
	debug(T...);
}

#define dbg(...) cerr << "[" << #__VA_ARGS__ << "] => ", debug(__VA_ARGS__)