#include <hiredis/hiredis.h>

int main(void) {
    redisReader *reader = redisReaderCreate();
    void *reply = NULL;
    int result = 1;
    if (reader == NULL)
        return 1;
    if (redisReaderFeed(reader, ":42\r\n", 5) == REDIS_OK &&
        redisReaderGetReply(reader, &reply) == REDIS_OK && reply != NULL) {
        redisReply *parsed = reply;
        result = parsed->type != REDIS_REPLY_INTEGER || parsed->integer != 42;
    }
    freeReplyObject(reply);
    redisReaderFree(reader);
    return result;
}
