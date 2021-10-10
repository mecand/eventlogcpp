#include "EventLogWriter.h"
#include "EventInfo.h"
#include <iostream>
/*
    Creator     : MCD
    Version     : v.0.1
    Description : Event Log Writing
                  These functions are used according to EventLogInfo.h header file definitions. This file generated with mc.exe(message compiler) along with
                  EventInfo.res file.
Future Work 

    1.  C# DLL Import Functionality Test
    2.  EventInfo.mc mc.exe batch builder with rc.exe to generate resource and header files
    3.  Uninstalling requires created registry keys to be deleted. Delete generated registry keys while uninstalling program

*/


void EventLogSourceInitialization(const std::string& a_name)
{
    const std::string key_path("SYSTEM\\CurrentControlSet\\Services\\"
        "EventLog\\Application\\" + a_name);

    HKEY key;
    
    DWORD last_error = RegCreateKeyExW(HKEY_LOCAL_MACHINE,
        s2ws(key_path).c_str(),
        0,
        0,
        REG_OPTION_NON_VOLATILE,
        KEY_SET_VALUE,
        0,
        &key,
        0);

    if (ERROR_SUCCESS == last_error)
    {
        std::wstring exe_path = L"C:\\Program Files\\DLP\\EventLogConverter.dll";  //L"C:\\Users\\mehme\\Desktop\\DLPapril\\ska\\x64\\Release\\EventLogConverter.dll"; //
        DWORD last_error;
        const DWORD types_supported = EVENTLOG_ERROR_TYPE |
            EVENTLOG_WARNING_TYPE |
            EVENTLOG_INFORMATION_TYPE;

        last_error = RegSetValueExW(key,
            L"EventMessageFile",
            0,
            REG_EXPAND_SZ,
            (BYTE*)exe_path.c_str(),
            (exe_path.length() + 1) * sizeof(WCHAR));

        if (ERROR_SUCCESS == last_error)
        {
            last_error = RegSetValueEx(key,
                L"TypesSupported",
                0,
                REG_DWORD,
                (LPBYTE)&types_supported,
                sizeof(types_supported));
        }

        if (ERROR_SUCCESS != last_error)
        {
            
            std::cerr << "Failed to install source values: "
                << last_error << "\n";
                
        }

        RegCloseKey(key);
    }
    else
    {
         std::cerr << "Failed to install source: " << last_error << "\n";
    }
}

void EventLogWriter(const std::string& a_msg, const WORD a_type, const std::string& a_name)
{
    DWORD event_id;

    switch (a_type)
    {
    case EVENTLOG_ERROR_TYPE:
        event_id = MSG_ERROR_1;
        break;
    case EVENTLOG_WARNING_TYPE:
        event_id = MSG_WARNING_1;
        break;
    case EVENTLOG_INFORMATION_TYPE:
        event_id = MSG_INFO_1;
        break;
    default:
          std::cerr << "Unrecognised type: " << a_type << "\n";
        event_id = MSG_INFO_1;
        break;
    }

    HANDLE h_event_log = RegisterEventSource(0, s2ws(a_name).c_str());

    if (0 == h_event_log)
    {
          std::cerr << "Failed open source '" << a_name << "': " <<
             GetLastError() << "\n";
    }
    else
    {
        LPCTSTR message = s2ws(a_msg).c_str();
        OutputDebugStringW(L"Something message??");
        OutputDebugStringW(message);
        if (FALSE == ReportEvent(h_event_log,
            a_type,
            0,
            event_id,
            0,
            1,
            0,
            &message,
            0))
        {
             std::cerr << "Failed to write message: " <<
                 GetLastError() << "\n";
        }

        DeregisterEventSource(h_event_log);
    }
}
std::wstring s2ws(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}
void DeleteEventSource(const std::string& a_name)
{
    const std::string key_path("SYSTEM\\CurrentControlSet\\Services\\"
        "EventLog\\Application\\" + a_name);

    DWORD last_error = RegDeleteKey(HKEY_LOCAL_MACHINE,
        s2ws(key_path).c_str());

    if (ERROR_SUCCESS != last_error)
    {
        std::cerr << "Failed to uninstall source: " << last_error << "\n";
    }
}

void TestEvents()
{
    const std::string EventSource("TEST EVENTS");
    
    EventLogSourceInitialization(EventSource);

    EventLogWriter("Information",
        EVENTLOG_INFORMATION_TYPE,
        EventSource);

    EventLogWriter("Error",
        EVENTLOG_ERROR_TYPE,
        EventSource);

    EventLogWriter("Warning",
        EVENTLOG_WARNING_TYPE,
        EventSource);

    // Uninstall when your application is being uninstalled.
    //DeleteEventSource(EventSource);

}