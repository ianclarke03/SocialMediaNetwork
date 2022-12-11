/****************************************************************************************************************************
Title         :   Account.cpp
Author        :   Ian Clarke
Description   :   Implementation for Account class
****************************************************************************************************************************/


#include "Account.hpp"

#include <iostream>
#include <ctime>
using namespace std;


/**

   Default constructor.

   Sets the username and password of the Account to an empty string

   Sets the vector of posts to an empty vector

*/



Account::Account(){

  std::string username = "";
  std::string password ="";
  //posts_.clear();

}

   /**

      Parameterized constructor.

      @param username  : username of the Account

      @param password  : password of the Account


      Sets the username and password of the Account to what was passed by the user

      Sets the vector of posts to an empty vector

   */



Account::Account(std::string username, std::string password){


  this->username = username;
  this->password = password;
  //std::vector<Post> posts;


}
/**

   @param a reference to the username of the Account
   This will set the username private variable to string variable username


   */

void Account::setUsername(const std::string& username){

  this->username = username;
}

/**

   @return the username of the Account
   This method will return the username

*/
std::string Account::getUsername() const{

  return username;
}


/**

      @param a reference to the password of the Account
      This will set the password private variable to string variable password


   */
void Account::setPassword(const std::string& password){

  this->password = password;

}

/**

   @return the password of the Account
   This method will return password for the account

*/
std::string Account::getPassword() const{

  return password;
}

/**

     @param title   : A reference to the title used to generate the Post object

     @param body    : A reference to the body used to generate the Post object

     @post         : generates a Post with the given title and body and adds it to it's vector of posts

     @return       : Will return true if the Post does not have an empty title or body and the Post is successfully added to the vector

  */


  /**
        MODIFY this function to also add the Account username to the Post and then add the Post
        to its Networks feed if it is connected to one. NOTE: you will need to add this functionality
        to the network as well (see Network modifications below - you may want to create a STUB for it,
        or implement this functionality after you modified the Network.)

  */
bool Account::addPost(Post* item){ //modify

posts_.insert(item, 0);

if(accountnet != nullptr){
  accountnet -> addToFeed(item);
  return true;
  }
  
return false;
}




   /*
      @post         : Prints the vector of Posts using their display function
   */
   void Account::viewPosts(){

    Node<Post*>* currptr = posts_.getHeadPtr();
    while(currptr != nullptr){

    currptr->getItem()->displayPost();
    std::cout << "\n"; //might be unessesary
    currptr = currptr->getNext();
    }


   }




/**
      Accessor function
      @return           :   the pointer to the Network the account is in
   */



Network<Account>* Account::getNetwork() const{

  return accountnet;
}




/**
      Mutator function
      @param            :   a pointer to a Network
      @post             :   the Network pointer private member points to the input Network
   */



void Account::setNetwork(Network<Account>* net){
  accountnet = net;
}
/**
      @param            :   the username of the Account to follow
      @return           :   true if the account was successfully able to follow, false otherwise
      @post             :   adds the username to the vector of following accounts only if
                            it is affiliated to a Network AND it is not already following an account
                            with the same username.
   */

bool Account::followAccount(const std::string input_username){

  if (input_username == getUsername() || accountnet == nullptr)  {
        return false;
    }
  for (long unsigned int i = 0; i < usernames.size(); i++)
    {
        if ((usernames[i] == input_username))
        {
            return false;
        }
    }  if (accountnet->containsAccount(input_username))
        {
            usernames.push_back(input_username);
            return true;
        }
    return false;
  }



   /**
      @return           :   the vector of usernames the Account is following
   */
std::vector<std::string> Account::viewFollowing() const {

  return usernames;
}


//--------------------------------------------------------------------p4 task 2---------------------------------------------------------------------------


/*
    @param            :   Pointer to a Post object
    @param            :   The new title of the Post (or an empty string if you do not
                          want to change it)
    @param            :   The new body of the Post (or an empty string if you do not
                          want to change it)

    @post            :This function will take the Post and given the new title and body,
    update the Posts title and body as appropriate. It will also update the `timestamp_` to the current time of the update. This function should then
    update the location of the Post in its list of `posts_` to the front of the list as well as utilizing its Network pointer to do the same in the `feed_`.

    You are encouraged to create your own helper functions for this endevour.
*/
void Account::updatePost(Post* postobject, std::string title_, std::string body_) {

  if (title_ != "") {
    postobject->setTitle(title_);
  }
  if (body_ != "") {
    postobject->setBody(body_);
  }

  posts_.moveItemToTop(postobject);
  accountnet->insertBeginningFeed(postobject);

}




/*
    @param            :   A pointer to a Post
    @return           :   If the Post was successfully found and removed

    This function will remove the given Post from its list as well as from the Network's feed.
    Returns True if successfully removed, False if not. Afterwards, tell the Network to remove
    the Post as well from its feed.

    You are encouraged to create your own helper functions for this endevour.
*/
bool Account::removePost(Post* item){

  bool removed = false;
  int i = 0;
  Node<Post*>* currptr = posts_.getHeadPtr();


  while(currptr->getItem() != item){
    currptr = currptr->getNext();
    i++;
  }


  if(posts_.remove(i)){
    removed = true;
    accountnet->removeFromFeed(item); //calling helper func from network
  }

  return removed;

  //return true; //stub
}


