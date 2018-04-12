# FT_SELECT - @42Born2Code

A robust file browser and manager in the terminal.

![](https://github.com/jon-finkel/ft_select/blob/master/ft_select.gif)

## About

[ft_select][2] is the third project of the Unix branch at [42][1]. The goal for this project is to learn more about event-driven programming using the termcaps library.

## Installation

`cd libft ; git submodule init ; git submodule update ; cd .. ; make`

## Running

A basic usage would involve at least one argument:

 	./ft_select argument

## Features

* If you pass a list of arguments to the program it gets displayed in your terminal.
* You can move through the list using arrows.
* One or more choices can be selected or un-selected with the `space` key. With
each selection, the cursor will automatically position itself on the next element.
* You can validate the selection with the `return` key, the list of choices will
be sent back to the shell. This allows other programs to use the output of the program as their input. i.e: rm `./ft_select file1 file2 file3`
* Dynamic search: search for a file by typing it's name. If it is found, cursor will be placed on it automatically.
* Re-organizes the display on window resize.
* Exits on `ESC` key
* Displays keybinds on `TAB` key
* Pressing the `delete` or `backspace` keys removes an element from the list.
* Press `*` to select all and `\` to unselect all.
* Colored output based on some file type (ie. directories, executables, sockets...).
* Handles interruption signals gracefully (ctrl + z, ctrl + c, kill, etc...)
* Restores the screen to what it was before clearing it.

### Final Mark

`116/100`

[1]: http://42.fr "42 Paris"
[2]: https://github.com/jon-finkel/ft_select/blob/master/project_instructions/ft_select.en.pdf "ft_select"
