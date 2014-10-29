env = {
    debug : true
};
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
    callbacks : []
};
api.setSid = function(sid){
    api.sid = sid;
    var expire = new Date();
    //Exactly 1 year - 1min (value in ms)
    //(1min because of the time, the cookie travels from server to client)
    expire.setTime(expire.getTime() + 31536000000 - 60000);
    document.cookie = 'sid=' + escape(sid) + '; expires=' + expire.toGMTString();
};
api.deleteSid = function(){
    document.cookie = 'sid=; expires=Thu, 01 Jan 1970 00:00:01 GMT';
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
api.send = function(type, obj){
    if(!obj){ obj = {}; }
    if(type != ApiRequest.Login){ obj.sid = api.getSid(); } //TODO: remove -> Not needed for websockets
    obj.t = type;
    if(api.ws != null && api.ready){
        var message = JSON.stringify(obj);
        api.ws.send(message);
    }
};
api.handle = function(evt){
    if(evt.data){
        if(env.debug){ console.log('message: ' + evt.data); }
        var obj = JSON.parse(evt.data);
        if(obj.r){
            var r = parseInt(obj.r);
            if(r in api.callbacks && $.isArray(api.callbacks[r])){
                //Execute callbacks
                var key;
                for(key in api.callbacks[r]){
                    api.callbacks[r][key](obj);
                }
            }
        }
    }
};
api.register = function(type, callback){
    if(type && callback){
        if(!(type in api.callbacks)){ api.callbacks[type] = [callback]; }
        else { api.callbacks[type].push(callback); }
    }
}
api.formatTime = function(time){
    var now = new Date();
    var date = new Date(time*1000); //api delivers times in seconds
    return (now.getDate() != date.getDate() ||
            now.getMonth() != date.getMonth() ||
            now.getFullYear() != date.getFullYear() ?
        date.toLocaleDateString() + ' ' : '') +
        date.toLocaleTimeString();
}
//Predefined callback handler
api.callbacks[ApiRequest.Login] = [function(data){
    if(data.s){ api.setSid(data.sid); }
}];
api.callbacks[ApiRequest.ContinueSession] = [function(data){
    if(!data.s){ api.deleteSid(); }
}];
