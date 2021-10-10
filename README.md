
# EventLogCPP

Event Log writing process is simplified. 

## API Usage

#### Example Usage to Write to Event Viewer


 1. Define Event Log Source
    ```http
       EventLogSourceInitialization("TEST INITIALIZATION");
    ```
2. There are 3 types of Application Notification in order to write to Event Viewer.

    ```http 
     Information | Error | Warning.

    ```
 These types and related EventID's may vary  according to EventInfo.mc file content and resource files. 

        
    EventLogWriter("TEST Information", EVENTLOG_INFORMATION_TYPE, EventSource);
    EventLogWriter("TEST DLP Warning", EVENTLOG_WARNING_TYPE, EventSource);
    EventLogWriter("TEST DLP Error", EVENTLOG_ERROR_TYPE, EventSource);
        



  
