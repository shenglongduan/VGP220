#pragma once

//Assignment 5: Implement a templatized priority queue, using a Max Heap for operations 
//like Enqueue and Daqueue

template<typename T>
class PriorityQueue {

public:

    struct Data {
        int priority;
        T data;
    };

    PriorityQueue(Data emptyValue) {
        //TODO_1: Implement the constructor of this priority queue
        //Look to do this, look at the member variables that you have.
        //You can default initiliaze your capacity with 10 elements.
        mEmptyValue = emptyValue;
        mSize = 0;
        mCapacity = 10;
        mDataArray = new Data[10];
    }

    ~PriorityQueue() {
        //TODO_2: Implement the destructor of this priority queue
        //Remember that whatever you "new" you have to "delete"
        delete[] mDataArray;
    }

    void Enqueue(Data data) {
        //TODO_3: Implement an Enqueue method for this priority queue.
        //This enqueue should follow the same insertion method that
        //a max heap has.
        //
        //Remember:
        //Heaps Insertion: Place the element at the end of the array,
        //In a loop, check yourself against you parent.priority.
        //If yours is bigger, swap;
        if (mSize == mCapacity) {
            mCapacity *= 2;
            Data* temp = new Data[mCapacity];
            for (int i = 0; i < mSize; ++i) {
                temp[i] = mDataArray[i];
            }
            mDataArray = temp;
        }
        mDataArray[mSize] = data;
        int index = mSize;
        while (index > 0) {
            int parentIndex = GetParent(index);
            if (mDataArray[parentIndex].priority < mDataArray[index].priority) {
                swap(&(mDataArray[parentIndex]), &(mDataArray[index]));
                index = parentIndex;
            }
            else {
                break;
            }
        }
        mSize++;
    }

    Data Dequeue() {
        //TODO_4: Implement a Dequeue method for this priority queue.
        //This Dequeue should follow the same RemoveMax method that
        //a max heap has.
        //
        //Remember:
        //Heaps RemoveMax: Make the first element to receive the last
        //element from your array. After this, Heapfy.
        //If the queue is empty, return mEmptyValue
        if (mSize <= 0) {
            return mEmptyValue;
        }
        Data res = mDataArray[0];
        mDataArray[0] = mDataArray[mSize - 1];
        mSize--;
        Heapfy(0);
        return res;
    }

    int GetSize() const {
        return mSize;
    }

private:
    int GetParent(int index) const {
        return (index - 1) / 2;
    }

    int GetLeft(int index) const {
        return (index * 2) + 1;
    }

    int GetRight(int index) const {
        return (index * 2) + 2;
    }

    void swap(Data* a, Data* b) {
        Data temp = *a;
        *a = *b;
        *b = temp;
    }

    void Heapfy(int index) {
        //TODO_5: Implement Heapfy
        //
        //Remember:
        //Heapfy: In a loop, checks which one is bigger in priority between left and right. and select.
        //Then compares with it's priority. If parent priority is smaller, Swap.
        while (index < mSize) {
            int leftIndex = GetLeft(index);
            int rightIndex = GetRight(index);
            if (leftIndex < mSize && rightIndex < mSize) {
                Data left = mDataArray[leftIndex];
                Data right = mDataArray[rightIndex];
                if (left.priority >= right.priority) {
                    if (left.priority > mDataArray[index].priority) {
                        swap(&(mDataArray[index]), &(mDataArray[leftIndex]));
                        index = leftIndex;
                    }
                    else {
                        break;
                    }
                }
                else {
                    if (right.priority > mDataArray[index].priority) {
                        swap(&(mDataArray[index]), &(mDataArray[rightIndex]));
                        index = rightIndex;
                    }
                    else {
                        break;
                    }
                }
            }
            else if (leftIndex < mSize) {
                Data left = mDataArray[leftIndex];
                if (left.priority > mDataArray[index].priority) {
                    swap(&(mDataArray[index]), &(mDataArray[leftIndex]));
                    index = leftIndex;
                }
                else {
                    break;
                }
            }
            else if (rightIndex < mSize) {
                Data right = mDataArray[rightIndex];
                if (right.priority > mDataArray[index].priority) {
                    swap(&(mDataArray[index]), &(mDataArray[rightIndex]));
                    index = rightIndex;
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
    }

    Data* mDataArray;
    int mCapacity;
    int mSize;
    Data mEmptyValue;
};
#pragma once
