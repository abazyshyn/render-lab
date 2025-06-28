#include "pch.hpp"

#include "application/application.hpp"

using namespace Lab;

int main(int argc, char **argv)
{
// #if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
//
//     testing::InitGoogleTest(&argc, argv);
//
// #endif

    CApplication &application = CApplication::GetInstance();

    application.Run();

    return 0;
}
