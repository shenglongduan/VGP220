#pragma once

#include <iostream>
#include "ltem.h"

class Inventory 
{
public:
    //COMMENT: Use more often the initialization list.
    Inventory() {
        //TODO: Implement a default constructor for the Inventory class where the max number of slots
        // is 5 and all the slots are free (They are not occupied).
        mMaxSlots = 5;
        mSlotsOccupied = 0;
        mInventory = new Item[5];
    }

    //COMMENT: Use more often the initialization list.
    Inventory(uint32_t capacity) {
        //TODO: Implement a non default constructor for the Inventory class where
        //all the slots are free (They are not occupied).
        mMaxSlots = capacity;
        mSlotsOccupied = 0;
        mInventory = new Item[capacity];

    }

    //ERROR: -1. You don't need to use this->mInventory. You should use just mInventory.
    Inventory(const Inventory& other) {
        //TODO: Implement a copy constructor for this class. Avoid shallow copy.
        mMaxSlots = other.mMaxSlots;
        mSlotsOccupied = other.mSlotsOccupied;
        mInventory = new Item[other.mMaxSlots];

        for (int i = 0; i < mSlotsOccupied; ++i) {
            this->mInventory[i] = other.mInventory[i];
        }
    }

    //ERROR: -10. You don't need to use this->mInventory. You should use just mInventory.
    //Also, in the move constructor yopu should move the other not copy it... 
    //mInventory = other.mInventory;
    //other.mInventory = nullptr;
    Inventory(Inventory&& other) {
        //TODO: Implement a move constructor for this class. Reset to a default state the other inventory.
        mMaxSlots = other.mMaxSlots;
        mSlotsOccupied = other.mSlotsOccupied;
        mInventory = new Item[other.mMaxSlots];

        for (int i = 0; i < mSlotsOccupied; ++i) {
            this->mInventory[i] = std::move(other.mInventory[i]);
        }
    }

    //ERROR: -2. Dangling pointer. Forgot to set mInventory = nullptr.
    ~Inventory() {
        //TODO: Implement a destructor for this class.
        delete[] mInventory;
    }

    //ERROR: -3. You don't need to use this->mInventory. You should use just mInventory.
    //You should check also if they are not equal. And just copy if they are not.
    //TODO: Implement a copy assignment operator
    Inventory& operator=(const Inventory& other) {
        if (this == &other) return *this;
        delete[] this->mInventory;

        mMaxSlots = other.mMaxSlots;
        mSlotsOccupied = other.mSlotsOccupied;
        mInventory = new Item[other.mMaxSlots];

        for (int i = 0; i < mSlotsOccupied; ++i) {
            this->mInventory[i] = other.mInventory[i];
        }
        return *this;
    }
    //TODO: Implement a move assignment operator

    //ERROR: -10. You don't need to use this->mInventory. You should use just mInventory.
    //Again, you are copying here and not moving.
    Inventory& operator=(Inventory&& other) noexcept {
        if (this == &other) return *this;
        delete[] this->mInventory;

        mMaxSlots = other.mMaxSlots;
        mSlotsOccupied = other.mSlotsOccupied;
        mInventory = new Item[other.mMaxSlots];

        for (int i = 0; i < mSlotsOccupied; ++i) {
            this->mInventory[i] = std::move(other.mInventory[i]);
        }
        return *this;
    }


    //ERROR: -5. Your add item is not calculating the item quantity properly.
    //Also, when you add a special case it's adding a different number of slots than the required ammount.
    //follow the correct code to check:
    //void AddItem(Item newItem)
    //{
    //    if (!isFullForItem(&newItem))
    //    {
    //        int slotIndex = SearchItemByNameLessThan50(newItem.name);
    //        //I have this Item in inventory
    //        if (slotIndex != -1)
    //        {
    //            int futureQuantity = mInventory[slotIndex].quantity + newItem.quantity;
    //            if (futureQuantity > 50)
    //            {
    //                newItem.quantity = futureQuantity - 50;
    //                mInventory[slotIndex].quantity = 50;
    //                mInventory[mSlotsOccupied] = newItem;
    //                mSlotsOccupied++;
    //                return;
    //            }

    //            mInventory[slotIndex].quantity += newItem.quantity;
    //            return;
    //        }
    //        //Inserting for the first time
    //        else
    //        {
    //            //Expanding inventory;
    //            if ((newItem.type == ItemType::Charm) && (newItem.name.compare("Expansion") == 0))
    //            {
    //                Item* temp = mInventory;
    //                mMaxSlots += 5;
    //                mInventory = new Item[mMaxSlots];
    //                for (int i = 0; i < mSlotsOccupied; ++i)
    //                {
    //                    mInventory[i] = temp[i];
    //                }
    //                delete[] temp;
    //                temp = nullptr;
    //            }

    //            //After expansion, insert.
    //            mInventory[mSlotsOccupied] = newItem;
    //            mSlotsOccupied++;
    //        }
    //    }

    //    std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
    //}

    void AddItem(Item newItem) {
        //TODO: Implement AddItem MethodThis method adds a new item to the inventory.
        //First it searches for this item to see if the item exists, and if the item exists
        //it checks the quantity, because the max quantity allowed per slot is 50.
        //So, for example, if you have 50 healing potions in your inventory, and you want to add one more, this potion
        //should occupy a new slot. Pay attention that the SearchItem function already does this quantity check for you.
        //The extra check that you should do is for the accumulated quantity. So your function should check
        //how many items this current slot has and if you add this new item quantity, how many items you will have.
        //If it's greater than 50, you should make the quantity of one slot 50 and add the remainder quantity to a new slot.
        //For example:
        //[ HP 48 ] [  ] [  ] [  ] [  ] Inventory has a HP(healing potions) with 48 as quantity and you want to add more 5 HP
        //[ HP 50 ] [HP 3] [  ] [  ] [  ] Inventory after you added 5 HP

        if (newItem.name == "Expansion") {
            Item* newArray = new Item[mMaxSlots + 3];
            for (int i = 0; i < mSlotsOccupied; ++i) {
                newArray[i] = std::move(mInventory[i]);
            }
            delete[] mInventory;
            mInventory = newArray;
            mMaxSlots += 3;

            std::cout << "adding 5 more empty slots" << std::endl;
            return;
        }

        bool foundSame = false;
        for (int i = 0; i < mSlotsOccupied; ++i) {
            if (mInventory[i].name == newItem.name && mInventory[i].quantity < 50) {
                foundSame = true;
            }
        }

        //If the Inventory is full, return a message to the user that the inventory is full and the items will be discarted.
        //Use the method IsFullForItem;
        if (!foundSame && mSlotsOccupied) {
            std::cout << "the inventory is full and the items will be discarted" << std::endl;
            return;
        }

        //If after you insert the item your inventory becomes full for the remainder, Print a message to the user with how many
        //items will be discarted;

        std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";

        for (int i = 0; i < mSlotsOccupied; ++i) {
            if (mInventory[i].name == newItem.name && mInventory[i].quantity < 50) {
                uint32_t r = 50 - mInventory[i].quantity;
                if (r >= newItem.quantity) {
                    mInventory[i].quantity += newItem.quantity;
                    newItem.quantity = 0;
                }
            }
        }
        while (newItem.quantity > 0 && mSlotsOccupied < mMaxSlots) {
            if (newItem.quantity <= 50) {
                mInventory[mSlotsOccupied].name = newItem.name;
                mInventory[mSlotsOccupied].type = newItem.type;
                mInventory[mSlotsOccupied].quantity = newItem.quantity;
                mSlotsOccupied++;
                newItem.quantity = 0;
            }
            else {
                mInventory[mSlotsOccupied].quantity = 50;
                mInventory[mSlotsOccupied].name = newItem.name;
                mInventory[mSlotsOccupied].type = newItem.type;
                mInventory[mSlotsOccupied].quantity = newItem.quantity;
                mSlotsOccupied++;
                newItem.quantity -= 50;
            }
        }

        if (newItem.quantity > 0) {
            std::cout << newItem.quantity << " items will be discarted" << std::endl;
            return;
        }

        //SPECIAL CASE: If the user adds an item of type charm with the name "Expansion" your inventory
        //should expand adding 5 more empty slots for the user.
    }

    //ERROR -5: RemoveItem is simpler than this. Also your remove item is damaging the main data structure.
    //After you remove, you can't add anything else. A good example of remove item:
    //void RemoveItem(std::string itemName, int quantity)
    //{
    //    bool isExpansion = itemName.compare("Expansion") == 0;
    //    if (mSlotsOccupied != 0)
    //    {
    //        int slotIndex = SearchItemByName(itemName);
    //        if (slotIndex == -1)
    //        {
    //            std::cout << "Item not found.\n";
    //            return;
    //        }

    //        //Remove whole item.
    //        if (quantity >= mInventory[slotIndex].quantity)
    //        {
    //            for (int i = slotIndex; i < mSlotsOccupied - 1; ++i)
    //            {
    //                mInventory[i] = mInventory[i + 1];
    //            }
    //            mSlotsOccupied--;
    //            //Special case
    //            if (isExpansion && (SearchItemByName(itemName) == -1))
    //            {
    //                mMaxSlots -= 5;
    //            }
    //        }
    //        //Remove some quantity
    //        else
    //        {
    //            mInventory[slotIndex].quantity -= quantity;
    //        }
    //    }

    //    std::cout << "Removing " << quantity << " " << itemName << " from inventory." << "\n";
    //}

    void RemoveItem(std::string itemName, int quantity) {
        //TODO: Implement RemoveItem method
        //RemoveItem, should remove a quantity from the slot with the item. If the whole slot
        //is empty, you should shift all the other items of the inventory;
        //If you try to remove more than what you have in one slot, just make the slot empty.
        //For example:
        //[ HP 50 ] [ HP 30 ] [  ] [  ] [  ] //You tried to remove 80 HP from the inventory
        //[ HP 30 ] [  ] [  ] [  ] [  ] //You just remove from one slot.


        if (itemName == "Expansion") {
            if (mMaxSlots > 5) {
                Item* newArray = new Item[mMaxSlots - 5];
                for (int i = 0; i < mSlotsOccupied; ++i) {
                    newArray[i] = std::move(mInventory[i]);
                }
                delete[] mInventory;
                mInventory = newArray;
                mMaxSlots -= 5;
                mSlotsOccupied = std::max(mMaxSlots, mSlotsOccupied);

                std::cout << "remove 5 more slots" << std::endl;
            }
            return;
        }

        int removed = 0;
        for (int i = (int)mSlotsOccupied - 1; i >= 0; --i) {
            if (mInventory[i].name == itemName) {
                if (mInventory[i].quantity >= quantity) {
                    mInventory[i].quantity -= quantity;
                    removed += quantity;
                    quantity = 0;
                    break;
                }
                else {
                    quantity -= mInventory[i].quantity;
                    removed += mInventory[i].quantity;
                    mInventory[i].quantity = 0;
                }
            }
        }

        int newsize = 0;
        for (int i = 0; i < mSlotsOccupied; ++i) {
            if (mInventory[i].quantity != 0) {
                mInventory[newsize++] = mInventory[i];
            }
        }
        mSlotsOccupied = newsize;

        std::cout << "Removing " << removed << " " << itemName << " from inventory." << "\n";

        //SPECIAL CASE: If the user removes the charm Expansion from the inventory, your inventory
        //should reduce the number of slots in 5, discarting all the items from the removed slots.
    }

    //COMMENT: You should remove an Item using the RemoveItem function. 
    Item* UseItem(std::string itemName) {
        // TODO: Search for the item and if it exists, return this item and remove one from the inventory
        // otherwise, return nullptr.
        // The user is just allowed to use the Types: Posion and Utility.
        for (int i = 0; i < mSlotsOccupied; ++i) {
            if (mInventory[i].name == itemName) {
                if (mInventory[i].type == ItemType::Potion && mInventory[i].type == ItemType::Utility) {
                    mInventory[i].quantity--;
                    std::cout << "Using " << itemName << "\n";
                    return &mInventory[i];
                }
            }
        }
        return nullptr;

    }

private:
    //Array of Items
    Item* mInventory;
    //This variable tracks the capacity of the inventory
    uint32_t mMaxSlots;
    //This variable tracks how many slots are occupied.
    uint32_t mSlotsOccupied;


    //This method seaches for the item inside the Inventory and if it finds the item with less than
    //50 as quantity, it returns the index of the item inside the inventory array, otherwise, returns -1.
    int SearchItemByNameLessThan50(std::string target) const {
        int index = -1;
        for (int i = 0; i < mSlotsOccupied; i++) {
            if (target.compare(mInventory[i].name) == 0 && mInventory[i].quantity < 50) {
                index = i;
                break;
            }
        }

        return index;
    }

    //Returns the index of the item if it exists and -1 if it doesn't.
    int SearchItemByName(std::string target) const {
        int index = -1;
        for (int i = 0; i < mSlotsOccupied; i++) {
            if (target.compare(mInventory[i].name) == 0) {
                index = i;
                break;
            }
        }
        return index;
    }

    //If you don't have the item inside the inventory and all the slots are occupied - True
    //If you have the item in the inventory with max capacity and all the other slots are occupied - True
    //Otherwise - False.
    bool isFullForItem(Item* item) const {
        int index = SearchItemByNameLessThan50((*item).name);
        if (index == -1 && mSlotsOccupied == mMaxSlots) {
            return true;
        }
        if (index != -1 && mInventory[index].quantity >= 50 && mSlotsOccupied == mMaxSlots) {
            return true;
        }
        return false;
    }
};
