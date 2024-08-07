# Nodes - Messages

#### Login

When this is received:

```
{ 
  "type": "login", 
  "session": "internal session id",
  "password": "password" 
}
```

We process and return;

```
{ 
  "type": "user", 
  "name": "tracy",
  "fullname": "Tracy",
  "id": "user guid",
  "session": "internal session id"
}
```

The session id, is just turned around for convenience. It isn't used by Nodes.

#### Streams

When this is received:

```
{ 
  "type": "streams", 
  "user": "user guid",
}
```

We process and return;

```
{ 
  "type": "streams", 
  "user": "user guid",
  "streams": [
    {
      "name": "Conversation 1",
      "stream": "stream guid",
      "policy": "stream policy guid"
    }
  ]
}
```

#### Stream

When this is received:

```
{ 
  "type": "stream", 
  "stream": "stream guid"
}
```

We process and return;

```
{ 
  "type": "streams, 
  "stream": ""stream guid",
  "stream": {
    "name": "Conversation 1",
    "stream": "stream guid",
    "policy": "stream policy guid"
  }
}
```

#### Policy users

Since the Nodes system is persistent, when you join a stream, you can query the 
users in that stream by the stream policy and join those users too.

When this is received:

```
{ 
  "type": "policyusers", 
  "policy": "stream policy guid" 
}
```

We process and return;

```
{ 
  "type": "user", 
  "name": "policyusers",
  "id": "stream policy guid",
  "users": [
    {
      "name": "tracy",
      "fullname": "Tracy",
      "id": "user guid"
    },
    {
      "name": "leanne",
      "fullname": "Leanne",
      "id": "user guid"
    }
  ]
}
```

#### Message

This is sent to the REQ socket when a message happens on IRC, and will be received on the 
SUB socket when a new message is received.

```
{ 
  "type": "message", 
  "text": "Message text",
  "stream": "stream guid",
  "policy": "stream policy guid",
  "user": "user guid"
}
```

#### Users

When this is received:

```
{ 
  "type": "users"
}
```

We process and return;

```
{ 
  "type": "users", 
  "users": [
    {
      "name": "tracy",
      "fullname": "Tracy",
      "id": "user guid"
    },
    {
      "name": "leanne",
      "fullname": "Leanne",
      "id": "user guid"
    }
  ]
}
```

#### User

When this is received:

```
{ 
  "type": "user", 
  "user": "user guid"
}
```

We process and return;

```
{ 
  "type": "user, 
  "user": "user guid",
  "user": {
    "name": "tracy",
    "fullname": "Tracy",
    "id": "user guid"
  }
}
```

#### Certs

```
{ 
  "type": "certs"
}
```

This will be processed by the Visual Ops system and it will return:

```
{ 
  "type": "certs", 
  "ssl": true,
  "cettFile": "xxxx",
  "chainFile": "yyy"
}
```

The session id, is just turned around for convenience. It isn't used by Visual Ops.

#### Acknowlege

This is received on the REP socket when a Message is sent.

```
{ 
  "type": "ack"
}
```

#### Error

This is received on the REP socket when a bad request has happened

```
{ 
  "type": "err",
  "msg": "LOL what are you doing!"
}
```
