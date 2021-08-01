
/*TODO: think about these things for multithreading.

create an interface(IQueuableCommand) which has a function ExcuteCommand().
Then put whatever data you need into it and store it in the queue.
Then the queue would call its ExecuteCommand() function instead of having a switch statement.
In the case of lambdas you'd have a QueuableCommand contructor take an std::function that would then get called when ExecuteCommand() is called.
That's how I would begin to approach it.

vector or a map of some sort with function pointers and forwarded arguments
or just using a lambda to wrap the function call and everything you need to
do in the lambda, so that you just have a queue command function that takes in the
type of command and the lambda and executes all of a given command type together

Just create the command type and submit it.
You could combine the two approaches by having the interface have a GetCommandType() function that could be used within the QueueCommand() function
to sort the commands into a map, which could then call the ExecuteCommand() functions of each type as well.

*/

/*

TODO: Start rendering using opengl
TODO: Start rendering using vulkan
TODO: Start networking stuff
TODO: Start physics engine
TODO: Start on OS agnostic realtime audio
TODO: Make the trigonometric functions arcsin() arccos() arctan()

*/