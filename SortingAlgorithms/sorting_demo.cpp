#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 冒泡排序
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

// 选择排序
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

// 插入排序
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// 快速排序分区函数
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high-1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

// 快速排序
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

// 测试函数
void testSortingAlgorithm(void (*sortFunc)(vector<int>&), const string& name) {
    vector<int> test1 = {64, 34, 25, 12, 22, 11, 90};
    vector<int> test2 = {1, 2, 3, 4, 5};
    vector<int> test3 = {5, 4, 3, 2, 1};
    
    vector<vector<int>> tests = {test1, test2, test3};
    
    for (auto& t : tests) {
        vector<int> original = t;
        sortFunc(t);
        
        if (is_sorted(t.begin(), t.end())) {
            cout << name << " 测试通过 ✓" << endl;
        } else {
            cout << name << " 测试失败 ✗ 输入:";
            for (auto num : original) cout << num << " ";
            cout << "输出:";
            for (auto num : t) cout << num << " ";
            cout << endl;
        }
    }
    cout << endl;
}

int main() {
    cout << "========== 排序算法测试 ==========\n\n";
    
    testSortingAlgorithm(bubbleSort, "冒泡排序");
    testSortingAlgorithm(selectionSort, "选择排序");
    testSortingAlgorithm(insertionSort, "插入排序");
    
    // 快速排序需要lambda包装
    testSortingAlgorithm([](vector<int>& arr) { 
        quickSort(arr, 0, arr.size()-1); 
    }, "快速排序");
    
    cout << "所有测试完成！" << endl;
    return 0;
}