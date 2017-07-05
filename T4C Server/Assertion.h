// Implements the Contract pattern for C++

#include <stdexcept>

namespace vir{
    // Assertion handler. Actual code hidden from interface for easy update.
    class Assertion;
    class AssertionImp{
    private:
        // Only allow assertions to get assertion handlers.
        friend Assertion;

        static AssertionImp *GetDefaultImp();
    
    protected:
        virtual void HandlePrecondition() = 0;
        virtual void HandlePostcondition() = 0;
    };

    // This is the assertion class as defined by the contract pattern.
    class Assertion{
    public:
        // Called at the beginning of a function which requires
        // values for parameters.
        // You can supply a special handler object derived from AssertionImp
        // to handle a particular assertion case.
        static void Require( bool expr, AssertionImp *specialHandler = NULL ){
            if( !expr ){
                if( specialHandler != NULL ){
                    specialHandler->HandlePrecondition();
                }else{
                    AssertionImp::GetDefaultImp()->HandlePrecondition();
                }
            }
        }
        // Called at the end of a function, or as the invariant assertion,
        // to ensure the stability of an object after the function ends.
        // You can supply a special handler object derived from AssertionImp
        // to handle a particular assertion case.
        static void Ensure( bool expr, AssertionImp *specialHandler = NULL ){
            if( !expr ){
                if( specialHandler != NULL ){
                    specialHandler->HandlePostcondition();
                }else{
                    AssertionImp::GetDefaultImp()->HandlePostcondition();
                }
            }
        }
    };

};