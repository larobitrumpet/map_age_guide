# Map Age Guide

This is a command line program written in C that will tell you the age of an undated map, (assuming it's complete, labeled in English, and detailed enough). This is an adaptation of xkcd comic 1688, [Map Age Guide](https://xkcd.com/1688), which is licensed under a [Creative Commons Attribution-NonCommercial 2.5 License](https://creativecommons.org/licenses/by-nc/2.5/). The commic is shown below.
![xkcd comic 1688, Map Age Guide](https://imgs.xkcd.com/comics/map_age_guide.png)


## Build and Run

To build, all you need to do is have gcc and make installed and run `make`. To run the program, just run `make run`.


## Usage

You will be asked a series of questions. One answer will be highlighted. Press the left and right arrow keys to highlight a different answer. Once your answer is highlighted, press enter or the down arrow key to choose that answer. Press the up arrow to go back to the previous question. Press 'q' at anytime to quit.


## Previous Question Caveat

For some of the questions, there are multiple ways of getting there, but every question only "knows" about one of the ways to get there. Because of this, pressing up won't always go to the previous question you answered. For example, if you are on the question "Zaire? or: "Hong Kong (UK)"", and you press up, you will go to the question "Does the Soviet Union exist?", even if you got there from "North Korea?". This could be fixed by creating a stack, pushing questions to the stack as they are answered, and pop from the stack whenever we want to go back. However, by the time I found this problem I was well into the way I was already doing it and didn't want to change what I was doing.

## License

This program is licensed under an MIT license, which means you are free to use,copy, share,  To learn more, look at [LICENSE](LICENSE).