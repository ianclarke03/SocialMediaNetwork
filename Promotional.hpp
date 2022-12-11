
/****************************************************************************************************************************
Title         :   Promotional.hpp
Author        :   Ian Clarke
Description   :   Header/Implementation for the Promotional class
****************************************************************************************************************************/




#ifndef PROMOTIONAL_
#define PROMOTIONAL_

#include "Post.hpp"
#include <string>
#include <iostream>
#include <regex>


class Promotional :public Post {
    public:

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
        Promotional(std::string name, std::string description, std::string username, std::string link);



        /**
           Accessor function
           @return         : Returns the post link
        */
        std::string getLink() const;




        /**
           @param    : A reference to the link that is in the format 'https://www.something.something'
                       or 'http://www.something.something' with the last 'something' being at least 2 characters
           @return   : true if the link is correctly formatted, false otherwise

           @post     : If the link is not correctly formatted, store "Broken Link"
                       in the link member variable, otherwise store the value of the
                       parameter (Hint: see <regex>)
        */
        bool setLink(const std::string& link); //checks if link is valid using regex





        /**
           @post      : displays the entire Promotional post (example):
                       \n
                       {post_title_} at {time_stamp_}:
                       {post_body_}
                       \n
                       {link}
                       \n
        */
        virtual void displayPost() override;

    private:
        std::string link_;


}; //end Promotional
#endif
