#include "chat_processor.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

namespace {
    ChatMessageCallback g_callback = nullptr;
    void *g_callback_user_data = nullptr;

    void normalize_message(const char *input, char *output, size_t output_size) {
        size_t write_pos = 0;
        int last_was_space = 1;

        if (output_size == 0) {
            return;
        }

        if (!input) {
            output[0] = '\0';
            return;
        }

        for (size_t i = 0; input[i] != '\0' && write_pos + 1 < output_size; ++i) {
            unsigned char ch = static_cast<unsigned char>(input[i]);
            if (isspace(ch)) {
                if (!last_was_space) {
                    output[write_pos++] = ' ';
                    last_was_space = 1;
                }
                continue;
            }
            output[write_pos++] = static_cast<char>(ch);
            last_was_space = 0;
        }

        if (write_pos > 0 && output[write_pos - 1] == ' ') {
            --write_pos;
        }

        output[write_pos] = '\0';
    }

    const char *context_label(ChatContext context) {
        switch (context) {
        case CHAT_CONTEXT_LOBBY:
            return "LOBBY";
        case CHAT_CONTEXT_ROOM:
            return "ROOM";
        case CHAT_CONTEXT_UNKNOWN:
        default:
            return "UNKNOWN";
        }
    }
} // namespace

void ChatProcessor_SetCallback(ChatMessageCallback callback, void *user_data) {
    g_callback = callback;
    g_callback_user_data = user_data;
}

void ChatProcessor_ProcessEvent(const char *message, ChatContext context) {
    char normalized[512];
    normalize_message(message, normalized, sizeof(normalized));

    if (normalized[0] != '\0') {
        printf("[CHAT][%s] %s\n", context_label(context), normalized);
    } else {
        printf("[CHAT][%s] <empty>\n", context_label(context));
    }

    if (g_callback) {
        g_callback(normalized, context, g_callback_user_data);
    }
}
