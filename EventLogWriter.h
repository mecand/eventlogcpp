#pragma once
#ifndef EVENTLOGWRITER_H_
#define EVENTLOGWRITER_H_
#ifdef EVENTLOGAPI_EXPORTS
#define EVENTLOG_API __declspec(dllexport)
#else
#define EVENTLOG_API __declspec(dllimport)
#endif
#else
#define EVENTLOG_API
#endif
#include <windows.h>
#include <string>
#include <codecvt>
/*
    Writer      : MCD
    Version     : v.0.1
    Description : Event Log Writing
                  These functions are used according to EventLogInfo.h header file definitions. This file generated with mc.exe(message compiler) along with
                  EventInfo.res file.
Future Work

    1.  C# DLL Import Functionality Test
    2.  EventInfo.mc mc.exe batch builder with rc.exe to generate resource and header files automation
    3.  Uninstalling requires created registry keys to be deleted. Delete generated registry keys while uninstalling program

Example Usage to Write to Event Viewer

    1. Define Event Log Source

       EventLogSourceInitialization("TEST INITIALIZATION");

    2. There are 3 types of Application Notification in order to write to Event Viewer. Information, Error, Warning. These types and related 
       EventID's may vary  according to EventInfo.mc file content and resource files. 

       EventLogWriter("TEST Information", EVENTLOG_INFORMATION_TYPE, EventSource);
       EventLogWriter("TEST DLP Warning", EVENTLOG_WARNING_TYPE, EventSource);
       EventLogWriter("TEST DLP Error", EVENTLOG_ERROR_TYPE, EventSource);

*/

extern "C" __declspec(dllexport)  void EventLogSourceInitialization(const std::string& a_name);
extern "C" __declspec(dllexport)  void EventLogWriter(const std::string& a_msg, const WORD a_type, const std::string& a_name);
std::wstring s2ws(const std::string& str);
extern "C" __declspec(dllexport)  void DeleteEventSource(const std::string& a_name);
void TestEvents();