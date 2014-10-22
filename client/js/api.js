var ApiRequest = {
    //User Operations
    Login : 11,
    Logout : 12,
    Register : 13,
    ChangePassword : 14,
    ChangeProfile : 15,
    ContinueSession : 16,

    //Chat Operations
    SendMessage : 31,
    OpenConversation : 32,
    CloseConversation : 33,
    GetMessagesOlder : 34,
    CreateConversation : 35,
    DeleteConversation : 36,
    ChangeConversation : 37,
    InviteConversation : 38,
    ChangeConversationPermission : 39,
    GetConversations : 40,

    //Admin Operations
    Mute : 51,
    Ban : 52,
    ChangePermission : 53
};
var ApiResponse = {
    //1 client request to 1 server response
    Response : 1,
    //1 client request to n server responses
    Notify : 2
};
var api = {
    wsUri : 'ws://127.0.0.1:8080', //Testing environment
    sid : null,
    ws : null,
    ready : false,
    callbacks : [],
    user : { login, logout }
};
api.setSid = function(sid){
    api.sid = sid;
    var expire = new Date();
    expire.setTime(expire.getTime() + 31536000000);  //Exactly 1 year (value in ms)
    document.cookie = 'sid=' + escape(sid) + '; expires=' + expire.toGMTString();
};
api.getSid = function (){
    //Is the session id already set?
    if(api.sid == null){
        //No: Try reading it from the cookies
        var start, end;
        start = document.cookie.indexOf('sid=');
        if(start < 0){ return null; } else { start += 4; }
        end = document.cookie.indexOf(';', start);
        if(end < 0){ end = document.cookie.length; }
        api.sid = document.cookie.substring(start, end);
    }
    return api.sid;
};
api.connect = function(callback){
    if(api.ws == null){
        api.ws = new WebSocket(api.wsUri);
        api.ws.onopen = function(evt){ api.ready = true; if(callback){ callback(); } };
        api.ws.onclose = function(evt){ api.ready = false; api.ws = null; };
        api.ws.onmessage = function(evt){ api.handle(evt) };
        api.ws.onerror = function(evt){ alert('error: ' + evt.data); };
    }
};
api.disconnect = function(){
    if(api.ws != null){
        api.ready = false;
        api.ws.close();
        api.ws = null;
    }
};
api.send = function(obj){
    if(api.ws != null && api.ready){
        var message = JSON.stringify(obj);
        api.ws.send(message);
    }
};
api.handle = function(evt){
    console.log('message: ' + evt.data);
    /*if(evt.data && evt.data.t){
    
    }*/
}

//Api functions
api.user.login = function(username, password){
};
