C++ standard library makes most thread management tasks relatively easy.
Everything is managed through std::thread object associated with given thread.

1) Launching a thread
2) Waiting for thread to finish or running thread in background
3) Passing addditional parameters to thread
4) Passing ownership of a thread from one std::thread object to another
5) Choosing number of threads to use and indentifying particular thread

Every C++ program has at least one thread, which is started by the C++ runtime.
Our main program can then launch additional threads that have another function as the entry point.

--------------------------------------------------------------------------------------------------
* Launching a Thread *

Case 1: Thread performs a task that is an ordinary void returning function without parameters

Case 2: Instance of an class with a function call operator to the std::thread constructor
(As, std::thread works with any callable type)

Supplied function object is copied into the storage belonging to newly created thread of executution and invoked from
there. It's therefore essential that copy behaves equivalent to the original, or result may not be as expected.

Case 3: Passing a function object to thread constructor
std::thread t(class_instace()); --> this declares that t is function taht takes single parameter (of type pointer-to-a-
function-taking-no-parameters-and-returning-a-class-instance) and returns std::thread object rather than launching a thread.

This can be avoided by an extra parentheses or new uniform initialization syntax
std::thread t( (class_instance()) );
std::thread t{class_instace()};
Here t is declared as a variable of type std::thread

Case 4: Lambda expression
-----------------------------------------------------------------------------------------------------

Waiting for threads to fininsh:

Once we started thread, it need to explicitly decide whether to wait for it or to finish. (by joining or detaching thread)

If programmer don't decide before std::thread object is detroyed, then program is terminated (std::thread destructor calls
std::terminate()).
It's therefore imperative that you ensure that thread is correctly joined or detached.

If programmer don't wait for your thread to finish, it need to ensure that the data accessed by thread is valid until
thread is finished.
---------------------------------
Running threads in background:
Calling detach() on std::thread object leaves the thread to run in the backgound, with no direct means of communicating with it.
If the thread becomes detached, it's not possible to obtain a std::thread object that refrences it, so it no longer be joined.

Detached threads truely runs in backgound; ownership and control are passed over to the C++ runtime library, which ensures that
resources associated with the thread are correctly reclaomed when the thread exits.

Detached threads are often called 'deamon threads' after UNIX concept of a deamon process.
----------------------------------
Passing arguments to a thread function:
By default passed arguments are copied into internal storage, where these can be accessed by newly created thread of execution
and then passed to the callable object or function as rvalue as if they were temporaries.





