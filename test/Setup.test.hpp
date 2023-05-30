/// Apache License 2.0

#include <Global.test.hpp>

namespace ostk
{
namespace physics
{
namespace test
{

namespace global
{

std::string someGlobalString;

}  // namespace global

class Environment : public testing::Environment
{
   public:
    Environment(const std::string& aCommandLineArg)
        : commandLineArg_(aCommandLineArg)
    {
        if (commandLineArg_ != "")
        {
            global::someGlobalString = commandLineArg_;
        }
        else
        {
            global::someGlobalString = "World";
        }
    }

    virtual ~Environment() {}

    virtual void SetUp() {}

    virtual void TearDown() {}

   private:
    std::string commandLineArg_;
};

}  // namespace test
}  // namespace physics
}  // namespace ostk

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
