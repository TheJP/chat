Chat
====
Websocket chat api, server and client

The vision is to create a performant, cross platform (server and client), multipurpose chat system.
The chat will initially be provided as a website. Later on clients will be created for other systems and maybe included in projects (e.g. in game chat).

API
===
Describes the data transfer protocol between server and client.

Client
======
The client is fully static. There's no server side code, in the client.
Every dynamic content will be retrieved from the server with the api (using javascript and websockets).

The client is for: api calls, Data visualization, UI (User interface)

There's the potential for other clients then the html/javascript one in the future. (app / gui application / cli client)

Server
======
The server implements the api. It doesn't include any graphical elements.

The server is for: api handling, Data management, Access control, Session management
