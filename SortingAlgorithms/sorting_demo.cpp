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

// 堆排序辅助函数：维护堆的性质
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;    // 初始化根节点为最大值
    int left = 2*i + 1; // 左子节点
    int right = 2*i + 2; // 右子节点

    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点大于当前最大值
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大值不是根节点
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // 递归地对受影响的子树调用heapify
        heapify(arr, n, largest);
    }
}

// 归并排序辅助函数：合并两个有序子数组
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建临时数组
    vector<int> L(n1), R(n2);

    // 复制数据到临时数组
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // 合并临时数组回原数组
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 复制剩余元素
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序主函数
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // 避免溢出

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// 堆排序
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 一个个从堆顶取出元素
    for (int i = n - 1; i > 0; i--) {
        // 将当前根节点（最大值）移到数组末尾
        swap(arr[0], arr[i]);

        // 调用heapify函数维护剩余元素的堆性质
        heapify(arr, i, 0);
    }
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
    
    testSortingAlgorithm(heapSort, "堆排序");
    
    // 归并排序需要lambda包装
    testSortingAlgorithm([](vector<int>& arr) { 
        mergeSort(arr, 0, arr.size()-1); 
    }, "归并排序");
    
    cout << "所有测试完成！" << endl;
    return 0;
}