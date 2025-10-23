

// el siguiente mayor a la derecha mas cercano
// indexado desde 1
// para IZQ, cambiar el sentido del for y el pivot
vi nearest_greater(vi &a, int n) {
    vi ans(n + 2);
    ans[n + 1] = n + 1; // n + 1 es el pivot

    vi stack;
    stack.push_back(n + 1);
    for (int i = n; i >= 1; i--) {
        while (sz(stack) > 1 && a[stack.back()] <= a[i]) {
            stack.pop_back();
        }
        ans[i] = stack.back();
        stack.push_back(i);
    }
    return ans;
}

