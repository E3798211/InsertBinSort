#include <iostream>
#include <cctype>
#include <assert.h>

using namespace std;

int  SecureUserInput();
int* InsertBinSort(int* arr_to_sort, int elements_amnt);
int  BinSearch(int* arr_sorted, int start_pos, int end_pos, int curr_elem);


int main()
{
    cout << "# \"InsertSort + BinSearch\" - function demonstration." << endl;
    cout << "# Me, 08.2017\n" << endl;

    cout << "Enter amount of elements in array (this number should be > 0): " << endl;
    int elements_amnt = SecureUserInput();

    int* arr = new int [elements_amnt];
    for(int i = 0; i < elements_amnt; i++)
        arr[i] = rand() % 100;


    cout << "Before:" << endl;
    for(int i = 0; i < elements_amnt; i++)
        cout << "arr[" << i << "] = " << arr[i] << endl;

    arr = InsertBinSort(arr, elements_amnt);

    cout << "After:" << endl;
    for(int i = 0; i < elements_amnt; i++)
        cout << "arr[" << i << "] = " << arr[i] << endl;

}

//========================================================================

int  SecureUserInput()
{
    int elements_amnt;

    bool imput_correct = false;
    while(!imput_correct){
        cin >> elements_amnt;

        if(elements_amnt <= 0)
            cout << "Wrong input. Number should be more then 0." << endl;
        else
            imput_correct = true;
    }
    return elements_amnt;
}

int* InsertBinSort(int* arr_to_sort, int elements_amnt)
{
    //Exceptions
    assert(arr_to_sort != nullptr);
    assert(elements_amnt >= 0);

    //Sort itself
    //Part of the array before current_element is already sorted => finding position for
    //  current_element with BinSearch and placing it there. In the very beginning first element
    //  is considered sorted.
    int current_pos = 1;
    while(current_pos < elements_amnt){
        int current_elem = arr_to_sort[current_pos];
        int new_pos = BinSearch(arr_to_sort, 0, current_pos, current_elem);

        //Replacing elements
        for(int i = current_pos; i > new_pos; i--)
            arr_to_sort[i] = arr_to_sort[i - 1];
        arr_to_sort[new_pos] = current_elem;

        //Going for next element
        current_pos++;
    }

    return arr_to_sort;
}

int  BinSearch(int* arr_sorted, int start_pos, int end_pos, int curr_elem)
{
    //Exceptions
    assert(end_pos >= start_pos);

    if(end_pos > start_pos){
        int middle_pos = (end_pos + start_pos)/2;

        int new_pos;
        if(curr_elem < arr_sorted[middle_pos])
            new_pos = BinSearch(arr_sorted, start_pos, middle_pos, curr_elem);
        else
            new_pos = BinSearch(arr_sorted, middle_pos + 1, end_pos, curr_elem);

        return new_pos;
    }else /*if (end_pos <= start_pos)*/
        return start_pos;
}
