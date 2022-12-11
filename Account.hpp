/****************************************************************************************************************************
Title         :   Account.hpp
Author        :   Ian Clarke
Description   :   header/interface for Account class
****************************************************************************************************************************/


#pragma once
#include "Network.hpp"
#include <string>
#include <ctime>
#include "Post.hpp"
#include "LinkedList.hpp"
#include "Node.hpp"
#include <vector>
#include <algorithm>



class Account{

private:
  std::string username;
  std::string password;
  LinkedList<Post*> posts_;
  std::vector<std::string> usernames;
  Network<Account>* accountnet = nullptr;

  /* The account username (a string)

   The account password (a string)

   A vector of Post objects that stores all the Posts posted by this account*/

 public:



    Account(); //   Default constructor.
    Account(std::string username, std::string password);//   Parameterized constructor.
    void setUsername(const std::string& username);//setter
    std::string getUsername() const;//getter
    void setPassword(const std::string& password);//setter
    std::string getPassword() const;//getter
    bool addPost( Post* item);//addpost
    void viewPosts();//  @post : Prints the vector of Posts using their display function
    void setNetwork(Network<Account>* net); //    Mutator function
    bool followAccount(const std::string input_username); //follows
    std::vector<std::string> viewFollowing() const; //      @return :   the vector of usernames the Account is following
    Network<Account>* getNetwork() const; //    Accessor function

    //p4 task 2
    void updatePost(Post* apost, std::string newtitle, std::string newbody);

    bool removePost(Post* item);



};






