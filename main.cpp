#include <iostream>
#include <cstdio>
#include <assert.h>

#define MAX_INPUT_SIZE 10

using namespace std;

int  SecureUserInput();
int* InsertBinSort(int* arr_to_sort, size_t elements_amnt);
int  BinSearchR(int* arr_sorted, int start_pos, int end_pos, int curr_elem);
int  BinSearchC(int* arr_sorted, int start_pos, int end_pos, int curr_elem);
int* FillArray(int* arr_to_fill, size_t elements_amnt, int max_elem_value = 100);
void PrintArray(int* arr_to_print, size_t elements_amnt);
void ElemInsert(int* arr_to_ins_in, int start_pos, int end_pos,
                int new_elem_pos, int new_elem_value);


int main()
{
    cout << "# \"InsertSort + BinSearch\" - function demonstration." << endl;
    cout << "# Me, 08.2017\n" << endl;

    cout << "Enter amount of elements in array (this number should be > 0)." << endl;
    cout << "Do not forget, that your number will be interpreted as integer." << endl;
    cout << "Enter size: ";
    int elements_amnt = SecureUserInput();

    int* arr = new int [elements_amnt];
    arr = FillArray(arr, elements_amnt);

    cout << "Before:" << endl;
    PrintArray(arr, elements_amnt);

    arr = InsertBinSort(arr, elements_amnt);

    cout << "After:" << endl;
    PrintArray(arr, elements_amnt);

}

//========================================================================

int  SecureUserInput()
{
    int elements_amnt = 0;

    while(elements_amnt < 1){
        char input[MAX_INPUT_SIZE] = "";
        scanf("%s", input);
        sscanf(input, "%d", &elements_amnt);

        if(elements_amnt <= 0)
            cout << "Wrong input." << endl;
    }

    return elements_amnt;
}

int* InsertBinSort(int* arr_to_sort, size_t elements_amnt)
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
        int current_elem_value = arr_to_sort[current_pos];
        int new_pos = BinSearchC(arr_to_sort, 0, current_pos, current_elem_value);

        ElemInsert(arr_to_sort, 0, current_pos, new_pos, current_elem_value);

        //Going for next element
        current_pos++;
    }

    return arr_to_sort;
}

int  BinSearchR(int* arr_sorted, int start_pos, int end_pos, int curr_elem)
{
    //Exceptions
    assert(arr_sorted != nullptr);
    assert(end_pos >= start_pos);
    assert(start_pos >= 0);
    assert(end_pos >= 0);

    if(end_pos > start_pos){
        int middle_pos = (end_pos + start_pos)/2;

        int new_pos;
        if(curr_elem < arr_sorted[middle_pos])
            new_pos = BinSearchR(arr_sorted, start_pos, middle_pos, curr_elem);
        else
            new_pos = BinSearchR(arr_sorted, middle_pos + 1, end_pos, curr_elem);

        return new_pos;
    }else /*if (end_pos <= start_pos)*/
        return start_pos;
}

int  BinSearchC(int* arr_sorted, int start_pos, int end_pos, int curr_elem)
{
    //Exceptions
    assert(arr_sorted != nullptr);
    assert(end_pos >= start_pos);
    assert(start_pos >= 0);
    assert(end_pos >= 0);

    while(start_pos != end_pos){
        int middle_pos = (start_pos + end_pos)/2;

        if(curr_elem < arr_sorted[middle_pos])
            end_pos = middle_pos;
        else
            start_pos = middle_pos + 1;
    }
    return start_pos;
}

int* FillArray(int* arr_to_fill, size_t elements_amnt, int max_elem_value)
{
    //Exceptions
    assert(arr_to_fill != nullptr);
    assert(elements_amnt >= 0);
    assert(max_elem_value > 0);

    for(int i = 0; i < elements_amnt; i++)
        arr_to_fill[i] = rand() % max_elem_value;
    return arr_to_fill;
}

void PrintArray(int* arr_to_print, size_t elements_amnt)
{
    //Exceptions
    assert(arr_to_print!= nullptr);
    assert(elements_amnt >= 0);

    for(int i = 0; i < elements_amnt; i++)
        cout << "arr[" << i << "] = " << arr_to_print[i] << endl;
}

void ElemInsert(int* arr_to_ins_in, int start_pos, int end_pos,
                int new_elem_pos, int new_elem_value)
{
    //Exceptions
    assert(arr_to_ins_in != nullptr);
    assert(start_pos >= 0);
    assert(end_pos >= 0);
    assert(end_pos >= start_pos);
    assert(new_elem_pos >= start_pos);
    assert(new_elem_pos <=  end_pos);

    for(int i = end_pos; i > new_elem_pos; i--)
        arr_to_ins_in[i] = arr_to_ins_in[i - 1];
    arr_to_ins_in[new_elem_pos] = new_elem_value;
}

