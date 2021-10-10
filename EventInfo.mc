;#ifndef _EXAMPLE_EVENT_LOG_MESSAGE_FILE_H_
;#define _EXAMPLE_EVENT_LOG_MESSAGE_FILE_H_

MessageIdTypeDef=DWORD


SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
               Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
               Warning=0x2:STATUS_SEVERITY_WARNING
               Error=0x3:STATUS_SEVERITY_ERROR
               )

LanguageNames=(EnglishUS=0x401:MSG00401
               Dutch=0x113:MSG00113
               Neutral=0x0000:MSG00000
               )

MessageId=0x1000   SymbolicName=MSG_INFO_1
Severity=Informational
Facility=Application
Language=Neutral
TEST Info %n%n%n%1
.

MessageId=0x1001   SymbolicName=MSG_WARNING_1
Severity=Warning
Facility=Application
Language=Neutral
TEST Warning %n%n%n%1
.

MessageId=0x1002   SymbolicName=MSG_ERROR_1
Severity=Error
Facility=Application
Language=Neutral
TEST Error %n%n%n%1
.

MessageId=0x1003   SymbolicName=MSG_SUCCESS_1
Severity=Success
Facility=Application
Language=Neutral
TEST Success %n%n%n%1
.


;#endif