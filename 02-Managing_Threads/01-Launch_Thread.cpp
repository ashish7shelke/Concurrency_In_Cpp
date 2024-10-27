#include <iostream>
#include <thread>

void do_some_work()
{
    std::cout << "Function - do_some_work() \n";
}

void do_something()
{
    std::cout << "Function - do_something() \n";
}

void do_something_else()
{
    std::cout << "Function - do_something_else() \n";
}

class background_task
{
    public:
        void operator() () const
        {
            do_something();
            do_something_else();
        }
};

/* --------------------------------------------- */
void do_something(int i)
{
    std::cout << "Function - do_something()" << i << "\n";
}

struct func
{
    int& i;
    func(int &i_):i(i_){}
    void operator() ()
    {
        for(unsigned j = 0; j < 100; ++j)
        {
            do_something(i); // Potential access to dangling refrence
            //do_something(j);
        }
    }
};

void oops() // Thread is detached from calling function
{
    int local_variable = 5;
    func thread_function(local_variable);

    std::thread t(thread_function);

    //Try out with commenting this line to - It will terminate program
    
    t.detach(); //Dont wait for thread to finish
    //t.join();
    //New thread might be running and main function is returning 
}

/* ------------------------------------------ */
// Try/catch technique for - Waiting for thread to finish
void do_something_in_current_thread()
{
    //throw 5;
}

void oops_avoided()
{
    int local_variable = 10;
    func thread_function(local_variable);

    std::thread t(thread_function);

    try
    {
        do_something_in_current_thread();
    }
    catch(...)
    {
        std::cout << "Inside Exceptional handler \n";
        t.join();
        throw;
    }
    t.join(); // try with commenting this line
}
/* ---------------------------------- */

/* Using 'Resource Acquisition Is Initialized (RAII)' to wait for thread to finish */
class thread_guard
{
        std::thread& t;

    public:
        explicit thread_guard(std::thread& t_): t(t_)
        {}

        ~thread_guard()
        {
            if(t.joinable())
            {
                t.join();
            }
        }

    thread_guard(thread_guard const&) = delete;
    thread_guard& operator= (thread_guard const&) = delete;  
};

void thrad_guard_function()
{
    int local_variable = 15;
    func thread_function(local_variable);

    std::thread t(thread_function);
    thread_guard g(t);

    do_something_in_current_thread();
}

int main()
{
    //Case 1: Task is an ordinary void returning function without parameters
	std::thread t1(do_some_work);
	std::cout << "Case1: Before joining thread" << std::endl;
	t1.join();
	std::cout << "Case1: After joining thread" << std::endl;
	
    //Case 2: Task is an instance of class with function call operator
    background_task f;
    std::thread t2(f);
    std::cout << "Case2: Before joining thread" << std::endl;
	t2.join();
	std::cout << "Case2: After joining thread" << std::endl;    

    //Case 3: Function object
    //std::thead t3(background_task()); //This an unexpected error as t3 is declared as function instead std::thread object
    std::thread t3{background_task()};
    std::cout << "Case3: Before joining thread" << std::endl;
	t3.join();
	std::cout << "Case3: After joining thread" << std::endl;

    //Case 4: Lambda expression
    std::thread t4( [] { do_something(); do_something_else(); });
    std::cout << "Case4: Before joining thread" << std::endl;
	t4.join();
	std::cout << "Case4: After joining thread" << std::endl;    

    //Importance of joining: Thread is accessing local varialbe though function is returned

    //Try this commenting either block at a time. Dont uncooment oops() block if rnning further code
    /*
    std::cout << "Join/Detach: Before calling function oops()" << std::endl;
	oops();
	std::cout << "Join/Detach: After calling function oops()" << std::endl;*/

    /*
    std::cout << "Join/Detach: Before calling function oops_avoided()" << std::endl;
    oops_avoided(); // Waiting for thread to finish with try/catch block
	std::cout << "Join/Detach: After calling function oops_avoided()" << std::endl; */
    
    //Waiting for tread to finish using RAII
    std::cout << "Join/Detach: Before calling function thrad_guard_function()" << std::endl;
    thrad_guard_function(); // Waiting for thread to finish with try/catch block
	std::cout << "Join/Detach: After calling function thrad_guard_function()" << std::endl;

    // Running threads in background
    
	return 0;
}
