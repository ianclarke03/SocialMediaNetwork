
/****************************************************************************************************************************
Title         :   Promotional.cpp
Author        :   Ian Clarke
Description   :   Implementation for the Promotional class
****************************************************************************************************************************/



#include "Promotional.hpp"
#include <regex>


/**
   Parameterized constructor.
      @param       : The name of the Promotional post (a string)
      @param       : The body of the Promotional post (a string)
      @param    : : The username of the Account that added this post (a string)
      @param       : The link of the Promotional post (a string)

     @post         : Sets the title, body, username and link (if it's a proper link otherwise "Broken Link")
                    of the Promotional to the value
                    of the parameters.
                    It will also generate the current time and store it.
*/
Promotional::Promotional(const std::string name, std::string description, std::string username, std::string link):Post(name, description, username){
    setLink(link);
};




/**
   Accessor function
   @return         : Returns the post link
*/
std::string Promotional::getLink() const{
    return link_;
}



/**
   @param    : A reference to the link that is in the format 'https://www.something.something'
               or 'http://www.something.something' with the last 'something' being at least 2 characters
   @return   : true if the link is correctly formatted, false otherwise

   @post     : If the link is not correctly formatted, store "Broken Link"
               in the link member variable, otherwise store the value of the
               parameter (Hint: see <regex>)
*/
bool Promotional::setLink(const std::string& link) {
    const std::regex pattern("((http|https)://)(www.)[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    if (regex_match(link,pattern)) {
        link_ = link;
        return true;
    }

    link_ = "Broken link";
    return false;
}

void Promotional::displayPost() {
    std::cout << '\n' << getTitle() << " at ";
    getTimeStamp();
    std::cout << getBody() << std::endl;
    std::cout << getLink() << std::endl;
}