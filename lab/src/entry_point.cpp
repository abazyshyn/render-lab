// ██████╗ ███████╗███╗   ██╗██████╗ ███████╗██████╗ ██╗      █████╗ ██████╗
// ██╔══██╗██╔════╝████╗  ██║██╔══██╗██╔════╝██╔══██╗██║     ██╔══██╗██╔══██╗
// ██████╔╝█████╗  ██╔██╗ ██║██║  ██║█████╗  ██████╔╝██║     ███████║██████╔╝
// ██╔══██╗██╔══╝  ██║╚██╗██║██║  ██║██╔══╝  ██╔══██╗██║     ██╔══██║██╔══██╗
// ██║  ██║███████╗██║ ╚████║██████╔╝███████╗██║  ██║███████╗██║  ██║██████╔╝
// ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝

#include "pch.hpp"

#include "application/application.hpp"

using namespace Lab;

int main(int argc, char **argv)
{
    // TODO: move it somewhere
    // #if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
    //
    //     testing::InitGoogleTest(&argc, argv);
    //
    // #endif // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

    CApplication::GetInstance().Run();

    return 0;
}
