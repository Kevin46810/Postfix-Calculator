Goal: create a postfix calculator that accepts user input with exception handling

Inputs and Outputs:

-       P -> prints the top of the stack
-       N -> prints top of stack and deletes it
-       F -> prints stack contents with a new line made for each item
-       C -> deletes all contents of the stack
-       D -> copies the top of the stack and pushes it
-       R -> switches the positions of the top two items in the stack
-       + -> pops the top two items, adds them, and pushes the sum
-       - -> pops the top two items, subtracts them (2nd popped – 1st popped), and pushes the difference
-       * -> pops the top two items, multiplies them, and pushes the product
-       / -> pops the top two items, divides them, and pushes the quotient
-       % -> pops the top two items, does a 2nd popped % 1st popped operation, and pushes the result
-       (integer) -> pushes the entered integer into the stack.  The end of an integer is indicated by a white space
-       _ -> Must be to the left of an integer.  It makes said integer negative by performing int-(int * 2)
-       The program may also print exception statements

Classes Used:

-       Underflow -> throws an exception when an operation is being performed on either an empty stack or on an illegal pop 
-       DivisionByZero -> throws an exception when the user attempts to divide by 0
-       DataError -> throws an exception for invalid input
-       Overflow -> throws an exception for when the stack is full
-       Stack -> a data structure that allows its most recently added item to be removed first (push(), pop(), makeEmpty(), top(), )

                                                                        Algorithm

        This algorithm uses a do-while (cin) loop that ends when the user presses CTRL-D to end the input.   Once the input is made, the program either enters the ConvertToInt function, which pushes the item onto the stack as an int if the input is an integer, or the switch statement, where the rest of the functions are for the inputs listed above.  An input string is used so that the user’s input can be read from a getline function.  The program stores each integer in a stack.  

If there is an invalid input the program responds in one of two different ways.  If the user types in an unknown command, the program informs the user of this and does nothing else.  If the user violates the postfix order with operands and/or operators, the program clears the stack and keeps running.  

If an empty stack is getting deleted, the Underflow exception is thrown.  If the user attempts to add to a full stack, the Overflow exception gets thrown.  The program continues to run in both cases.

Finally, in the cases of the second operand being 0 in a division or modulo problem, the program does not perform this operation and informs the user that they have a division by zero error instead.  The stack remains unchanged and the program continues to run.
