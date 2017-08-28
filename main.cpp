#include <iostream>
#include <cstdio>
#include <assert.h>
#include <string>

#define MAX_INPUT_SIZE 10

using namespace std;
/// Gets User's input, checks it and returns integer.
/**
    Gets string and interpretes it as an integer.
    Asks User for imput untill he makes it correct.
*/
int  SecureUserInput();

/// Insert-sort that uses BinSearch in it.
/**
    Faster version of Insert-Sort.
    Uses BinSearch instead of brute force.

    \param [in, out] arr_to_sort Array that is going to be sorted.
    \param [in] elements_amnt Amount of elements in array.
*/
int* InsertBinSort(int* arr_to_sort, size_t elements_amnt);

/// Recurrent BinSearch.
/**
    \param [in, out] arr_sorted Sorted array where you want to place new element.
    \param [in] start_pos First position of search area.
    \param [in] end_pos Last position of search area.
    \param [in] curr_elem Value of element you want to place in.
*/
int  BinSearchR(int* arr_sorted, int start_pos, int end_pos, int curr_elem);

/// Cyclic BinSearch.
/**
    \param [in, out] arr_sorted Sorted array where you want to place new element.
    \param [in] start_pos First position of search area.
    \param [in] end_pos Last position of search area.
    \param [in] curr_elem Value of element you want to place in.
*/
int  BinSearchC(int* arr_sorted, int start_pos, int end_pos, int curr_elem);

/// Fills array with random numbers.
/**
    Fills array with random numbers, that are less than max_elem_value.

    \param [in, out] arr_to_fill Array to be filled.
    \param [in] elements_amnt Amount of elements in array.
    \param [in] max_elem_value Max size of element in array. 99 by default.
*/
int* FillArray(int* arr_to_fill, size_t elements_amnt, int max_elem_value = 100);

/// Prints array.
/**
    \param [in] arr_to_print Array that is going to be printed.
    \param [in] elements_amnt Amount of elements in array.
    \param [in] name Name of the array.
*/
void PrintArray(int* arr_to_print, size_t elements_amnt, string name = "arr");

/// Inserts element in array.
/**
    Places element between start_pos and end_pos.

    \param [in, out] arr_to_ins_in Array where new element inserts
    \param [in] start_pos First position of insert area.
    \param [in] end_pos Last position of insert area.
    \param [in] new_elem_pos New element's position.
    \param [in] new_elem_value Value of element to insert.
*/
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

    int* arr = nullptr;
    try{
        arr = new int [elements_amnt];
    }
    catch (bad_alloc){
        cout << "main.cpp (89) Can not allocate " << elements_amnt << " bytes for array." << endl;
        return -1;
    }

    arr = FillArray(arr, elements_amnt);

    cout << "Before:" << endl;
    PrintArray(arr, elements_amnt);

    arr = InsertBinSort(arr, elements_amnt);

    cout << "After:" << endl;
    PrintArray(arr, elements_amnt);

    //Preventing memory leak
    delete [] arr;
    arr = nullptr;

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
    assert(max_elem_value > 0);

    for(int i = 0; i < elements_amnt; i++)
        arr_to_fill[i] = rand() % max_elem_value;
    return arr_to_fill;
}

void PrintArray(int* arr_to_print, size_t elements_amnt, string name)
{
    //Exceptions
    assert(arr_to_print!= nullptr);

    for(int i = 0; i < elements_amnt; i++)
        cout << name << "[" << i << "]\t=  " << arr_to_print[i] << endl;
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

