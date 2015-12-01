
#ifndef TIACTOR_ACTOR_MESSAGEBASE_H
#define TIACTOR_ACTOR_MESSAGEBASE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string>

//#include "TiActor/actor/ActorRef.h"
#include "TiActor/actor/MessageObject.h"
#include "TiActor/actor/IMessage.h"

namespace TiActor {

class IActorRef;

template <typename T, message_type _MsgType = message_type_t::UnknownMessage>
class MessageBase : public IMessage {
public:
    typedef T * object_type;

private:
    message_type type_;
    object_type object_;

    IActorRef * sender_;
    IActorRef * receiver_;

public:
    MessageBase() : type_(_MsgType),
        object_(nullptr),
        sender_(nullptr),
        receiver_(nullptr) {
    }

    ~MessageBase() { }

    message_type getType() const {
        return type_;
    }

    void setType(message_type type) {
        type_ = type;
    }

    object_type setTypeEx(message_type type) {
        type_ = type;
        return static_cast<object_type>(this);
    }

    MessageObject getObject() const {
        return reinterpret_cast<MessageObject>(object_);
    }

    void setObject(MessageObject object) {
        object_ = reinterpret_cast<object_type>(object);
    }

    object_type getObjectEx() const {
        return object_;
    }

    void setObjectEx(object_type object) {
        object_ = object;
    }

    IActorRef * getSender() const {
        return sender_;
    }
    
    void setSender(IActorRef * sender) {
        sender_ = sender;
    }
    
    IActorRef * getReceiver() const {
        return receiver_;
    }

    void setReceiver(IActorRef * receiver) {
        receiver_ = receiver;
    }
};

} // namespace TiActor

#endif  /* TIACTOR_ACTOR_MESSAGEBASE_H */
