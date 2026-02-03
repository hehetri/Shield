#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ChatContext {
    CHAT_CONTEXT_UNKNOWN = 0,
    CHAT_CONTEXT_LOBBY = 1,
    CHAT_CONTEXT_ROOM = 2
} ChatContext;

typedef void (*ChatMessageCallback)(const char *message, ChatContext context, void *user_data);

void ChatProcessor_SetCallback(ChatMessageCallback callback, void *user_data);
void ChatProcessor_ProcessEvent(const char *message, ChatContext context);

#ifdef __cplusplus
}
#endif
