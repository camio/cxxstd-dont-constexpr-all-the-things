#include <algorithm>
#include <vector>

@meta std::vector<int> myvec{ 3, 6, 2, 1 };
@meta std::sort(myvec.begin(), myvec.end());

int main() {
    std::vector<int> v = myvec;
}
