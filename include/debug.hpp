#ifndef PHYSICA_DEBUG_HPP
#define PHYSICA_DEBUG_HPP


#include <string>
//#include <fmt/format.h>
//#include <fmt/core.h>
//#include <fmt/color.h>
//#include <fmt/chrono.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/color.h>

#define PHYSICA_DEBUG_FMT_STR "({})[{}](Physica::{}::{}): {}\n"

#define PHYSICA_ERROR(msg) raiseError(this, __FUNCTION__, msg)

#ifdef PHYSICA_DEBUG

#define PHYSICA_INFO(msg) debugPrint(phys::DebugMsgType::Info, this, __FUNCTION__, msg)
#define PHYSICA_WARNING(msg) debugPrint(phys::DebugMsgType::Warning, this, __FUNCTION__, msg)

#else

#define PHYSICA_INFO(msg)
#define PHYSICA_WARNING(msg)

#endif


namespace phys {
    enum DebugMsgType
    {
        Error,
        Info,
        Warning
    };

    class Debug {
    private:
        std::string className_;
    
    public:
        Debug(std::string className) : className_(className)
        {}

        void debugPrint(DebugMsgType msgType, const void *thisPtr, std::string funcName, std::string msg) const
        {
            std::string msgTypeStr; 

            switch (msgType)
            {
            case DebugMsgType::Error:
                msgTypeStr = fmt::format("{}", fmt::styled("ERROR", fmt::fg(fmt::color::red)));
                break;

            case DebugMsgType::Info:
                msgTypeStr = fmt::format("{}", fmt::styled("INFO", fmt::fg(fmt::color::cyan)));
                break;

            case DebugMsgType::Warning:
                msgTypeStr = fmt::format("{}", fmt::styled("WARNING", fmt::fg(fmt::color::orange)));
                break;
            }

            fmt::print("({}) [{}]({}::{}::{}): {}\n",
                    msgTypeStr,
                    fmt::ptr(thisPtr),
                    fmt::styled("Physica", fmt::fg(fmt::color::lime)),
                    fmt::styled(className_, fmt::fg(fmt::color::blue_violet)),
                    fmt::styled(funcName, fmt::fg(fmt::color::orange)),
                    msg
            );
        }

        void raiseError(const void *thisPtr, std::string funcName, std::string msg) const
        {
            debugPrint(DebugMsgType::Error, thisPtr, funcName, msg);
            exit(1);
        }
    };
}


#endif // PHYSICA_DEBUG_HPP
