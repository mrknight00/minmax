%%writefile minmax.cpp
#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

#include <ctime>
#include <chrono>
#include <cstdlib>

using namespace std;
void generate_random_input(vector<int>& arr, int n) 
{
    for (int i = 0; i < n; ++i) 
    {
        arr.push_back(rand() % 1000); 
    }
    for (int i = 0; i < n; ++i)
    {
      cout<<arr[i]<<" ";
    }
    cout<<endl;
}


void min_seq(const vector<int>& arr) {
  int min_value = INT_MAX;
  for (int i = 0; i < arr.size(); i++) 
  {
    if (arr[i] < min_value) 
    {
      min_value = arr[i];
    }
  }
  cout << "Sequential Minimum value: " << min_value << endl;
}

void max_seq(const vector<int>& arr) {
  int max_value = INT_MIN;
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];
    }
  }
  cout << "Sequential Maximum value: " << max_value << endl;
}

void sum_seq(const vector<int>& arr) {
  int sum = 0;
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  cout << "Sequential Sum: " << sum << endl;
}

void average_seq(const vector<int>& arr) {
  int sum = 0;
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  cout << "Sequential Average: " << (double)sum / arr.size() << endl;
}

void min_reduction(vector<int>& arr) {
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] < min_value) {
      min_value = arr[i];
    }
  }
  cout << "Minimum value: " << min_value << endl;
}

void max_reduction(vector<int>& arr) {
  int max_value = INT_MIN;
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < arr.size(); i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];
    }
  }
  cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(vector<int>& arr) {
  int sum = 0;
   #pragma omp parallel for reduction(+: sum)
   for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  cout << "Sum: " << sum << endl;
}

void average_reduction(vector<int>& arr) {
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
  }
  cout << "Average: " << (double)sum / arr.size() << endl;
}

int main() {
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;

//   vector<int> arr(n);
//  cout << "Enter " << n << " elements:\n";
//  for (int i = 0; i < n; ++i) 
//  {
//    cin >> arr[i];
//  }

  vector<int> arr;
  generate_random_input(arr, n);

// Parallel reductions
  clock_t start_time = std::clock();
  min_reduction(arr);
  max_reduction(arr);
  sum_reduction(arr);
  average_reduction(arr);
  clock_t end_time = std::clock();
  double parallel_time = double(end_time - start_time) / CLOCKS_PER_SEC;
  cout << "Time taken for parallel reductions: " << parallel_time << " seconds" << endl;
  cout<<endl;

  // Sequential reductions
  start_time = std::clock();
  min_seq(arr);
  max_seq(arr);
  sum_seq(arr);
  average_seq(arr);
  end_time = std::clock();
  double sequential_time = double(end_time - start_time) / CLOCKS_PER_SEC;
  cout << "Time taken for sequential reductions: " << sequential_time << " seconds" << endl;

  return 0;
}