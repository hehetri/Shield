#include "chat_processor.h"

#include <stdio.h>

static void OnChatMessage(const char *message, ChatContext context, void *user_data) {
    const char *tag = user_data ? static_cast<const char *>(user_data) : "NO_TAG";
    printf("[CHAT][CALLBACK][%s][%d] %s\n", tag, static_cast<int>(context), message);
}

void ChatProcessor_ExampleUsage() {
    ChatProcessor_SetCallback(OnChatMessage, (void *)"DEBUG");

    ChatProcessor_ProcessEvent("  hello   world  ", CHAT_CONTEXT_LOBBY);
    ChatProcessor_ProcessEvent("/start  ", CHAT_CONTEXT_ROOM);
    ChatProcessor_ProcessEvent("", CHAT_CONTEXT_UNKNOWN);
}
