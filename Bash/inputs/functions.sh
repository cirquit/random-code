#!/bin/bash

## -| how to "return" argument

myfun(){
  a="Hello World"
}

myfun
echo $a

## -| more interesting try on functions

# add_a_user(){

#   USER=$1
#   PASSWORD=$2
#   shift; shift;
#   COMMENTS=$@

#   echo "Adding user $USER"
#   echo "useradd -c "$COMMENTS" $USER"
#   echo "passwd $USER $PASSWORD"
#   echo "Added user $USER ($COMMENTS) with passwd $PASSWORD"

# }

# echo "Start of script..."
# add_a_user bob letmein Bob Holness the presenter
# add_a_user fred badpassword Fred Durst the singer
# add_a_user bilko worsepassword Sgt. Bilko the role model
# echo "End of script!"

## -| first try on functions

# function fun_a {
#   echo $1
# }

# function fun_c {
#   echo $1
# }

# function fun_b {
#   echo "Function B!"
# }

# function fun_d {
#   echo "Function D!"
# }

# # pass parameter to function A

# fun_a "Function A!"
# fun_b
# fun_c "Function C!"
# fun_d