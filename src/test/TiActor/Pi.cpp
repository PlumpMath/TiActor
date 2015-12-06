
#include "Pi.h"

void Worker::onReceive(IMessage * message) {
    message_type msgType = message->getType();
    if (msgType == Worker::InnerMessage::Work) {
        Work * work = reinterpret_cast<Work *>(message->getObject());
        if (work) {
            double result = calulatePiFor(work->getStart(), work->getNumOfElements());
            this->getSender()->tell((new Result(result))->setTypeEx(Master::InnerMessage::Result), getSelf());
        }
    }
    else {
        unhandleMessage("Worker", message);
    }
}
