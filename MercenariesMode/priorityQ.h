#include <vector>
#include <unordered_map>
#include <cstdlib>

template <class t1, class t2>
class priorityQ
{
public:
  /*
priorityQ:
- Option 1: Have index 1 as root, then default constructor must be able to resize the heap array by 1 element

   */
    priorityQ(); // Default Constructor (index 1 = root, index 0 = throwaway element).

    /*
             push_back:
             - Create some temporary "priorityType" object,
assign it parameter (t1&) into key field and parameter (t2&) into priority field,
             - Then push the object to the back of the heap array, and call "bubbleUp"() function
from that last index that we just pushed_back to.
     */
    void push_back(const t1&, const t2&); // Passing in the key and priority

    /*
             pop_front:
             - Take the last element of the heap array, overwrite the root with the last element,
do a pop_back from heapArray and "bubbleDown"() function from index 1
     */
    void pop_front();


    void increaseKey(const t1&, const t2&);
    t2 get_front_priority() const; // Return the root element's priority field
    t1 get_front_key() const;     // Return root element's key field
    bool isEmpty() const;        // If bool is empty, return true if priority queue is empty and false otherwise

    // Private Members
private:
	struct priorityType // Each element in heapArray is of type priorityType
    {
          // priorityType contains the following members:
        t1 key; // A string (Mercenary name)
        t2 priority; // The struct (MercType)
    };

    void bubbleUp(std::size_t);
    void bubbleDown(std::size_t);

/*
   - heapArray is the array that maintains Max or Min Heap (Max heap is the best for this program)
 */
    std::vector<priorityType> heapArray; // Each element in heapArray is of type priorityType
/*
  - unordered_map (increase and decrease key)
 */
    std::unordered_map<t1, std::size_t> itemToPQ;
};

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ()
{
    // Start the root at index 1 (making index 0 a throwaway/dummy element)
    heapArray.resize(1);

}

template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& priority)
{
    // Create a priorityType object
    priorityType newMercenary = {key, priority}; // Initialize the passed in key & priority to new object
    // Append newMercenary object to heapArray
    heapArray.push_back(newMercenary);
    // Map key to index by inserting/updating to itemToPQ map
    itemToPQ[key] = heapArray.size() - 1;
    // Call bubbleUp to maintain (max-heap) property starting from last index upward
    bubbleUp(heapArray.size() - 1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front() {

    //  Map key to index by updating to itemToPQ map
    itemToPQ.erase(heapArray[1].key);  // Get the mercenary's name at index 1 of heapArray (root) and erase them from map
    // Overwrite the root (index 1) with the last element in the heapArray
    heapArray[1] = heapArray[heapArray.size() - 1]; // Dereference index to assign priortyType object to root (index 1)
    // Remove the last element
    heapArray.pop_back();
    // Update the new Mercenary as index 1 in map
    itemToPQ[heapArray[1].key] = 1;
    // Call bubbleDown to maintain (max-heap) property starting from index 1 downward
    bubbleDown(1);

}

template <class t1, class t2>
void priorityQ<t1, t2>::increaseKey(const t1& key, const t2& priority)
{
    // Locate the element: Find the index of the mercenary in heapArray using itemToPQ map
    std::size_t index = itemToPQ[key]; // Retrieve index
    // Update the priority (scores) by adding the new priority to it (new score)
    heapArray[index].priority += priority; // "+=" overloaded to add onto score
    // Call bubbleUp starting from the index
    bubbleUp(index);

}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
    // Return the top priority (mercType object) of the root of the heapArray
    return heapArray[1].priority;

}

template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
    // Return the top key (mercenary name) of the root of the heapArray
    return heapArray[1].key;
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const {
    // Determine whether the heapArray is empty or not
    if (heapArray.size() == 1) { // Index 0 is dummy element
        return true;

    } else {
        return false;

    }
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index) {
    // Calculate the parent's index
    std::size_t parentIndex = index / 2;
    // Check that we haven't reached root
    if(index != 1){
    // Check if the current element's priority is higher that it's parent (continue process until we hit root OR parent is larger)
    if (heapArray[index].priority > heapArray[parentIndex].priority) { // ">" overloaded for comparison of priorities
        std::swap(heapArray[index], heapArray[parentIndex]); // Use built-in swap function

        // After swap, swap the items in itemsToPQ
        itemToPQ[heapArray[index].key] = index;
        itemToPQ[heapArray[parentIndex].key] = parentIndex;

        // Recursively call bubbleUp until element is in correct position
        bubbleUp(parentIndex);
    }

    }
    // Once root is reached or parent > child, terminate function
}


template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
    // Calculate left & right child index
    std::size_t left_childIndex = index * 2;
    std::size_t right_childIndex = (index * 2) + 1;

    // Determine which child has higher priority
    std::size_t higherChildIndex = left_childIndex;
    if(right_childIndex < heapArray.size()) {
        if(heapArray[right_childIndex].priority > heapArray[left_childIndex].priority) {
            higherChildIndex = right_childIndex;
        }
    } else {
        if(left_childIndex >= heapArray.size()) {
            // Leaf Node: If no children exist, terminate function (recursion stops)
            return;
        }
    }

    // Once higher priority child is determined, compare current priority with higher priority child
    // If child's priority > root, swap
    if(heapArray[higherChildIndex].priority > heapArray[index].priority) {
        std::swap(heapArray[index], heapArray[higherChildIndex]);

        // After swap, swap the items in itemsToPQ
        itemToPQ[heapArray[index].key] = index;
        itemToPQ[heapArray[higherChildIndex].key] = higherChildIndex;

        // Recursively call until we hit leaf or both children are < parent
        bubbleDown(higherChildIndex);
    }
}