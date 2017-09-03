#ifndef EXITCODE_H
#define EXITCODE_H

// STILL_ACTIVE = 0x103 = 259 !!
#define NORMAL_SERVER_EXIT              0
#define ANOTHER_SERVER_ALREADY_RUNNING	1
#define SERVER_RECEIVED_SIGNAL			2
#define WINSOCK2_NOT_FOUND				3
#define INVALID_PROGRAM_ARGUMENT		4
#define COULDNT_START_AS_A_SERVICE		5
#define ASYNC_FUNC_QUEUE_CRASH          100
#define COMMMODULE_THREAD_CRASH         101
#define COMMINTR_THREAD_CRASH           102
#define COMMLISTEN_THREAD_CRASH         103
#define COMMSENDING_THREAD_CRASH        104
#define COMMMAINTENANCE_THREAD_CRASH    105
#define DEADLOCK_CRASH                  106
#define NPC_THREAD_CRASH                107
#define ODBC_THREAD_CRASH               108
#define CANNOT_BIND_TO_PORT             109
#define PLAYERMAINTENANCE_THREAD_CRASH  110
#define SHUTDOWNCMD_EXIT                111
#define SERVERPATH_EMPTY                112
#define WRONG_LICENSE_KEY               113
#define COULD_NOT_INIT_LOAD_DIALOG      114
#define COULD_NOT_INIT_MAIN_DIALOG      115
#define SERVER_GP_TIMEOUT_KILL          116
#define REPORTGP_SPAWNING_THREAD_END    117
#define SERVERGP_EXIT                   118
#define CRASH_LOADING_EXTENSION_DLL     119
#define FATAL_NO_REQUIRED_DLL1          120
#define FATAL_NO_REQUIRED_DLL2          121
#define FATAL_NO_REQUIRED_DLL3          122
#define FATAL_NO_REQUIRED_DLL4          123
#define CANNOT_OPEN_T4C_WORLDS          124
#define DAO_ERROR_OPENING_WORLDS        125
#define DAO_ERROR_MOVEFIRST_WORLD       126
#define TERMINATE_FAIL_INIT             127
#define TERMINATE_FAIL_EXIT             128
#define TERMINATE_AUTODESTROY           129
#define TERMINATE_SPAWNING_THREAD       130
#define TERMINATE_SERVERGP              131
#define DEBUG_CRT_FAIL                  132
#define SHUTDOWN_FAILURE                133
#define CANNOT_OPEN_T4C_EDIT_WDA		134

#endif