/****************************************************************************************************************************
Title         :   Network.cpp
Author        :   Ian Clarke
Description   :   Implementation for Network class
****************************************************************************************************************************/



#include "LinkedList.hpp"
#include <iostream>
#include <string>
#include "Network.hpp"
#include "Account.hpp"
#include <fstream>
#include <sstream>
#include <algorithm> 



/*
   private function
   @param            :   string - the username of item we want the index of
   @return           :   int - the index of the item, -1 if the account is not found
*/

template <class T>
int Network<T>::getIndexOf(const std::string& username_1){
  for (int i = 0; i < item_count_; i++){
    if (items_[i]->getUsername() == username_1){
      return i;
    }
  }
  return -1;
}


/**
     Default constructor.

     Initializes private variables to default initial values.
  */

template <class T>
Network<T>::Network() : item_count_{0} {

}
// this helper function for the strings that are not T*
template<class T>
bool Network<T>::containsAccount(const std::string input_username)
{
    return getIndexOf(input_username) > -1;
}


/**
      Accessor function
      @return           : int -  the current size of the network (number of items in the array)
   */
template <class T>
int Network<T>::getSizeOfNetwork() const{
  return item_count_;
}
/**
      @return           : bool -  true if the bag is empty, false otherwise
   */
template <class T>
bool Network<T>::isEmpty() const{
return item_count_ == 0;
}

   /**
      @param            : a POINTER to the item that will be added to the Network
      @return           : bool- true  if the item was successfully added, false otherwise
      @post             : stores a pointer to the item, if there is room. This is a network specific function,
                          it has an additional constraint: the item will be added only if no other item in the network
                          has the same username (usernames are considered unique)
                          REMEMBER WE ARE STORING POINTERS TO ITEMS, NOT ITEMS.
                          Finally, the Account being added to the network will update it's private member to point to this network
                          (see Account class modifications below, you may come back and implement this feature after
                          you work on Task 2, but don't forget!!!).
                          NOTE: every object in C++ has access to a pointer to itself called `this`, thus the nework can pass `this` pointer to the account!
   */
template <class T>
bool Network<T>::addAccount(T* new_entry) //fix
{

  bool has = (item_count_ < DEFAULT_CAPACITY);
	if (has && !containsAccount(new_entry))

	{
	items_[item_count_] = new_entry;
  item_count_++;
  new_entry -> setNetwork(this);
  return true;

	}  // end if()
  return false;

}


   /**
      Mutator function
      @post             :   Empties the bag/network
   */


template <class T>
void Network<T>::clear(){
item_count_ = 0;
}


/**
      @param            :   a POINTER to the item to find
      @return           :   true if the item was successfully found, false otherwise
   */


template <class T>
bool Network<T>::containsAccount(const T* an_entry){
  return getIndexOf(an_entry->getUsername()) != -1;
}
/**
    Mutator function
    @param            :   a POINTER to the item that will be removed from Network
    @return           :   true if if the item was successfully removed, false otherwise
    @post             :   updates the bag/network to remove the pointer, if a pointer to that item was found.
 */
template <class T>
bool Network<T>::removeAccount(const T* an_entry){
  int found_index = getIndexOf(an_entry->getUsername());
	bool can_remove = !isEmpty() && (found_index > -1);
	if (can_remove)
	{
		item_count_--;
		items_[found_index] = items_[item_count_];
	}
  return can_remove;


}
/**
   Mutator function
   @param            :   the name of an input file
   @pre              :   The format of the text file is as follows:
                         username password
                         username password
                         ;

                         where ';' signals the end of the file. Check the provided example (accounts.txt).

   @post             :   Reads every line in the input file, creates an Account from that information and
                         adds the Account to the network. If a line of input is missing some required information,
                         it prints out "Improper Format" and terminates.
                         Keep in mind that, although the input will always be an Account, the Network class is
                         a template, thus it will store a pointer to a generic type. It will do so by creating a new
                         dynamic object of type ItemType but passing the account information (username and password)
                         as to the Account constructor. This is a bit hacky, but it will work for our Network.


*/



/**
   Mutator function
   @param            :   the name of an input file
   @pre              :   The format of the text file is as follows:
                         username password
                         username password
                         ;

                         where ';' signals the end of the file. Check the provided example (accounts.txt).

   @post             :   Reads every line in the input file, creates an Account from that information and
                         adds the Account to the network. If a line of input is missing some required information,
                         it prints out "Improper Format" and terminates.

*/
template <class T>
void Network<T>::populateNetwork(const std::string input){
    std::fstream fin;
    fin.open(input, std::ios::in);
    std::string usr = "";
    std::string pswd = "";
    std::string line;
    std::string word;
    while (std::getline(fin, line)){
        if(line == ";") {
            break;
        }
        std::stringstream s(line);
        s >> usr;
        s >> pswd;
        if(usr == "" || pswd == "") {
            std::cout << "Improper format" << std::endl;
            break;
        }
        T* new_entry = new T(usr,pswd);
        bool is_added = addAccount(new_entry);
        if(!is_added) {
            std::cout << "Error when adding account" << std::endl;
            break;
        }
        usr = "";
        pswd = "";
    }
    fin.close();
}


/**
   Mutator function
   @param            :   a reference to another Network

   @post             :  Removes from the Network any items that also appear in the other Network.
                        In other words, removes elements from the network on the left of the operator that
                        are also found in the network on the right of the operator.
   Why is this useful? For example, given a network of known bot accounts, remove all bots from this Network.
*/

template <class T>
void Network<T>::operator-=(Network<T> other)
{

      int count = 0;
      while (count < this->getSizeOfNetwork()) {
          if(other.containsAccount(items_[count])) {
              removeAccount(items_[count]);
              count--;
          }
          count++;
      }



  }

  /**
       Accessor function
       @param            :   a reference to the item whose feed will be displayed
       @post             :   prints the feed of the given account by checking who they are following
                             and displaying all the posts from the feed that were made by those accounts.
                             Keep in mind that the Network parameters are general template types
                             in this project rather than accounts, although this functionality is
                             specific to accounts.
    */

template <class T>
void Network<T>::printFeedForAccount(const T& rhs)
{ {
  for (long unsigned int i = 0; i < rhs.viewFollowing().size(); i++)
    {
        int stats = getIndexOf(rhs.viewFollowing()[i]);
        if (stats >= 0){
          items_[stats]->viewPosts();
            }
        }  }}




   /**
      @param            :   a reference to an item (account) and the username of the account
                            it wants to follow
      @return           :   true if the item was authorized to follow, false otherwise

      @post             :   the referenced Account follows another account with the username
                            specified by the second argument if they both exist in the network
   */
template <class T>
bool Network<T>::authenticateFollow(T& lhs, std::string txt) const{

  return lhs.followAccount(txt);

}


   /**
      Mutator function
      @param            :   a reference to a Post be added to the feed
      @return           :   returns true if the Post was successfully added to the feed, false otherwise
      @post             :   Adds the post to its feed only if the Post was created by an Account
                            in this Network.
   */
template <class T>
bool Network<T>::addToFeed( Post* const item){

    if(getIndexOf(item->getUsername()) > -1){
      feed_.insert(item, 0);
      return true;
    }
    return false;

}



/*
    @param            :   A string (word or phrase, case-sensitive) passed by reference
    @return           :   The number of items removed from the list

    @post              :  Any Post that contains the provided word or phrase in it's title,
                          body or both is removed from the Network's `feed_` as well as
                          the Account's `posts_`.

    You are encouraged to create your own helper functions for this endeavour.
*/



template<class T>
int Network<T>::removeIfContains(std::string &input){

  int rmcount = 0;
  int index = 0;
  Node<Post*>* currptr = feed_.getHeadPtr();
  std::string t = currptr->getItem()->getTitle();
  std::string b = currptr->getItem()->getBody();


  while(currptr != nullptr){
    if(  (t).find(input) != std::string::npos || (b).find(input) != std::string::npos   ){
      feed_.remove(getIndexOf(input));
      rmcount++;
      index++;
    }
    currptr = currptr->getNext();
    if(currptr != nullptr){
    t = currptr->getItem()->getTitle();
    b = currptr->getItem()->getBody();
    }
    else{
    t = "stub";
    b = "stub";
    }

  }
  return rmcount;


}


//helper function for Account::removePost function

template<class T>
bool Network<T>::removeFromFeed(Post* item){

  Node<Post*>* currptr = feed_.getHeadPtr();
  bool removed;
  int i = 0;

  while(currptr->getItem() != item){
    currptr = currptr->getNext();
    i++;
  }

  if(feed_.remove(i)){
    removed = true;
  }
  else
    removed = false;

  return removed;

}


template<class T>
void Network<T>::insertBeginningFeed(Post* apost){
  feed_.moveItemToTop(apost);
}


template <typename ItemType>
template <typename Comparator>
LinkedList<Post*> Network<ItemType>::bSortByUsername(Comparator compare, int* counter){
    return feed_;
}
