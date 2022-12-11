/****************************************************************************************************************************
Title         :   Network.hpp
Author        :   Ian Clarke
Description   :   header/interface for Network class
****************************************************************************************************************************/


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Post.hpp"
#include "LinkedList.hpp"
#include "Account.hpp"
#include "Node.hpp"


#ifndef NETWORKH
#define NETWORKH

template <class T>
class Network
{
private:

    static const int DEFAULT_CAPACITY = 200;
    T* items_[DEFAULT_CAPACITY];
    int item_count_;
    int value;
    LinkedList <Post*> feed_;
    int getIndexOf(const std::string& username_1);

/*- An array (with a capacity of 200) that stores POINTERS to the template items.

   - A count of the current number of accounts in the network.

   - A vector of Posts: the Network's feed where all posts posted by accounts in the network will be stored.

*/
/*
   private function
   @param            :   string - the username of item we want the index of
   @return           :   int - the index of the item, -1 if the account is not found
*/


  public:
    Network();     // Default constructor.
    int getSizeOfNetwork()const; //size getter
    bool isEmpty()const; //empties function
    bool addAccount(T* new_entry); //a POINTER to the item that will be added to the Network
    bool removeAccount(const T* an_entry);//removes
    void clear();//emmpties bag
    bool containsAccount(const T* an_entry);//@param  :   a POINTER to the item to find
    bool containsAccount(const std::string input_username);//helper fuction
    void populateNetwork(const std::string input);//Mutator function
    void operator-=(Network<T> other); //   Mutator function
    void printFeedForAccount(const T& rhs); //  Accessor function
    bool authenticateFollow(T& lhs, std::string txt) const; //authenticateFollow
    bool addToFeed( Post * const item); //      Mutator function //takes a pointer now
    /*
    @param            :   A string (word or phrase, case-sensitive) passed by reference
    @return           :   The number of items removed from the list

    @post              :  Any Post that contains the provided word or phrase in it's title,
                          body or both is removed from the Network's `feed_` as well as
                          the Account's `posts_`.

    You are encouraged to create your own helper functions for this endeavour.
    */
   int removeIfContains(std::string &input);

   //helper function for Account::removePost function
   bool removeFromFeed(Post* item);

   //helper func for Account::updatePost func
   void insertBeginningFeed(Post* apost);


   template <typename Comparator>
    LinkedList<Post*> bSortByUsername(Comparator compare, int* counter);


};

#include "Network.cpp"
#endif



